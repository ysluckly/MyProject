#include "udp_client.h"

void Usage(std::string proc)
{
  std::cout<<"Usage"<<proc<< "ip port"<<std::endl;
}
//./chatclient  ip  8000
int main(int argc,char* argv[])
{
  if(argc!=3)
  {
    Usage(argv[0]);
    return 1;
  }

  udp_client cli(argv[1],atoi(argv[2]));
  cli.init_client();

  std::string message;
  while(1)
  {
    std::cout<<"Please Enter#";
    std::cin>>message;
    cli.send_data(message);

  }
  return 0;
}
