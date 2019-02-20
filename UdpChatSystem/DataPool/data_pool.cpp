#include "data_pool.h"


data_pool::data_pool(int _cap):cap(_cap),pool(_cap)
{
  consum_step = 0;
  product_step =  0;
  sem_init(&space_sem,0,_cap);
  sem_init(&message_sem,0,0);
}

void data_pool::get_message(std::string& out_message)
{
  sem_wait(&message_sem);
  out_message = pool[consum_step];
  sem_post(&space_sem);
  consum_step++;
  consum_step%=cap;

}

void data_pool::put_message(const std::string & in_message)
{
  sem_wait(&space_sem);
  pool[product_step] = in_message;
  sem_post(&message_sem);
  product_step++;
  product_step%=cap;
}

data_pool::~data_pool()
{
  sem_destroy(&space_sem);
  sem_destroy(&message_sem);

}
