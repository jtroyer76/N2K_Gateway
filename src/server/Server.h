#pragma once

#include <ESPAsyncWebServer.h>

#include "config\Configuration.h"

namespace N2kGateway
{
    class Server
    {
        const Configuration &_config;
        AsyncWebServer *_server;

    public:
        Server(const Configuration &config);
        void Begin();
    };
}