#include <string>
#include <cstdlib>


namespace http {
    struct url {
        std::string protocol, user, password, host, path, query, fragment, port;
    };


    //--- Helper Functions -------------------------------------------------------------~
    static inline std::string TailSlice(std::string &subject, std::string delimiter, bool keep_delim=false) {
        // Chops off the delimiter and everything that follows (destructively)
        // returns everything after the delimiter
        size_t delimiter_location = subject.find(delimiter);
        size_t delimiter_length = delimiter.length();
        std::string output = "";

        if (delimiter_location < std::string::npos) {
            size_t start = keep_delim ? delimiter_location : delimiter_location + delimiter_length;
            size_t end = subject.length() - start;
            output = subject.substr(start, end);
            subject = subject.substr(0, delimiter_location);
        }
        return output;
    }

    static inline std::string HeadSlice(std::string &subject, std::string delimiter) {
        // Chops off the delimiter and everything that precedes (destructively)
        // returns everthing before the delimeter
        size_t delimiter_location = subject.find(delimiter);
        size_t delimiter_length = delimiter.length();
        std::string output = "";
        if (delimiter_location < std::string::npos) {
            output = subject.substr(0, delimiter_location);
            subject = subject.substr(delimiter_location + delimiter_length, subject.length() - (delimiter_location + delimiter_length));
        }
        return output;
    }


    //--- Extractors -------------------------------------------------------------------~
    static inline std::string ExtractPort(std::string &hostport) {
        std::string portstring = TailSlice(hostport, ":");
        return  portstring;
    }

    static inline std::string ExtractPath(std::string &in) { return TailSlice(in, "/", true); }
    static inline std::string ExtractProtocol(std::string &in) { return HeadSlice(in, "//"); }
    static inline std::string ExtractQuery(std::string &in) { return TailSlice(in, "?"); }
    static inline std::string ExtractPassword(std::string &userpass) { return TailSlice(userpass, ":"); }
    static inline std::string ExtractUserpass(std::string &in) { return HeadSlice(in, "@"); }


    //--- Public Interface -------------------------------------------------------------~
    static inline url ParseHttpUrl(std::string &in) {
        url ret;

        ret.protocol = ExtractProtocol(in);
        ret.query = ExtractQuery(in);
        size_t fragmentPos = ret.query.find("#");
        if (fragmentPos < std::string::npos) {
            ret.fragment = ret.query.substr(fragmentPos + 1, ret.query.length());
            ret.query = ret.query.substr(0, fragmentPos);
        }
        ret.path = ExtractPath(in);
        std::string userpass = ExtractUserpass(in);
        ret.password = ExtractPassword(userpass);
        ret.user = userpass;
        ret.port = ExtractPort(in);
        if (!ret.protocol.empty()) {
            ret.host = in;
        } else if (ret.path.empty()) {
            ret.path = in;
        }
        return ret;
    }
}
