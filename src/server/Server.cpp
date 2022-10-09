#include "Server.h"
#include <ArduinoJson.h>
#include <LittleFS.h>

namespace N2kGateway
{
    Server::Server(const Configuration &config) : _config(config)
    {
        _server = new AsyncWebServer(80);
        
        // Initialize webserver URLs
        const JsonDocument &doc = _config.Config();
        _server->on("/api", HTTP_GET, [&doc](AsyncWebServerRequest *request)
        {
            AsyncResponseStream *response = request->beginResponseStream("application/json");
            serializeJson(doc, *response);
            request->send(response); 
        });

        // Routes for web page
        _server->on("/", HTTP_GET, [](AsyncWebServerRequest *request){
            request->send(LittleFS, "/index.html", String(), false);
        });

        _server->on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
            request->send(LittleFS, "/style.css","text/css");
        });
    }

    void Server::Begin()
    {
       _server->begin();
    }
}