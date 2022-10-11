#include "Server.h"
#include "AsyncJson.h"
#include <ArduinoJson.h>
#include <LittleFS.h>

namespace N2kGateway
{
    Server::Server(const Configuration &config) : _config(config)
    {
        _server = new AsyncWebServer(80);
        
        // API get
        const JsonDocument &doc = _config.Config();
        _server->on("/api", HTTP_GET, [&doc](AsyncWebServerRequest *request)
        {
            AsyncResponseStream *response = request->beginResponseStream("application/json");
            serializeJson(doc, *response);
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