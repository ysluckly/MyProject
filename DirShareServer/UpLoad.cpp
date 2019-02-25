#include "Utils.hpp"

enum _boundry_type
{
  BOUNDRY_NO = 0,
  BOUNDRY_FIRST,
  BOUNDRY_MIDDLE,
  BOUNDRY_LAST,
  BOUNDRY_BAK //备注
};
//正文数据解析，存储
class UpLoad
{
  private:
    int _file_fd;
    int64_t content_len;
    std::string _f_boundry;
    std::string _m_boundry;
    std::string _l_boundry;

  private:
    int  MatchBoundry(char* buf,int blen,int *boundry_pos)
    {
      //--boundry 
      //first ------boundry\r\n
      //middle \r\n------boundry\r\n
      //last   \r\n------boundry--\r\n
      //起始位置匹配first_boundry,strstr可能遇到零停止
      if( !memcmp(buf,_f_boundry.c_str(),_f_boundry.length()))
      {
        return BOUNDRY_FIRST;
      }
      for(int i = 0; i< blen; ++i)
      {
        if((blen-i) > _m_boundry.length()) 
        { 
            if(!memcmp(buf+i, _m_boundry.c_str(),_m_boundry.length()))
            {
              return BOUNDRY_MIDDLE;
            }else if(!memcmp(buf+i, _l_boundry.c_str(),_l_boundry.length()))
            {
              return BOUNDRY_LAST; 
            }
            
        }else 
        {
          //防止半个boundry匹配
          //进行部分匹配
            int cmp_len = (blen - i) > _m_boundry.length() ? _m_boundry.length() : (blen - i);
            if(!memcmp( buf +i , _m_boundry.c_str(),cmp_len ))
            {
              return BOUNDRY_BAK;
            }
            if(!memcmp( buf +i , _l_boundry.c_str(),cmp_len ))
            {
              return BOUNDRY_BAK;
            }

        }
      }
      return BOUNDRY_NO; 
    }
public:
    UpLoad():_file_fd(-1){}
    //初始化boundry信息
    bool InitUpLoadInfo()
    {
      char* ptr = getenv("Content-Length");
      if(ptr == NULL)
      {
        fprintf(stderr, "have no content-length\n");
        return false;
      }
      content_len = Utils::StrToDigit(ptr);
      char* ptr = getenv("Content-Type");
      if(ptr == NULL)
      {
        fprintf(stderr,"have no type\n");
        return false; 
      }
      std::string boundry_sep = "boundary=";
      std::string contemt_type = ptr;
      size_t pos = content_type.find(boundry_sep);
      if(pos == std::string::npos)
      {
        fprintf(stderr,"HAVE NO BOUNDRY\n");
        return false; 
      }

      std::string boundry; 
      std::string boundry = content_type.substr(pos + boundry_sep.length());

      _f_boundry = "--" + boundry ;
      _m_boundry = "\r\n" + _f_boundry + "\r\n";
      _l_boundry = "\r\n" + _f_boundry + "--";

      return true; 
    }
    //对正文进行处理，将文件进行存储（处理文件上传）
    bool ProcessUpLoad()
    {
      int64_t tlen = 0, blen = 0;
      char buf[MAX_BUFF];
      while(tlen < content_len)
      {
        int len = read(0,buf + blen, MAX_BUFF- blen);
        blen += len ; //当前buf中数据长度
        int boundry_pos; 
        int flag = MatchBoundry(buf, blen , &boundry_pos);
        if(flag == BOUNDRY_FIRST )
        { 
          //1,从boundry获取文件名
          //若成功，创建文件名，打开文件
          //将头信息从buf移除，剩余数据进行下一步匹配
            if(GetFileName(buf,&content_pos))
            {
              CreateFile();
              blen -= content_len;
              memmove(buf,buf+ content_pos, blen);
            }

        }
        
        while(1)
        {
          int flag = MatchBoundry(buf, blen , &boundry_pos);
          if(flag != BOUNDRY_MIDDLE )
          {
            break; 
          }
          //1,将boundry之前的数据写入文件，将数据在buf中移除
          //看boundry头是否含有文件名--雷同boundry
          WriteFile(buf,boundry_pos - buf);
          blen -= (boundry_pos - buf);
          memmove(buf, buf + boundry_pos, blen);
        
          if(GetFileName(buf,&content_pos))
          {
            CreateFile();
            blen -= content_len;
            memmove(buf,buf+ content_pos, blen);
          }
        }
        
        int flag = MatchBoundry(buf, blen , &boundry_pos);
        if(flag == BOUNDRY_LAST)
        {


        }

        int flag = MatchBoundry(buf, blen , &boundry_pos);
        if(flag == BOUNDRY_BAK)
        {
        }
        
        if(flag == BOUNDRY_NO)
        {

        }

        tlen += len;
      }

    }

};
int main()
{
  std::string rsp_body;                                                                                                        
  rsp_body = "<html><body><h1> UpLoad Success!!!</h1></body></html>";               
  LOG("File rsp:[%s]\n",rsp_body.c_str());

  fflush(stdout);
  return 0;
}
