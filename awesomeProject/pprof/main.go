package main

import (
	"awesomeProject/pprof/data"
	"fmt"
	"log"
	"net/http"
	_ "net/http/pprof"
	"time"
)

func main() {
	fmt.Println("pprof")
	go func() {
		for {
			time.Sleep(time.Second * 1)
			log.Println(pprof.Add("https://www.baidu.com/"))
		}
	}()
	http.ListenAndServe("0.0.0.0:6060", nil)
}
