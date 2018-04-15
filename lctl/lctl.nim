import os, system, httpclient, json, strutils

proc change_light(light: int, state: int) =
    let client = newHttpClient()
    let body = %*{
        "light": light,
        "state": state,
    }
    let response = client.request("http://[2606:a000:1127:4082:ba27:ebff:fe59:23c]/update", httpMethod = HttpPost, body = $body)

if paramCount() != 2:
    echo "usage: lctl <light> <state>"
    quit(QuitFailure)

let params = commandLineParams()
try:
    let light = parseInt(params[0])
    let state = parseInt(params[1])

    change_light(light, state)
except ValueError:
    echo "Params must be integers"
    quit(QuitFailure)
