#include <ossimPredator/ossimPredatorVideo.h>
#include <ossimPredator/ossimPredatorInit.h>
#include <ossim/base/ossimDate.h>
#ifndef EINVAL
#define EINVAL 0
#endif
extern "C"
{
#include <libavutil/avutil.h>
#include <libavutil/imgutils.h>
#include <libavformat/avformat.h>
#include <libavformat/avio.h>
#include <libavcodec/avcodec.h>
}
#include <iostream>
#include <algorithm>
#include <iomanip>

namespace
{
   AVCodecParameters* streamCodecParameters(AVFormatContext* formatCtx, ossim_int32 streamIndex)
   {
      return formatCtx->streams[streamIndex]->codecpar;
   }

   AVMediaType streamCodecType(AVFormatContext* formatCtx, ossim_int32 streamIndex)
   {
      return streamCodecParameters(formatCtx, streamIndex)->codec_type;
   }

   void unrefPacket(AVPacket* packet)
   {
      av_packet_unref(packet);
   }

   int decodeVideoPacket(AVCodecContext* codecCtx, AVFrame* frame, int* frameFinished, AVPacket* packet)
   {
      *frameFinished = 0;
      int result = avcodec_send_packet(codecCtx, packet);
      if(result < 0)
      {
         return result;
      }

      result = avcodec_receive_frame(codecCtx, frame);
      if(result == AVERROR(EAGAIN) || result == AVERROR_EOF)
      {
         return 0;
      }
      if(result < 0)
      {
         return result;
      }

      *frameFinished = 1;
      return packet->size;
   }

   ossimString streamDescription(AVFormatContext* formatCtx, ossim_int32 streamIndex)
   {
      AVCodecContext* codecCtx = avcodec_alloc_context3(0);
      if(!codecCtx)
      {
         return "";
      }

      if(avcodec_parameters_to_context(codecCtx, streamCodecParameters(formatCtx, streamIndex)) < 0)
      {
         avcodec_free_context(&codecCtx);
         return "";
      }

      static const int BUF_SIZE = 256;
      char buf[BUF_SIZE];
      avcodec_string(buf, sizeof(buf), codecCtx, 0);
      avcodec_free_context(&codecCtx);

      return ossimString(buf);
   }
}

enum ossimPredatorMediaType
{
   ossimPredator_AVMEDIA_TYPE_UNKNOWN = -1,
   ossimPredator_AVMEDIA_TYPE_VIDEO,
   ossimPredator_AVMEDIA_TYPE_AUDIO,
   ossimPredator_AVMEDIA_TYPE_DATA,
   ossimPredator_AVMEDIA_TYPE_SUBTITLE,
   ossimPredator_AVMEDIA_TYPE_ATTACHMENT,
   ossimPredator_AVMEDIA_TYPE_NB
   
};

ossim_int64 ossimPredatorVideo::MY_NOPTS_VALUE = static_cast<ossim_int64>(0x8000000000000000LL);
ossimPredatorVideo::ossimPredatorVideo()
   :theFormatCtx(0),
    theVideoStreamIndex(-1),
    theKlvStreamIndex(-1),
    theImageWidth(0),
    theImageHeight(0),
    theVideoFrame(0),
    theRgbFrame(0),
    theVideoCodecCtx(0),
    theVideoDecoder(0),
    theBuffer(0),
    theBufferSizeInBytes(0),
    theVideoFrameRate(0.0),
    theVideoClock(0.0),
    theKlvTimestamp(0),
    theFirstFrameFlag(false),
    theFirstKlvTimeSetFlag(false),
    theFirstFrameTime(0.0),
    theFirstKlvTime(0.0),
    theDurationInSeconds(0.0),
    theSeekTarget(0.0),
    theSeekTargetType(ossimPredatorVideo::SEEK_NONE),
theSeekingFlag(false),
theImageConvertContext(0)
{
   
}

ossimPredatorVideo::~ossimPredatorVideo()
{
   close();
}

bool ossimPredatorVideo::open(const ossimFilename& videoFile)
{
   // make sure the system is initialized
   ossimPredatorInit::instance();
   close();
   int err = avformat_open_input(&theFormatCtx, videoFile.c_str(), NULL, NULL);

   
   // open input file using the ffmpeg library
   if(err!=0)
   {

      theFormatCtx = 0;
      return false;
   }
   // now determine if we have a klv stream and video stream.
   // if not then eturn false;
   //
  // Retrieve stream information
  if(avformat_find_stream_info(theFormatCtx, NULL)<0)
  {
     return false; // Couldn't find stream information
  }
  ossim_int32 i = 0;
   ossim_int32 klvStream = -1;
   ossim_int32 lastDataStream = -1;
   ossim_int32 lastAudioStream = -1;
  for(i=0; i<(ossim_int32)theFormatCtx->nb_streams; i++)
  {
     ossimString testBuf = streamDescription(theFormatCtx, i);

    // std::cout  << "START TIME = " << theFormatCtx->start_time << std::endl;
    // std::cout << "CODEC TYPE === "  << theFormatCtx->streams[i]->codec->codec_type << std::endl;
     if((int)streamCodecType(theFormatCtx, i)==(int)ossimPredator_AVMEDIA_TYPE_VIDEO &&
        theVideoStreamIndex < 0)
     {
        theVideoStreamIndex=i;
     }
     else if((static_cast<int>(streamCodecType(theFormatCtx, i))==static_cast<int>(ossimPredator_AVMEDIA_TYPE_DATA))&&
             (lastDataStream==-1))
     {
        lastDataStream = i;
     }
     else if((static_cast<int>(streamCodecType(theFormatCtx, i))==static_cast<int>(ossimPredator_AVMEDIA_TYPE_AUDIO))&&
             (lastDataStream==-1))
     {
        lastAudioStream = i;
     }
     testBuf = testBuf.upcase();
     //std::cout << "TESTING BUFFER = " << testBuf << std::endl;
     if(testBuf.contains("KLVA"))
     {
       // std::cout << "*****************HERE**************\n";
        //std::cout << testBuf << std::endl;
        klvStream = i;
     }
     else if(testBuf.contains("KLV")&&(klvStream<0))
     {
        klvStream = i;
     }
#if 0
     
     else if(theFormatCtx->streams[i]->id == 0xBD) // 0xBD is a fixed id for KLV streams in predator video
     {
        // disable parsing so we do our own parsing.  Let it return raw data.
        theKlvStreamIndex = i;
     }
     else if((static_cast<int>(theFormatCtx->streams[i]->codec->codec_type)==static_cast<int>(ossimPredator_AVMEDIA_TYPE_DATA))&&
             (lastDataStream==-1))
     {
        lastDataStream = i;
     }
     else if((static_cast<int>(theFormatCtx->streams[i]->codec->codec_type)==static_cast<int>(ossimPredator_AVMEDIA_TYPE_AUDIO))&&
             (lastDataStream==-1))
     {
        lastAudioStream = i;
     }
#endif
  }
  if(theVideoStreamIndex==-1)
  {
    return false; // Didn't find a video stream
  }
   if(klvStream < 0)
   {
      if(theKlvStreamIndex==-1)
      {
         if(lastAudioStream != -1) // try audio, older version of ffmpeg sets audio codec for klv
         {
            theKlvStreamIndex = lastAudioStream;
         }
         else if(lastDataStream != -1)
         {
            theKlvStreamIndex = lastDataStream;
         }
      }
   }
   else
   {
      theKlvStreamIndex = klvStream;
   }
//std::cout << "KLV STREAM IDX!!!! ===== " << theKlvStreamIndex << std::endl;
  if(theKlvStreamIndex != -1)
  {
#if LIBAVFORMAT_VERSION_MAJOR < 59
     theFormatCtx->streams[theKlvStreamIndex]->need_parsing = AVSTREAM_PARSE_NONE;
#endif
  }
  theImageWidth  = streamCodecParameters(theFormatCtx, theVideoStreamIndex)->width;
  theImageHeight = streamCodecParameters(theFormatCtx, theVideoStreamIndex)->height;
  theVideoFrameRate = av_q2d(theFormatCtx->streams[theVideoStreamIndex]->r_frame_rate);
  theVideoFrame = av_frame_alloc();
  theRgbFrame   = av_frame_alloc();
  
  theVideoDecoder=avcodec_find_decoder(streamCodecParameters(theFormatCtx, theVideoStreamIndex)->codec_id);
  if(!theVideoDecoder)
  {
     close();
     return false; // Could not find codec
  }
  theVideoCodecCtx=avcodec_alloc_context3(theVideoDecoder);
  if(!theVideoCodecCtx ||
     avcodec_parameters_to_context(theVideoCodecCtx,
                                   streamCodecParameters(theFormatCtx, theVideoStreamIndex)) < 0)
  {
     close();
     return false; // Could not allocate codec context
  }
  if(avcodec_open2(theVideoCodecCtx, theVideoDecoder, NULL)<0)
  {
     close();
     return false; // Could not open codec
  }
  
  theBufferSizeInBytes = av_image_get_buffer_size(AV_PIX_FMT_RGB24,
                                                  theImageWidth,
                                                  theImageHeight,
                                                  1);
  theBuffer = (ossim_uint8 *)av_malloc(theBufferSizeInBytes);

  av_image_fill_arrays(theRgbFrame->data,
                       theRgbFrame->linesize,
                       theBuffer,
                       AV_PIX_FMT_RGB24,
                       theImageWidth,
                       theImageHeight,
                       1);

  theCurrentFrameInfo = new FrameInfo;
  theCurrentFrameInfo->setImageRect(ossimIrect(0,
                                               0,
                                               theImageWidth-1,
                                               theImageHeight-1));
  theCurrentFrameInfo->allocate();
  AVRational r = {1, AV_TIME_BASE};
  theDurationInSeconds = av_q2d(r)*theFormatCtx->duration;
  return true;
}

void ossimPredatorVideo::close()
{

   if(theVideoFrame)
   {
      av_frame_free(&theVideoFrame);
   }
   if(theRgbFrame)
   {
      av_frame_free(&theRgbFrame);
   }
   if(theBuffer)
   {
      av_free(theBuffer);
   }
   if(theImageConvertContext)
   {
      sws_freeContext(theImageConvertContext);
   }
   if(theVideoCodecCtx)
   {
      avcodec_free_context(&theVideoCodecCtx);
   }
   if(theFormatCtx)
   {
      avformat_close_input(&theFormatCtx);
   }

   // set all values to initial state
   theFormatCtx = 0;
   theVideoStreamIndex = -1;
   theKlvStreamIndex   = -1;
   theImageWidth       = 0;
   theImageHeight      = 0;
   theVideoFrame       = 0;
   theRgbFrame         = 0;
   theVideoCodecCtx    = 0;
   theVideoDecoder     = 0;
   theBuffer           = 0;
   theBufferSizeInBytes = 0;
   theVideoFrameRate    = 0.0;
   theVideoClock        = 0.0;
   theKlvTimestamp      = 0;
   theFirstFrameFlag    = false;
   theFirstKlvTimeSetFlag = false;
   theFirstFrameTime      = 0.0;
   theFirstKlvTime        = 0.0;
   theDurationInSeconds   = 0.0;
   theSeekTarget          = 0.0;
   theSeekTargetType      = ossimPredatorVideo::SEEK_NONE;
   theSeekingFlag         = false;
   theImageConvertContext = 0;
   
   flushQueues();
}

bool ossimPredatorVideo::isOpen()const
{
   return (theFormatCtx!=0);
}

void ossimPredatorVideo::rewind()
{
   seek(0, SEEK_ABSOLUTE);
}

void ossimPredatorVideo::seek(ossim_float64 reference, ossimPredatorVideo::SeekType seekType)
{
   
   theSeekingFlag    = true;
   theSeekTargetType = seekType;
   theSeekTarget     = reference;
}

ossim_float64 ossimPredatorVideo::referenceTime()const
{
   if(isOpen()&&theFirstFrameFlag)
   {
      return (theVideoClock-theFirstFrameTime);
   }

   return 0.0;
}

// void SaveFrame(AVFrame *pFrame, int width, int height, int iFrame)
// {
//   FILE *pFile;
//   char szFilename[32];
//   int  y;
  
//   // Open file
//   sprintf(szFilename, "frame%d.ppm", iFrame);
//   pFile=fopen(szFilename, "wb");
//   if(pFile==NULL)
//     return;
  
//   // Write header
//   fprintf(pFile, "P6\n%d %d\n255\n", width, height);
  
//   // Write pixel data
//   for(y=0; y<height; y++)
//     fwrite(pFrame->data[0]+y*pFrame->linesize[0], 1, width*3, pFile);
  
//   // Close file
//   fclose(pFile);
// }

ossimRefPtr<ossimPredatorVideo::KlvInfo> ossimPredatorVideo::nextKlv()
{
   if(theKlvStreamIndex == -1) return 0;
   AVPacket        packet;
   ossimRefPtr<ossimPredatorKlvTable>         klvTable;
   bool needMoreKlvPacketsFlag = false;
   if(!isOpen()) return 0;
   adjustSeek();

   while(av_read_frame(theFormatCtx, &packet)>=0)
   {
      if(packet.stream_index == theKlvStreamIndex)
      {
         if(!klvTable.valid())
         {
            klvTable = new ossimPredatorKlvTable;
         }
         needMoreKlvPacketsFlag = klvTable->addKeys(packet.data, packet.size);
         if(!needMoreKlvPacketsFlag)
         {
           // klvTable->print(std::cout) << std::endl; 
            ossim_int64 unixT = 0;
            if(klvTable->getUnixEpocTimestamp(unixT))
            {
               if(!theFirstKlvTimeSetFlag)
               {
                  theFirstKlvTimeSetFlag = true;
                  theFirstKlvTime = unixT*1e-6;
               }
               ossimRefPtr<KlvInfo>             klvInfo = new KlvInfo;
               
               klvInfo->setTime(unixT*1e-6 - theFirstKlvTime);
               theVideoClock = klvInfo->time();
               klvInfo->setTable(klvTable.get());
               unrefPacket(&packet);
               return klvInfo.release();
            }
            klvTable = 0;
         }
      }
      unrefPacket(&packet);
   }
   return 0;
}

void ossimPredatorVideo::countFrames(ossim_uint32& frames, ossim_uint32& klvs)
{
   AVPacket        packet;
   if(isOpen())
   {
     adjustSeek();
     while(av_read_frame(theFormatCtx, &packet)>=0)
     {
       if(packet.stream_index == theKlvStreamIndex) ++klvs;
       if(packet.stream_index == theVideoStreamIndex) ++frames;
       unrefPacket(&packet);
     }
   }
}

bool ossimPredatorVideo::skipKlv()
{
   if(theKlvStreamIndex == -1) return false;
   AVPacket        packet;
   if(!isOpen()) return false;
    adjustSeek();

   while(av_read_frame(theFormatCtx, &packet)>=0)
   {
      if(packet.stream_index == theKlvStreamIndex)
      {
         unrefPacket(&packet);
         return true;
      }
      unrefPacket(&packet);
   }
   return false;
}

bool ossimPredatorVideo::skipFrame()
{
   AVPacket        packet;
   if(!isOpen()) return false;
   adjustSeek();

   while(av_read_frame(theFormatCtx, &packet)>=0)
   {
      if(packet.stream_index == theVideoStreamIndex)
      {
         unrefPacket(&packet);
         return true;
      }
      unrefPacket(&packet);
   }
   return false;
}

void ossimPredatorVideo::adjustSeek()
{
   if(theSeekingFlag)
   {
      ossim_float64 adjustedToRelative = theSeekTarget;
      switch(theSeekTargetType)
      {
         case ossimPredatorVideo::SEEK_ABSOLUTE:
         {
            // look at the current video clock and adjust to relative increment
            adjustedToRelative = theSeekTarget - (theVideoClock - theFirstFrameTime); 
            break;
         }
         case ossimPredatorVideo::SEEK_RELATIVE:
         {
            break;
         }
         default:
         {
            adjustedToRelative = 0.0;
         }
      }
      int seekFlag = adjustedToRelative < 0?AVSEEK_FLAG_BACKWARD : 0;
      adjustedToRelative += theVideoClock;
      if(adjustedToRelative < theFirstFrameTime)
      {
         adjustedToRelative = theFirstFrameTime;
      }
      ossim_int64 scaledAdjust = (ossim_int64)(adjustedToRelative*AV_TIME_BASE);
      AVRational r = {1, AV_TIME_BASE};
      
      ossim_int64 seekTarget = av_rescale_q(scaledAdjust, 
                                            r, 
                                            theFormatCtx->streams[theVideoStreamIndex]->time_base);
      if(av_seek_frame(theFormatCtx, theVideoStreamIndex, seekTarget, seekFlag)<0)
      {
         // ERROR
      }
      if(theVideoStreamIndex>=0) avcodec_flush_buffers(theVideoCodecCtx);
      flushQueues();
   }
   theSeekingFlag = false;
}

ossimRefPtr<ossimPredatorVideo::FrameInfo> ossimPredatorVideo::nextFrame()
{
   AVPacket        packet;
   ossimRefPtr<ossimPredatorKlvTable>         klvTable;
//    ossimRefPtr<ossimPredatorVideo::FrameInfo> frameInfo;
   ossim_int64    firstFramePts = 0;
   bool    firstFrame = true;
   int frameFinished = 0;
   ossim_float64  pts = 0;
   bool needMoreKlvPacketsFlag = false;
   theCurrentFrameInfo->setKlvTable(0);
   if(!isOpen()) return 0;
   adjustSeek();

//   std::cout << "KLV IDX = " << theKlvStreamIndex << std::endl;
   while(av_read_frame(theFormatCtx, &packet)>=0)
   {
//      std::cout << "packet idx = " << packet.stream_index << std::endl;
      /**
       * see if the packet is a klv stream and update the geometry
       */
      if(packet.stream_index == theKlvStreamIndex)
      {
         if(!klvTable.valid())
         {
            klvTable = new ossimPredatorKlvTable;
         }
         //std::cout << "ROOT!!!!!!\n";
         needMoreKlvPacketsFlag = klvTable->addKeys(packet.data, packet.size);
         // new geometry detected for the next frame
         //
         //std::cout << "needMoreKlvPacketsFlag: " << needMoreKlvPacketsFlag << std::endl;
         if(!needMoreKlvPacketsFlag)
         {
            ossim_int64 unixT = 0;
            if(klvTable->getUnixEpocTimestamp(unixT)
               &&(!theFirstKlvTimeSetFlag || (unixT != (ossim_int64)theKlvTimestamp)))
            {
               theKlvTimestamp = unixT;
               if(!theFirstKlvTimeSetFlag)
               {
                  theFirstKlvTimeSetFlag = true;
                  theFirstKlvTime = unixT*1e-6;
               }
               ossimRefPtr<ossimPredatorVideo::TimestampKlv> klvTimestamp = new ossimPredatorVideo::TimestampKlv;
               klvTimestamp->theOffsetInSeconds = theKlvTimestamp*1e-6 - theFirstKlvTime;
               klvTimestamp->theKlvInfo = klvTable;
               theKlvQueue.push(klvTimestamp.get());
            }
         }
      }
     else if(packet.stream_index == theVideoStreamIndex)
      {
//         if(avcodec_decode_video(theVideoCodecCtx,
//                                 theVideoFrame,
//                                 &frameFinished, 
//                                 packet.data,
//                                 packet.size) > 0)
           if(decodeVideoPacket(theVideoCodecCtx,
                                theVideoFrame,
                                &frameFinished,
                                &packet) >= 0)
            {
               if(firstFrame)
               {
                  // grab first frame pts
                  firstFramePts = packet.pts;
                  firstFrame = false;
               }
               if(packet.dts == MY_NOPTS_VALUE 
                  && firstFramePts != MY_NOPTS_VALUE)
               {
                  pts = firstFramePts;
               }
               else if(packet.dts != MY_NOPTS_VALUE)
               {
                  pts = packet.dts;
               }
               else
               {
                  pts = 0;
               }
               // next frame found.  Once finished then return
               if(frameFinished)
               {
                  if(!theImageConvertContext)
                  {
                     int dstW = theImageWidth;
                     int dstH = theImageHeight;
                     theImageConvertContext = sws_getContext(theVideoCodecCtx->width,
                                                             theVideoCodecCtx->height,
                                                             theVideoCodecCtx->pix_fmt,
                                                             dstW,
                                                             dstH,
                                                             AV_PIX_FMT_RGB24,
                                                             SWS_BICUBIC,
                                                             0, 0, 0);
                  }
                  if(theImageConvertContext!=0)
                  {
                     sws_scale(theImageConvertContext, theVideoFrame->data, 
                               theVideoFrame->linesize, 0, 
                               theVideoCodecCtx->height,
                               theRgbFrame->data, theRgbFrame->linesize);               
                  }
#if 0
                  img_convert((AVPicture *)theRgbFrame, PIX_FMT_RGB24, 
                              (AVPicture*)theVideoFrame, theVideoCodecCtx->pix_fmt, 
                              theImageWidth, theImageHeight);
#endif
                  // let's do our own copy it's faster
                  memcpy(theCurrentFrameInfo->rgbBuffer(),
                         (ossim_uint8*)theRgbFrame->data[0],
                         theCurrentFrameInfo->rgbBufferSizeInBytes());
                  
                  pts *= av_q2d(theFormatCtx->streams[theVideoStreamIndex]->time_base);
                  pts = synchronizeVideo(theVideoFrame, pts);
                  bool addKlvForFirstFrame = false;
                  if(!theFirstFrameFlag)
                  {
                     theFirstFrameTime = theVideoClock;
                     theFirstFrameFlag = true;
                     addKlvForFirstFrame = true;
                  }
                  ossim_float64 deltaTime = theVideoClock-theFirstFrameTime;
                  if(!theKlvQueue.empty())
                  {
                     if((deltaTime > theKlvQueue.front()->theOffsetInSeconds)||
                        (addKlvForFirstFrame))
                     {
                        //                   std::cout << "FRAME TIME OFFSET = " << deltaTime << std::endl
                        //                             << "KLV TIME OFFSET   = " <<  theKlvQueue.front()->theOffsetInSeconds << std::endl;
                        theCurrentFrameInfo->setKlvTable(theKlvQueue.front()->theKlvInfo.get());
                        theCurrentFrameInfo->setKlvTime(theKlvQueue.front()->theOffsetInSeconds);
                        theKlvQueue.pop();
                     }
                  }
                  theCurrentFrameInfo->setVideoFrameTime(theVideoClock);
                  unrefPacket(&packet);
                  
                  return theCurrentFrameInfo.get();
               }
            }
           else
           {
              //  std::cout << "ERROR!!!!!!!!!!!!!!!!!!" << std::endl;
           }
      }
      unrefPacket(&packet);
   }
   return 0;
}

ossimFilename ossimPredatorVideo::filename()const
{
   return theFilename;
}

ossim_float64 ossimPredatorVideo::videoFrameRate()const
{
   return theVideoFrameRate;
}

ossim_float64 ossimPredatorVideo::videoClock()const
{
   return theVideoClock;
}

bool ossimPredatorVideo::seekingFlag()const
{
   std::lock_guard<std::mutex> lock(theSeekMutex);
   return theSeekingFlag;
}

void ossimPredatorVideo::setFirstFrameFlag(bool flag)
{
   theFirstFrameFlag = flag;
}

bool ossimPredatorVideo::firstFrameFlag()const
{
   return theFirstFrameFlag;
}

void ossimPredatorVideo::debugScan()
{
   if(!isOpen()) return;
   
   AVPacket        packet;
   ossimPredatorKlvTable klvTable;
   bool needMoreKlvPacketsFlag = false;
   ossim_uint64 prevT = 0;
   int frameFinished = 0;
   ossim_int64    firstFramePts = 0;
   ossim_float64  pts = 0;
   while(av_read_frame(theFormatCtx, &packet)>=0)
   {
      if(packet.stream_index == theKlvStreamIndex)
      {
         //std::cout << "KLV\n";
         needMoreKlvPacketsFlag = klvTable.addKeys(packet.data, packet.size);
         if(!needMoreKlvPacketsFlag)
         {
            ossimDate date;
            ossim_int64 t;
            ossim_float64 fraction=0;
            ossim_int64 unixT;
            klvTable.getUnixEpocTimestamp(unixT);
           
            klvTable.getUnixEpocTimestampInSeconds(t, fraction);
            date.setTimeNoAdjustmentGivenEpoc(t);
            date.setFractionalSecond(fraction);
            if(static_cast<ossim_int64>(prevT) != static_cast<ossim_int64>(unixT))
            {
               prevT = unixT;
               //std::cout << "VIDEO START = " << klvTable.valueAsString(KLV_KEY_VIDEO_START_DATE_TIME_UTC) << std::endl;
               //std::cout << "EPOC KLV = " << t << std::endl;
               std::cout << std::setw(4) << std::setfill('0') << date.getYear()
                         << std::setw(2) << std::setfill('0') << date.getMonth()
                         << std::setw(2) << std::setfill('0') << date.getDay()
                         << " " << std::setw(2) << std::setfill('0') << date.getHour() << ":"
                         << std::setw(2) << std::setfill('0') << date.getMin() << ":"
                         << std::setprecision(20) << (date.getSec()+date.getFractionalSecond()) << std::endl;
            }
            klvTable.clear();
         }
         else 
         {
            std::cout << "Need more" << std::endl;
         }

      }
      else if(packet.stream_index == theVideoStreamIndex)
      {
         if(!frameFinished)
         {
            // grab first frame pts
            firstFramePts = packet.pts;
         }
//         avcodec_decode_video(theVideoCodecCtx, theVideoFrame, &frameFinished, 
//                              packet.data, packet.size);
         decodeVideoPacket(theVideoCodecCtx, theVideoFrame, &frameFinished, &packet);
         if(packet.dts == MY_NOPTS_VALUE 
            && firstFramePts != MY_NOPTS_VALUE)
         {
            pts = firstFramePts;
         }
         else if(packet.dts != MY_NOPTS_VALUE)
         {
            pts = packet.dts;
         }
         else
         {
            pts = 0;
         }
         if(frameFinished)
         {
            ossimDate date;

//            date.setTimeNoAdjustmentGivenEpoc(static_cast<ossim_uint64>(packet.dts));
//                std::cout << std::setw(4) << std::setfill('0') << date.getYear()
//                          << std::setw(2) << std::setfill('0') << date.getMonth()
//                          << std::setw(2) << std::setfill('0') << date.getDay()
//                          << " " << std::setw(2) << std::setfill('0') << date.getHour() << ":"
//                          << std::setw(2) << std::setfill('0') << date.getMin() << ":"
//                          << std::setprecision(20) << (date.getSec()+date.getFractionalSecond()) << std::endl;
            frameFinished = 0;
            pts *= av_q2d(theFormatCtx->streams[theVideoStreamIndex]->time_base);
            pts = synchronizeVideo(theVideoFrame, pts);
            //std::cout << "pts = " << pts << std::endl;
         }
         
      }
      unrefPacket(&packet);
   }
//    std::cout << "klvCount   = " << klvCount << std::endl;
//    std::cout << "videoCount = " << videoCount << std::endl; 
}

ossim_float64 ossimPredatorVideo::synchronizeVideo(AVFrame *src_frame, ossim_float64 pts)
{
   ossim_float64 frame_delay = 0.0;
   
   if(pts != 0)
   {
      /* if we have pts, set video clock to it */
      theVideoClock = pts;
   }
   else
   {
      /* if we aren't given a pts, set it to the clock */
      pts = theVideoClock;
   }
   /* update the video clock */
   frame_delay = av_q2d(theVideoCodecCtx->time_base);

   /* if we are repeating a frame, adjust clock accordingly */
   frame_delay += src_frame->repeat_pict * (frame_delay * 0.5);

   theVideoClock += frame_delay;

   return pts;
}


void ossimPredatorVideo::flushQueues()
{
   while(!theKlvQueue.empty())theKlvQueue.pop();
}
