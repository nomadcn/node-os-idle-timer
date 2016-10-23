#!/bin/sh

# If ELECTRON_VERSION environment variable is not set,
# 1.3.6 will be used as a default value.
: ${ELECTRON_VERSION=1.3.6}

ARCH=x64
if [ $OSTYPE == "cygwin" ]; then
    echo "ia32"
    ARCH=ia32
    # Install all dependencies, and store cache to ~/.electron-gyp.
    export npm_config_msvs_version=2013
fi

# Electron's version.
export npm_config_target=$ELECTRON_VERSION
# The architecture of Electron, can be ia32 or x64.
export npm_config_arch=$ARCH
# Download headers for Electron.
export npm_config_disturl=https://atom.io/download/atom-shell
# Tell node-pre-gyp that we are building for Electron.
export npm_config_runtime=electron
# Tell node-pre-gyp to build module from source code.
export npm_config_build_from_source=true

rm -rf ./build

node-pre-gyp configure --target_arch=$ARCH && \
node-pre-gyp build --target_arch=$ARCH && \
node-pre-gyp package --target_arch=$ARCH && \
node-pre-gyp-github publish --release
