#!/bin/bash
set -e -x

readonly ROOT_DIR=$(cd $(dirname $0)/../; pwd)

# install require library
/opt/python/cp35-cp35m/bin/pip install cmake
yum install gcc-c++ -y
# for installing cryptography on manylinux1_i686 upper python 3.6
yum install openssl101e-devel -y

# build basic
mkdir -p ${ROOT_DIR}/build
cd ${ROOT_DIR}/build
/opt/python/cp35-cp35m/bin/cmake ..
/opt/python/cp35-cp35m/bin/cmake --build .
/opt/python/cp35-cp35m/bin/ctest --verbose
cd python

# Compile wheels
for PYBIN in /opt/python/*/bin; do
    LDFLAGS="-L/usr/lib/openssl101e $LDFLAGS" CFLAGS="-I/usr/include/openssl101e $CFLAGS" "${PYBIN}/pip" install -r ${ROOT_DIR}/python/requirements-dev.txt
    
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