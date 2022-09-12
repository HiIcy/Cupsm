#include <string>
#include <vector>
#include "command.h"

using namespace std;
cmdline::parser getParser(int argc, char *argv[])
{
    cmdline::parser args;
    args.add<string>("site", 's', "which blog to upload", false, "cnblog");
    args.add<string>("file", 'f', "file path to be upload", true, "");
    args.add<string>("category", 'c', "Which category do blogs fall into", false, "");

    args.add<bool>("dir", 'd', "whether upload dir or not", false, false);
    //args.add<vector<string>>("tag", 't', "Which tag do blogs fall into", false, vector<string>());
    args.add<string>("tag", 't', "Which tag do blogs fall into", false, "");

    args.set_program_name("Cup");
    args.parse_check(argc, argv);
    return args;
}
