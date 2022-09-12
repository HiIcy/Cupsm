#include <string>
#include <map>
#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/client_simple.hpp>
#include "../service/UploadService.h"

class Utils {
public:
    static Utils* getInstance();
    bool checkFile(std::string);
    std::map<std::string, xmlrpc_c::value> parseMd(CnBlog& cb, const std::string&, const std::vector<std::string>&);
    void imgRejg(CnBlog& cb, std::string&  content);
};


std::string& wuReplace(std::string& s, const std::string& pattern, const std::string& mod);
std::string& wuReplaceAll(std::string& s, const std::string& pattern, const std::string& mod);