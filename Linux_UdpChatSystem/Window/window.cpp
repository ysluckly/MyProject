#include "window.h"

//方数据
void window::put_string_to_window(WINDOW* win,int startx,int starty,std::string* message)
{

}

window::window()
{
  initscr();   //COLS,,,LINES
  

}
void window::draw_header()
{
  int x = 0;
  int y = 0;
  int h = LINES/5;
  int w =  COLS;

  header = newwin(h,w,y,x);
  box(header,0,0);//绘制边框，还需要刷新窗口 ,两个参数指的是风格（“字符”）
  wrefresh(heasder);
}
void window::draw_output()
{
  int x = 0;
  int y = LINES/5;
  int h = LINES*3/5;
  int w =  COLS*3/4;

  output = newwin(h,w,y,x);
  box(output,0,0);//绘制边框，还需要刷新窗口 ,两个参数指的是风格（“字符”）
  wrefresh(output);

}
void window::draw_flist()
{
  int x = CLOS*3/4;
  int y = LINES/5;
  int h = LINES*3/5;
  int w =  COLS/4;

  flist = newwin(h,w,y,x);
  box(flist,0,0);//绘制边框，还需要刷新窗口 ,两个参数指的是风格（“字符”）
  wrefresh(flist);

}
void window::draw_input()
{
  int x = 0;
  int y = LINES*4/5;
  int h = LINES/5;
  int w =  COLS;

  input = newwin(h,w,y,x);
  box(input,0,0);//绘制边框，还需要刷新窗口 ,两个参数指的是风格（“字符”）
  wrefresh(input);

}
window::~window()
{
  endwin();
}


/*
 * 测试
 * 
 * main()
 * {
 *  window w;
 *  w.draw_header();
 *  sleep(3);
 *  w.draw_input();
 *  sleep(3);
 *  return 0;
 * }
 * 
 
 * */
