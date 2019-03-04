package main

import (
	"bytes"
	"encoding/json"
	"fmt"
	"net/http"
	"os"
	"strconv"
)

type State struct {
	Light int `json:light`
	State int `json:state`
}

func main() {
	if len(os.Args) != 3 {
		exit()
	}

	light, errLight := strconv.Atoi(os.Args[1])
	state, errState := strconv.Atoi(os.Args[2])

	if errLight != nil || errState != nil {
		exit()
	}

	sendCode(State{light, state})
}

func sendCode(state State) {
	body, _ := json.Marshal(state)
	http.Post("http://IP_ADDRESS/update",
		"application/json", bytes.NewBuffer(body))
}

func exit() {
	fmt.Println("usage: lctl <light> <state>")
	os.Exit(1)
}
