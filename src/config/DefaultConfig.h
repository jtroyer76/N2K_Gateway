#pragma once

namespace N2kGateway
{
    char default_config[] = R"(
    {
        "wifi" : {
            "ssid": "bitfu2",
            "password": "J&TTroyer"
        },
        "display" : [
            {
                "type" : "SingleUnit",
                "data" : "depth",
                "unit" : "feet"
            },
            {
                "type" : "SingleUnit",
                "data" : "tws",
                "unit" : "knots"
            },
            {
                "type" : "Status"
            }
        ]
    }
    )";
}