package impl

import (
	"awesomeProject/testInit/testcommon"
	"fmt"
)

func init(){
	testcommon.SendCommonMsg = sendCommonMsg
}

func sendCommonMsg(str string)error{
	fmt.Println(str)
	return nil
}