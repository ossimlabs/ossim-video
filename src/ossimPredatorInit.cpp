#include <ossimPredator/ossimPredatorInit.h>
#include <ossimPredator/ossimPredatorApi.h>
#include <mutex>
ossimPredatorInit* ossimPredatorInit::theInstance = 0;

extern "C"
{
int ffmpeg_lock_callback(void **mutex, enum AVLockOp op);
}

int ffmpeg_lock_callback(void **mutex, enum AVLockOp op)
{
   static std::mutex m;

   switch(op)
   {
      case AV_LOCK_CREATE:
      {
         *mutex = &m;
          break;
      }
      case AV_LOCK_OBTAIN:
      {
         ((std::mutex*)(*mutex))->lock();
         break;
      }
      case AV_LOCK_RELEASE:
      {
         ((std::mutex*)(*mutex))->unlock();
        break;      
      }
      case AV_LOCK_DESTROY:
      {
        *mutex = 0;
        break;
      }

   }

   return 0;
}

ossimPredatorInit::ossimPredatorInit()
{
   theInstance = this;
}

ossimPredatorInit* ossimPredatorInit::instance()
{
   // synch the entry of instance
   static std::mutex m;
   std::lock_guard<std::mutex> lock(m);
   if(!theInstance)
   {
      theInstance = new ossimPredatorInit;
      av_lockmgr_register(&ffmpeg_lock_callback);
      // now synch the critcal section
      //
     avcodec_register_all();
     avdevice_register_all();
     av_register_all();

      av_log_set_level(AV_LOG_QUIET);
   }

   return theInstance;
}
