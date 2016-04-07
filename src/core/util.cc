#include <util.h>
#include <debug.h>

void app::fold_str(std::string& line, size_t size) {
  if (line.length() <= size) return;
  for (int i = size; i < line.length(); i += size) {
    for (int j = 0; j < size && i + j < line.length(); j++) {
      DEBUG("FOLD line[" << j << "]=" << HEX(line[j]) << ", line[" << i + j << "]=" << HEX(line[i + j]));
      line[j] ^= line[i + j];
      DEBUG("FOLD line[" << j << "] XOR line[" << i + j << "]=" << HEX(line[j]));
    }
  }
  if (line.length() > size) line.resize(size);
}
