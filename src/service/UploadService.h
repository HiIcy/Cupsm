#ifndef __UPLOADSERVICE__H__
#define __UPLOADSERVICE__H__
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/client_simple.hpp>

class Service
{
private:
    // TODO: 用户名通过get方式获取
	// xmlrpc_c::paramList paramLst;
public:
    std::string method;
    std::string userName;
    std::string passWd;
    std::string blogAddr;
    std::string url;

    xmlrpc_c::clientSimple myClient;

    Service(const std::string& _userName,
                 const std::string& _passWd,
                 const std::string& _blogAddr,
                 const std::string& _url);
    //virtual int UpBlog();
    ~Service();
};


class CnBlog : public Service {
private:
    std::string blogId;
public:
    CnBlog(const std::string& _userName,
                 const std::string& _passWd,
                 const std::string& _blogAddr,
                 const std::string& _url):
        Service(_userName, _passWd, _blogAddr, _url){}

    int UpBlog(std::map<std::string, std::string>&  nPost);
    int UpBlog(std::map<std::string, xmlrpc_c::value>&  nPost);
    std::string NewMediaObj(const std::string& ss);
    std::string NewMediaObj(std::ifstream& ift);
    void GetUserBlogs();
};


#endif // !__UPLOADSERVICE__H__
