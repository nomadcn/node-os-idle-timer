const idleTimer = require('../index.js');

function callback(idleTime_ms) {
    console.log('idleTimer is called. ' + idleTime_ms);
    idleTimer.clearIdleTimer();
}

setInterval(() => {
    console.log(idleTimer.getIdleTime_ms());
}, 2000);

idleTimer.setIdleTimer(callback, 5000);
