#include <sys/time.h>

#include <stdexcept>
#include <stdio.h>

#include "inject_utimes.h"

UtimesInjectPlugin::~UtimesInjectPlugin() {}

void UtimesInjectPlugin::inject(const std::vector<std::string>& paths)
{
    FILE *fp;
    for (const auto& path : paths) {
        fp=fopen (path.c_str(), "r");
	if (fp != NULL) {
		fclose(fp);
	}
    }
}
