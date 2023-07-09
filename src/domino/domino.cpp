#include "domino.h"
#include <array>
#include <iostream>
#include <ostream>
#include <random>
#include <vector>

namespace domino {
std::ostream& operator<<(std::ostream& os, const Tile& tile) {
  return os << tile.left << ":" << tile.right;
}

std::ostream& operator<<(std::ostream& os, const Player& player) {
  for (Tile tile : player.hand) {
    os << tile << ",";
  }
  return os;
}

Game::Game() {
  // TODO: allow for 2-4 players
  const int numPlayers = 4;

  std::vector<Tile> tiles;

  const int maxPips = 6;

  // Generate tiles
  for (int i = 0; i <= maxPips; i++) {
    for (int j = i; j <= maxPips; j++) {
      tiles.push_back(Tile{i, j});
    }
  }

  // Shuffle tiles
  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(tiles.begin(), tiles.end(), g);

  const int numTiles = (maxPips + 1) * (maxPips + 2) / 2;
  const int handSize = numTiles / numPlayers;

  // Distribute tiles to each player
  for (int i = 0; i < numPlayers; i++) {
    std::vector<Tile> hand{};
    for (int j = 0; j < handSize; j++) {
      hand.push_back(tiles[(i * handSize) + j]);
    }
    players.push_back(Player{hand});
  }
}

void Game::move(Move move) {}

}
