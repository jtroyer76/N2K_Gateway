/*
  This code is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
  This code is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

// N2k Gateway
// Version 0.0.1, 9/19/2022, Jess Troyer

// Port A - Red
#define ESP32_CAN_TX_PIN GPIO_NUM_32
#define ESP32_CAN_RX_PIN GPIO_NUM_33

#include <Arduino.h>
#include <NMEA2000_CAN.h> // This will automatically choose right CAN library and create suitable NMEA2000 object
#include <N2kMessages.h>
#include <Preferences.h>
#include "LittleFS.h"

#include <M5Core2.h>
#include <time.h>
#include <sys/time.h>

#include "N2kGateway.h"
#include "functions.h"
#include "display\SingleDisplay.h"
#include "display\DisplayController.h"
#include "config\Configuration.h"
#include "server\Server.h"

using N2kGateway::DisplayController;
using N2kGateway::SingleDisplay;
using N2kGateway::Configuration;

std::unique_ptr<Configuration> config { new Configuration() };
DisplayController displayController(*config);
N2kGateway::Server server(*config);

//*****************************************************************************
void setup()
{
  uint8_t chipid[6];
  uint32_t id = 0;
  int i = 0;

  M5.begin(true, true, true, false);
  // Init USB serial port
  Serial.begin(115200);
  delay(10);

  if(!LittleFS.begin()){
    Serial.println("An Error has occurred while mounting LittleFS");
    return;
  }

  // Init WiFi connection
  Serial.println("Start WLAN");
  WiFi.begin(ssid, ssidPass);
  WiFi.setHostname("NMEA2000-Gateway");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    i++;
    if (i > 20)
      ESP.restart();
  }

  IPAddress IP = WiFi.localIP();
  Serial.println("");
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // Reserve enough buffer for sending all messages.
  NMEA2000.SetN2kCANMsgBufSize(8);
  NMEA2000.SetN2kCANReceiveFrameBufSize(150);
  NMEA2000.SetN2kCANSendFrameBufSize(150);

  // Generate unique number from chip id
  esp_efuse_mac_get_default(chipid);
  for (i = 0; i < 6; i++)
    id += (chipid[i] << (7 * i));

  // Set product information
  NMEA2000.SetProductInformation("1",                     // Manufacturer's Model serial code
                                 100,                     // Manufacturer's product code
                                 "NMEA Reader",           // Manufacturer's Model ID
                                 "1.0.2.25 (2019-07-07)", // Manufacturer's Software version code
                                 "1.0.2.0 (2019-07-07)"   // Manufacturer's Model version
  );

  // Set device information
  NMEA2000.SetDeviceInformation(id,  // Unique number. Use e.g. Serial number.
                                131, // Device function=NMEA 2000 to Analog Gateway. See codes on http://www.nmea.org/Assets/20120726%20nmea%202000%20class%20&%20function%20codes%20v%202.00.pdf
                                25,  // Device class=Inter/Intranetwork Device. See codes on  http://www.nmea.org/Assets/20120726%20nmea%202000%20class%20&%20function%20codes%20v%202.00.pdf
                                2046 // Just choosen free from code list on http://www.nmea.org/Assets/20121020%20nmea%202000%20registration%20list.pdf
  );

  // If you also want to see all traffic on the bus use N2km_ListenAndNode instead of N2km_NodeOnly below
  NMEA2000.SetForwardStream(&Serial);
  NMEA2000.SetForwardType(tNMEA2000::fwdt_Text); // Show in clear text. Leave uncommented for default Actisense format.

  preferences.begin("nvs", false);                         // Open nonvolatile storage (nvs)
  NodeAddress = preferences.getInt("LastNodeAddress", 34); // Read stored last NodeAddress, default 34
  preferences.end();
  Serial.printf("NodeAddress=%d\n", NodeAddress);

  // If you also want to see all traffic on the bus use N2km_ListenAndNode instead of N2km_NodeOnly below
  NMEA2000.SetMode(tNMEA2000::N2km_ListenOnly, NodeAddress);
  NMEA2000.SetMsgHandler(MyHandleNMEA2000Msg);

  NMEA2000.Open();

  displayController.AddDisplay(new SingleDisplay("Depth", "Ft", BoatData.WaterDepth));
  displayController.AddDisplay(new SingleDisplay("Speed", "Kn", BoatData.STW));
  displayController.AddDisplay(new SingleDisplay("SOG", "Kn", BoatData.SOG));
  displayController.Show();

  server.Begin();
}

void loop()
{  
  NMEA2000.ParseMessages();
  CheckSourceAddressChange();

  // Dummy to empty input buffer to avoid board to stuck with e.g. NMEA Reader
  if (Serial.available())
  {
    Serial.read();
  }

  M5.update();

  if (millis() > t + 1000)
  {
    t = millis();

    displayController.Update();
  }

  if (M5.BtnA.wasPressed() == true)
  {
    displayController.PreviousScreen();
  }

  if (M5.BtnC.wasPressed() == true)
  {
    displayController.NextScreen();
  }
}
