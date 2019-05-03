#!/bin/bash
set -e -x

readonly ROOT_DIR=$(cd $(dirname $0)/../; pwd)
readonly VERSIONS=(3.4-dev 3.5-dev 3.6-dev 3.7-dev 3.8-dev)

# install require library
for version in ${VERSIONS[@]}; do
    if [ ! -d ~/.pyenv/versions/$version ]; then
        CONFIGURE_OPTS="--with-openssl=$(brew --prefix openssl@1.1)" pyenv install $version
    fi
done

# build basic
mkdir -p ${ROOT_DIR}/build
cd ${ROOT_DIR}/build
cmake ..
make
make test ARGS='-V'
cd python

# Compile wheels
for version in ${VERSIONS[@]}; do
    pyenv local $version
    pip install -r $ROOT_DIR/python/requirements-dev.txt
    find $ROOT_DIR/python | grep -E "(__pycache__|\.pyc|\.pyo$)" | xargs rm -rf
    python $ROOT_DIR/python/setup.py test bdist_wheel
done