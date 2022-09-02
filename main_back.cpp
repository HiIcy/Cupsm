#include <string>
#include <iostream>
#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/client_simple.hpp>

using namespace std;
using namespace xmlrpc_c;

class XMLRPCSERVICE {
public:
    XMLRPCSERVICE() = default;
    void init(){
	string const serverUrl(this->url);
	string const methodName(this->method);
	
	xmlrpc_c::clientSimple myClient;
	xmlrpc_c::value result;
	xmlrpc_c::paramList paramLst;

	paramLst.add(value_string(this->blog_addr));
	paramLst.add(value_string(this->username));
	paramLst.add(value_string(this->passwd));
	
	myClient.call(serverUrl, methodName, paramLst, &result);
        string const blogid = value_string(value_struct(value_array(result).vectorValueValue()[0]).cvalue()["blogid"]);
        std::cout<<"blogid: "<<blogid<<"\n";

    }
private:
    string method = "blogger.getUsersBlogs";
    string url = "https://rpc.cnblogs.com/metaweblog/rnly";
    string username = "HiIcy"; 
    // metaweblog 更改访问方式用令牌！
    string passwd = "246A4C29B93EC8D263AAB0DCA152F3079F9061F86D3B3AFE86900A37B1E2C619";
    string blog_addr = "rnly";
    string blogid;
};

int main(){
    XMLRPCSERVICE xs;
    xs.init();
    return 0;
}
      
