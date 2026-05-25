#include <ossimPredator/ossimPredatorInit.h>
#include <ossimPredator/ossimPredatorApi.h>
#include <mutex>
ossimPredatorInit* ossimPredatorInit::theInstance = 0;

extern "C"
{
#if LIBAVCODEC_VERSION_MAJOR < 59
int ffmpeg_lock_callback(void **mutex, enum AVLockOp op);
#endif
}

#if LIBAVCODEC_VERSION_MAJOR < 59
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
#endif

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
#if LIBAVCODEC_VERSION_MAJOR < 59
      av_lockmgr_register(&ffmpeg_lock_callback);
#endif
      // now synch the critcal section
      //
#if LIBAVCODEC_VERSION_MAJOR < 59
     avcodec_register_all();
#endif
     avdevice_register_all();
#if LIBAVFORMAT_VERSION_MAJOR < 59
     av_register_all();
#endif

      av_log_set_level(AV_LOG_QUIET);
   }

   return theInstance;
}
