#include "game.h"

Game game;

void reset_game() { game = Game(); }

Game &get_game() { return game; }

int BoardState::get_piece(const Vec2i &p) {
    if (p.x < 0 || p.x >= 4 || p.y < 0 || p.y >= 4) {
        return -2;
    }
    return m_pieces[p.x * 4 + p.y];
}

void BoardState::set_piece(const Vec2i &p, int value) {
    if (p.x < 0 || p.x >= 4 || p.y < 0 || p.y >= 4) {
        return;
    }
    m_pieces[p.x * 4 + p.y] = value;
}

std::string BoardState::to_string() {
    std::string s;
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            auto piece = get_piece({r, c});
            if (piece == -1) {
                s += "_";
            } else if (piece == 0) {
                s += "O";
            } else if (piece == 1) {
                s += "X";
            }
        }
        s += "\n";
    }
    return s;
}

std::vector<Move> Game::get_available_moves(int player_piece) {
    std::vector<Move> out;
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            Vec2i pos{r, c};
            if (m_board_state.get_piece(pos) != player_piece) {
                continue;
            }
            Vec2i right{r, c + 1};
            if (m_board_state.get_piece(right) == -1) {
                out.push_back({pos, right});
            }
            Vec2i left{r, c - 1};
            if (m_board_state.get_piece(left) == -1) {
                out.push_back({pos, left});
            }
            Vec2i down{r + 1, c};
            if (m_board_state.get_piece(down) == -1) {
                out.push_back({pos, down});
            }
            Vec2i up{r - 1, c};
            if (m_board_state.get_piece(up) == -1) {
                out.push_back({pos, up});
            }
        }
    }
    return out;
}

void Game::do_move(Move &move) {
    m_history.push_back(m_board_state);
    m_board_state.set_piece(move.m_to, m_board_state.get_piece(move.m_from));
    m_board_state.set_piece(move.m_from, -1);
    check_eating_pieces(move);
    m_board_state.m_turned_piece = 1 - m_board_state.m_turned_piece;
}

void Game::undo_the_last_move() {
    if (m_history.size() > 0) {
        m_board_state = m_history.back();
        m_history.pop_back();
    } else {
        printf("Can not undo\n");
    }
}

GameResult Game::check_is_game_over() {
    GameResult result;
    if (m_board_state.m_pieces_count[0] <= 0) {
        result.is_over = true;
        result.winner = 1;
        return result;
    }
    if (m_board_state.m_pieces_count[1] <= 0) {
        result.is_over = true;
        result.winner = 0;
        return result;
    }
    std::vector<Move> available_moves =
        get_available_moves(m_board_state.m_turned_piece);
    if (available_moves.size() == 0) {
        result.is_over = true;
        result.winner = 1 - m_board_state.m_turned_piece;
        return result;
    }
    result.is_over = false;
    result.winner = -1;
    return result;
}

void Game::check_eating_pieces(Move &move) {
    auto to = move.m_to;
    int moved_piece = m_board_state.get_piece(to);
    int opposide_piece = 1 - moved_piece;
    Vec2i directions[4] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
    for (int i = 0; i < 4; i++) {
        auto d = directions[i];
        auto d1 = to + d;
        if (m_board_state.get_piece(d1) != moved_piece) {
            continue;
        }
        auto d2 = d1 + d;
        auto dn1 = to - d;
        auto d3 = d2 + d;
        auto piece_d2 = m_board_state.get_piece(d2);
        if (piece_d2 == opposide_piece) {
            if (m_board_state.get_piece(dn1) < 0 &&
                m_board_state.get_piece(d3) < 0) {
                m_board_state.set_piece(d2, -1);
                m_board_state.m_pieces_count[opposide_piece] -= 1;
            }
        } else if (m_board_state.get_piece(dn1) == opposide_piece) {
            auto dn2 = dn1 - d;
            if (m_board_state.get_piece(dn2) < 0 && piece_d2 < 0) {
                m_board_state.set_piece(dn1, -1);
                m_board_state.m_pieces_count[opposide_piece] -= 1;
            }
        }
    }
}

BoardState &Game::get_board_state() { return m_board_state; }
