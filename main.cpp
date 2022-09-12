#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "src/service/UploadService.h"
#include "src/commands/command.h"
#include "src/utils/cmdline.h"
#include "src/utils/utils.h"
#include "src/constants/constants.h"
#include "xmlrpc-c/base.hpp"
#include "xmlrpc-c/client_simple.hpp"

using namespace std;
using namespace xmlrpc_c;

int main(int argc, char *argv[])
{
    CnBlog cn(
        USER_NAME,
        PASSWD,
        BLOG_ADDR,
        URL);
    cmdline::parser args = getParser(argc, argv);

    if (args.get<bool>("dir")){
        cout<<"sorry, we not' support apply dir param currently, coming soon, expected please!";
        return -1;
    }
    string md = args.get<string>("file");
    if (md.compare("") == 0) {
        cout<<"file can't be null"<<endl;
        return -1;
    }
    if (!Utils::getInstance()->checkFile(md)) {
        return -1;
    }
    vector<string> par;
    auto nPost = Utils::getInstance()->parseMd(cn, md, par);
    // init CnBlog
    cn.GetUserBlogs();
    cn.UpBlog(nPost);

    
    return 0;
}
