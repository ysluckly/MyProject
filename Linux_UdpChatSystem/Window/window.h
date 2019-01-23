#pragma  once 

#include <iostream>
#include <ncurses.h>
class window
{
public:
  window();
  void draw_header();
  void draw_output();
  void draw_flist();
  void draw_input();
  ~window();
private:
  WINDOW *header;
  WINDOW *output;
  WINDOW *flist; 
  WINDOW *input;
};
