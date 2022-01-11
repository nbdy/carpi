//
// Created by nbdy on 16.11.21.
//

#include "GPS.h"

GPS::GPS(): IModule(ModuleInformation {"GPS"}) {
  setCycleTime(200);
}

void GPS::work() {
  LockGuard lg(m_GpsDataMutex);
  if(gps_waiting(&m_GpsData, 50000)) {
    m_bReadError = gps_read(&m_GpsData, nullptr, 0) == -1;
#ifdef ENABLE_SHARED_DATA
    if(!m_bReadError) {
      if(m_GpsData.fix.mode == MODE_2D || m_GpsData.fix.mode == MODE_3D) {
        setSharedData(this, &GPS::onNewGpsData);
      }
    }
#endif
  }
}

void GPS::onStart() {
  gps_open(m_sHost.c_str(), m_sPort.c_str(), &m_GpsData);
  gps_stream(&m_GpsData, WATCH_ENABLE | WATCH_JSON, nullptr);
}

void GPS::onStop() {
  gps_stream(&m_GpsData, WATCH_DISABLE, nullptr);
  gps_close(&m_GpsData);
}

void GPS::setHost(const std::string &i_sHost) {
  m_sHost = i_sHost;
}

void GPS::setPort(const std::string &i_sPort) {
  m_sPort = i_sPort;
}

void GPS::getGpsData(gps_data_t &o_GpsData) {
  LockGuard lg(m_GpsDataMutex);
  o_GpsData = m_GpsData;
}

#ifdef ENABLE_DRAW_FUNCTION
void GPS::draw(float i_fX, float i_fY) {
  static float xOffset = i_fX + 8;
  LockGuard lg(m_GpsDataMutex);
  GuiLabel(Rectangle{xOffset, i_fY, 64, 16}, ("Time: " + std::to_string(m_GpsData.fix.time.tv_sec)).c_str());
  GuiLabel(Rectangle{xOffset, i_fY + 16, 64, 16}, ("Lat: " + std::to_string(m_GpsData.fix.latitude)).c_str());
  GuiLabel(Rectangle{xOffset, i_fY + 32, 64, 16}, ("Lon: " + std::to_string(m_GpsData.fix.longitude)).c_str());
  GuiLabel(Rectangle{xOffset, i_fY + 48, 64, 16}, ("Alt: " + std::to_string(m_GpsData.fix.altitude)).c_str());
  GuiLabel(Rectangle{xOffset, i_fY + 64, 64, 16}, ("Spd: " + std::to_string(m_GpsData.fix.speed)).c_str());
}
#endif

#ifdef ENABLE_SHARED_DATA
void GPS::onNewGpsData(nlohmann::json &i_Data) {
  LockGuard lg(m_GpsDataMutex);
  i_Data["longitude"] = m_GpsData.fix.longitude;
  i_Data["latitude"] = m_GpsData.fix.latitude;
  i_Data["altitude"] = m_GpsData.fix.altitude;
  i_Data["speed"] = m_GpsData.fix.speed;
  i_Data["time"] = m_GpsData.fix.time.tv_nsec;
  i_Data["climb"] = m_GpsData.fix.climb;
  i_Data["status"] = m_GpsData.fix.status;
  i_Data["valid"] = i_Data["longitude"] != 0 && i_Data["latitude"] != 0;
}
#endif

F_CREATE(GPS)
