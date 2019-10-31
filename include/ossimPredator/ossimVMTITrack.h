// VMTI Track Object derived from VMTI KLV MISP ST 903

#ifndef ossimVMTITrack_HEADER
#define ossimVMTITrack_HEADER 1

#include <ossimPredator/ossimPredatorExport.h>
#include <ossim/base/ossimString.h>
#include <ossim/base/ossimReferenced.h>
#include <ossim/base/ossimDate.h>
#include <ossim/base/ossimObject.h>

#include <geos_c.h>
class ossimVMTITrackPrivate;

class OSSIMPREDATOR_DLL ossimVMTITrack : public ossimObject
{

public:
  ossimVMTITrack();
  ~ossimVMTITrack();

  //bool operator< (const ossimVMTITrack& track) const;

  void updateGsds(const ossim_float64& gsd);
  void updateIntensities(const ossim_float64& intensity);
  void updateFrames(const ossim_uint32& frameNumber);
  void updateTimes(const ossim_uint64& time);
  ossim_uint32 getTargetID() const;
  ossim_float64 getMinGsd() const;
  ossim_float64 getMaxGsd() const;
  ossimString getJson(ossim_uint32 tabcount, bool comma=true) const;
  void writeJsonKVP(std::string& outputString, ossimString key, ossimString value, bool comma, ossim_uint32 tabcount, bool quote=true) const;
  //GEOSGeometry *getGroundTrack();
  //GEOSGeometry *getCentroidTrack();
  ossimString getGroundTrackWKT() const;
  ossimString getCentroidWKT() const;
  void getGroundTrackWKT(ossimString &result) const;
  void getCentroidWKT(ossimString &result) const;
  void addToGroundTrack(const ossimString &wktString);
  void addToCentroidTrack(const ossimString &wktString);
  void clearGroundTrack();
  void clearCentroidTrack();
  //GEOSGeometry *setGroundTrack(GEOSGeometry *source);
  //GEOSGeometry *setCentroidTrack(GEOSGeometry *source);
  void setTargetID(ossim_uint32 targetId);
  ossimString getDate(const ossim_uint64& epoc) const;
  ossimString getKlvTrackMetadata() const;
  void updateKlvTrackMetadata(const ossimString append, bool data=true);



private:
  ossim_uint32 m_targetID;
  ossim_uint64 m_trackStartTime;
  ossim_uint64 m_trackEndTime;
  ossim_uint32 m_trackFrameStart;
  ossim_uint32 m_trackFrameEnd;
  ossim_float64 m_targetMinIntensity;
  ossim_float64 m_targetMaxIntensity;
  ossim_float64 m_minGsd;
  ossim_float64 m_maxGsd;
  ossimString m_klvTrackMetadata;
  bool m_init;

  ossimVMTITrackPrivate* m_vmtiTrackPrivate;

  TYPE_DATA
};
#endif
