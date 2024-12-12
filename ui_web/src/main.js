import "./style.css";

const elBoard = document.querySelector(".board");
const elText = document.querySelector(".human-piece");
const elReset = document.querySelector(".button-reset");
const elUndo = document.querySelector(".button-undo");
const elAI = document.querySelector(".button-ai");
const elSwitch = document.querySelector(".button-switch");
const boardPieces = [1, 1, 1, 1, 1, -1, -1, 1, 0, -1, -1, 0, 0, 0, 0, 0];
const size = 150;
let clickedPiece = null;
let humanPiece = 0;
const game = liuzi.get_game();
const boardState = game.get_board_state();

elReset.onclick = function () {
  console.log("reset");
  liuzi.reset_game();
  if (boardState.m_turned_piece == 1 - humanPiece) {
    let m = liuzi.alphabeta_search(1 - humanPiece);
    game.do_move(m);
  }
  drawPieces();
};

elUndo.onclick = function () {
  console.log("undo");
  if (boardState.m_turned_piece == humanPiece) {
    game.undo_the_last_move();
    game.undo_the_last_move();
    drawPieces();
  }
};

elAI.onclick = function () {
  console.log("AI");
  if (boardState.m_turned_piece == humanPiece) {
    let m = liuzi.alphabeta_search(humanPiece);
    console.log("search:", m.m_from.x, m.m_from.y, m.m_to.x, m.m_to.y);
    game.do_move(m);
    drawPieces();

    setTimeout(function () {
      m = liuzi.alphabeta_search(1 - humanPiece);
      console.log("search:", m.m_from.x, m.m_from.y, m.m_to.x, m.m_to.y);
      game.do_move(m);
      drawPieces();
    }, 100);
  }
};

elSwitch.onclick = function () {
  console.log("switch");
  humanPiece = 1 - humanPiece;
  if (boardState.m_turned_piece == 1 - humanPiece) {
    let m = liuzi.alphabeta_search(1 - humanPiece);
    game.do_move(m);
    drawPieces();
  }
};

function onClickBoard(e) {
  const row = Math.floor(e.offsetY / 150);
  const column = Math.floor(e.offsetX / 150);
  const value = boardPieces[row * 4 + column];
  if (value !== -1) {
    return;
  }
  if (!clickedPiece) {
    return;
  }
  if (humanPiece === boardPieces[clickedPiece.row * 4 + clickedPiece.column]) {
    console.log("Try make a move: ", clickedPiece, "to", { row, column });
    check_do_move(clickedPiece, { row, column });
    drawPieces();
    if (boardState.m_turned_piece == 1 - humanPiece) {
      const m = liuzi.alphabeta_search(1 - humanPiece);
      console.log("search:", m.m_from.x, m.m_from.y, m.m_to.x, m.m_to.y);
      game.do_move(m);
      drawPieces();
    }
  }
}

function unselectClickedPiece() {
  const pieces = elBoard.querySelectorAll(".piece");
  for (let i = 0; i < pieces.length; i++) {
    pieces[i].classList.remove("clicked");
  }
  clickedPiece = null;
}

function onClickPiece(e) {
  console.log(this._piece);
  unselectClickedPiece();
  this.classList.add("clicked");
  clickedPiece = this._piece;
  e.stopPropagation();
}

elBoard.onclick = onClickBoard;

function check_do_move(from, to) {
  const available_moves = game.get_available_moves(boardState.m_turned_piece);
  for (let i = 0; i < available_moves.size(); i++) {
    const move = available_moves.get(i);
    if (
      move.m_from.x == from.row &&
      move.m_from.y == from.column &&
      move.m_to.x == to.row &&
      move.m_to.y == to.column
    ) {
      const vfrom = new liuzi.Vec2i();
      vfrom.x = from.row;
      vfrom.y = from.column;
      const vto = new liuzi.Vec2i();
      vto.x = to.row;
      vto.y = to.column;
      const move = new liuzi.Move();
      move.m_from = vfrom;
      move.m_to = vto;
      game.do_move(move);
      return;
    }
  }
}

function drawPieces() {
  elText.lastElementChild.textContent = humanPiece === 0 ? "黑方" : "白方";
  for (let j = 0; j < boardState.m_pieces.size(); j++) {
    boardPieces[j] = boardState.m_pieces.get(j);
  }
  const pieces = elBoard.querySelectorAll(".piece");
  for (let i = 0; i < pieces.length; i++) {
    elBoard.removeChild(pieces[i]);
  }
  clickedPiece = null;
  for (let i = 0; i < 16; i++) {
    const value = boardPieces[i];
    if (value == -1) {
      continue;
    }
    const row = Math.floor(i / 4);
    const column = i % 4;
    elBoard.insertAdjacentHTML(
      "beforeend",
      `
      <div class="piece ${value == 0 ? "black" : "white"}"
          style="top: ${row * size + 75}px; left: ${column * size + 75}px;">
      </div>
      `,
    );
    const elPiece = elBoard.lastElementChild;
    elPiece.dataset.position = `${row},${column}`;
    elPiece._piece = {
      value,
      row,
      column,
    };
    elPiece.onclick = onClickPiece;
    row * size;
  }
}

elReset.click();
