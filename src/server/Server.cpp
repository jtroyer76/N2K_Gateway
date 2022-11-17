#include "Server.h"
#include "AsyncJson.h"
#include <ArduinoJson.h>
#include <LittleFS.h>

namespace N2kGateway
{
    Server::Server(const Configuration &config, const Status &status) : _config(config), _status(status)
    {
        _server = new AsyncWebServer(80);
        
        // API get
        _server->on("/api", HTTP_GET, [this](AsyncWebServerRequest *request)
        {
            AsyncResponseStream *response = request->beginResponseStream("application/json");
            serializeJson(_config.Config(), *response);
            request->send(response); 
        });

        // API post
        AsyncCallbackJsonWebHandler *handler = 
        new AsyncCallbackJsonWebHandler("/api", [](AsyncWebServerRequest *request, JsonVariant &json) {
            const JsonObject &jsonObj = json.as<JsonObject>();
            serializeJson(jsonObj, Serial);
            request->send(200, "application/json", "{\"status\":\"ok\"}");
        });
        _server->addHandler(handler);

        // Routes for web page
        _server->on("/", HTTP_GET, [this](AsyncWebServerRequest *request){
            request->send(LittleFS, "/index.html", "text/html", false, [this](const String& var)
            {
                if (var == "IP_ADDRESS")
                {
                    return String(_status.IpAddress);
                }
                return String();
            });
        });

        _server->on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
            request->send(LittleFS, "/style.css", "text/css");
        });
    }

    void Server::Begin()
    {
       _server->begin();
    }
}