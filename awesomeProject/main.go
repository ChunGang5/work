package main

import "fmt"

//import (
//	"awesomeProject/goroutine/pubsub"
//	"fmt"
//	"strings"
//	"time"
//)
//
//func main() {
//	pub := pubsub.NewPublisher(100*time.Millisecond, 10)
//	defer pub.Close()
//	all := pub.Subscribe()
//	golang := pub.SubscriberTopic(func(v interface{}) bool {
//		if s, ok := v.(string); ok {
//			return strings.Contains(s, "golang")
//		}
//		return false
//	})
//	pub.Publish("hello, world!")
//	pub.Publish("hello, golang")
//
//	go func() {
//		for msg := range all {
//			fmt.Println("all: ", msg)
//		}
//	}()
//	go func() {
//		for msg := range golang {
//			fmt.Println("golang: ", msg)
//		}
//	}()
//
//	time.Sleep(5 * time.Second)
//}

//func main() {
//	var str string
//	fmt.Println(str)
//	var a interface{} = 10
//	fmt.Printf("a的类型%T\n", a)
//	if t, ok := a.(float64); ok{
//		fmt.Printf("转换后%T\n", t)
//	}else{
//		fmt.Println("fail", t)
//	}
//	//fmt.Println("类型")
//}

//func main(){
//	var a, b float64 = 1.0, 4.0
//	fmt.Println(a | b)
//}

//func main() {
//	m := map[string]int{
//		"a": 1,
//		"b": 2,
//	}
//	if val, ok := m["c"]; ok {
//		fmt.Println(val)
//	} else {
//		fmt.Println("ok = ", ok)
//		fmt.Println("val = ", val)
//	}
//}

//func main() {
//	var aArray = [3]int{1, 2, 3}
//	defer func(array [3]int){
//		fmt.Println(":",&array)
//		for i := range array{
//			fmt.Println(array[i])
//		}
//	}(aArray)
//	aArray[0] = 10
//
//	defer func() {
//		defer func() {
//			fmt.Println("B")
//		}()
//		fmt.Println("A")
//	}()
//	fmt.Println(test())
//	ok,v := testreturn()
//	fmt.Println("ok = ",ok," v = ", v)
//}
//
//func testreturn()(flag bool, result int){
//	return
//}
//
//func test()int{
//	var i int
//	defer func(){
//		i++
//	}()
//	return i
//}

// 判断两个map是否相等
// golang里map是无序排列的

//func isEquality(m1 map[string]interface{}, m2 map[string]interface{}) bool {
//	if (m1 == nil && m2 == nil){
//		return true
//	}
//	// 开始判断里面的元素是否相等
//	keySlice := make([]interface{}, 0)
//	data1Slice := make([]interface{}, 0)
//	data2Slice := make([]interface{}, 0)
//	if (m1 != nil && m2 != nil){
//		if len(m1) == len(m2){
//			// 将其中一个map的key存储
//			for key, value := range m1{
//				keySlice = append(keySlice, key)
//				data1Slice = append(data1Slice, value)
//			}
//			for _, key := range keySlice{
//				if data, ok := m2[key.(string)]; ok {
//					data2Slice = append(data2Slice,data)
//				}else{
//					// 在m2中没有这个key，两个map不相等
//					return false
//				}
//			}
//		}
//	}
//	data1Bytes, _ := json.Marshal(data1Slice)
//	data2Bytes, _ := json.Marshal(data2Slice)
//	return string(data1Bytes) == string(data2Bytes)
//}
//
//func main() {
//	m1 := map[string]int{
//		"a":1,
//		"b":2,
//	}
//	m2 := map[string]int{
//		"b":2,
//		"a":1,
//	}
//	fmt.Println(isEquality(m1,m2))
//}

//func main() {
//	a := 1 << 9
//	fmt.Println(a)
//}

//func main() {
//	//resp, err := http.Get("https://www.baid.com/")
//	//if err != nil {
//	//	fmt.Println("err")
//	//	return
//	//}
//	//defer resp.Body.Close()
//	serverList := []string{"https://www.bilili.com/", "https://www.baid.com/", "https://"}
//	resp, err := Get(serverList)
//	if err != nil {
//		fmt.Println("err")
//		return
//	}
//	defer resp.Body.Close()
//	fmt.Printf("code = %v\n", resp.StatusCode)
//}
//
//func Get(serverList []string) (*http.Response, error) {
//	failErr := "requset error"
//	serverListLen := len(serverList)
//	fmt.Printf("serverListLen = %v\n", serverListLen)
//	if serverListLen <= 0 {
//		return nil, errors.New(failErr)
//	}
//	mask := make([]bool, serverListLen, serverListLen)
//	maskLen := len(mask)
//	for i := 0; i < maskLen; i++ {
//		mask[i] = true
//	}
//	fmt.Printf("maskLen = %v\n", maskLen)
//	for {
//		i := rand.Intn(serverListLen - 1)
//		fmt.Printf("i = %v\n", i)
//		resp, err := http.Get(serverList[i])
//		if err != nil {
//			mask[i] = false
//			flags := 0
//			for i := 0; i < maskLen; i++ {
//				if mask[i] == false {
//					flags++
//				}
//			}
//			if flags == serverListLen {
//				return nil, errors.New(failErr)
//			}
//		}
//		if resp != nil {
//			if resp.StatusCode/100 == 1 || resp.StatusCode/100 == 2 ||
//				resp.StatusCode/100 == 4 || resp.StatusCode/100 == 5 {
//				return resp, nil
//			}
//		}
//	}
//}

//func main() {
//	a := [...]int{0, 1, 2, 4, 5}
//	//
//	//for i := range a{
//	//	fmt.Println(i)
//	//}
//	//for i := 0; i < 10; i++ {
//	//	fmt.Println(i)
//	//}
//	//fmt.Println(len(a))
//	//fmt.Println(cap(a))
//	for index, v := range a {
//		fmt.Println(index)
//		fmt.Println(v)
//	}
//
//}
//func main() {
//	arr := []int{1, 2, 3}
//	//newArr := []*int{}
//	//for _, v := range arr {
//	//	newArr = append(newArr, &v)
//	//}
//	//for _, v := range newArr {
//	//	fmt.Println(*v)
//	//}
//
//	var m = map[string]int{
//		"A": 21,
//		"B": 22,
//		"C": 23,
//	}
//
//	counter := 0
//	for range m {
//		if counter == 0 {
//			delete(m, "A")
//		}
//		counter++
//	}
//	fmt.Println(counter)
//	a := arr[0:2]
//	getSclie(a)
//	var lice []int
//	var lice2 = []int{}
//	fmt.Println(lice)
//	fmt.Println(lice2)
//}
//func getSclie(s []int) {
//	fmt.Println(s)
//}

//func main() {
//	arr := []int{1, 2, 3}
//	for _, v := range arr {
//		arr = append(arr, v)
//	}
//	fmt.Println(arr)
//}

//func app() func(string) string {
//	t := "Hi"
//	c := func(b string) string {
//		t = t + " " + b
//		return t
//	}
//	return c
//}
//
//func main() {
//	a := app()
//	b := app()
//	a("go")
//	fmt.Println(b("All"))
//}

//func main() {
//	fmt.Println("Hello, 世界")
//	var val uint64 = 730
//	var ratio uint64 = 50000
//	res := val * ratio / 1e6
//	fmt.Println("res:", res)
//
//	var val2 float64 = 730
//	var ratio2 float64 = 50000
//	temp := float64(3300 / 10000)
//	fmt.Println(temp)
//	res2 := val2 * (ratio2 / 1000000.00)
//	fmt.Println("res2:", res2)
//}
//func f() {
//	defer fmt.Println("D")
//	fmt.Println("F")
//}
//
//func main() {
//	f()
//	fmt.Println("M")
//}

//func main(){
//	var a []int
//	b := []int{}
//	println(a)
//	println(b)
//	timer := time.NewTimer(10)
//
//
//}

//func tickerDemo() {
//
//	ticker := time.NewTicker(1 * time.Second)
//	//defer timer.Stop()
//	defer ticker.Stop()
//
//	for range ticker.C {
//		log.Println("Ticker tick.")
//	}
//}
//
//func main() {
//	timer := time.NewTimer(5 * time.Second)
//	select {
//	case <-timer.C:
//		fmt.Println("timer")
//	}
//	ticker := time.NewTicker(1 * time.Second)
//	defer timer.Stop()
//	ticker.Stop()
//
//	for range ticker.C {
//		log.Println("Ticker tick.")
//	}
//	//tickerDemo()
//
//func main() {
//	timer := time.NewTimer(5 * time.Second)
//	select {
//	case <-timer.C:
//		fmt.Println("timer")
//	}
//	ticker := time.NewTicker(1 * time.Second)
//	defer timer.Stop()
//	ticker.Stop()
//
//	for range ticker.C {
//		log.Println("Ticker tick.")
//	}
//	//tickerDemo()
//
//
//}

//func main() {
//	//LOOP:
//	for {
//		fmt.Println(1)
//		for {
//			fmt.Println(2)
//			for {
//				fmt.Println(3)
//				break
//				//break LOOP
//			}
//		}
//	}
//}
//func sendTime(c interface{}, i int) {
//	select {
//	case c.(chan int) <- i:
//	default:
//
//	}
//}

//func main() {
//	c := make(chan int, 1)
//	sendTime(c, 1)
//	sendTime(c, 2)
//	a, ok := <-c
//	if ok {
//		fmt.Println(a)
//	}
//
//	b, ok := <-c
//	if ok {
//		fmt.Println(b)
//	}
//	sendTime(c, 3)
//	close(c)
//}
//import "C"
//func main(){
//	var ch chan struct{}
//	<-ch
//}

//func main() {
//	//ch := make(chan int, 1)
//	var ch1 chan int
//	if ch1 == nil {
//		fmt.Println("yes")
//	}
//	//go func() {
//	//	ch <- 1
//	//}()
//	//if ch == nil{
//	//	fmt.Println("yes")
//	//}
//	select {
//	case <-ch1:
//		fmt.Println("success")
//		//default:
//		//	fmt.Println("fal")
//	}
//}

//func main() {
//	//ticker := time.NewTicker(time.Second * 5)
//	//fmt.Println("now time", time.Now().Unix())
//	//defer ticker.Stop()
//	//for range ticker.C{
//	//	fmt.Println(time.Now().Unix())
//	//}
//	var a = []int{1, 2, 3, 4, 5}
//	var b = [5]int{1, 2, 3, 4, 5}
//	fmt.Printf("%T\n", a)
//	fmt.Printf("%T\n", b)
//}

//func main() {
//	// panic只会执行当前goroutine的defer
//	//defer fmt.Println("in main")
//	//go func() {
//	//	defer fmt.Println("int goroutine")
//	//	panic("test panic")
//	//}()
//	//time.Sleep(1 * time.Second)
//
//	//fmt.Println("in main")
//	////panic("error")
//	//defer func(){
//	//	if err := recover(); err != nil{
//	//		fmt.Println(err)
//	//	}else{
//	//
//	//		fmt.Println("normal")
//	//	}
//	//}()
//	//panic("error")
//
//	defer fmt.Println("a")
//	defer func() {
//		defer func() {
//			fmt.Println("b")
//		}()
//		fmt.Println("c")
//	}()
//	fmt.Println("d")
//
//}

//type user struct{
//	name string
//	email string
//}
//func (u user) notify (){
//	fmt.Printf("%s, %s\n",u.name, u.email)
//}
//func (u *user) changeEmail(newEmail string) {
//	u.email = newEmail
//}
//// 调用
//func main() {
//	u1 := user{
//		name:  "cg",
//		email: "123",
//	}
//	u2 := &user{
//		name:  "lkc",
//		email: "456",
//	}
//	u1.changeEmail("new123")
//	// 编译器优化为--->(&u1).changeEmail("new123")
//	u1.notify()
//	u2.changeEmail("new456")
//	u2.notify()
//	// 编译器优化为--->(*u2).notify()
//}

//type People struct {
//	Name string
//	sex string
//}
//func (p People) Message() {
//	fmt.Printf("%s %s\n", p.Name, p.sex)
//}
//func (p *People) changeName(sex string) {
//	p.sex = sex
//}
//type User struct {
//	p People
//	sroce int
//}
//func (u User)Message(){
//	fmt.Printf("%s %s %d\n", u.Name, u.sex, u.sroce)
//}
//func main(){
//	u1 := User{
//		People: People{
//			Name: "cg",
//			sex: "boy",
//		},
//		sroce:  10,
//	}
//	p1 := People{
//		Name: "cg",
//		sex:  "boy",
//	}
//	u2 := User{
//		p:    People{
//			Name: "cg",
//			sex:  "boy",
//		},
//		sroce: 0,
//	}
//	u2.p.changeName("girl")
//	u1.Message()	// cg boy 10
//	u1.People.Message()	// cg boy
//	u1.changeName("girl")
//	u1.Message() // cg girl 10
//	u2.Message()
//	u2.p.Message()
//}

//type People interface {
//	message()
//}
//type stu struct {
//	name string
//	sex  string
//}
//
//type tech struct {
//	age int
//}
//
//func (s stu) message() {
//	fmt.Printf("%s %s\n", s.name, s.sex)
//}
//func (t tech) message() {
//	fmt.Println(t.age)
//}
//func main() {
//	s1 := stu{
//		name: "cg",
//		sex:  "boy",
//	}
//	t1 := tech{1}
//	//var p1 People = s1
//	//var p2 People = t1
//	//p1.message()
//	//p2.message()
//	s1.message()
//	t1.message()
//	//todo:接口和方法的区别到底在哪？
//}

//type stu struct{
//	age uint64
//	i int32
//}
//
//func main() {
//	status := ""
//	u1 := stu{
//		10,
//		5,
//	}
//	//status += string(u1.age) + "-" +string(u1.i)
//	status += strconv.Itoa(int(u1.age)) + "-" + strconv.Itoa(int(u1.i))
//	fmt.Println(status)
//}

//func main() {
//	var i int32
//	i = 589826
//	funcType := i >> 16
//	pos := int16(i) | int16(0)
//	fmt.Printf("%v %v\n", funcType, pos)
//	//v := float64(2/3) * 2
//	//fmt.Println(v)
//	//arr := make([]int, 10)
//	//arr = append(arr, 1)
//	//fmt.Println(arr)
//}

//type Driver interface {
//	Name() string
//}
//
//func main() {
//	p, err := plugin.Open("driver.so")
//	if err != nil {
//		panic(err)
//	}
//	newDriverSymbol, err := p.Lookup("NewDriver")
//	if err != nil {
//		panic(err)
//	}
//	newDriverFunc := newDriverSymbol.(func() Driver)
//	newDriver := newDriverFunc()
//	fmt.Println(newDriver.Name())
//}

//func main() {
//	i := 70
//	s := string(i)
//	fmt.Println(s)
//}

//type Duck interface {
//	Quack()
//	Test()
//}
//type Cat struct {
//	a int
//}
//
//func (c Cat) Quack() {
//	fmt.Println("test")
//}
//
//func (c Cat) Test() {
//	fmt.Println("test2")
//}
//
//func main() {
//	a := Cat{3}
//	var c Duck = a // 匿名
//	c.Quack()
//}

//func main() {
//	args := []int{1,2,2,3,2}
//	for i, v := range args {
//		if v == 2 {
//			args = append(args[:i], args[i+1:]...)
//		}
//	}
//}

//func main() {
//	s := [3]int{}
//	a := []int{1, 2, 3}
//	fmt.Println(len(s), cap(s))
//	fmt.Println(len(a), cap(a))
//}

//func main() {
//	fmt.Println(5 / -2)
//}

//type A interface {
//	ShowA() int
//}
//
//type B interface {
//	ShowB() int
//}
//
//type Work struct {
//	i int
//}
//
//func (w Work) ShowA() int {
//	return w.i + 10
//}
//
//func (w Work) ShowB() int {
//	return w.i + 20
//}
//
//func main() {
//	var a A = Work{3}
//	s := a.(Work)
//	fmt.Println(s.ShowA())
//	fmt.Println(s.ShowB())
//}

//func main(){
//	m1 := make(map[int]int,0)
//	m1[1]=3
//	v, ok := m1[2]
//	if !ok{
//		fmt.Println(v)
//	}else{
//		fmt.Println("err")
//	}
//}

//func main() {
//	i := float64(12.0)
//	//i:=string("a")
//	a := int(i)
//	fmt.Println(a)
//}

//var c chan int
//
//func handle(int) {
//	log.Println("wait")
//}
//
//func main() {
//	select {
//	case m := <-c:
//		handle(m)
//	case <-time.After(10 * time.Second):
//		fmt.Println("timed out")
//	}
//}
//const (
//	LOG_CRIT    = 2 + iota // 2  Crit:       严重级
//	LOG_ERR                // 3  Err：        错误级
//	LOG_WARNING            // 4  Warning：    警告级
//	LOG_INFO               // 5  Info：       关键信息记录
//	LOG_TRACE              // 6  Trace：      一般信息记录
//	LOG_DEBUG              // 7  Debug：      调试信息
//	LOG_STAT               // 8  Stat：       一些特殊信息记录（比如进程启动相关信息、gauge监控信息等）
//)
//
//func main(){
//	log_crit_mask       :=   1 << LOG_CRIT
//	log_err_mask        :=   1 << LOG_ERR
//	log_warning_mask    :=   1 << LOG_WARNING
//	log_info_mask       :=   1 << LOG_INFO
//	log_trace_mask      :=   1 << LOG_TRACE
//	log_debug_mask      :=   1 << LOG_DEBUG
//	log_stat_mask       :=   1 << LOG_STAT
//	a := log_crit_mask + log_err_mask + log_warning_mask + log_info_mask + log_stat_mask
//	fmt.Println(a)
//
//	fmt.Println("-----------------------------")
//	fmt.Println(log_trace_mask,log_debug_mask, log_stat_mask)
//}

//func main() {
//	timer := time.Now()
//	fmt.Println(timer.Year())
//	message := "机器人" + "-->" + strconv.Itoa(timer.Year()) + ":" + timer.Month().String() + ":" + strconv.Itoa(timer.Day()) +
//		":" + strconv.Itoa(timer.Hour()) + ":" + strconv.Itoa(timer.Minute()) + ":" + strconv.Itoa(timer.Second())
//	commond := "marquee 16000 0 0 " + message + " a b c d "
//	fmt.Println(commond)
//}

//func main(){
//	//a := float64(187)/float64(600) * float64(761) + 0
//	a := int64(187)/ int64(0)
//	fmt.Println(a)
//}

//func test(i interface{})  {
//	if i == nil {
//		fmt.Println("nil")
//	}else{
//		fmt.Println("no nil")
//	}
//}
//func main() {
//	var a *int = nil
//	test(a)
//}

//func main() {
//	v := 5 /0
//	fmt.Println(v)
//}

//func main() {
//	var ch chan int
//
//	go func() {
//		fmt.Println(<-ch)
//	}()
//
//	go func() {
//		time.Sleep(3 * time.Second)
//		ch = make(chan int)
//		ch <- 1
//	}()
//
//	time.Sleep(10 * time.Second)
//}

//func main() {
//	production := float64(356) / float64(300) * float64(225)
//	a := int32(production) * 4
//	fmt.Println(a)
//	fmt.Println(production)
//}

//func main() {
//	slice := []int{0,1,2,3}
//	m := make(map[int]*int)
//
//	for key,val := range slice {
//		m[key] = &val
//	}
//
//	for k,v := range m {
//		fmt.Println(k,"->",*v)
//	}
//}

//type Test struct {
//	name string
//}
//
//func (this *Test) Point() {
//	fmt.Println(this.name)
//}
//
//func main() {
//
//	ts := []Test{
//		{"a"},
//		{"b"},
//		{"c"},
//	}
//
//	for _, t := range ts {
//		//fmt.Println(reflect.TypeOf(t))
//		defer t.Point()
//	}
//
//}

//func main() {
//	arr := []int{1,2,5,2,5,7,8,9,8,6}
//	result := bobblSort(arr)
//	for _, v := range result {
//		println(v)
//	}
//}
//
//func bobblSort(arr []int) []int {
//	if len(arr) <= 1 {
//		return arr
//	}
//	for i := 1; i < len(arr); i ++ {
//		for j := 0; j < len(arr) - i; j++ {
//			if arr[j] > arr[j+1] {
//				temp := arr[j]
//				arr[j] = arr[j+1]
//				arr[j+1] = temp
//			}
//		}
//	}
//	return arr
//}
//func main() {
//	c := make(chan int,1)
//	//var c chan int
//	//go read(c)
//	c <- 1
//	c <- 2
//	//s:=<-c
//	//fmt.Println(s)
//}
//func read(c chan int)  {
//	s := <-c
//	println(s)
//}

//func main() {
//	arr := []int{49,38,65,97,76,13,27,49}
//	//arr := []int{2,3,4,6,5,3,2,1}
//	fmt.Println("start")
//	fmt.Println(arr)
//	quickSort(arr, 0 , len(arr) - 1)
//	fmt.Println(arr)
//
//}
//func quickSort (arr []int, i, j int) {
//	var k int
//	if i < j {
//		k = sort(arr, i, j)
//		quickSort(arr, i, k - 1)
//		quickSort(arr, k+1, j)
//	}
//}
//
//func sort(arr []int,i, j int) int {
//	temp := arr[i]
//	for i < j {
//		for arr[j] >= temp && i < j{
//			j--
//		}
//		if i < j {
//			arr[i] = arr[j]
//			i++
//		}
//		for arr[i] <= temp && i<j{
//			i++
//		}
//		if i < j {
//			arr[j] = arr[i]
//			j--
//		}
//	}
//	arr[i] = temp
//	return i
//}
//type TreeNode struct {
//   Val int
//   Left *TreeNode
//   Right *TreeNode
// }
//
//func main() {
//	arr := []int{1,2,3}
//	arr = arr[1:]
//	arr = append(arr, 4)
//	node := new(TreeNode)
//	node.Val=1
//	fmt.Println(arr)
//	fmt.Println(node)
//}

//func main() {
//	arr := []int{1, 2, 5, 2, 5, 7, 8, 9, 8, 6}
//	//	result := bobblSort(arr)
//	//	for _, v := range result {
//	//		println(v)
//	//	}
//	fmt.Println(sort(arr))
//}

//func inserSort(arr []int) []int {
//	//result := []int{}
//	for i := 1; i < len(arr); i++ {
//		end := i - 1
//		key := arr[i]
//		for end > 0 && arr[end] > key {
//			arr[end+1] = arr[end]
//			end--
//		}
//		arr[end] = key
//	}
//	return arr
//}
//
//func shellSort(arr []int, n, gap int) []int {
//	for gap > 0 {
//		for i := gap; i < n; i++ {
//			key := arr[i]
//			end := i - gap
//			for arr[end] > key && end >= 0 {
//				arr[end+gap] = arr[end]
//				end -= gap
//			}
//			arr[end+gap] = key
//		}
//	}
//	return arr
//}
//
//func selectSort(arr []int) []int {
//	for i := 0; i < len(arr)-1; i++ {
//		var min, temp int
//		min = i
//		for j := i + 1; j < len(arr); j++ {
//			if arr[j] < arr[i] {
//				min = j
//			}
//		}
//		//arr[i], arr[min] = arr[min], arr[i]
//		temp = arr[i]
//		arr[i] = arr[min]
//		arr[min] = temp
//	}
//	return arr
//}
//
//func sort(arr []int) []int{
//	for i := 1; i < len(arr); i++ {
//		for j := 0; j < len(arr) - i; j ++ {
//			if arr[j] > arr[j + 1] {
//				temp := arr[j]
//				arr[j] = arr[j+1]
//				arr[j+1] = temp
//			}
//		}
//	}
//	return arr
//}
//
//func insert (arr []int, index, key int) []int {
//	if index >= len(arr) {
//		return arr
//	}
//	return arr
//}
//
//func main() {
//	args := []string{"aa", "bb", "bb", "cc", "bb"}
//	for i,v:=range args{
//		if v=="bb"{
//			args=append(args[:i],args[i+1:]...)
//		}
//	}
//}

//func getPos(id int) int {
//	// 4 国
//	i := id / 4
//	j := id % 4
//	// 双数列逆，单数列顺
//	if i%2 == 0 && j != 0 {
//		// 单数列
//		return j - 1
//	} else if i%2 != 0 && j != 0 {
//		// 双数列
//		return 4 - j
//	} else if i%2 == 0 && j == 0 {
//		// 双数列
//		return 4 - j
//	} else { // i%2 != 0 && j == 0
//		// 单数列
//		return j - 1
//	}
//}
//
//func stack(arr []int) {
//
//}
//
//func main() {
//	pos := getPos(10)
//	fmt.Println(pos)
//}

//func main() {
//	var ch chan int
//	ch = make(chan int, 1)
//	ch <- nil
//	//close(ch)
//	fmt.Println(<-ch)
//}

//func main() {
//	s1 := []int{1}
//	fmt.Printf("%p    %p\n", &s1, s1)
//	s2 := []int{2, 3, 4, 5, 6, 67, 8, 8, 9, 3, 2, 1, 5, 3}
//	fmt.Printf("%p    %p\n", &s2, s2)
//	copy(s1, s2)
//	fmt.Printf("%p    %p\n", &s1, s1)
//	fmt.Printf("%p    %p\n", &s2, s2)
//	m := make(map[int]int)
//	m[1] = 1
//
//	var a *int
//	a = nil
//	fmt.Println(a)
//
//	s := "abc"
//	fmt.Printf("%p    %p\n", &s, s)
//	s = "awhuahdwuahu"
//	fmt.Printf("%p    %p\n", &s, s)
//	s = s + "dawdwada"
//	fmt.Println(s)
//}

//func main() {
//	arr := []int{1,2,3}
//	test(arr)
//	fmt.Println(arr)
//}
//
//func test(arr []int) {
//	arr[0]=5
//}

func main() {
	//arr := []int{2,5,2,1,7,6,4,8,9}
	//bubbleSort(arr)
	//quickSort(arr,0, len(arr)-1)
	//insertSort(arr)
	//shellSOrt(arr, 3)
	//quickSelectSort(arr)
	//heapSort(arr)
	//s1 := "abc"
	//s2 :=""
	//copy(s2, s1)
	//MergeSort(arr)
	//s1 := "abcd"
	//arr1 := []byte(s1)
	//fmt.Printf("%p    %p\n", &s1, s1)
	//fmt.Printf("%p    %p\n", &arr1, arr1)
	//s1= string(arr1)
	//fmt.Printf("%p    %p\n", &s1, s1)
	////fmt.Printf("%p    %p\n", &s, s)
	//fmt.Println(arr1)
	//fmt.Println(s)
	defer func() {
		i := recover()
		fmt.Println(i)
	}()
	panic("a")

	//s1 := []int{1, 2, 3, 4, 5, 6, 7, 8}
	//s2 := []int{10, 11}
	//copy(s2, s1)
	//fmt.Println(s1)
	//fmt.Println(s2)
}

func mergeData(arr []int, left, mid, right int, temp []int) {
	begin1 := left
	end1 := mid
	begin2 := mid
	end2 := right
	index := left
	for begin1 < end1 && begin2 < end2 {
		if arr[begin1] <= arr[begin2] {
			temp[index] = arr[begin1]
			begin1++
		} else {
			temp[index] = arr[begin2]
			begin2++
		}
		index++
	}
	for begin1 < end1 {
		temp[index] = arr[begin1]
		index++
		begin1++
	}
	for begin2 < end2 {
		temp[index] = arr[begin2]
		index++
		begin2++
	}
}
func merge(arr []int, left, right int, temp []int) {
	if right-left > 1 {
		middle := left + (right-left)/2
		merge(arr, left, middle, temp)
		merge(arr, middle, right, temp)
		mergeData(arr, left, middle, right, temp)
		copy(arr[left:right], temp[left:right])
	}
}
func MergeSort(arr []int) {
	temp := make([]int, len(arr))
	merge(arr, 0, len(arr), temp)
}

func adjustHeap(arr []int, parent, n int) {
	child := parent*2 + 1
	for child < n {
		if child+1 < n && arr[child] < arr[child+1] {
			child = child + 1
		}
		if arr[child] > arr[parent] {
			temp := arr[child]
			arr[child] = arr[parent]
			arr[parent] = temp
			parent = child
			child = child*2 + 1
		} else {
			break
		}
	}
}
func heapSort(arr []int) {
	// 建堆
	for root := (len(arr) - 2) / 2; root >= 0; root-- {
		adjustHeap(arr, root, len(arr))
	}
	end := len(arr) - 1
	for end > 0 {
		temp := arr[end]
		arr[end] = arr[0]
		arr[0] = temp
		adjustHeap(arr, 0, end)
		end--
	}
}

func quickSelectSort(arr []int) {
	for i := 0; i < len(arr)-1; i++ {
		min := i
		for j := i; j < len(arr); j++ {
			if arr[j] < arr[min] {
				min = j
			}
		}
		temp := arr[i]
		arr[i] = arr[min]
		arr[min] = temp
	}
}

func shellSort(arr []int, gap int) {
	for gap >= 1 {
		for i := gap; i < len(arr); i++ {
			key := arr[i]
			end := i - gap
			for end >= 0 && arr[end] > key {
				arr[end+gap] = arr[end]
				end -= gap
			}
			arr[end+gap] = key
		}
		gap--
	}
}

func insertSort(arr []int) {
	for i := 1; i < len(arr); i++ {
		end := i - 1
		for arr[end] > arr[i] && end >= 0 {
			arr[end+1] = arr[end]
			end--
		}
		// 这块有两个作用，一个是防止数组越界，一个是条件不成立的适合，不会覆盖掉前面的数字
		arr[end+1] = arr[i]
	}
}

func quickSort(arr []int, i, j int) {
	if i < j {
		k := partition(arr, i, j)
		quickSort(arr, 0, k-1)
		quickSort(arr, k+1, j)
	}
}

func partition(arr []int, i, j int) int {
	key := arr[i]
	for i < j {
		for arr[j] > key && i < j {
			j--
		}
		if i < j {
			arr[i] = arr[j]
			i++
		}
		for arr[i] < key && i < j {
			i++
		}
		if i < j {
			arr[i] = arr[j]
			j--
		}
	}
	arr[i] = key
	return i
}

func bubbleSort(arr []int) {
	for i := 1; i < len(arr); i++ {
		for j := 0; j < len(arr)-i; j++ {
			if arr[j] > arr[j+1] {
				temp := arr[j]
				arr[j] = arr[j+1]
				arr[j+1] = temp
			}
		}
	}
}
