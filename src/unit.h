#ifndef UNIT_H
#define UNIT_H
#include <QAbstractListModel>

enum color {undef, white, black};

enum shape {
	def, pawn, rook, knight,
	bishop,	queen, king
};

class Unit
{
public:
	shape type;
    int x;
	int y;
    color PlayerColor;

	Unit(int xN, int yN, color PlayerColorN);
	virtual bool    moveChess(int fromX, int fromY, int toX, int toY) = 0;
	virtual			~Unit() = 0;
    bool            checkBorderMove(int fromX, int fromY, int toX, int toY);
};

class Pawn : public Unit
{
   public :
	bool attack;
	Pawn(int xN, int yN, color PlayerColorN);
    Q_INVOKABLE virtual bool moveChess(int fromX, int fromY, int toX, int toY);
};

class Rook : public Unit
{
public :
	Rook(int xN, int yN, color PlayerColorN);
	Q_INVOKABLE virtual bool moveChess(int fromX, int fromY, int toX, int toY);
};

class Bishop : public Unit
{
public :
	Bishop(int xN, int yN, color PlayerColorN);
	Q_INVOKABLE virtual bool moveChess(int fromX, int fromY, int toX, int toY);
};

class Knight : public Unit
{
public :
	Knight(int xN, int yN, color PlayerColorN);
	Q_INVOKABLE virtual bool moveChess(int fromX, int fromY, int toX, int toY);
};

class Queen : public Unit
{
public :
	Queen(int xN, int yN, color PlayerColorN);
	Q_INVOKABLE virtual bool moveChess(int fromX, int fromY, int toX, int toY);
};

class King : public Unit
{
public :
	King(int xN, int yN, color PlayerColorN);
	Q_INVOKABLE virtual bool moveChess(int fromX, int fromY, int toX, int toY);
};
#endif // UNIT_H
