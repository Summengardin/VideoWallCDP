#ifndef VIDEOWALLLIB_URI_H
#define VIDEOWALLLIB_URI_H

#include <string>
#include <iostream>

namespace VideoWallLib {

class Uri
{
public:
    std::string uri;
    std::string scheme;
    std::string user;
    std::string password;
    std::string host;
    int         port    = -1;      // -1 means “not specified”
    std::string path;
    std::string query;
    std::string fragment;

    bool parse(const std::string&);
    Uri();
    Uri(const std::string&);
    std::string toString() const;
    std::string toStringExtended() const;

    friend std::ostream& operator<<(std::ostream& os, const Uri& uri) {
        return os << uri.toString();
    }
};

} // namespace VideoWallLib

#endif // VIDEOWALLLIB_URI_H
