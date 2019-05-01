#!/bin/bash
set -e -x

# install require library
/opt/python/cp35-cp35m/bin/pip install cmake
yum install gcc-c++ -y

# build basic
rm -rf /io/build
mkdir -p /io/build
cd /io/build
/opt/python/cp35-cp35m/bin/cmake ..
make
make test ARGS='-V'
cd python

# Compile wheels
for PYBIN in /opt/python/*/bin; do
    "${PYBIN}/pip" install -r /io/python/requirements-dev.txt
    rm -rf build
    "${PYBIN}/python" /io/python/setup.py bdist_wheel
done

# Bundle external shared libraries into the wheels
for whl in dist/*.whl; do
    auditwheel repair "$whl" --plat $PLAT -w wheelhouse/
done

# Install packages and test
for PYBIN in /opt/python/*/bin/; do
    rm -rf build
    "${PYBIN}/python" /io/python/setup.py test
done
