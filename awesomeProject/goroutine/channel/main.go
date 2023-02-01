package main

//func process(ch chan int) {
//	time.Sleep(time.Second)
//	ch <- 1
//}
//func main() {
//	channels := make([]chan int, 10)
//	for i := 0; i < 10; i++ {
//		channels[i] = make(chan int) // 这一步才是真正的创建int类型的chan，上一步是创建chan int类型的切片
//		go process(channels[i])
//	}
//
//	for i, ch := range channels {
//		<-ch
//		fmt.Println("Routine ", i, "quit!")
//	}
//}

//var done = make(chan bool)
//var msg string
//func aGoroutine(){
//	msg=" dawdawd"
//	close(done)
//}
//func main(){
//	go aGoroutine()
//	<-done
//	println(msg)
//}

//var limit = make(chan int, 3)
//var work = []func(){
//	func() { println("1"); time.Sleep(1 * time.Second) },
//	func() { println("2"); time.Sleep(1 * time.Second) },
//	func() { println("3"); time.Sleep(1 * time.Second) },
//	func() { println("4"); time.Sleep(1 * time.Second) },
//	func() { println("5"); time.Sleep(1 * time.Second) },
//}
//
//func main() {
//	for _, w := range work {
//		go func(w func()) {
//			limit <- 1
//			w()
//			<-limit
//		}(w)
//	}
//	select {}
//}

//func main() {
//	done := make(chan int, 10)
//
//	go func() {
//		fmt.Println("你好, 世界")
//		<-done
//
//	}()
//// 这种才比较合适，带缓冲的通道在缓存未满的情况下发送操作不是阻塞式的
//	done <- 1
//}

// 生产者-消费者模型
//func Producer(factor int, out chan<- int){
//	for i := 0; ; i++ {
//		out <- i*factor
//	}
//}
//func Consumer(in <-chan int) {
//	for v := range in{
//		fmt.Println(v)
//	}
//}
//func main(){
//	ch := make(chan int, 64)
//	go Producer(3, ch)
//	go Producer(5, ch)
//	go Consumer(ch)
//	//time.Sleep(5*time.Second)
//	sig := make(chan os.Signal, 1)
//	signal.Notify(sig, syscall.SIGINT)
//	fmt.Printf("quit (%v)\n", <-sig)
//}

// pub-sub模型
