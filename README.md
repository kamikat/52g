52g
---

Process & query leaked password data using bloom filter.

Installation
------------

Prerequisites:

- CMake &gt;= 3.0
- GCC &gt;= 4.9 or clang with c++11 support
- Node.js & npm

Execute following command:

    npm install

should build following artifacts in `build/`

- mkbfidx: create a bloom filter index
- openidx: query a bloom filter index created by mkbfidx

See `--help` for option details.

License
-------

(The MIT License)
