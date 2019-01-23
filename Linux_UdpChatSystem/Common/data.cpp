#include "data.h"


data::data()
{

}

void data::order(std::string & out_string)
{
  Json::Value root; 
  root["nick_name"] = nick_name;
  root["school"] = school;
  root["message"] = message; 
  root["type"] = type;

  //序列化
  Json::FastWriter w; //StyleWrite 会有更好的格式，就是加了换行符
  out_string = w.write(root);

}

void data::unorder(std::string& in_string)
{
  //反序列
  Json::Value root;
  Json::Reader r;
  r.parse(in_string,root,false);
  //提取数据
  nick_name = root["nick_name"].asString();
  school = root["school"].asString();
  message = root["message"].asString();
  type = root["type"].asString();


}
data::~data()
{

}

/*测试序列化
 * 
 * int main()
 * {
 *  data d;
 *  d.nick_name = "Hunter";
 *  d.school = "xust";
 *  d.message = "nihao";
 *  d.type = "None";
 *  std::string out_string;
 *  d.order(std::string& out_string);
 *  
 *  std::cout<<out_string<<std::endl;
 *  
 * }
 * */
