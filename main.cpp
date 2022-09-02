#include <iostream>
#include "src/service/UploadService.h"
#include "src/constants/constants.h"
int main()
{

    CnBlog cn(
        USER_NAME,
        PASSWD,
        BLOG_ADDR,
        URL);
    // init CnBlog
    cn.GetUserBlogs();
    
    return 0;
}
