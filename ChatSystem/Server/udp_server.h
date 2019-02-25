#pragma once 

#include <iostream>
#include <sys/types.h>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <map>
#include <unistd.h>
#include "data_pool.h"

#define SIZE 1024
class udp_server
{
  public:
    udp_server(int _port);
    void init_server();
    void recv_data(std::string& out_string);
    void send_data(const std::string& in_string,const struct sockaddr_in &peer);  //可以私有。因为不对外
    void broadcast();//对多人发送
    ~udp_server();
  private:
    //局域网，ip可以不定义
    int port;
    int sock;
    data_pool pool;
    std::map<uint32_t,struct sockaddr_in> online;
};
