#include "parser.hpp"

#include <fstream>
#include <sstream>
#include <vector>

namespace Tre {
auto parse() -> std::vector<Coord> {
  auto in  = std::ifstream("input.txt");
  auto vec = std::vector<Coord>{};

  if (in.is_open()) {
    auto line = std::string{};
    while (std::getline(in, line)) {
      // skip empty line.
      if (line.empty()) { continue; }
      if (line.starts_with('#')) { continue; }
      auto stream = std::stringstream(line);
      auto x      = 0ULL;
      auto y      = 0ULL;
      stream >> x;
      stream >> y;
      vec.emplace_back(Coord(x, y));
    }
  }
  return vec;
}
}  // namespace Tre
