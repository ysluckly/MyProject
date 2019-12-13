package main

import (
	"src/github.com/astaxie/beego/logs"

	"Kafka_Zookeeper/LogAgent/tailf"
	"fmt"
)

func main() {
	//加载配置文件
	filename := "./conf/logagent.conf"
	err := LoadConf("ini",filename)
	if err != nil {
		fmt.Printf("Load conf faild. err :%v\n",err)
		panic("load conf failed")
		return
	}

	//初始化日志组件
	err = InitLogger()
	if err != nil {
		fmt.Printf("Load logger faild. err :%v\n",err)
		panic("load logger failed")
		return
	}

	logs.Debug("LoadConf success ! confi:%v",AppConfig)

	//加载tailf组件
	err = tailf.InitTailf(AppConfig.CollectConf,AppConfig.ChanSize)
	if err != nil {
		logs.Error("Init tailf faild,err:%v\n",err)
		return
	}

	logs.Debug("InitTialize  success")

	//执行逻辑
	err = ServerRun()
	if err != nil {
		logs.Error("ServeerRun faild,err:%v\n",err)
		return
	}
	logs.Info("Program exited")
}