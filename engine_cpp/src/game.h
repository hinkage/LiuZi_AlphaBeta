#pragma once

#include "vec2.h"
#include <string>
#include <vector>

struct Move {
    Vec2i m_from;
    Vec2i m_to;
};

struct BoardState {
    // 0表示黑色棋子，1表示白色棋子。黑色棋子先行
    // 当玩家选择执白后行时，棋盘的上下翻转在UI层实现，这里不考虑
    std::vector<int> m_pieces = {1, 1,  1,  1, 1, -1, -1, 1,
                                 0, -1, -1, 0, 0, 0,  0,  0};
    std::vector<int> m_pieces_count = {6, 6};
    int m_turned_piece = 0;

    int get_piece(const Vec2i &p);
    void set_piece(const Vec2i &p, int value);
    std::string to_string();
};

struct GameResult {
    bool is_over;
    int winner;
};

class Game {
  public:
    std::vector<Move> get_available_moves(int player_piece);
    void do_move(Move &move);
    void undo_the_last_move();
    GameResult check_is_game_over();
    BoardState &get_board_state();

  private:
    void check_eating_pieces(Move &move);

    BoardState m_board_state;
    std::vector<BoardState> m_history;
};

extern Game game;

void reset_game();

Game &get_game();
