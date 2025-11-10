#define _CRT_SECURE_NO_WARNINGS  // disables localtime() warning
#include "utils.h"
#include <ctime>
#include <sstream>
#include <iomanip>

std::string getCurrentTime() {
    std::time_t now = std::time(nullptr);
    std::tm localTime{};
    localtime_s(&localTime, &now); // Windows-safe version

    std::ostringstream oss;
    oss << std::put_time(&localTime, "%Y-%m-%d %H:%M");
    return oss.str();
}
