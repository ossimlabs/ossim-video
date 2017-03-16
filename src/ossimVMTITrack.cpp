#include <ossimPredator/ossimVMTITrack.h>
#include <iostream>
#include <iomanip>
#include <sstream>

RTTI_DEF1(ossimVMTITrack, "ossimVMTITrack", ossimObject);

ossimVMTITrack::ossimVMTITrack()
   :m_targetID(0),
    m_trackStartTime(18446744073709551615),
    m_trackEndTime(0),
    m_trackFrameStart(OSSIM_DEFAULT_MAX_PIX_UINT32),
    m_trackFrameEnd(0),
    m_targetMinIntensity(FLT_MAX),
    m_targetMaxIntensity(0.0),
    m_minGsd(FLT_MAX),
    m_maxGsd(0.0), 
    m_klvTrackMetadata(ossimString("[\n\t\t\t\t")),
    m_init(true)
{
    m_groundTrack = 0;
    m_centroidTrack = 0;
}

ossimVMTITrack::~ossimVMTITrack()
{
    delete m_groundTrack;
    delete m_centroidTrack;
    m_groundTrack = 0;
    m_centroidTrack = 0;
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

geos::geom::Geometry* ossimVMTITrack::getGroundTrack()
{
  return m_groundTrack;
}

geos::geom::Geometry* ossimVMTITrack::getCentroidTrack()
{
  return m_centroidTrack;
}

geos::geom::Geometry* ossimVMTITrack::setGroundTrack(geos::geom::Geometry* source)
{
  m_groundTrack = source;
}

geos::geom::Geometry* ossimVMTITrack::setCentroidTrack(geos::geom::Geometry* source)
{
  m_centroidTrack = source;
}

ossimString ossimVMTITrack::getGroundTrackWKT()const
{
  ossimString result = "";
  if(m_groundTrack)
  {
    geos::io::WKTWriter writer;
    try
    {
      result = writer.write(m_groundTrack);
    }
    catch(...)
    {
    }
  }
  return result;
}

ossimString ossimVMTITrack::getCentroidWKT()const
{
  ossimString result = "";
  if(m_centroidTrack)
  {
    geos::io::WKTWriter writer;
    try
    {
      result = writer.write(m_centroidTrack);
    }
    catch(...)
    {
    }
  }
  return result;
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
