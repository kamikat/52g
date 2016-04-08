#include <iostream>
#include <fstream>
#include <docopt.h>
#include <bloom_filter.h>
#include <util.h>
#include <debug.h>
#include <nghttp2/asio_http2_server.h>

const char USAGE[] =
R"(
  RESTful API server to query bloom filter index.

  Usage:
    servidx <file> [-H <hostname>] [-p <port>]

  Options:
    file                   bloom filter index file
    -H, --host <hostname>  hostname to listen [default: localhost]
    -p, --port <port>      port to listen [default: 8088]
    -h, --help             print help message
)";

using namespace app;
using namespace std;
using namespace nghttp2::asio_http2;
using namespace nghttp2::asio_http2::server;

bloom_filter load(const string& file) {
  ifstream ifs { file, ios::binary };
  Header header;
  ifs.read((char*) &header, sizeof(header));
  DEBUG("LOAD k=" << header.k << ", m=" << header.m);
  bloom_filter bf(header.k, header.m);
  auto& storage = bf.storage();
  char* data = (char*) storage.bits_.data();
  size_t size = sizeof(bf::bitvector::block_type) * storage.blocks();
  ifs.read(data, size);
  return move(bf);
}

int search(const bloom_filter& bf, string line) {
  fold_str(line, bf::default_hash_function::max_obj_size);
  return bf.lookup(line);
}

int main(int argc, const char* argv[]) {
  auto args = docopt::docopt(USAGE, { argv + 1, argv + argc });
  bloom_filter bf = load(args["<file>"].asString());

  boost::system::error_code ec;
  http2 server;

  server.handle("/search", [&bf](const request &req, const response &res) {
    uri_ref uri = req.uri();
    string query = uri.raw_query;
    // TODO parse raw query string
    DEBUG("HTTP " << req.method() << " " << uri.raw_path);
    string body;
    if (search(bf, query)) {
      body = "{ \"found\": true }\n";
    } else {
      body = "{ \"found\": false }\n";
    }
    res.write_head(200);
    res.end(body);
  });

  string hostname = args["--host"].asString(), port = args["--port"].asString();
  cerr << "server listening " << hostname << ":" << port << endl;
  if (server.listen_and_serve(ec, hostname, port)) {
    std::cerr << "error: " << ec.message() << std::endl;
  }

  return 0;
}
