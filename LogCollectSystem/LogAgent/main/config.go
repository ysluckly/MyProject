package main

import (
	"Kafka_Zookeeper/LogAgent/tailf"
	"errors"
	"fmt"

	"src/github.com/astaxie/beego/config"
)

var (
	AppConfig *Config
)



//存储配置文件字段
type Config struct {
	LogLevel string
	LogPath string
	ChanSize int

	CollectConf []tailf.CollectConf //可能会有多个collect
}


func LoadCollectConf(conf config.Configer) (err error ){
	 var cc tailf.CollectConf
	 cc.LogPath = conf.String("collect::log_path")
	 if len(cc.LogPath) == 0 {
	 	err = errors.New("collect::log_path")
	 	return
	 }
	cc.Topic = conf.String("collect::topic")
	if len(cc.Topic) == 0 {
		err = errors.New("collect::topic")
		return
	}
	AppConfig.CollectConf = append(AppConfig.CollectConf,cc)

	return
	}

func LoadConf(conftype ,filename string) (err error) {
	conf, err := config.NewConfig(conftype, filename)
	if err != nil {
		fmt.Println("new config failed, err:", err)
		return
	}

	AppConfig = &Config{}
	AppConfig.LogLevel = conf.String("logs::log_level")
	if len(AppConfig.LogLevel) == 0 {
		AppConfig.LogLevel = "debug"
	}
	AppConfig.LogPath = conf.String("logs::log_path")
	if len(AppConfig.LogPath) == 0 {
		AppConfig.LogPath = "./logs"
	}
	AppConfig.ChanSize,err = conf.Int("collect::chan_size")
	if err != nil {
		AppConfig.ChanSize = 100
	}

	//可能会有多个collect，就模块化
	err = LoadCollectConf(conf)
	if err != nil {
		fmt.Printf("load collect faild, err :%v\n",err)
		return
	}

	return
}