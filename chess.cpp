#include <iostream>
#include <vector>
#include <set>
#include <deque>
#include <algorithm>
using namespace std;

class Piece {
public:
	bool white;
	Piece(bool white = 0) {
		this->white = white;
	}
	virtual char symbol()=0;
	virtual ~Piece() {
	}
};

class Rook: public Piece {
public:
	Rook(bool white) :
			Piece(white) {
	}

	char symbol() override {
		if (white)
			return 'R';
		else
			return 'r';
	}
};

class Knight: public Piece {
public:
	Knight(bool white) :
			Piece(white) {
	}

	char symbol() override {
		if (white)
			return 'K';
		else
			return 'k';
	}
};

class Bishop: public Piece {
public:
	Bishop(bool white) :
			Piece(white) {
	}
	char symbol() override {
		if (white)
			return 'B';
		else
			return 'b';
	}
};

class Queen: public Piece {
public:
	Queen(bool white) :
			Piece(white) {
	}
	char symbol() override {
		if (white)
			return 'Q';
		else
			return 'q';
	}
};

class King: public Piece {
public:
	King(bool white) :
			Piece(white) {
	}
	char symbol() override {
		if (white)
			return 'S';
		else
			return 's';
	}
};

class Pawn: public Piece {
public:
	Pawn(bool white) :
			Piece(white) {
	}
	char symbol() override {
		if (white)
			return 'P';
		else
			return 'p';
	}
};

class Board {
	vector<vector<Piece*>> board;
public:
	Board() {
		for (int i = 0; i < 8; i++) {
			vector<Piece*> v(8);
			board.push_back(v);
		}
	}

	Board(const Board *board) :
			Board() {
		for (int i = 0; i < 8; ++i)
			for (int j = 0; j < 8; ++j)
				this->board[i][j] = board->board[i][j];
	}

	void showBoard() {
		cout << "    0 1 2 3 4 5 6 7 " << endl;
		cout << "  -------------------" << endl;
		for (int i = 0; i < 8; i++) {
			cout << i << " | ";
			for (int j = 0; j < 8; j++) {
				if (this->board[i][j])
					cout << board[i][j]->symbol() << " ";
				else
					cout << ". ";
			}
			cout << "|" << endl;
		}
		cout << "  -------------------" << endl;
	}

	void addPiece(int x, int y, Piece *piece) {
		board[x][y] = piece;
	}
	friend class BoardController;
	friend class LegalMoveset;
};

class LegalMoveset {
	Board *board;
public:
	LegalMoveset(Board *board) :
			board(board) {
	}
	set<pair<int, int>> RookLegalMoves(int i, int j, bool white) {
		set<pair<int, int>> ret;
		for (int k = i - 1; k >= 0; k--) {
			if (this->board->board[k][j]) {
				if (this->board->board[k][j]->white != white)
					ret.insert(make_pair(k, j));
				break;
			}
			ret.insert(make_pair(k, j));
		}
		for (int k = i + 1; k < 8; k++) {
			if (this->board->board[k][j]) {
				if (this->board->board[k][j]->white != white)
					ret.insert(make_pair(k, j));
				break;
			}
			ret.insert(make_pair(k, j));
		}
		for (int k = j - 1; k >= 0; k--) {
			if (this->board->board[i][k]) {
				if (this->board->board[i][k]->white != white)
					ret.insert(make_pair(i, k));
				break;
			}
			ret.insert(make_pair(i, k));
		}
		for (int k = j + 1; k < 8; k++) {
			if (this->board->board[i][k]) {
				if (this->board->board[i][k]->white != white)
					ret.insert(make_pair(i, k));
				break;
			}
			ret.insert(make_pair(j, k));
		}
		return ret;
	}

	set<pair<int, int>> BishopLegalMoves(int i, int j, bool white) {
		set<pair<int, int>> ret;
		for (int d = 1; i - d >= 0 && j - d >= 0; d++) {
			if (this->board->board[i - d][j - d]) {
				if (this->board->board[i - d][j - d]->white != white)
					ret.insert(make_pair(i - d, j - d));
				break;
			}
			ret.insert(make_pair(i - d, j - d));
		}
		for (int d = 1; i + d < 8 && j - d >= 0; d++) {
			if (this->board->board[i + d][j - d]) {
				if (this->board->board[i + d][j - d]->white != white)
					ret.insert(make_pair(i + d, j - d));
				break;
			}
			ret.insert(make_pair(i + d, j - d));
		}
		for (int d = 1; i - d >= 0 && j + d < 8; d++) {
			if (this->board->board[i - d][j + d]) {
				if (this->board->board[i - d][j + d]->white != white)
					ret.insert(make_pair(i - d, j + d));
				break;
			}
			ret.insert(make_pair(i - d, j + d));
		}
		for (int d = 1; i + d < 8 && j + d < 8; d++) {
			if (this->board->board[i + d][j + d]) {
				if (this->board->board[i + d][j + d]->white != white)
					ret.insert(make_pair(i + d, j + d));
				break;
			}
			ret.insert(make_pair(i + d, j + d));
		}
		return ret;
	}

	set<pair<int, int>> QueenLegalMoves(int i, int j, bool white) {
		set<pair<int, int>> ret = this->RookLegalMoves(i, j, white);
		set<pair<int, int>> tmp = this->BishopLegalMoves(i, j, white);
		for (auto p : tmp) {
			ret.insert(p);
		}
		return ret;
	}

	set<pair<int, int>> KnightLegalMoves(int i, int j, bool white) {
		set<pair<int, int>> d;
		d.insert(make_pair(-2, -1));
		d.insert(make_pair(-2, 1));
		d.insert(make_pair(-1, -2));
		d.insert(make_pair(-1, 2));
		d.insert(make_pair(2, -1));
		d.insert(make_pair(2, 1));
		d.insert(make_pair(1, -2));
		d.insert(make_pair(1, 2));
		set<pair<int, int>> ret;
		for (auto p : d) {
			if ((i + p.first >= 0) && (i + p.first < 8) && (j + p.second >= 0)
					&& (j + p.second < 8)
					&& ((!this->board->board[i + p.first][j + p.second])
							|| this->board->board[i + p.first][j + p.second]->white
									!= white))
				ret.insert(make_pair(i + p.first, j + p.second));
		}
		return ret;
	}

	set<pair<int, int>> KingLegalMoves(int i, int j, bool white) {
		set<pair<int, int>> d;
		d.insert(make_pair(-1, -1));
		d.insert(make_pair(-1, 0));
		d.insert(make_pair(-1, 1));
		d.insert(make_pair(1, -1));
		d.insert(make_pair(1, 0));
		d.insert(make_pair(1, 1));
		d.insert(make_pair(0, -1));
		d.insert(make_pair(0, 1));
		set<pair<int, int>> ret;
		for (auto p : d) {
			if (i + p.first >= 0 && i + p.first < 8 && j + p.second >= 0
					&& j + p.second < 8
					&& ((!this->board->board[i + p.first][j + p.second])
							|| this->board->board[i + p.first][j + p.second]->white
									!= white))
				ret.insert(make_pair(i + p.first, j + p.second));
		}
		return ret;
	}

	set<pair<int, int>> PawnLegalMoves(int i, int j, bool white) {
		set<pair<int, int>> ret;
		if (white) {
			if (i - 1 >= 0 && !this->board->board[i - 1][j])
				ret.insert(make_pair(i - 1, j));
			if (i - 1 >= 0 && j - 1 >= 0 && this->board->board[i - 1][j - 1]
					&& this->board->board[i - 1][j - 1]->white != white)
				ret.insert(make_pair(i - 1, j - 1));
			if (i - 1 >= 0 && j + 1 < 8 && this->board->board[i - 1][j + 1]
					&& this->board->board[i - 1][j + 1]->white != white)
				ret.insert(make_pair(i - 1, j + 1));
		} else {
			if (i + 1 < 8 && !this->board->board[i + 1][j])
				ret.insert(make_pair(i + 1, j));
			if (i + 1 < 8 && j - 1 >= 0 && this->board->board[i + 1][j - 1]
					&& this->board->board[i + 1][j - 1]->white != white)
				ret.insert(make_pair(i + 1, j - 1));
			if (i + 1 < 8 && j + 1 < 8 && this->board->board[i + 1][j + 1]
					&& this->board->board[i + 1][j + 1]->white != white)
				ret.insert(make_pair(i + 1, j + 1));
		}
		return ret;
	}

};

class UndoBoardStack {
	deque<Board*> stk;
public:
	void push(Board *board) {
		this->stk.push_back(board);
	}
	Board* pop() {
		Board *ret = new Board(this->stk.back());
		this->stk.pop_back();
		return ret;
	}
	bool empty() {
		return this->stk.empty();
	}
	void printParty() {
		int i = 0;
		for (auto it = this->stk.begin(); it != this->stk.end(); ++i, ++it) {
			cout << "Move " << i<<endl;;
			(*it)->showBoard();
		}
	}
};

class BoardController {
	Board *board;
	LegalMoveset *lm;
	UndoBoardStack undo;
	bool isWhiteMove;

	void showLegalMoves(set<pair<int, int>> moves) {
		cout << "    0 1 2 3 4 5 6 7 " << endl;
		cout << "  -------------------" << endl;
		for (int i = 0; i < 8; i++) {
			cout << i << " | ";
			for (int j = 0; j < 8; j++) {
				if (moves.count(make_pair(i, j)) != 0)
					cout << "* ";
				else if (this->board->board[i][j])
					cout << this->board->board[i][j]->symbol() << " ";
				else
					cout << ". ";
			}
			cout << "|" << endl;
		}
		cout << "  -------------------" << endl;

		cout << "Your legal moves:" << endl;
		for (auto move : moves)
			cout << move.first << " " << move.second << ", ";
	}

	void makeMove() {
		set<pair<int, int>> moves;
		while (1) {
			this->showBoard();
			if (this->isWhiteMove)
				cout << "White ";
			else
				cout << "Black ";
			cout << "move" << endl;
			int x { }, y { }, x1 { }, y1 { };
			cout << "Select a piece to move (y and x 0 to 7)" << endl;
			cin >> x >> y;
			cin.ignore();
			if (x < 0 || y < 0 || x > 7 || y > 7) {
				cout << "Wrong coordinates!" << endl;
				continue;
			} else if (!this->board->board[x][y]) {
				cout << "No piece there!" << endl;
				continue;
			} else if (this->board->board[x][y]->white != this->isWhiteMove) {
				cout << "This is not your piece!" << endl;
				continue;
			} else {
				switch (this->board->board[x][y]->symbol()) {
				case 'R':
				case 'r':
					moves = this->lm->RookLegalMoves(x, y, this->isWhiteMove);
					break;
				case 'K':
				case 'k':
					moves = this->lm->KnightLegalMoves(x, y, this->isWhiteMove);
					break;
				case 'B':
				case 'b':
					moves = this->lm->BishopLegalMoves(x, y, this->isWhiteMove);
					break;
				case 'S':
				case 's':
					moves = this->lm->KingLegalMoves(x, y, this->isWhiteMove);
					break;
				case 'Q':
				case 'q':
					moves = this->lm->QueenLegalMoves(x, y, this->isWhiteMove);
					break;
				case 'P':
				case 'p':
					moves = this->lm->PawnLegalMoves(x, y, this->isWhiteMove);
					break;
				}
				if (moves.empty()) {
					cout << "You have no moves with that piece!" << endl;
					continue;
				}
				showLegalMoves(moves);
			}
			cout << "Enter your move:" << endl;
			cin >> x1 >> y1;
			if (moves.count(make_pair(x1, y1)) == 0) {
				cout << "Illegal move!" << endl;
				continue;
			}
			this->undo.push(new Board(this->board));
			this->board->board[x1][y1] = this->board->board[x][y];
			this->board->board[x][y] = nullptr;
			this->isWhiteMove = !(this->isWhiteMove);
			return;
		}
	}

public:
	BoardController() {
		this->board = new Board;
		this->board->addPiece(0, 0, new Rook(0));
		this->board->addPiece(0, 1, new Knight(0));
		this->board->addPiece(0, 2, new Bishop(0));
		this->board->addPiece(0, 3, new King(0));
		this->board->addPiece(0, 4, new Queen(0));
		this->board->addPiece(0, 5, new Bishop(0));
		this->board->addPiece(0, 6, new Knight(0));
		this->board->addPiece(0, 7, new Rook(0));

		this->board->addPiece(1, 0, new Pawn(0));
		this->board->addPiece(1, 1, new Pawn(0));
		this->board->addPiece(1, 2, new Pawn(0));
		this->board->addPiece(1, 3, new Pawn(0));
		this->board->addPiece(1, 4, new Pawn(0));
		this->board->addPiece(1, 5, new Pawn(0));
		this->board->addPiece(1, 6, new Pawn(0));
		this->board->addPiece(1, 7, new Pawn(0));

		this->board->addPiece(7, 0, new Rook(1));
		this->board->addPiece(7, 1, new Knight(1));
		this->board->addPiece(7, 2, new Bishop(1));
		this->board->addPiece(7, 3, new King(1));
		this->board->addPiece(7, 4, new Queen(1));
		this->board->addPiece(7, 5, new Bishop(1));
		this->board->addPiece(7, 6, new Knight(1));
		this->board->addPiece(7, 7, new Rook(1));

		this->board->addPiece(6, 0, new Pawn(1));
		this->board->addPiece(6, 1, new Pawn(1));
		this->board->addPiece(6, 2, new Pawn(1));
		this->board->addPiece(6, 3, new Pawn(1));
		this->board->addPiece(6, 4, new Pawn(1));
		this->board->addPiece(6, 5, new Pawn(1));
		this->board->addPiece(6, 6, new Pawn(1));
		this->board->addPiece(6, 7, new Pawn(1));

		this->lm = new LegalMoveset(this->board);
		this->isWhiteMove = true;
	}
	void showBoard() {
		this->board->showBoard();
	}

	void undoMove() {
		if (this->undo.empty()) {
			cout << "Can't undo, no moves made!";
			return;
		}
		this->board = this->undo.pop();
		this->lm = new LegalMoveset(this->board);
		this->isWhiteMove = !this->isWhiteMove;
	}

	void control() {
		char command { };
		while (command != 'q') {
			this->showBoard();
			cout << "Enter command" << endl;
			cout << "q to quit, u to undo, anything else to make a move"
					<< endl;
			cin >> command;
			cin.ignore();
			if (command == 'q'){
				this->undo.push(this->board);
				return;}
			if (command == 'u') {
				undoMove();
				continue;
			}
			this->makeMove();
		}
	}
	void printParty() {
		this->undo.printParty();
	}
};

int main() {
	BoardController board;

	board.control();

	cout << "Party recording:" << endl;
	board.printParty();

	return 0;
}
