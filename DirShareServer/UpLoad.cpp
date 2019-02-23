#include "Utils.hpp"

int main()
{
  std::string rsp_body;                                                                                                        
  rsp_body = "<html><body><h1> UpLoad Success!!!</h1></body></html>";               
  LOG("File rsp:[%s]\n",rsp_body.c_str());

  fflush(stdout);
  return 0;
}
