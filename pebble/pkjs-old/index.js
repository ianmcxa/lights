//js code for making requests

// Get AppMessage events
Pebble.addEventListener('appmessage', function(e) {
  // Get the dictionary from the message
  var dict = e.payload;
  console.log('Message received.');
  updateLight(dict['light'], dict['state']);
});

function updateLight(light, state) {
    var request = new XMLHttpRequest();
    
    function errorListener () {
        console.log('Request failed! Code:' + request.status);
    }
    
    function loadListener () {
        console.log("Request loaded!")
    }
    
    request.addEventListener("error", errorListener);
    request.addEventListener("load", loadListener);
    request.open('POST', 'http://[2606:a000:1127:4082:ba27:ebff:fe59:23c]/update', true);
    request.setRequestHeader('Content-Type', 'application/json');
    request.send(JSON.stringify({'light': light, 'state': state}));
}
