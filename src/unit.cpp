#include "gamehandler.h"

Unit::Unit(int xN, int yN, color PlayerColorN) {
	x = xN;
	y = yN;
	PlayerColor = PlayerColorN;
}

Unit::~Unit() {
}

bool	Unit::checkBorderMove(int fromX, int fromY, int toX, int toY) {
	if ((toX >= 0 && toX < BOARD_SIZE && toY >= 0 && toY < BOARD_SIZE)
			&& (toX != fromX || toY != fromY))
		return true;
	return false;
}

Pawn::Pawn(int xN, int yN, color PlayerColorN)
		: Unit(xN, yN, PlayerColorN) {
	attack = false;
	type = pawn;
}

Rook::Rook(int xN, int yN, color PlayerColorN)
	: Unit(xN, yN, PlayerColorN) {
	type = rook;
}

Bishop::Bishop(int xN, int yN, color PlayerColorN)
	: Unit(xN, yN, PlayerColorN) {
	type = bishop;
}

Knight::Knight(int xN, int yN, color PlayerColorN)
	: Unit(xN, yN, PlayerColorN) {
	type = knight;
}

Queen::Queen(int xN, int yN, color PlayerColorN)
	: Unit(xN, yN, PlayerColorN) {
	type = queen;
}

King::King(int xN, int yN, color PlayerColorN)
	: Unit(xN, yN, PlayerColorN) {
	type = king;
}

bool	Queen::moveChess(int fromX, int fromY, int toX, int toY) {
	if (checkBorderMove(fromX, fromY, toX, toY)) {
		if (((toX - fromX) == (toY - fromY))
			||  ((toX - fromX) == (fromY - toY))
			||	(toX == fromX) || (toY == fromY)) {
			return true;
		}
	}
	return false;
}

bool	Bishop::moveChess(int fromX, int fromY, int toX, int toY) {
	if (checkBorderMove(fromX, fromY, toX, toY)) {
		if (((toX - fromX) == (toY - fromY))
			||  ((toX - fromX) == (fromY - toY))) {
			return true;
		}
	}
	return false;
}

bool	Rook::moveChess(int fromX, int fromY, int toX, int toY) {
	if (checkBorderMove(fromX, fromY, toX, toY)) {
		if ((toX == fromX && toY != fromY) ||
			(toY == fromY && toX != fromX)) {
			return true;
		}
	}
	return false;
}

bool	Knight::moveChess(int fromX, int fromY, int toX, int toY) {
	if (checkBorderMove(fromX, fromY, toX, toY)) {
		if (((toY == fromY - 2 || toY == fromY + 2)
			&& (toX == fromX + 1 || toX == fromX - 1))
			|| ((toX == fromX - 2 || toX == fromX + 2)
			&& (toY == fromY + 1 || toY == fromY - 1))) {
			return true;
		}
	}
	return false;
}

bool	Pawn::moveChess(int fromX, int fromY, int toX, int toY)
{
	if (checkBorderMove(fromX, fromY, toX, toY)) {
		if (PlayerColor == white) {
			if (attack == false && ((toY >= (BOARD_SIZE / 2) && toY == fromY - 2)
				|| (toY == fromY - 1)) && toX == fromX) {
				return true;
			}
			else if (attack == true && toY == fromY - 1
					 && (toX == fromX - 1 || toX == fromX + 1)) {
				attack = false;
				return true;
			}
		}
		else if (PlayerColor == black) {
			if (attack == false && ((toY <= (BOARD_SIZE / 2) && toY == fromY + 2)
				|| (toY == fromY + 1)) && toX == fromX) {
				return true;
			}
			else if (attack == true && toY == fromY + 1
					 && (toX == fromX - 1 || toX == fromX + 1)) {
				attack = false;
				return true;
			}
		}
	}
	attack = false;
	return false;
}

bool	King::moveChess(int fromX, int fromY, int toX, int toY) {
	if (checkBorderMove(fromX, fromY, toX, toY)) {
		if (toX >= fromX - 1 && toX <= fromX + 1 &&
			toY >= fromY - 1 && toY <= fromY + 1) {
			return true;
		}
	}
	return false;
}
