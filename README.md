# os-idle-timer
Detect user's system inactivity.  
Windows and Mac only

# Requisites
* windows: msvs
* mac: xcode

# Installation
```
npm install os-idle-timer
```

# Example
``` js
const idleTimer = require('os-idle-timer');

/**
 * Once an idleTimer callback is called,
 * it is automatically cleared from idleTimer.
 */
function callback(idleTime_ms) {
    console.log('idleTimer is called. ' + idleTime_ms);
}

// Set a new idle timer in milliseconds.
var handle = idleTimer.setIdleTimer(callback, 5000);

// Remove the idle timer indicated by handle.
idleTimer.clearIdleTimer(handle);

// Remove all idleTimers.
idleTimer.clearIdleTimers();

// Get the current idle time in milliseconds.
var idleTime_ms = idleTimer.getIdleTime_ms();
console.log(idleTime_ms);

setInterval(() => {
    console.log(idleTimer.getIdleTime_ms());
}, 2000);

idleTimer.setIdleTimer(callback, 5000);
```
