#pragma  once 

#include <iostream>
#include <ncurses.h>
#define SIZE 1024
class window
{
public:
  window();
  void put_string_to_window(WINDOW* win,int y,int x,std::string& message);
  void get_string_from_window(WINDOW* win,std::string& out_string)
  void draw_header();
  void draw_output();
  void draw_flist();
  void draw_input();
  WINDOW* GetHeader();
  WINDOW* GetInput();
  WINDOW* GetFlist();
  WINDOW* GetOutput();
  ~window();
private:
  WINDOW *header;
  WINDOW *output;
  WINDOW *flist; 
  WINDOW *input;
};
