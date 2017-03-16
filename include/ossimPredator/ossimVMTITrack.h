// VMTI Track Object derived from VMTI KLV MISP ST 903

#ifndef ossimVMTITrack_HEADER
#define ossimVMTITrack_HEADER
#include <ossim/base/ossimString.h>
#include <ossim/base/ossimReferenced.h>
#include <ossim/base/ossimDate.h>
#include <ossim/base/ossimObject.h>
#include <geos/geom/Coordinate.h>
#include <geos/geom/CoordinateArraySequence.h>
#include <geos/geom/GeometryFactory.h>
#include <geos/geom/LinearRing.h>
#include <geos/geom/Point.h>
#include <geos/geom/Polygon.h>
#include <geos/geom/PrecisionModel.h>
#include <geos/io/WKTReader.h>
#include <geos/io/WKTWriter.h>
#include <geos/util/GEOSException.h>

class ossimVMTITrack : public ossimObject {

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
  geos::geom::Geometry* getGroundTrack();
  geos::geom::Geometry* getCentroidTrack();
  geos::geom::Geometry* setGroundTrack(geos::geom::Geometry* source);
  geos::geom::Geometry* setCentroidTrack(geos::geom::Geometry* source);
  void setTargetID(ossim_uint32 targetId);
  ossimString getGroundTrackWKT()const;
  ossimString getCentroidWKT()const;
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
  geos::geom::Geometry* m_groundTrack;
  geos::geom::Geometry* m_centroidTrack;

  TYPE_DATA
};
#endif
