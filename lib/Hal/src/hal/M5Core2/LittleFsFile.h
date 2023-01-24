#pragma once

#include "HalFile.h"

#include <stdint.h>
#include <stddef.h>

#include "FS.h"

namespace N2kGateway
{
    namespace Hal
    {
        class LittleFsFile : public HalFile
        {
        public:
            LittleFsFile(fs::File file);
            size_t Write(const uint8_t *buf, size_t size);            
            size_t Read(uint8_t *buf, size_t size);
            void Close();

        private:
            fs::File _file;
        };
    }
}