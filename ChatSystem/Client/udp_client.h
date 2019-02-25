#pragma once 

#include <iostream>
#include <sys/types.h>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

#define SIZE 1024
class udp_client
{
  public:
    udp_client(std::string client_ip,int client_port);//https 443
    void init_client();
    void recv_data(std::string& out_string);
    void send_data(const std::string &in_string);
    ~udp_client();

    int sock;
    struct sockaddr_in server;

};
