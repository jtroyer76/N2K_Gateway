#include "data\BoatData.h"

// Boat data
N2kGateway::BoatData BoatData;

//*****************************************************************************
void HandleSytemTime(const tN2kMsg & N2kMsg) {
  unsigned char SID;
  tN2kTimeSource TimeSource;

  ParseN2kSystemTime(N2kMsg, SID, DaysSince1970, SecondsSinceMidnight,
                     TimeSource);
}


//*****************************************************************************
void HandleGNSS(const tN2kMsg & N2kMsg) {

  unsigned char SID;
  double Latitude;
  double Longitude;
  double Altitude;
  tN2kGNSStype GNSStype;
  tN2kGNSSmethod GNSSmethod;
  unsigned char nSatellites;
  double HDOP;
  double PDOP;
  double GeoidalSeparation;
  unsigned char nReferenceStations;
  tN2kGNSStype ReferenceStationType;
  uint16_t ReferenceSationID;
  double AgeOfCorrection;

  if ( ParseN2kGNSS(N2kMsg, SID, DaysSince1970, SecondsSinceMidnight, Latitude, Longitude, Altitude,
                    GNSStype, GNSSmethod, nSatellites, HDOP, PDOP, GeoidalSeparation,
                    nReferenceStations, ReferenceStationType, ReferenceSationID, AgeOfCorrection) ) {
                      BoatData.Longitude = Longitude;
                      BoatData.Latitude = Latitude;
                      BoatData.Altitude = Altitude;                    
  }
}

void HandleDepth(const tN2kMsg & N2kMsg) {
  unsigned char SID;
  double DepthBelowTransducer;
  double Offset;

  if ( ParseN2kWaterDepth(N2kMsg, SID, DepthBelowTransducer, Offset) ) {
    BoatData.WaterDepth = DepthBelowTransducer;              
  }
}

void HandleSpeed(const tN2kMsg &n2kMsg)
{
  unsigned char SID;
  double stw;
  double sog;
  tN2kSpeedWaterReferenceType swrt;

  if(ParseN2kBoatSpeed(n2kMsg, SID, stw, sog, swrt)) {
    BoatData.STW = stw * 1.94384;
    BoatData.SOG = sog * 1.94384;
  }
}

// 16:29:27.082 R 09F8017F 50 C3 B8 13 47 D8 2B C6

//*****************************************************************************
void N2kToYD_Can(const tN2kMsg &msg, char *MsgBuf) {
  int i, len;
  uint32_t canId = 0;
  char time_str[20];
  char Byte[5];
  unsigned int PF;
  time_t rawtime;
  struct tm  ts;

  len = msg.DataLen;
  if (len > 134) len = 134;

  // Set CanID

  canId = msg.Source & 0xff;
  PF = (msg.PGN >> 8) & 0xff;

  if (PF < 240) {
    canId = (canId | ((msg.Destination & 0xff) << 8));
    canId = (canId | (msg.PGN << 8));
  } else {
    canId = (canId | (msg.PGN << 8));
  }

  canId = (canId | (msg.Priority << 26));

  rawtime = (DaysSince1970 * 3600 * 24) + SecondsSinceMidnight;  // Create time from GNSS time;
  ts = *localtime(&rawtime);
  strftime(time_str, sizeof(time_str), "%T.000", &ts);  // Create time string

  snprintf(MsgBuf, 25, "%s R %0.8x", time_str, canId);  // Set time and canID

  for (i = 0; i < len; i++) {
    snprintf(Byte, 4, " %0.2x", msg.Data[i]);           // Add data fields
    strcat(MsgBuf, Byte);
  }
}


//*****************************************************************************
void MyHandleNMEA2000Msg(const tN2kMsg &N2kMsg) {

  if (N2kMsg.PGN == 129029L) HandleGNSS(N2kMsg);      // Just to get time from GNSS
  if (N2kMsg.PGN == 126992L) HandleSytemTime(N2kMsg); // or this way
  if (N2kMsg.PGN == 128267L) HandleDepth(N2kMsg);
  if (N2kMsg.PGN == 128259L) HandleSpeed(N2kMsg);
  
  N2kToYD_Can(N2kMsg, YD_msg);            // Create YD message from PGN

  udp.beginPacket(udpAddress, udpPort);   // Send to UDP
  udp.println(YD_msg);
  udp.endPacket();

  // Serial.println(YD_msg);
}


//*****************************************************************************
void CheckSourceAddressChange() {
  int SourceAddress = NMEA2000.GetN2kSource();
  if (SourceAddress != NodeAddress) { // Save potentially changed Source Address to NVS memory
    NodeAddress = SourceAddress;      // Set new Node Address (to save only once)
    preferences.begin("nvs", false);
    preferences.putInt("LastNodeAddress", SourceAddress);
    preferences.end();
    Serial.printf("Address Change: New Address=%d\n", SourceAddress);
  }
}
