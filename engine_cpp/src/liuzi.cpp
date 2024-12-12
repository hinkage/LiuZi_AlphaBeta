#define USE_EM 1

#include "./alphabeta.h"
#include "./game.h"
#ifdef USE_EM
#include <emscripten/bind.h>
#endif

AlphaBeta alphabeta(game, 10);

Move alphabeta_search(int max_piece) {
    printf("max_piece: %d\n", max_piece);
    alphabeta.m_best_move = {{0, 0}, {0, 0}};
    alphabeta.alphabeta(max_piece, 0, alphabeta.m_min_score,
                        alphabeta.m_max_score);
    return alphabeta.m_best_move;
}

#ifdef USE_EM
EMSCRIPTEN_BINDINGS(my_module) {
    emscripten::class_<Vec2i>("Vec2i")
        .constructor<>()
        .property("x", &Vec2i::x)
        .property("y", &Vec2i::y);

    emscripten::class_<Move>("Move")
        .constructor<>()
        .property("m_from", &Move::m_from)
        .property("m_to", &Move::m_to);

    emscripten::class_<GameResult>("GameResult")
        .constructor<>()
        .property("is_over", &GameResult::is_over)
        .property("winner", &GameResult::winner);

    emscripten::register_vector<Move>("vector<Move>");
    emscripten::register_vector<int>("vector<int>");

    emscripten::class_<BoardState>("BoardState")
        .smart_ptr_constructor("BoardState", &std::make_shared<BoardState>)
        .property("m_pieces", &BoardState::m_pieces)
        .property("m_pieces_count", &BoardState::m_pieces_count)
        .property("m_turned_piece", &BoardState::m_turned_piece);

    emscripten::class_<Game>("Game")
        .function("check_is_game_over", &Game::check_is_game_over)
        .function("get_available_moves", &Game::get_available_moves)
        .function("do_move", &Game::do_move, emscripten::allow_raw_pointers())
        .function("undo_the_last_move", &Game::undo_the_last_move)
        .function("get_board_state", &Game::get_board_state,
                  emscripten::return_value_policy::reference());

    emscripten::function("reset_game", &reset_game);
    emscripten::function("get_game", &get_game,
                         emscripten::return_value_policy::reference());
    emscripten::function("alphabeta_search", &alphabeta_search);
}
#endif
