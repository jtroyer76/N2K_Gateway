#include "HalFs.h"
#include "HalFile.h"

#include <stdint.h>
#include <stddef.h>

#include "LittleFS.h"
#include "LittleFsFile.h"

namespace N2kGateway
{
    namespace Hal
    {
        bool FsExists(const char* path)
        {
            return LittleFS.exists(path);
        }

        std::shared_ptr<HalFile> FsOpen(const char* path, const char* mode, const bool create)
        {
            return std::shared_ptr<HalFile>(new LittleFsFile(LittleFS.open(path, mode, create)));
        }
    }
}