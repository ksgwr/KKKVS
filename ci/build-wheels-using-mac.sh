#!/bin/bash
set -e -x

readonly ROOT_DIR=$(cd $(dirname $0)/../; pwd)
readonly VERSIONS=($PYTHON_VERSIONS)

eval "$(pyenv init -)"
# install require library
for version in ${VERSIONS[@]}; do
    if [ ! -d ~/.pyenv/versions/$version ]; then
        pyenv install $version
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
    export PYENV_VERSION=$version
    python -m pip install -r $ROOT_DIR/python/requirements-dev.txt
    find $ROOT_DIR/python | grep -E "(__pycache__|\.pyc|\.pyo$)" | xargs rm -rf
    python $ROOT_DIR/python/setup.py test bdist_wheel
done