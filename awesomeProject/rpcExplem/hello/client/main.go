package main

// ###################简单的RPC

//func main(){
//	client, err := rpc.Dial("tcp","localhost:1234")
//	if err != nil{
//		log.Fatal("dialing: ", err)
//	}
//	var reply string
//	err = client.Call("HelloService.Hello","chengang",&reply)
//	if err != nil {
//		log.Fatal(err)
//	}
//	fmt.Println(reply)
//	var result int
//	err = client.Call("HelloService.Add",1,&result)
//	if err != nil {
//		log.Fatal(err)
//	}
//	fmt.Println(result)
//}
