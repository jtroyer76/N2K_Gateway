#include "boatdata.h"

// Boat data
tBoatData BoatData;

//*****************************************************************************
void HandleSytemTime(const tN2kMsg & N2kMsg) {
  unsigned char SID;
  tN2kTimeSource TimeSource;

  ParseN2kSystemTime(N2kMsg, SID, DaysSince1970, SecondsSinceMidnight,
                     TimeSource);

 Serial.println("Got System Time");
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


void Page_5(void) {
  char buffer[40];

  M5.Lcd.fillRect(0, 31, 320, 178, 0x439);
  M5.Lcd.setCursor(0, 45, 2);
  M5.Lcd.setTextSize(3);
  sprintf(buffer, " Water %3.0f", BoatData.WaterTemperature);
  M5.Lcd.print(buffer);
  M5.Lcd.setTextSize(1);
  M5.Lcd.print(" o ");
  M5.Lcd.setTextSize(3);
  M5.Lcd.println("C  ");
  sprintf(buffer, " Trip  %4.1f nm", BoatData.TripLog);
  M5.Lcd.print(buffer);
  M5.Lcd.println("  ");
  sprintf(buffer, " Log %5.0f nm", BoatData.Log);
  M5.Lcd.println(buffer);
}



void Page_4(void) {
  char buffer[40];

  M5.Lcd.fillRect(0, 31, 320, 178, 0x439);
  M5.Lcd.setCursor(0, 45, 2);
  M5.Lcd.setTextSize(3);
  sprintf(buffer, " STW   %3.1f kn", BoatData.STW);
  M5.Lcd.print(buffer);
  M5.Lcd.println("  ");
  sprintf(buffer, " Depth %4.1f m", BoatData.WaterDepth);
  M5.Lcd.print(buffer);
  M5.Lcd.println("  ");
  sprintf(buffer, " Rudder %2.1f", BoatData.RudderPosition);
  M5.Lcd.print(buffer);
  M5.Lcd.setTextSize(1);
  M5.Lcd.print(" o ");
  M5.Lcd.setTextSize(3);
}



void Page_3(void) {
  char buffer[40];

  M5.Lcd.fillRect(0, 31, 320, 178, 0x439);
  M5.Lcd.setCursor(0, 45, 2);
  M5.Lcd.setTextSize(3);
  sprintf(buffer, " HDG %03.0f", BoatData.Heading);
  M5.Lcd.print(buffer);
  M5.Lcd.setTextSize(1);
  M5.Lcd.print(" o ");
  M5.Lcd.setTextSize(3);
  M5.Lcd.println("  ");
  sprintf(buffer, " COG %03.0f", BoatData.COG);
  M5.Lcd.print(buffer);
  M5.Lcd.setTextSize(1);
  M5.Lcd.print(" o ");
  M5.Lcd.setTextSize(3);
  M5.Lcd.println("  ");
  sprintf(buffer, " SOG %2.1f kn", BoatData.SOG);
  M5.Lcd.println(buffer);
}

void Page_2(void) {
  char buffer[40];
  double minutes;

  M5.Lcd.fillRect(0, 31, 320, 178, 0x439);
  M5.Lcd.setCursor(0, 40, 2);
  M5.Lcd.setTextSize(2);

  minutes = BoatData.Latitude - trunc(BoatData.Latitude);
  minutes = minutes / 100 * 60;

  M5.Lcd.println("LAT");
  M5.Lcd.setTextSize(3);
  sprintf(buffer, "   %02.0f", trunc(BoatData.Latitude));
  M5.Lcd.print(buffer);
  M5.Lcd.setTextSize(1);
  M5.Lcd.print("o ");
  M5.Lcd.setTextSize(3);
  sprintf(buffer, "%06.3f", minutes * 100);
  M5.Lcd.print(buffer);
  if (BoatData.Latitude > 0 ) M5.Lcd.println("'N"); else M5.Lcd.println("'S");

  minutes = BoatData.Longitude - trunc(BoatData.Longitude);
  minutes = minutes / 100 * 60;

  M5.Lcd.setTextSize(2);
  M5.Lcd.println("LON");
  M5.Lcd.setTextSize(3);
  sprintf(buffer, "  %03.0f", trunc(BoatData.Longitude));
  M5.Lcd.print(buffer);
  M5.Lcd.setTextSize(1);
  M5.Lcd.print("o ");
  M5.Lcd.setTextSize(3);
  sprintf(buffer, "%06.3f", minutes * 100);
  M5.Lcd.print(buffer);
  if (BoatData.Longitude > 0 ) M5.Lcd.println("'E"); else M5.Lcd.println("'W");
}

void Page_1(void) {
  char buffer[40];

  double AWS = 0;

  if (BoatData.AWS > 0) AWS = BoatData.AWS;

  M5.Lcd.fillRect(0, 31, 320, 178, 0x439);
  M5.Lcd.setCursor(0, 50, 2);
  M5.Lcd.setTextSize(4);
  sprintf(buffer, " AWS %3.0f kn", AWS);
  M5.Lcd.println(buffer);
  sprintf(buffer, " MAX %3.0f kn", BoatData.MaxAws);
  M5.Lcd.println(buffer);
}

void DisplayDateTime(void) {
  char buffer[50];

  M5.Lcd.setTextFont(1);
  M5.Lcd.setTextSize(2);                                      /* Set text size to 2 */
  M5.Lcd.setTextColor(WHITE);                                 /* Set text color to white */

  M5.Lcd.fillRect(265, 0, 320, 30, 0x1E9F);

  M5.Lcd.setCursor(265, 7);
  sprintf(buffer, "%3.0d", M5.Axp.GetBatPower());
  M5.Lcd.print(buffer);
  M5.Lcd.print("%");


  M5.Lcd.fillRect(0, 210, 320, 30, 0x1E9F);
  M5.Lcd.setCursor(10, 218);

  if (MyTime != 0) {

    time_t rawtime = MyTime; // Create time from NMEA 2000 time (UTC)
    struct tm  ts;
    ts = *localtime(&rawtime);

    strftime(buffer, sizeof(buffer), "%d.%m.%Y - %H:%M:%S UTC", &ts); // Create directory name from date
    M5.Lcd.print(buffer);
  }

}

void Display_Main (void)
{
  // // setting the humidity
  // M5.Lcd.clear();
  // M5.Lcd.setTextColor(TFT_WHITE);
  // M5.Lcd.setFreeFont(FSSB12);
  // M5.Lcd.drawString("Depth", 10, 10);
  // M5.Lcd.drawString("Feet", 260, 10);
  // M5.Lcd.setFreeFont(&FreeSansBold90pt7b);
  // M5.Lcd.drawNumber(354, 10, 70);

  // M5.Lcd.setTextFont(1);
  // M5.Lcd.fillRect(0, 0, 320, 30, 0x1E9F);                      /* Upper dark blue area */
  // M5.Lcd.fillRect(0, 31, 320, 178, 0x439);                   /* Main light blue area */
  // M5.Lcd.fillRect(0, 210, 320, 30, 0x1E9F);                    /* Lower dark blue area */
  // M5.Lcd.fillRect(0, 30, 320, 4, 0xffff);                     /* Upper white line */
  // M5.Lcd.fillRect(0, 208, 320, 4, 0xffff);                    /* Lower white line */
  // //  M5.Lcd.fillRect(0, 92, 320, 4, 0xffff);                     /* First vertical white line */
  // //  M5.Lcd.fillRect(0, 155, 320, 4, 0xffff);                    /* Second vertical white line */
  // //  M5.Lcd.fillRect(158, 30, 4, 178, 0xffff);                   /* First horizontal white line */
  // M5.Lcd.setTextSize(2);                                      /* Set text size to 2 */
  // M5.Lcd.setTextColor(WHITE);                                 /* Set text color to white */
  // M5.Lcd.setCursor(10, 7);                                    /* Display header info */
  // M5.Lcd.print("NMEA Display");
  // M5.Lcd.setCursor(210, 7);
  // M5.Lcd.print("Batt");
}