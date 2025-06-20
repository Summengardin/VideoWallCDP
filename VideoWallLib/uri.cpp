#include "uri.h"
#include <regex>

namespace VideoWallLib {

Uri::Uri()
{
}

Uri::Uri(const std::string& uri)
{
    this->parse(uri);
}

bool Uri::parse(const std::string& u) {
    uri = u;
    // Pattern breakdown:
    // ^([^:/?#]+):           - scheme (required, ends with :)
    // (?://                  - authority section (optional, starts with //)
    //   (?:([^:/?#@]*)       - user (optional)
    //     (?::([^@/?#]*))?   - password (optional, preceded by :)
    //     @)?                - @ separator for user:pass
    //   ([^:/?#]*)           - host
    //   (?::([0-9]+))?       - port (optional, numeric)
    // )?                     - end of authority section
    // ([^?#]*)               - path
    // (?:\?([^#]*))?         - query (optional, starts with ?)
    // (?:#(.*))?$            - fragment (optional, starts with #)
    std::regex pattern(
        R"(^([^:/?#]+):(?://(?:([^:/?#@]*)(?::([^@/?#]*))?@)?([^:/?#]*)(?::([0-9]+))?)?([^?#]*)(?:\?([^#]*))?(?:#(.*))?$)"
        );
    std::smatch m;

    if (!std::regex_match(uri, m, pattern))
        return false;

    scheme   = m[1].str();
    user     = m[2].str();
    password = m[3].str();
    host     = m[4].str();
    if (m[5].matched) port = std::stoi(m[5].str());
    path     = m[6].matched ? m[6].str() : "/";
    query    = m[7].str();
    fragment = m[8].str();
    return true;
}

std::string Uri::toString() const {
    std::string out = scheme + "://";

    if (!user.empty()) {
        out += user;
        if (!password.empty()) out += ":" + password;
        out += "@";
    }

    out += host;

    if (port != -1) {
        out += ":" + std::to_string(port);
    }

    out += path;

    if (!query.empty()) {
        out += "?" + query;
    }

    if (!fragment.empty()) {
        out += "#" + fragment;
    }

    return out;
}

std::string Uri::toStringExtended() const {
    std::string out;
    out += "uri: "       + uri;
    out += " scheme: "   + scheme;
    out += " user: "     + user;
    out += " password: " + password;
    out += " host: "     + host;
    out += " port: "     + std::to_string(port);
    out += " path: "     + path;
    out += " query: "    + query;
    out += " fragment: " + fragment ;

    return out;
}

} // namespace VideoWallLib
