
#include <Preferences.h>
#include <WiFi.h>

#define Max_YD_Message_Size 500
char YD_msg[Max_YD_Message_Size] = "";

int NodeAddress;            // To store last Node Address
Preferences preferences;    // Nonvolatile storage on ESP32 - To store LastDeviceAddress

const char* hostname  = "TQ-Gateway";    // Hostname for network discovery
const char* ssid      = "bitfu2";                // SSID to connect to
const char* ssidPass  = "J&TTroyer";            // Password for wifi

// UPD broadcast to SignalK server
const char* udpAddress = "192.168.1.255"; // UDP (broadcast) address. Should be the SignalK server or .255 for all
const int udpPort = 4444;                  // YD UDP port

double t = 0;  // Time
int page = 0;  // Initial page to show
int pages = 4; // Number of pages -1
int LCD_Brightness = 250;

long MyTime = 0;  // System Time from NMEA2000
bool TimeSet = false;

// Create UDP instance
WiFiUDP udp;

uint16_t DaysSince1970 = 0;
double SecondsSinceMidnight = 0;