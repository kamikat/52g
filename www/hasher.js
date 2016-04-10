var minstd_rand0 = (function (a, c, m) {
  return function (seed) {
    var x = seed || 1;
    return function () {
      return x = (a * x + c) % m;
    };
  };
})(16807, 0, 2147483647);

var BITS_PER_BYTE = 8;
var MAX_OF_BYTE = 256;

var h3 = (function (h, n) {
  return function (seed) {
    var prng = minstd_rand0(seed);
    var sxor = function (s1, s2) {
      return Array.prototype.map.call(s1, function (a, i) { return (parseInt(a, 16) ^ parseInt(s2[i], 16)).toString(16); }).join('');
    };
    var byte_lookup = (function () {
      var bytes = []; bytes.length = n;
      var bits = []; bits.length = n * BITS_PER_BYTE;
      for (var i = 0; i < bits.length; i++) {
        bits[i] = '00'.repeat(h);
        for (var j = 0; j < (h / 2); j++) {
          var rnd = ('0000' + (prng() & 0xFFFF).toString(16)).slice(-4);
          bits[i] = (bits[i] + rnd).slice(rnd.length);
        }
      }
      for (var i = 0; i < n; i++) {
        bytes[i] = []; bytes[i].length = MAX_OF_BYTE;
        for (var j = 0; j < MAX_OF_BYTE; j++) {
          bytes[i][j] = '00'.repeat(h);
          for (var ii = 0; ii < BITS_PER_BYTE; ii++) {
            if (j & (1 << ii)) {
              bytes[i][j] = sxor(bytes[i][j], bits[i * BITS_PER_BYTE + ii]);
            }
          }
        }
      }
      return bytes;
    })();
    return function (data) {
      data = data.toString();
      if (data.length > n) {
        throw new Error('data block too looong');
      }
      var result = '00'.repeat(h);
      for (var i = 0; i != data.length; i++) {
        result = sxor(result, byte_lookup[i][data.charCodeAt(i)]);
      }
      return result;
    };
  };
})(8, 36);

var hasher = function (k, seed) {
  var prng = minstd_rand0(seed);
  var fns = [];
  for (var i = 0; i != k; i++) fns.push(h3(prng()));
  return function(data) {
    return fns.map(function (fn) { return fn(data); });
  }
}
