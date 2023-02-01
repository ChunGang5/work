package main

import (
	"fmt"
	"sync"
	"sync/atomic"
)

var total uint64

func worker(wg *sync.WaitGroup) {
	// 计数器减1，很想linux下并发编程方面的信号量，值可以为负数
	defer wg.Done()
	var i uint64
	for i = 0; i < 100; i++ {
		atomic.AddUint64(&total, i)
	}
}
func main() {
	var wg sync.WaitGroup
	wg.Add(2)
	worker(&wg)
	worker(&wg)
	// 在这里阻塞式等待两个goroutine执行完成
	wg.Wait()
	fmt.Println(total)
}
