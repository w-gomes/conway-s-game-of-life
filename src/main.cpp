#include <array>

#include "game.hpp"

int main() {
  using namespace Tre;
  [[maybe_unused]] constexpr auto pattern1 = std::array<Coord, 20>{{
    {8ULL, 8ULL},  {8ULL, 9ULL},  {8ULL, 10ULL}, {7ULL, 10ULL}, {9ULL, 10ULL},

    {8ULL, 13ULL}, {8ULL, 14ULL}, {8ULL, 15ULL}, {8ULL, 16ULL}, {8ULL, 17ULL},
    {8ULL, 18ULL}, {7ULL, 13ULL}, {9ULL, 13ULL}, {7ULL, 18ULL}, {9ULL, 18ULL},

    {8ULL, 20ULL}, {7ULL, 20LL},  {9ULL, 20ULL}, {8ULL, 21ULL}, {8ULL, 22ULL},

  }};

  [[maybe_unused]] constexpr auto pattern2 = std::array<Coord, 4>{{
    {8ULL, 9ULL},
    {8ULL, 10ULL},
    {9ULL, 9ULL},
    {9ULL, 10ULL},
  }};

  // Oscillators
  [[maybe_unused]] constexpr auto pattern3 = std::array<Coord, 17>{{
    {7ULL, 8ULL},
    {8ULL, 8ULL},
    {9ULL, 8ULL},

    {11ULL, 11ULL},
    {11ULL, 12ULL},
    {11ULL, 13ULL},
    {12ULL, 12ULL},
    {12ULL, 13ULL},
    {12ULL, 14ULL},

    {15ULL, 15ULL},
    {15ULL, 16ULL},
    {16ULL, 15ULL},
    {16ULL, 16ULL},
    {17ULL, 17ULL},
    {17ULL, 18ULL},
    {18ULL, 17ULL},
    {18ULL, 18ULL},
  }};

  auto game = Game<30, 30>();
  game.run(pattern3);

  return 0;
}
