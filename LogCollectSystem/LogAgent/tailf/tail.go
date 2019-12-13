package tailf

import (
	"fmt"

	"src/github.com/astaxie/beego/logs"
	"src/github.com/hpcloud/tail"
	"time"
)

type CollectConf struct {
	LogPath string
	Topic string
}

//tail 一个文件
type TailObj struct {
	tail *tail.Tail
	conf CollectConf
}
type TextMsg struct {
	Msg string
	Topic string
}
type TailObjMgr struct {
	tailObjs []*TailObj

	msgChan chan *TextMsg
}

var (
	tailObjMgr* TailObjMgr
)

func InitTailf(conf []CollectConf,chansize int) (err error){
	if len(conf) == 0 {
		err = fmt.Errorf("config for log collect, config:^v\n",conf)
		return
	}

	tailObjMgr = &TailObjMgr{
		msgChan:make(chan *TextMsg,chansize),

	}
	for _,v := range conf {
		obj := &TailObj{
			conf:v,
		}

		tails,errTail := tail.TailFile(v.LogPath, tail.Config{
			ReOpen:    true,
			Follow:    true,
			//Location:  &tail.SeekInfo{Offset: 0, Whence: 2},
			MustExist: false,
			Poll:      true,
		})

		if errTail != nil {
			fmt.Println("tail file err:", err)
			return errTail
		}

		obj.tail = tails
		tailObjMgr.tailObjs = append(tailObjMgr.tailObjs, obj)

		go ReadFromTail(obj)
		}
	return
	}

func ReadFromTail(tailobj *TailObj) {
	for true {
		line, ok := <-tailobj.tail.Lines
		if !ok {
			logs.Warn("tail file close reopen, filename:%s\n", tailobj.tail.Filename)
			time.Sleep(100 * time.Millisecond)
			continue
		}

		textmsg := &TextMsg{
			Msg:line.Text,
			Topic:tailobj.conf.Topic,
		}

		tailObjMgr.msgChan <- textmsg
		//解耦合，所以不在tail直接到Kafka，而在main中写到kafka
	}
}
