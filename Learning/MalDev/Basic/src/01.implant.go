package implant

import (
	"syscall"
	"unsafe"
)

type Fun struct{
	p unsafe.Pointer
	n string
}

type Payload struct {
  length int
  data   []byte
}


func main(){
	lib, err := syscall.LoadLibrary("kernel32.dll")	
}
