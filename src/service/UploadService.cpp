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
