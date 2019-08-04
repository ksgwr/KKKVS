#!/bin/bash
set -e -x

readonly ROOT_DIR=$(cd $(dirname $0)/../; pwd)

# install require library
/opt/python/cp35-cp35m/bin/pip install cmake
yum install gcc-c++ -y

# build basic
mkdir -p ${ROOT_DIR}/build
cd ${ROOT_DIR}/build
/opt/python/cp35-cp35m/bin/cmake ..
make
make test ARGS='-V'
cd python

# Compile wheels
for PYBIN in /opt/python/*/bin; do
    "${PYBIN}/pip" install -r ${ROOT_DIR}/python/requirements-dev.txt
    
    # for rebuild in cp27m and cp27mu
    rm -rf build
    "${PYBIN}/python" ${ROOT_DIR}/python/setup.py bdist_wheel
done

# Bundle external shared libraries into the wheels
for whl in dist/*.whl; do
    auditwheel repair "$whl" --plat $PLAT -w wheelhouse/
done

for PYBIN in /opt/python/*/bin; do
    # for rebuild in cp27m and cp27mu
    rm -rf build
    "${PYBIN}/python" ${ROOT_DIR}/python/setup.py test
done