#include <fstream>
#include <vector>
#include "UploadService.h"


using namespace xmlrpc_c;

Service::Service(const std::string& _userName,
                 const std::string& _passWd,
                 const std::string& _blogAddr,
                 const std::string& _url):
    userName(std::move(_userName)),
    passWd(std::move(_passWd)),
    blogAddr(std::move(_blogAddr)),
    url(std::move(_url))
{
    std::cout<<"service init"<<std::endl;
}

Service::~Service()
{
}

void CnBlog::GetUserBlogs()
{
    xmlrpc_c::value result;
    xmlrpc_c::paramList paramLst;
    paramLst.add(value_string(this->blogAddr));
    paramLst.add(value_string(this->userName));
    paramLst.add(value_string(this->passWd));
    this->myClient.call(this->url, "blogger.getUsersBlogs", paramLst, &result);
    std::string const blogId = value_string(value_struct(
                value_array(result).vectorValueValue()[0]
            ).cvalue()["blogid"]);
    std::cout<<"blogid: "<<blogId<<"\n";
    this->blogId = std::move(blogId);
}

// TODO: 泛型思考
int CnBlog::UpBlog(std::map<std::string, std::string>& nPost)
{
    xmlrpc_c::value result;
    xmlrpc_c::paramList paramLst;
    paramLst.add(value_string(this->blogId));
	paramLst.add(value_string(this->userName));
	paramLst.add(value_string(this->passWd));
    std::map<std::string, xmlrpc_c::value> ncPost;
    std::map<std::string, std::string>::iterator nPostIt = nPost.begin();
    for(; nPostIt != nPost.end(); nPostIt++) {
        ncPost.emplace(std::map<std::string, xmlrpc_c::value>::value_type(
                                        (*nPostIt).first,
                                        value_string((*nPostIt).second)));
    }
    paramLst.add(value_struct(ncPost));
    paramLst.add(value_boolean(true));

    this->myClient.call(this->url, "metaWeblog.newPost", paramLst, &result);

    return 0;
}

int CnBlog::UpBlog(std::map<std::string, xmlrpc_c::value>& nPost) //TODO: 这里参数可以直接改成value_struct
{
    xmlrpc_c::value result;
    xmlrpc_c::paramList paramLst;
    paramLst.add(value_string(this->blogId));
	paramLst.add(value_string(this->userName));
	paramLst.add(value_string(this->passWd));
 
    paramLst.add(value_struct(nPost));
    paramLst.add(value_boolean(true));

    this->myClient.call(this->url, "metaWeblog.newPost", paramLst, &result);

    return 0;
}

std::string CnBlog::NewMediaObj(std::ifstream& ifs)
{
    xmlrpc_c::value result;
    xmlrpc_c::paramList paramLst;
    paramLst.add(value_string(this->blogId));
    paramLst.add(value_string(this->userName));
	paramLst.add(value_string(this->passWd));

    // REW: 字节流读写
    ifs.seekg(0, std::ios::end);
    int64_t f_size = ifs.tellg();
    uint8_t* byteBuf = new uint8_t[f_size]; // REW: 一个字节8个位，正好对应char, uint_8这些一个字节的数据类型
    ifs.seekg(0, std::ios::beg);
    ifs.read((char*)byteBuf, f_size);

    std::vector<unsigned char> fbytes(byteBuf, byteBuf + f_size);
    xmlrpc_c::value_bytestring cfbytes(fbytes);

    std::map<std::string, xmlrpc_c::value> media_obj = {
        {"bits", cfbytes},
        {"name", value_string("red.jpg")},
        {"type", value_string("image/jpg")},
    };

    paramLst.add(value_struct(media_obj));

    this->myClient.call(this->url, "metaWeblog.newMediaObject", paramLst, &result);
    std::string media_url = value_string(value_struct(result).cvalue()["url"]);// 这里有隐式转换
    std::cout << "media_url: " << media_url << std::endl;
    delete[] byteBuf;
    return media_url;
}

std::string CnBlog::NewMediaObj(const std::string& ss)
{
    std::ifstream ifs(ss, std::ios::binary);
    return NewMediaObj(ifs);
}