#ifndef ossimPredatorThread_HEADER
#define ossimPredatorThread_HEADER

#include "ossimPredatorApi.h"
#include <ossimPredator/ossimPredatorExport.h>
#include <ossim/base/Block.h>
#include <ossim/base/Thread.h>

#include <mutex>

class OSSIMPREDATOR_DLL ossimPredatorThread : public ossim::Thread
{
public:
   ossimPredatorThread()
   {
      theBlock = std::make_shared<ossim::Block>();
      theStartThreadCalledFlag = false;
      theDoneFlag = false;
      theBlock->set(true);
      theNumberOfFramesToBuffer = 1;
   }
   void setNumberOfFramesToBuffer(ossim_uint32 framesToBuffer)
   {
      theNumberOfFramesToBuffer = framesToBuffer;
   }
   virtual void run();
   virtual void cancel();

   ossimRefPtr<ossimPredatorVideo::FrameInfo> nextFrame();
   
   bool openPredator(const ossimFilename& file);
   void setVideo(ossimPredatorVideo* video);
   
   void updateThreadBlock()
   {
      std::lock_guard<std::mutex> lock(theFrameBufferMutex);
      
      // set true if we need to fill the frame buffer
      theBlock->set( (theFrameBuffer.size() < theNumberOfFramesToBuffer));
      // will update the block
   }
   
protected:
   
   std::shared_ptr<ossim::Block>             theBlock;
   bool                                       theDoneFlag;
   bool                                       theStartThreadCalledFlag;
   ossimRefPtr<ossimPredatorVideo>            theVideo;
   std::mutex                                 theFrameBufferMutex;
   ossim_uint32                               theNumberOfFramesToBuffer;
   std::deque<ossimRefPtr<ossimPredatorVideo::FrameInfo> > theFrameBuffer;
};

#endif
