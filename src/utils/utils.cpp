#include <experimental/filesystem>
#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <thread>
#include <queue>
#include "utils.h"

using namespace std;
using namespace std::experimental::filesystem;
using namespace xmlrpc_c;

//static vector<xmlrpc_c::value> categories({value_string("Markdown")});
//const static xmlrpc_c::value_array vecCategories(categories);

Utils* Utils::getInstance()
{
    static Utils instance;
    return &instance;
}

bool Utils::checkFile(string s)
{
    path p(s);
    if (!exists(p)) {
        cout<<"file path isn't exists!"<<endl;
        return false;
    }
    if(is_directory(p)) {
        cout<<"file path is directory"<<endl;
        return false;
    }
    return true;
}

// TODO: 多个tag

string& wuReplace(string& s, const string& pattern, const string& mod)
{
    s.replace(s.find(pattern), pattern.length(), mod);
    return s;
}

string& wuReplaceAll(string& s, const string& pattern, const string& mod)
{
    size_t s_size = s.size();
    size_t pos = s.find(pattern);
    while(pos != std::string::npos){
        s.replace(pos, pattern.length(), mod);
        pos += mod.length();
        pos = s.find(pattern, pos);
    }
}

/*
template<class T>
auto sliceFirst(T& t) -> decltype(T) 
{
    T tmp(t);
    return tmp;
}
template<class T, class ...Args>
auto sliceFirst(T& t, Args&... args) -> decltype(Args)
{
    T tmp(t);
    return tmp;
}
*/
// TODO: 
// template<class ...Args> // REW: 可变参数只能通过模板定义; 逗号表达式，递归，c++17的折叠表达式.
// map<string, xmlrpc_c::value> Utils::parseMd(const string& s, const Args&... params)
// {
//     string title;
//     string tag; // TODO 多tag
//     path filePath(s);
//     int64_t lenFileInfo = sizeof...(params);
//     string tempFile(s);
//     wuReplace(tempFile, "\\", "/");

//     switch (lenFileInfo) {
//         case 0:
//             // 文件名不带扩展
//             title = filePath.stem();
//             break;
//         case 1:
//             title = static_cast<string>(sliceFirst(params));
//     }
// }


map<string, xmlrpc_c::value> Utils::parseMd(CnBlog& cb, const string& s, const vector<string>& params)
{
    string title;
    string tag; // TODO 多tag
    path filePath(s);
    int64_t lenFileInfo = params.size();
    // string tempFile(s);
    // wuReplace(tempFile, "\\", "/");

    switch (lenFileInfo) {
        case 0:
            // 文件名不带扩展
            title = filePath.stem();
            break;
        case 1:
            title = params[0];
            break;
        case 2:
            title = params[0];
            tag = params[1];
            break;
    }
    ifstream ifs(s);
    string content((istreambuf_iterator<char>(ifs)), 
                     (istreambuf_iterator<char>()) );
    // TODO: 图片上传
    
    this->imgRejg(cb, content);

    vector<xmlrpc_c::value> categories({value_string("[Markdown]")});
    xmlrpc_c::value_array vecCategories(categories);
    map<string, xmlrpc_c::value> nPost = {
        {"title", value_string(title)},
        {"description", value_string(content)},
        {"categories", vecCategories},
        {"mt_keywords", value_string(tag)}
    };
    return nPost;
}

// FAQ: 为撒这里用const没有提示
static void NewMediaObj(CnBlog& cb, string& local_img)
{
    if (!Utils::getInstance()->checkFile(local_img)) {
        cout<<local_img<<" "<<"is invalid, please check!\n";
        return;
    }
    string remote_url = cb.NewMediaObj(local_img);
}

void Utils::imgRejg(CnBlog& cb, string&  content)
{
    string str = R"(!\[\w*\]\((.*?\.jpg|jpeg|png)\))";
    regex pattern(str);
    smatch result;
    vector<string> local_imgs;
    auto cpos = content.cbegin();
    auto cend = content.cend();
    while(regex_search(cpos, cend, result, pattern)) {
        cout<<"reg img: "<<result.str(1)<<endl;
        if (std::find(local_imgs.begin(), local_imgs.end(), result.str(1)) == local_imgs.end()) {
            local_imgs.emplace_back(result.str(1));
        }
        cpos = result[0].second;
    }
    if (local_imgs.empty()) {
        return;
    }
    map<string, string> remote_imgs;
    int len_local = local_imgs.size();
    thread *push_medias = new thread[len_local];

    for(int i = 0; i < len_local; i++) {
        // push_medias[i] = thread(&CnBlog::NewMediaObj, cb, std::ref(local_imgs[i]));
        push_medias[i] = thread([&](const string& local_img){
            if (!this->checkFile(local_img)) {
                cout<<local_img<<" "<<"is invalid, please check!\n";
                return;
            }
            string remote_url = cb.NewMediaObj(local_img);
            map<string, string> map_url{{local_img, remote_url}};
            remote_imgs[local_img] = remote_url;
        }, std::ref(local_imgs[i]));
    }
    for(int i = 0; i < len_local; i++) {
        push_medias[i].join();
    }

    map<string, string>::iterator rit = remote_imgs.begin();
    while(rit != remote_imgs.end()) {
        auto local_url = (*rit).first;
        auto remote_url = (*rit).second;
        wuReplaceAll(content, local_url, remote_url);
        rit++;
    }

}