#pragma once 
#include <iostream>
#include <string>
#include <json/json.h>
/*//jsoncpp序列化
 *nick_name(zs),school(xust),message("nihao"),type("None") --->
 *  "{nick_name:"zs",school:"xust",message:"nihao",type:"None"}"
 *  反序列化
 */

class data
{
  public:
    data();

    //序列化：将四个字段信息I打包
    void order(std::string& out_string);//输出型参数
    //反序列化：解包
    void unorder(std::string& in_string);
    ~data();

  private:
    std::string nick_name;//昵称
    std::string school;
    std::string message;
    std::string type;   //保留字段，如ipv6
};
