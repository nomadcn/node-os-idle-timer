const idleTimer = require('../index.js');

/**
 * Once this idleTimer callback is called,
 * it is automatically cleared from idleTimer.
 */
function callback(idleTime_ms) {
    console.log('idleTimer is called. ' + idleTime_ms);
}

setInterval(() => {
    console.log(idleTimer.getIdleTime_ms());
}, 2000);

idleTimer.setIdleTimer(callback, 5000);
