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

    string content = R"(
\d                   匹配数字
\D                   \D如果开启了re.ASCII,只匹配 [^0-9]                                       
\w                   匹配word(数字、字母)                                        
\W                   匹配非word(数字、字母)                                    
\s                   匹配white space(包括空格、tab等)
\S                   匹配非white space(包括空格、tab等)
.                    匹配除换行符 \n 之外的任何单字符
*                    代表前面的表达式必须至少出现一次
+                    1个或更多，至少1个
^                    匹配一行的开头.(方括号表达式中使用，此时它表示不接受该字符集合)(如果设置了re.MULTILINE标志，‘^’也匹配换行符之后的位置)
$                    匹配一行的结尾(如果设置了 RegExp 对象的 Multiline 属性，则 $ 也匹配 '\n' 或 '\r')
\b                   单词"结界"(word bounds)
?                    0个或1个(非贪婪限定符)
[a-z-=]              匹配里面的任意一个字符 (这里面会对那些特殊字符自动转义如+、*等)
|	                 指明两项之间的一个选择(或)
{min,max}            前面表达式出现的次数在一个范围内
{n,}                 加逗号，表示至少n次，去掉逗号，表示匹配n次
\A                   匹配输入字符串的开始位置
\z                   匹配输入的结束位置(哪结束看哪，不看符号)
\Z                   输入的结尾位置(可以有结尾符号或没得），但是字符串的结尾可以有也可以没有终止子
()                   组表达式(可以被\数字再次引用)
(?P<name>)           命名组
(?P=name)            它匹配指定命名组匹配的任何内容
(?=...)              前向零宽断言;# love(?=FishC) 只匹配后面跟着FishC的字符串
(?<=...)             后向零宽断言
(?!...)              前向否定断言
(?<!...)             后向否定断言
(?:...)              非捕获组，该组匹配的无法后面获取
\U                   将匹配项转为大写(Upper)
\L                   将匹配项转为小写(Lower)
\E                   终止转换,转换从\U或\L开始到\E结束之间的字母大小写类型.(End)


单行模式（single-line mode），此时，^ 和 $ 只能匹配整一个输入序列的开始和结束位置

编译标志:
ASCII,A使得转义符号\w,\b,\s,\d只能匹配ASCII字符

DOTALL,S使得‘.’匹配任何符号，包括换行符

IGNORECASE,I匹配的时候不区分大小写

LOCALE,L支持当前的语言（区域）设置

MULTILINE,M多行匹配，影响^$

Go 正则：http://c.biancheng.net/view/5124.html
-----------------------

group == group(0)，返回：匹配的字符串
groups 返回: 元组
str
pattern
res = re.search(pattern,str)
res.group()
)";
    // vector<xmlrpc_c::value> categories({value_string("Markdown")});
    // xmlrpc_c::value_array vecCategories(categories);
    // map<string, xmlrpc_c::value> nPost = {
    //     {"title", value_string("正则表达式拾遗")},
    //     {"description", value_string(content)},
    //     {"categories", vecCategories},
    //     {"mt_keywords", value_string("工具技巧")}
    // };

    return 0;
}
