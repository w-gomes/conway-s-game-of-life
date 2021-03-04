#include <array>

#include "game.hpp"
#include "parser.hpp"

int main() {
  using namespace Tre;
  const auto pattern = parse();
  auto game          = Game<30, 30>();
  game.run(pattern);

  return 0;
}
