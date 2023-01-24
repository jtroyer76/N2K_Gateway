#pragma once

#include "HalFile.h"

#include <memory>

namespace N2kGateway
{
    namespace Hal
    {
        bool FsExists(const char* path);
        std::shared_ptr<HalFile> FsOpen(const char* path, const char* mode, const bool create);
    }
}