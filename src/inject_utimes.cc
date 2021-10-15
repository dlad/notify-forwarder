#include <sys/time.h>

#include <stdexcept>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>

#include "inject_utimes.h"

UtimesInjectPlugin::~UtimesInjectPlugin() {}

void UtimesInjectPlugin::inject(const std::vector<std::string>& paths)
{
    FILE *fp;
    struct stat buffer;
    int status;

    for (const auto& path : paths) {
        // zero struct to clear out old data
        memset(&buffer, 0, sizeof(buffer));

        status = stat(path.c_str(), &buffer);
        if (status != 0) {
            // stat did not work - maybe file does not exist
            continue;
        }

        if (!S_ISREG(buffer.st_mode)) {
            // file is not a regular file
            // this will exclude directories
            continue;
        }

        // apply the existing permissions as just read in
        chmod(path.c_str(), buffer.st_mode);
    }
}
