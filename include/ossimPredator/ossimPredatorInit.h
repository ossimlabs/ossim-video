#ifndef ossimPredatorInit_HEADER
#define ossimPredatorInit_HEADER
#include <ossimPredator/ossimPredatorExport.h>
#include <mutex>
class OSSIMPREDATOR_DLL ossimPredatorInit
{
public:
   static ossimPredatorInit* instance();
   std::mutex&  criticalSectionMutex()
   {
      return theCriticalSectionMutex;
   }
   
protected:
   ossimPredatorInit();
   ossimPredatorInit(const ossimPredatorInit& src);

   std::mutex theCriticalSectionMutex;
   static ossimPredatorInit* theInstance;
};

#endif
