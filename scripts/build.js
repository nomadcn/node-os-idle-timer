'use strict';

const os = require('os');
const exec = require('child_process').exec;

// use the same version as the currently-installed electron-prebuilt
exec('npm list electron-prebuilt --dev', (err, stdout) => {
    var version;

    if (err) {
        version = '1.2.0';
    } else {
        version = stdout.split('electron-prebuilt@')[1].replace(/\s/g, '');
    }

    build(version);
});

function build(electronVersion) {
    var platform = os.platform();
    var command = "node-gyp rebuild --disturl=https://atom.io/download/atom-shell";
    command += " --target=" + electronVersion;

    if (platform === 'win32') {
        command += " --arch=ia32 --msvs_version=2013";
    }

    exec(command, (error, stdout, stderr) => {
        if (error) {
            console.error(`exec error: ${error}`);
            return;
        }

        console.log(`stdout: ${stdout}`);
    });
}
