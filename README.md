# Lights.mcxa.org

Code for controlling my custom light system.

## Components

* main.go - Golang server for controlling 433 Mhz lights. Integrates with Tim Leland's [codesend code](https://github.com/timleland/rfoutlet). Requires both that code and [wiringpi](https://projects.drogon.net/raspberry-pi/wiringpi/download-and-install/) to be installed.
* app.html - served by the golang code. Needs to be in same directory as complied go code to run properly. Very simple webapp to control lights.
* pebble/ - pebble app to control lights. Requires special [gadgetbridge](https://github.com/ianmcxa/GadgetBridge) and [lightingcontrol](https://github.com/ianmcxa/LightingControl) app.
* lctl/ - low level CLI. Sends API calls to API server. Written in Nim. IP address must be set at compile time.
