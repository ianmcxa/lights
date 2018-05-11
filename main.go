package main

import (
	"encoding/json"
	"log"
	"net/http"
	"os/exec"
	"strconv"
)

// formatted as {on, off}
var codes [][]int = [][]int{
	{1398067, 1398076}, // 0 - living room christmas lights
	{1398211, 1398220}, // 1 - kitchen christmas lights
	{1398531, 1398540}, // 2 - living room lamp
	{1400067, 1400076}, // 3 - bedroom christmas lights
	{1406211, 1406220}, // 4 - bedroom lamp
}

// names of the lights that match to a code
var lightNames []string = []string{
	"living room christmas lights",
	"kitchen christmas lights",
	"living room lamp",
	"bedroom christmas lights",
	"bedroom lamp",
}

type State struct {
	Light int `json:light`
	State int `json:state`
}

func sendCode(code int) error {
	cmd := exec.Command("/home/pi/rfoutlet/codesend", strconv.Itoa(code))
	log.Printf("Sending code %v\n", code)
	err := cmd.Run()
	return err
}

func listLights(w http.ResponseWriter, r *http.Request) {
	json.NewEncoder(w).Encode(lightNames)
}

func updateLight(w http.ResponseWriter, r *http.Request) {
	var s State
	err := json.NewDecoder(r.Body).Decode(&s)
	log.Printf("Update light %v to %v\n", s.Light, s.State)

	if err != nil {
		log.Printf("Bad update light request\n%v\n", err)
		w.WriteHeader(http.StatusBadRequest)
		return
	}

	sendCode(codes[s.Light][1-s.State])
	w.WriteHeader(http.StatusOK)
}

func main() {
	http.HandleFunc("/list", listLights)
	http.HandleFunc("/update", updateLight)

	// serve the static html homepage
	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		http.ServeFile(w, r, "./app.html")
	})

	log.Fatal(http.ListenAndServe(":8080", nil))
}
