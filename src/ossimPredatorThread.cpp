#include <ossimPredator/ossimPredatorThread.h>
#include <iostream>

void ossimPredatorThread::run()
{
   bool firstTime = true;
   theDoneFlag = false;

   if(!theVideo.valid()) return;
   if(!theVideo->isOpen()) return;
//    int frameCount = 0;
   do
   {
      interrupt();
      theBlock->block();

//       std::cout << "FILLING BUFFER!!!!" << std::endl;
      if (firstTime)
      {
         // do a yield to get round a peculiar thread hang when testCancel() is called 
         // in certain cirumstances - of which there is no particular pattern.
         ossim::Thread::yieldCurrentThread();
         firstTime = false;
      }
      ossimRefPtr<ossimPredatorVideo::FrameInfo> frameInfo = theVideo->nextFrame();
      
      if(!frameInfo.valid())
      {
         theDoneFlag = true;
      }
      else
      {
//          ossimRefPtr<ossimPredatorVideo::FrameInfo> f = frameInfo->dup();
//          ++frameCount;
         theFrameBufferMutex.lock();
         theFrameBuffer.push_back(frameInfo->dup());
         theFrameBufferMutex.unlock();
      }
//       updateThreadBlock();
   } while (!theDoneFlag);
//     std::cout << frameCount << std::endl;
}

ossimRefPtr<ossimPredatorVideo::FrameInfo> ossimPredatorThread::nextFrame()
{
   ossimRefPtr<ossimPredatorVideo::FrameInfo> result;
   theFrameBufferMutex.lock();
   
   if(!theFrameBuffer.empty())
   {
      result = theFrameBuffer.front();
      theFrameBuffer.pop_front();
   }
   theFrameBufferMutex.unlock();
   updateThreadBlock();
   
   return result;
}

void ossimPredatorThread::cancel()
{
   if( isRunning() )
   {
      theDoneFlag = true;
      // release the frameBlock and _databasePagerThreadBlock incase its holding up thread cancelation.
      theBlock->release();
      
      // then wait for the the thread to stop running.
      while(isRunning())
      {
         // commenting out debug info as it was cashing crash on exit, presumable
         // due to osg::notify or std::cout destructing earlier than this destructor.
         // osg::notify(osg::DEBUG_INFO)<<"Waiting for DatabasePager to cancel"<<std::endl;
         ossim::Thread::yieldCurrentThread();
      }
      theStartThreadCalledFlag = false;
   }
}

bool ossimPredatorThread::openPredator(const ossimFilename& file)
{
   ossimRefPtr<ossimPredatorVideo> video = new ossimPredatorVideo;
   if(video->open(file))
   {
      setVideo(video.get());
      
      return true;
   }
   return false;
}

void ossimPredatorThread::setVideo(ossimPredatorVideo* video)
{
   if(isRunning())
   {
      cancel();
   }

   theVideo = video;

   start();
}
