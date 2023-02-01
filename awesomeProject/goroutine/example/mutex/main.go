package main

import (
	"fmt"
	"sync"
)

//
var total struct {
	sync.Mutex
	value int
}

func worker(wg *sync.WaitGroup) {
	// 计数器减1，很想linux下并发编程方面的信号量，值可以为负数
	defer wg.Done()
	for i := 0; i < 100; i++ {
		total.Lock()
		total.value += i
		total.Unlock()
	}
}
func main() {
	var wg sync.WaitGroup
	wg.Add(2)
	worker(&wg)
	worker(&wg)
	// 在这里阻塞式等待两个goroutine执行完成
	wg.Wait()
	fmt.Println(total.value)
}
