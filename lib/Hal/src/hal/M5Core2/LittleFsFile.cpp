#include "LittleFsFile.h"

namespace N2kGateway
{
    namespace Hal
    {
        LittleFsFile::LittleFsFile(fs::File file) : _file(file)
        {
        }

        size_t LittleFsFile::Write(const uint8_t *buf, size_t size)
        {
            return _file.write(buf, size);
        }

        size_t LittleFsFile::Read(uint8_t *buf, size_t size)
        {
            return _file.read(buf, size);
        }

        void LittleFsFile::Close()
        {
            _file.close();
        }
    }
}