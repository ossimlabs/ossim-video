#ifndef ossimPredatorThread_HEADER
#define ossimPredatorThread_HEADER

#include <OpenThreads/Thread>
#include <OpenThreads/Block>
#include "ossimPredatorApi.h"
#include <ossimPredator/ossimPredatorExport.h>
#include <mutex>
class OSSIMPREDATOR_DLL ossimPredatorRefBlock : virtual public ossimReferenced,
                              public OpenThreads::Block
{
public:
   ossimPredatorRefBlock()
   {}
};

class OSSIMPREDATOR_DLL ossimPredatorThread : public OpenThreads::Thread
{
public:
   ossimPredatorThread()
   {
      theBlock = new ossimPredatorRefBlock;
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
   virtual int cancel();

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
   
   ossimRefPtr<ossimPredatorRefBlock>         theBlock;
   bool                                       theDoneFlag;
   bool                                       theStartThreadCalledFlag;
   ossimRefPtr<ossimPredatorVideo>            theVideo;
   std::mutex                                 theFrameBufferMutex;
   ossim_uint32                               theNumberOfFramesToBuffer;
   std::deque<ossimRefPtr<ossimPredatorVideo::FrameInfo> > theFrameBuffer;
};

#endif
