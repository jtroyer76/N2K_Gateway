#pragma once

#include <stdint.h>
#include <stddef.h>

namespace N2kGateway
{
    namespace Hal
    {
        class HalFile
        {
        public:
            virtual size_t Write(const uint8_t *buf, size_t size) = 0;
            virtual size_t Read(uint8_t *buf, size_t size) = 0;
            virtual void Close() = 0;
        };
    }
}