#!/usr/bin/env node

var path = require('path');
var spawn = require('child_process').spawn;
var death = require('death');
var fifo = require('fifo');
var express = require('express');
var compression = require('compression');
var morgan = require('morgan');
var parser = require('body-parser');
var serveStatic = require('serve-static');

var argv = require('yargs').demand(1).argv;

var app = express();

app.use(compression());
app.use(morgan('combined'));
app.use(parser.json());

app.get('/algorithm', function (req, res) {
  return res.status(200).send(openidx.params);
});

app.get('/query', function (req, res, next) {
  openidx.lookup(req.query.d, function (result) {
    return res.status(200).send({
      found: !!+result
    });
  });
});

app.use(serveStatic(path.resolve(__dirname, 'www')));

if (process.env.PROXY_MODE) {
  // parse client from X-Forwarded-* headers
  app.enable('trust proxy');
}

var server = app.listen(
  process.env.BIND_PORT || 8080,
  process.env.BIND_HOST || 'localhost',
  function () {
    console.log('Server listening at http://%s:%s', server.address().address, server.address().port);
  }
);

death(function () {
  server.close();
});

var openidx = (function (file) {
  var _callbacks = fifo();
  var _params = {};

  _callbacks.push(function (data) {
    console.log(data);
    Object.assign(_params, {
      k: parseInt(data.match(/k=([0-9]+)/)[1]),
      m: parseInt(data.match(/m=([0-9]+)/)[1]),
      seed: parseInt(data.match(/seed=([0-9]+)/)[1])
    });
  });

  var _child = spawn(
    path.resolve(__dirname, "build/openidx"), [ '--hex', file ]);

  _child.stdout.on('data', function (data) {
    var results = data.toString().split('\n');
    for (var i = 0; i < results.length - 1; i++) {
      _callbacks.shift()(results[i]);
    }
  });

  _child.stderr.on('data', function (data) { process.stderr.write(data); });

  death(function () {
    _child.kill('SIGTERM');
  });

  return {
    params: _params,
    lookup: function (data, cb) {
      _callbacks.push(cb);
      _child.stdin.write(data + '\n');
    },
  };
})(argv._[0]);
