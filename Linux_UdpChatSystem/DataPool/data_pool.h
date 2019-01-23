#pragma once 
#include <iostream>
#include <string>
#include <vector>  //基于vecto的环形队列
#include <semaphore.h>

#define NUM 256

class data_pool
{
  public:
    data_pool(int _cap = 256);
    void get_message(std::string& out_message);
    void put_message(const std::string& in_message);
    ~data_pool();

  private:
    std::vector<std::string> pool;
    int product_step;
    int consum_step;
    int cap;//池容量
    sem_t space_sem;
    sem_t message_sem;
};
