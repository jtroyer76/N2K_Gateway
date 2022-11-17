#pragma once

#include <ESPAsyncWebServer.h>

#include "config\Configuration.h"
#include "data\Status.h"

namespace N2kGateway
{   
    class Server
    {
        const Configuration &_config;
        const Status &_status;
        AsyncWebServer *_server;

    public:
        Server(const Configuration &config, const Status &status);
        void Begin();
    };
}