package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"crypto/sha512"
	"flag"
	"io"
	"io/ioutil"
	"os"

	"github.com/sirupsen/logrus"
)

type AESReadWriter struct {
	gcm cipher.AEAD
	aes cipher.Block
	nonce []byte
}

func (a *AESReadWriter) Write(p []byte)(int, error){
	length,err := os.Stdout.Write(a.gcm.Seal(a.nonce,a.nonce,p,nil))
	if(err!=nil){return 0, err}
	return length,nil
}

func main(){
	key := flag.String("k","asdfasdfasdfasdfasdfadsfasfd","The Key to use")
	file := flag.String("f","","File to read")
	str := flag.String("s","","The string to use")
	flag.Parse()
	
	var err error

	aw := AESReadWriter{}

	sha := sha512.New512_256()
	hash := sha.Sum([]byte(*key))

	aw.aes, err = aes.NewCipher(hash[:32])
	if(err != nil) {
		logrus.Errorf("%s",err)
		return
	}

	aw.gcm, err = cipher.NewGCM(aw.aes)	
	if(err != nil) {
		logrus.Errorf("%s",err)
		return 
	}

	aw.nonce = make([]byte,aw.gcm.NonceSize())
	_, err = io.ReadFull(rand.Reader,aw.nonce)
	if(err != nil) {
		logrus.Errorf("%s",err)
		return
	}

	if(*file!=""){
		return 
	}
	if(*str!=""){
		return
	}


	data,err := ioutil.ReadAll(os.Stdin)
	if(err != nil) {
		logrus.Errorf("%s",err)
		return
	}

	aw.Write(data)
	return
}

