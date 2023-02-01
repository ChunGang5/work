package main

import (
	"awesomeProject/testInit/testcommon"
	"fmt"
)

func main() {
	s1 := "init1"
	//testcommon.SendCommonMsg(s1)
	fmt.Println(testcommon.Show(s1))
}
