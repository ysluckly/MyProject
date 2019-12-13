package main

import (

	"encoding/json"
	"fmt"
	"src/github.com/astaxie/beego/logs"
)

func convertLogLever(lever string) int {

	switch lever {
	case "debug":
		return logs.LevelDebug
	case "info":
		return logs.LevelInfo
	case "warn":
		return logs.LevelWarn
	case "error":
		return logs.LevelError

	}
	return logs.LevelDebug
}

func InitLogger() (err error) {
	config := make(map[string]interface{})
	config["filename"] = AppConfig.LogPath
	config["level"] = convertLogLever(AppConfig.LogLevel)

	configStr, err := json.Marshal(config)
	if err != nil {
		fmt.Println(".initLogger faild, marshal failed, err:", err)
		return
	}

	//AdapterFile 包里常量
	logs.SetLogger(logs.AdapterFile, string(configStr))
	return
}


