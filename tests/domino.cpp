#include <domino/domino.h>
#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

domino::Tile tileFromString(std::string s) {
  // example str: "5:2"
  return domino::Tile{
      std::stoi(s.substr(0, 1)),
      std::stoi(s.substr(2, 1)),
  };
}

domino::Player playerFromString(std::string s) {
  // Example str: "6:6 6:2 5:4"

  std::unordered_set<domino::Tile, domino::Tile::HashFunction> hand{};
  std::stringstream ss(s);

  std::string tileString;
  while (ss >> tileString) {
    hand.insert(tileFromString(tileString));
  }

  return domino::Player{hand};
}

std::vector<domino::Player> playersFromString(std::string s) {
  std::stringstream ss(s);
  std::string line;
  std::vector<domino::Player> players{};
  while (std::getline(ss, line)) {
    players.push_back(playerFromString(line));
  }

  return players;
}

std::deque<domino::Tile> boardFromString(std::string s) {
  // Example str "2:6 6:6 6:4"

  std::deque<domino::Tile> tiles;
  std::stringstream ss(s);

  std::string tileString;
  while (ss >> tileString) {
    tiles.push_back(tileFromString(tileString));
  }

  return tiles;
}

TEST(DominoTest, BasicAssertions) {
  domino::Domino game{std::vector<domino::Player>{}, std::deque<domino::Tile>{},
                      0};
}

TEST(DominoTest, Move) {
  // Set things up
  // TODO: maybe move to fixture
  std::vector<domino::Player> players = playersFromString(
      "1:2 6:4"
      "1:2 6:4"
      "1:2 6:4"
      "1:2 6:4");
  std::deque<domino::Tile> board = boardFromString("6:6");
  domino::PlayerId turn{0};

  domino::Domino game{players, board, turn};

  domino::MoveSet expected{{0, tileFromString("4:6"), domino::LineEnd::left},
                           {0, tileFromString("6:4"), domino::LineEnd::right}};
  // should list all valid moves for current player
  ASSERT_EQ(game.moves(), expected);
}
