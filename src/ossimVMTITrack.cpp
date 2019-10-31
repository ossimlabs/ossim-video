#include <ossimPredator/ossimVMTITrack.h>
#include <iostream>
#include <iomanip>
#include <sstream>

#include <geos_c.h>

RTTI_DEF1(ossimVMTITrack, "ossimVMTITrack", ossimObject);

class ossimVMTITrackPrivate
{
  public:
    friend class ossimVMTITrack;

    ossimVMTITrackPrivate() : m_groundTrack(0),
                              m_centroidTrack(0),
                              m_reader(GEOSWKTReader_create()),
                              m_writer(GEOSWKTWriter_create())
    {
    }
    virtual ~ossimVMTITrackPrivate()
    {
      deleteGeoms();
      if (m_reader)
        GEOSWKTReader_destroy(m_reader);
      if (m_writer)
        GEOSWKTWriter_destroy(m_writer);
      m_reader = 0;
      m_writer = 0;
    }
    void deleteGeoms()
    {
      deleteGround();
      deleteCentroid();
    }
    void deleteGround()
    {
      if (m_groundTrack)
      {
        GEOSGeom_destroy(m_groundTrack);
      }
      m_groundTrack = 0;
    }
    void deleteCentroid()
    {
      if (m_centroidTrack)
      {
        GEOSGeom_destroy(m_centroidTrack);
      }
      m_centroidTrack = 0;
    }
    void setGroundTrack(GEOSGeometry *geom)
    {
      if (geom != m_groundTrack)
      {
        deleteGround();
        m_groundTrack = geom;
      }
    }
    void setCentroidTrack(GEOSGeometry *geom)
    {
      if (geom != m_centroidTrack)
      {
        deleteCentroid();
        m_centroidTrack = geom;
      }
    }
    void getGeomWkt(ossimString &result, GEOSGeometry *geom)const
    {
      result = "";
      if (geom)
      {
        if (m_writer)
        {
          char *str = GEOSWKTWriter_write(m_writer, geom);
          if (str)
          {
            result = str;
            GEOSFree(str);
          }
        }
      }
    }
public:
    GEOSGeometry  *m_groundTrack;
    GEOSGeometry  *m_centroidTrack;
    GEOSWKTReader *m_reader;
    GEOSWKTWriter *m_writer;
};

ossimVMTITrack::ossimVMTITrack()
    : m_targetID(0),
      m_trackStartTime(18446744073709551615UL),
      m_trackEndTime(0),
      m_trackFrameStart(OSSIM_DEFAULT_MAX_PIX_UINT32),
      m_trackFrameEnd(0),
      m_targetMinIntensity(FLT_MAX),
      m_targetMaxIntensity(0.0),
      m_minGsd(FLT_MAX),
      m_maxGsd(0.0),
      m_klvTrackMetadata(ossimString("[\n\t\t\t\t")),
      m_init(true),
      m_vmtiTrackPrivate(new ossimVMTITrackPrivate())
{
}

ossimVMTITrack::~ossimVMTITrack()
{
  if (m_vmtiTrackPrivate)
    delete m_vmtiTrackPrivate;
  m_vmtiTrackPrivate = 0;
}

/*
// Need to be able to order these objects in an std::set
bool ossimVMTITrack::operator< (const ossimVMTITrack& track) const
{
  return m_targetID < track.m_targetID;
}
*/

void ossimVMTITrack::updateGsds(const ossim_float64& gsd)
{
  if (gsd > m_maxGsd) m_maxGsd = gsd;
  if (gsd < m_minGsd) m_minGsd = gsd; 
}

void ossimVMTITrack::updateIntensities(const ossim_float64& intensity)
{
  if (intensity < m_targetMinIntensity) m_targetMinIntensity = intensity; 
  if (intensity > m_targetMaxIntensity) m_targetMaxIntensity = intensity; 
}

void ossimVMTITrack::updateFrames(const ossim_uint32& frameNumber)
{
  if (frameNumber < m_trackFrameStart) m_trackFrameStart = frameNumber;
  if (frameNumber > m_trackFrameEnd) m_trackFrameEnd = frameNumber;
}

void ossimVMTITrack::updateTimes(const ossim_uint64& timestamp)
{
  if (timestamp < m_trackStartTime && timestamp > 0) m_trackStartTime = timestamp;
  if (timestamp > m_trackEndTime) m_trackEndTime = timestamp;
}

ossim_uint32 ossimVMTITrack::getTargetID() const
{
  return m_targetID;
}

void ossimVMTITrack::setTargetID(ossim_uint32 targetId)
{
  m_targetID = targetId;
}


ossim_float64 ossimVMTITrack::getMinGsd() const
{
  return m_minGsd;
}

ossim_float64 ossimVMTITrack::getMaxGsd() const
{
  return m_maxGsd;
}

ossimString ossimVMTITrack::getJson(ossim_uint32 tabcount, bool comma) const
{
  ossimString result = "";
  if (comma) result += ",";
  result += "\n\t\t{";
  writeJsonKVP(result, "TRACK_ID", ossimString::toString(getTargetID()), true, tabcount);
  writeJsonKVP(result, "TRACK_START_TIME", getDate(m_trackStartTime), true, tabcount);
  writeJsonKVP(result, "TRACK_END_TIME", getDate(m_trackEndTime), true, tabcount);
  writeJsonKVP(result, "TRACK_FRAME_START", ossimString::toString(m_trackFrameStart), true, tabcount);
  writeJsonKVP(result, "TRACK_FRAME_END", ossimString::toString(m_trackFrameEnd), true, tabcount);
  writeJsonKVP(result, "TARGET_MIN_INTENSITY", ossimString::toString(m_targetMinIntensity), true, tabcount);
  writeJsonKVP(result, "TARGET_MAX_INTENSITY", ossimString::toString(m_targetMaxIntensity), true, tabcount);
  writeJsonKVP(result, "MIN_GSD", ossimString::toString(m_minGsd), true, tabcount);
  writeJsonKVP(result, "MAX_GSD", ossimString::toString(m_maxGsd), true, tabcount);
  writeJsonKVP(result, "TARGET_CENTROID_TRACK", getCentroidWKT().gsub("MULTIPOINT", "LINESTRING"), true, tabcount); 
  writeJsonKVP(result, "TARGET_FOOTPRINT", getGroundTrackWKT(), true, tabcount);
  writeJsonKVP(result, "KLV_TRACK_METADATA", getKlvTrackMetadata(), false, tabcount, false);

  result += "\n\t\t}";
  return result;
}

ossimString ossimVMTITrack::getKlvTrackMetadata() const
{
  return m_klvTrackMetadata;
}

void ossimVMTITrack::updateKlvTrackMetadata(const ossimString append, bool data)
{
  if (!m_init && data)
  {
    m_klvTrackMetadata += ",\n\t\t\t\t";
  }
  m_klvTrackMetadata += append;
  if (m_init) m_init = false;
}

ossimString ossimVMTITrack::getGroundTrackWKT()const
{
  ossimString result;

  m_vmtiTrackPrivate->getGeomWkt(result, m_vmtiTrackPrivate->m_groundTrack);

  return result;
}

ossimString ossimVMTITrack::getCentroidWKT() const 
{
  ossimString result;

  m_vmtiTrackPrivate->getGeomWkt(result, m_vmtiTrackPrivate->m_centroidTrack);

  return result;
}

void ossimVMTITrack::getGroundTrackWKT(ossimString &result) const
{
  m_vmtiTrackPrivate->getGeomWkt(result, m_vmtiTrackPrivate->m_groundTrack);
}

void ossimVMTITrack::getCentroidWKT(ossimString &result) const
{
  m_vmtiTrackPrivate->getGeomWkt(result, m_vmtiTrackPrivate->m_centroidTrack);
}

void ossimVMTITrack::addToGroundTrack(const ossimString &wktString)
{
  GEOSGeometry *groundTrack = GEOSWKTReader_read(m_vmtiTrackPrivate->m_reader, wktString.c_str());

  if (groundTrack)
  {
    if (m_vmtiTrackPrivate->m_groundTrack)
    {
      GEOSGeometry *unionGeom = GEOSUnion(groundTrack, m_vmtiTrackPrivate->m_groundTrack);
      if(unionGeom)
      {
        m_vmtiTrackPrivate->setGroundTrack(unionGeom);
      }

      GEOSGeom_destroy(groundTrack);
    }
    else
    {
      m_vmtiTrackPrivate->setGroundTrack(groundTrack);
    }
  }
}

void ossimVMTITrack::addToCentroidTrack(const ossimString &wktString)
{
  GEOSGeometry *centroidTrack = GEOSWKTReader_read(m_vmtiTrackPrivate->m_reader, wktString.c_str());

  if (centroidTrack)
  {
    if (m_vmtiTrackPrivate->m_centroidTrack)
    {
      GEOSGeometry *unionGeom = GEOSUnion(centroidTrack, m_vmtiTrackPrivate->m_centroidTrack);
      if (unionGeom)
      {
        m_vmtiTrackPrivate->setCentroidTrack(unionGeom);
      }

      GEOSGeom_destroy(centroidTrack);
    }
    else
    {
      m_vmtiTrackPrivate->setCentroidTrack(centroidTrack);
    }
  }
}

void ossimVMTITrack::clearGroundTrack()
{
  m_vmtiTrackPrivate->deleteGround();
}

void ossimVMTITrack::clearCentroidTrack()
{
  m_vmtiTrackPrivate->deleteCentroid();
}

ossimString ossimVMTITrack::getDate(const ossim_uint64& epoc) const
{
  ossimDate d;
  ossim_float64 fractionalSeconds = static_cast<ossim_float64>(epoc*1e-6);
  ossim_uint64 seconds = static_cast<ossim_uint64>(fractionalSeconds);
  ossim_float64 fraction = fractionalSeconds - seconds;

  d.setTimeNoAdjustmentGivenEpoc(seconds);
  d.setFractionalSecond(fraction);

  
  std::ostringstream datestr;
  ossim_uint32 roundStart = d.getFractionalSecond() * 1000;
  datestr << std::setw(4) << std::setfill('0') << d.getYear() << "-"
          << std::setw(2) << std::setfill('0') << d.getMonth() << "-"
          << std::setw(2) << std::setfill('0') << d.getDay() << " "
          << std::setw(2) << std::setfill('0') << d.getHour() << ":"
          << std::setw(2) << std::setfill('0') << d.getMin() << ":"
          << std::setw(2) << std::setfill('0') << d.getSec() << "."
	  << std::setw(3) << std::setfill('0') << roundStart;
  return ossimString(datestr.str());
}


void ossimVMTITrack::writeJsonKVP(std::string& outputString, ossimString key, ossimString value, bool comma, ossim_uint32 tabcount, bool quote) const
{
    outputString += "\n";
    for (ossim_uint32 i = 0; i < tabcount; ++i)
    {
      outputString += "\t";
    }
    if (quote) outputString += "\"" + key.string() + "\": \"" + value.string() + "\"";
    else outputString += "\"" + key.string() + "\": " + value.string();
    if (comma) outputString += ",";
}
