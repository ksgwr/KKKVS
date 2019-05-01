KKKVS(Work In Progress) [![Build Status](https://travis-ci.org/ksgwr/KKKVS.svg?branch=master)](https://travis-ci.org/ksgwr/KKKVS)
=====

# Install

```
$ pip install -i https://test.pypi.org/simple/ kkkvs
```

# Setup

```
$ git submodule update -i
(if cmake/DownloadProject is empty)
```

# Build

```
$ mkdir build
$ cd build
$ cmake ..
$ make
$ make VERBOSE=1
$ make test
$ make test ARGS='-V'
$ make install
```
