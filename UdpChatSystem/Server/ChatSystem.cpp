#include "udp_server.h"
#include <stdlib.h>
#include <pthread.h>

void Usage(std::string proc)
{
  std::cout <<"Usage:"<<proc<<"port"<<std::endl;
}

void* recv_massge(void* arg)
{
  udp_server* sp = (udp_server*)arg;
  std::string message;
  while(1)
  {
    sp->recv_data(message);
    std::cout<<"debug:"<<message<<std::endl;

  }
  
}

void* send_massge(void* arg)
{
  udp_server* sp = (udp_server*)arg;
  
  while(1)
  {   
    sp->broadcast();
  }
}
// ./chatsystem 8000
int main(int argc,char* argv[])
{
  if(argc!=2)
  {
    Usage(argv[0]);
    return 1;

  }

  udp_server ser(atoi(argv[1]));
  ser.init_server();

  pthread_t r,s;
  pthread_create(&r,NULL,recv_massge,(void*)&ser);
  pthread_create(&s,NULL,send_massge,(void*)&ser);
  pthread_join(r,NULL);
  pthread_join(s,NULL);
  return 0;
}
