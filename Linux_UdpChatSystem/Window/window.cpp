#include "window.h"

//方数据
void window::put_string_to_window(WINDOW* win,int starty,int startx,std::string& message)
{
  mvwaddstr(win,starty,x,message);
  wrefresh(win);
}

void window::get_string_from_window(WINDOW* win,std::string& out_string)
{
  char buf[SIZE];
  wgetnstr(win,buf,SIZE);
  out_string = buf;

  wrefresh(win);
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
  box(header,"=","+");//绘制边框，还需要刷新窗口 ,两个参数指的是风格（“字符”）
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

WINDOW* window::GetHeader()
{
  return header;
}
WINDOW* window::GetInput()
{
  return input;
}
WINDOW* window::GetFlist()
{
  return flist;
}
WINDOW* window::GetOutput()
{
  return output;
}
window::~window()
{
  endwin();
}



// 测试
 
 int main()
 {
  window w;
  w.draw_header();
  w.draw_flist();
  w.draw_output();
  w.draw_input();

  while(1)
  {
    50mintes;
  }





/*  std::string title = "Welcome To My Chat System";
  int i = 1;
  //自动获取窗口大小
  int x ,y;
  int dir =  0;
  while(1)
  {
   /* da印标题，第一行满了到第二行，并且首字母不断重复，解决方案：重复绘制header，
    * getmaxyx(w.draw_header(),y,x);
    w.put_string_to_window(w.GetHeader(),y/2,i,title);//居中，/2
    i++;
    usleep(300000);
  */

    /*w.draw_header();
    getmaxyx(w.draw_header(),y,x);
    w.put_string_to_window(w.GetHeader(),y/2,i,title);//居中，/2
    i%=(x-title.size());  //防止到第二行，减size(),但是会重复左-》右，不美观，，改进，，，右到左左到右
    usleep(300000);*/
/*
    w.draw_header();
    getmaxyx(w.draw_header(),y,x);
    w.put_string_to_window(w.GetHeader(),y/2,i,title);//居中，/2
    if(i>= x-title.size()-3) //减3缩小摆动范围
    {
      dir = 1;  //右到左
    }
    if(i<4)
    {
      dir = 0;  //左到右
    }
    if(dir == 0)
    {
      i++;
    }
    else{
      i--;
    }
    usleep(300000);
  }
  return 0;
}
 */
