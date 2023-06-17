KKKVS(Work In Progress) [![Build Status](https://travis-ci.org/ksgwr/KKKVS.svg?branch=master)](https://travis-ci.org/ksgwr/KKKVS) [![Build status](https://ci.appveyor.com/api/projects/status/yfmw2kna6iijxq82/branch/master?svg=true)](https://ci.appveyor.com/project/ksgwr/kkkvs/branch/master)
=====

# Design

![KKKVS Design](KKKVS_design.png)

# Usecase

![KKKVS Usecase](KKKVS_usecase.png)

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
