52g
---

[![Build Status](https://travis-ci.org/kamikat/52g.svg?branch=master)](https://travis-ci.org/kamikat/52g)

Process & query leaked password data using bloom filter.

Installation
------------

Prerequisites:

- CMake &gt;= 3.0
- GCC &gt;= 4.9 / clang with C++11 support
- Node.js + npm

On OS X

    brew install cmake nodejs

On Ubuntu

    apt install build-essential cmake nodejs-legacy npm

Execute following command in project root:

    git submodule update --init --recursive
    npm install

should build following artifacts in `build/`

- mkbfidx: create a bloom filter index
- openidx: query a bloom filter index created by mkbfidx

See `--help` for option details.

License
-------

(The MIT License)
