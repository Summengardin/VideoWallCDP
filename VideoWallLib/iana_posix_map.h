#ifndef VIDEOWALLLIB_IANA_POSIX_MAP_H
#define VIDEOWALLLIB_IANA_POSIX_MAP_H

#include <map>
#include <string>
#include <cstdlib>   // strtol, getenv, setenv
#include <cctype>
#include <cstdio>    // snprintf
#include <cmath>

namespace VideoWallLib {


#if defined(_MSC_VER) && _MSC_VER < 1900
#  define snprintf _snprintf
#endif

namespace tzmap_legacy {

// IANA -> POSIX rules
inline const std::map<std::string, const char*> kIanaToPosix = {
    // UTC / GMT
    {"UTC", "UTC0"}, {"Etc/UTC", "UTC0"}, {"Etc/Greenwich", "UTC0"}, {"GMT", "GMT0"}, {"Etc/GMT", "GMT0"},

    // North America
    {"America/New_York", "EST5EDT,M3.2.0/2,M11.1.0/2"},
    {"America/Detroit",  "EST5EDT,M3.2.0/2,M11.1.0/2"},
    {"America/Toronto",  "EST5EDT,M3.2.0/2,M11.1.0/2"},
    {"America/Chicago",  "CST6CDT,M3.2.0/2,M11.1.0/2"},
    {"America/Winnipeg", "CST6CDT,M3.2.0/2,M11.1.0/2"},
    {"America/Denver",   "MST7MDT,M3.2.0/2,M11.1.0/2"},
    {"America/Edmonton", "MST7MDT,M3.2.0/2,M11.1.0/2"},
    {"America/Phoenix",  "MST7"},
    {"America/Los_Angeles","PST8PDT,M3.2.0/2,M11.1.0/2"},
    {"America/Vancouver", "PST8PDT,M3.2.0/2,M11.1.0/2"},
    {"America/Anchorage", "AKST9AKDT,M3.2.0/2,M11.1.0/2"},
    {"America/Adak",      "HST10HDT,M3.2.0/2,M11.1.0/2"},
    {"Pacific/Honolulu",  "HST10"},

    // Latin America (mostly no DST)
    {"America/Mexico_City", "CST6"},
    {"America/Bogota",      "COT5"},
    {"America/Lima",        "PET5"},
    {"America/Sao_Paulo",   "BRT3"},
    {"America/Argentina/Buenos_Aires", "ART3"},
    {"America/Caracas",     "VET4"},
    {"America/Santiago",    "CLT4CLST,M9.1.0/0,M4.1.0/0"},

    // Europe (EU DST rule)
    {"Europe/Oslo",      "CET-1CEST,M3.5.0/2,M10.5.0/3"},
    {"Europe/Berlin",    "CET-1CEST,M3.5.0/2,M10.5.0/3"},
    {"Europe/Paris",     "CET-1CEST,M3.5.0/2,M10.5.0/3"},
    {"Europe/Madrid",    "CET-1CEST,M3.5.0/2,M10.5.0/3"},
    {"Europe/Rome",      "CET-1CEST,M3.5.0/2,M10.5.0/3"},
    {"Europe/Amsterdam", "CET-1CEST,M3.5.0/2,M10.5.0/3"},
    {"Europe/Copenhagen","CET-1CEST,M3.5.0/2,M10.5.0/3"},
    {"Europe/Stockholm", "CET-1CEST,M3.5.0/2,M10.5.0/3"},
    {"Europe/Prague",    "CET-1CEST,M3.5.0/2,M10.5.0/3"},
    {"Europe/Vienna",    "CET-1CEST,M3.5.0/2,M10.5.0/3"},
    {"Europe/Warsaw",    "CET-1CEST,M3.5.0/2,M10.5.0/3"},
    {"Europe/Zurich",    "CET-1CEST,M3.5.0/2,M10.5.0/3"},
    {"Europe/Brussels",  "CET-1CEST,M3.5.0/2,M10.5.0/3"},

    {"Europe/Lisbon",    "WET0WEST,M3.5.0/1,M10.5.0/2"},
    {"Atlantic/Canary",  "WET0WEST,M3.5.0/1,M10.5.0/2"},
    {"Europe/London",    "GMT0BST,M3.5.0/1,M10.5.0/2"},

    {"Europe/Helsinki",  "EET-2EEST,M3.5.0/3,M10.5.0/4"},
    {"Europe/Athens",    "EET-2EEST,M3.5.0/3,M10.5.0/4"},
    {"Europe/Bucharest", "EET-2EEST,M3.5.0/3,M10.5.0/4"},
    {"Europe/Kyiv",      "EET-2EEST,M3.5.0/3,M10.5.0/4"},

    {"Europe/Istanbul",  "TRT-3"},
    {"Europe/Moscow",    "MSK-3"},

    // Africa
    {"Africa/Lagos",        "WAT-1"},
    {"Africa/Algiers",      "CET-1"},
    {"Africa/Johannesburg", "SAST-2"},
    {"Africa/Nairobi",      "EAT-3"},
    {"Africa/Cairo",        "EET-2"},
    {"Africa/Casablanca",   "WET0"},

    // Middle East / Asia
    {"Asia/Jerusalem",   "IST-2IDT,M3.5.0/2,M10.5.0/2"},
    {"Asia/Beirut",      "EET-2EEST,M3.5.0/0,M10.5.0/0"},
    {"Asia/Dubai",       "GST-4"},
    {"Asia/Tehran",      "IRST-3:30"},
    {"Asia/Baghdad",     "AST-3"},
    {"Asia/Jeddah",      "AST-3"},
    {"Asia/Tbilisi",     "GET-4"},
    {"Asia/Baku",        "AZT-4"},
    {"Asia/Yerevan",     "AMT-4"},
    {"Asia/Tashkent",    "UZT-5"},
    {"Asia/Karachi",     "PKT-5"},
    {"Asia/Kolkata",     "IST-5:30"},
    {"Asia/Dhaka",       "BDT-6"},
    {"Asia/Bangkok",     "ICT-7"},
    {"Asia/Ho_Chi_Minh", "ICT-7"},
    {"Asia/Jakarta",     "WIB-7"},
    {"Asia/Shanghai",    "CST-8"},
    {"Asia/Hong_Kong",   "HKT-8"},
    {"Asia/Taipei",      "CST-8"},
    {"Asia/Singapore",   "SGT-8"},
    {"Asia/Tokyo",       "JST-9"},
    {"Asia/Seoul",       "KST-9"},

    // Oceania
    {"Australia/Brisbane", "AEST-10"},
    {"Australia/Sydney",   "AEST-10AEDT,M10.1.0/2,M4.1.0/3"},
    {"Australia/Melbourne","AEST-10AEDT,M10.1.0/2,M4.1.0/3"},
    {"Australia/Adelaide", "ACST-9:30ACDT-10:30,M10.1.0/2,M4.1.0/3"},
    {"Australia/Darwin",   "ACST-9:30"},
    {"Australia/Perth",    "AWST-8"},
    {"Pacific/Auckland",   "NZST-12NZDT,M9.5.0/2,M4.1.0/3"},
    {"Pacific/Guam",       "ChST-10"},
    {"Pacific/Port_Moresby","PGT-10"},
    {"Pacific/Fiji",       "FJT-12FJST,M11.2.0/2,M1.2.0/3"},
    };

// Parse fixed-offset “Etc/GMT±H[:MM]”. Returns true and sets `out` on success.
inline bool posixFromEtcGMT(const std::string& s, std::string& out) {
    const std::string prefix = "Etc/GMT";
    if (s.compare(0, prefix.size(), prefix) != 0) return false;
    if (s.size() == prefix.size()) { out = "UTC0"; return true; }

    char sign = s[prefix.size()];
    if (sign != '+' && sign != '-') return false;

    std::string rest = s.substr(prefix.size() + 1);
    if (rest.empty()) return false;

    char* endp = NULL;
    long hours = std::strtol(rest.c_str(), &endp, 10);
    if (endp == rest.c_str() || hours < 0 || hours > 24) return false;

    long minutes = 0;
    if (*endp == ':') {
        char* endp2 = NULL;
        minutes = std::strtol(endp + 1, &endp2, 10);
        if (endp2 == endp + 1 || minutes < 0 || minutes >= 60) return false;
        endp = endp2;
    }
    if (*endp != '\0') return false;

    long total = hours * 60 + minutes;

    // IANA “Etc/GMT+H” means actual offset = UTC-H (west). Reverse sign first:
    long actual_minutes = (sign == '+') ? -total : total;
    // POSIX offset = UTC - local
    long posix_minutes = -actual_minutes;

    int off_h = static_cast<int>(posix_minutes / 60);
    int off_m = std::abs(static_cast<int>(posix_minutes % 60));

    char buf[32];
    if (off_m == 0) snprintf(buf, sizeof(buf), "UTC%+d", off_h);
    else             snprintf(buf, sizeof(buf), "UTC%+d:%02d", off_h, off_m);

    out = buf;
    return true;
}

// Lookup that works without C++17
// Returns true and fills `out` if a mapping or fixed-offset was found.
inline bool iana_to_posix(const std::string& zone, std::string& out) {
    std::map<std::string, const char*>::const_iterator it = kIanaToPosix.find(zone);
    if (it != kIanaToPosix.end()) { out = it->second; return true; }

    if (posixFromEtcGMT(zone, out)) return true;

    if (zone == "Etc/Zulu" || zone == "Zulu") { out = "UTC0"; return true; }

    return false; // not found
}

} // namespace tzmap_legacy


} // namespace VideoWallLib

#endif // VIDEOWALLLIB_IANA_POSIX_MAP_H
