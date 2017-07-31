#include "gamehandler.h"
#include <iostream>

int		GameHandler::findByPosition(int x, int y) {
	for (int i(0); i < figures.size(); ++i)
		if (figures[i]->x == x && figures[i]->y == y )
			return (i);
	return (-1);
}

bool	GameHandler::access(int fromX, int fromY, int toX, int toY)
{
	if (figures[findByPosition(fromX, fromY)]->type == knight)
		return true;
	int i = fromX - (toX < fromX ? toX + 1 : toX > fromX ? toX - 1 : toX);
	int j = fromY - (toY < fromY ? toY + 1 : toY > fromY ? toY - 1 : toY);

	while (i || j) {
		if (findByPosition(fromX - i, fromY - j) >= 0)
			return false;
		i < 0 ? i++ : i > 0 ? i-- : 0;
		j < 0 ? j++ : j > 0 ? j-- : 0;
	}
	return true;
}

void	GameHandler::addNewUnit(int x, int y, color player, shape type) {
	beginInsertRows(QModelIndex(), figures.size(), figures.size());
	switch (type) {
		case (pawn): figures << new Pawn	{x, y, player}; break;
		case (queen): figures << new Queen	{x, y, player}; break;
		case (king): figures << new King	{x, y, player}; break;
		case (bishop): figures << new Bishop	{x, y, player}; break;
		case (knight): figures << new Knight	{x, y, player}; break;
		case (rook): figures << new Rook	{x, y, player}; break;
		case (def): break;
	}
	endInsertRows();
}

void	GameHandler::prevBtn() {
	int moveIndex = history.getIndex();
	if (moveIndex == -1) return ;
	struct moveProt *move = history.getMove(moveIndex - 1);

	if (!move)
		return;
	int index = findByPosition(move->toX, move->toY);
	if (index < 0)	return;
	figures[index]->x = move->fromX;
	figures[index]->y = move->fromY;
	if (move->type)
		addNewUnit(move->toX, move->toY, move->player, move->type);
	QModelIndex bottomRight = createIndex(figures.size(), 0);
	QModelIndex topLeft = createIndex(0, 0);
	emit dataChanged(topLeft, bottomRight);
	history.setIndex(moveIndex - 1);
	turn = !turn;
}

void	GameHandler::nextBtn() {
	int moveIndex = history.getIndex();
	if (moveIndex == -1) return;
	struct moveProt *move = history.getMove(moveIndex);

	if (!move)
		return;
	int index = findByPosition(move->fromX, move->fromY);
	if (index < 0)	return;
	if (move->type)
		removeUnit(findByPosition(move->toX, move->toY));
	figures[index]->x = move->toX;
	figures[index]->y = move->toY;
	QModelIndex bottomRight = createIndex(figures.size(), 0);
	QModelIndex topLeft = createIndex(0, 0);
	emit dataChanged(topLeft, bottomRight);
	history.setIndex(moveIndex + 1);
	turn = !turn;
}

void	GameHandler::removeUnit(int unitIndex)
{
	beginResetModel();
	if (figures[unitIndex])
		delete figures[unitIndex];
	figures.removeAt(unitIndex);
	endResetModel();
}

void	GameHandler::saveBtn() {
	QFile file("save.chess");

	if (file.exists())
		file.remove();
	if (!file.open(QIODevice::WriteOnly))
		return;
	file.write("current pos:\n", 13);
	int size = figures.size();
	for (int i = 0; i < size; i++)
	{
		if (i % 5 == 0 && i != 0)
			file.write("\n", 1);
		char tmp[5];
		tmp[0] = figures[i]->type + 48;
		tmp[1] = figures[i]->PlayerColor + 48;
		tmp[2] = figures[i]->x + 48;
		tmp[3] = figures[i]->y + 48;
		i + 1 < size ? tmp[4] = ',' : tmp[4] = '\n';
		file.write(tmp, 5);
	}
	history.saveHistory(&file);
	file.close();
}

bool	GameHandler::loadReadFile(QString downloadedFile)
{
	QStringList list = downloadedFile.split('\n',  QString::SkipEmptyParts);
	int i = 1;
	bool flag = true;

	if ((list[0]) != "current pos:")
		return false;
	while (i < list.size() && flag) {
		QStringList list2 = list[i].split(',',  QString::SkipEmptyParts);
		for (int j = 0; j < list2.size(); j++) {
			if (list2[j].size() == 4)
				addNewUnit(list2[j][2].digitValue(), list2[j][3].digitValue(),
					(color)list2[j][1].digitValue(), (shape)list2[j][0].digitValue());
			else {
				flag = false;
				break;
			}
		}
		i++;
	}
	if ((list[i - 1]) != "history save:")
		return false;
	else
		flag = true;
	while (i < list.size() && flag) {
		QStringList list2 = list[i].split(',',  QString::SkipEmptyParts);
		for (int j = 0; j < list2.size(); j++) {
			if (list2[j].size() == 6)
				history.addMoveToHistory(list2[j][2].digitValue(),
						list2[j][3].digitValue(),
						list2[j][4].digitValue(),
						list2[j][5].digitValue(),
						(color)list2[j][1].digitValue(),
						(shape)list2[j][0].digitValue());
			else {
				flag = false;
				break;
			}
		}
		i++;
	}
	if ((list[i - 1]) != "history pos:")
		return false;
	int newIndex = list[i].toInt();
	history.setIndex(newIndex);
	return true;
}

void	GameHandler::loadBtn() {
	QFile file("save.chess");
	char	buff[101];
	int		i;
	QString	downloadedFile;

	if (!file.open(QIODevice::ReadOnly))
		return;
	while ((i = file.read(buff, 100)))
	{
		buff[i] = '\0';
		downloadedFile.append(buff);
		bzero(buff, sizeof(buff));
	}
	clear();
	if (!(loadReadFile(downloadedFile)))
		qDebug() << "Invalid file";
}

GameHandler::GameHandler(QObject *parent)
	: QAbstractListModel(parent) {
}

GameHandler::~GameHandler() {
	clear();
}

int GameHandler::boardSize() const {
  return BOARD_SIZE;
}

void GameHandler::start() {
	clear();
	turn = false;
	addNewUnit(0, 6, white, pawn);
	addNewUnit(1, 6, white, pawn);
	addNewUnit(2, 6, white, pawn);
	addNewUnit(3, 6, white, pawn);
	addNewUnit(4, 6, white, pawn);
	addNewUnit(5, 6, white, pawn);
	addNewUnit(6, 6, white, pawn);
	addNewUnit(7, 6, white, pawn);
	addNewUnit(0, 7, white, rook);
	addNewUnit(1, 7, white, knight);
	addNewUnit(2, 7, white, bishop);
	addNewUnit(3, 7, white, queen);
	addNewUnit(4, 7, white, king);
	addNewUnit(5, 7, white, bishop);
	addNewUnit(6, 7, white, knight);
	addNewUnit(7, 7, white, rook);

	addNewUnit(0, 1, black, pawn);
	addNewUnit(1, 1, black, pawn);
	addNewUnit(2, 1, black, pawn);
	addNewUnit(3, 1, black, pawn);
	addNewUnit(4, 1, black, pawn);
	addNewUnit(5, 1, black, pawn);
	addNewUnit(6, 1, black, pawn);
	addNewUnit(7, 1, black, pawn);
	addNewUnit(0, 0, black, rook);
	addNewUnit(1, 0, black, knight);
	addNewUnit(2, 0, black, bishop);
	addNewUnit(3, 0, black, queen);
	addNewUnit(4, 0, black, king);
	addNewUnit(5, 0, black, bishop);
	addNewUnit(6, 0, black, knight);
	addNewUnit(7, 0, black, rook);
	QModelIndex topLeft = createIndex(0, 0);
	QModelIndex bottomRight = createIndex(figures.size(), 0);
	emit dataChanged(topLeft, bottomRight);
}

void	GameHandler::clear() {
  beginResetModel();
  for(int i = 0; i < figures.size(); i++)
	  delete figures[i];
  figures.clear();
  turn = false;
  endResetModel();
  history.clear();
}

int		GameHandler::rowCount(const QModelIndex &parent) const {
	Q_UNUSED(parent);
	return (figures.size());
}


QVariant GameHandler::data(const QModelIndex & modelIndex, int role) const {
    if (!modelIndex.isValid()) {
      return QVariant();
    }
    int index = static_cast<int>(modelIndex.row());

    if (index >= figures.size()  || index < 0) {
      return QVariant();
    }
    Unit *figure = figures[index];

    switch (role) {
	  case Roles::Type     :
			switch (figure->type) {
				case (pawn): return "pawn";
				case (rook): return "rook";
				case (knight): return "knight";
				case (bishop): return "bishop";
				case (queen): return "queen";
				case (king): return "king";
				case (def): return QVariant();
			}
	  case Roles::PositionX: return figure->x;
      case Roles::PositionY: return figure->y;
	  case Roles::Color	   : return figure->PlayerColor == 2 ? "black" : figure->PlayerColor == 1 ? "white" : 0;
    }
    return QVariant();
}

QHash<int, QByteArray> GameHandler::roleNames() const {
  QHash<int, QByteArray> names;
  names.insert(Roles::Type      , "type");
  names.insert(Roles::PositionX , "positionX");
  names.insert(Roles::PositionY , "positionY");
  names.insert(Roles::Color     , "color");
  return names;
}


bool	GameHandler::moveToEnemy(int fromX, int fromY, int toX, int toY,
								 int index, int enemy) {
	if (figures[index]->PlayerColor == white ?
			figures[enemy]->PlayerColor == black :
			figures[enemy]->PlayerColor == white) {
		turn = !turn;
		history.addMoveToHistory(fromX, fromY, toX, toY,
								 figures[enemy]->PlayerColor, figures[enemy]->type);
		figures[index]->x = toX;
		figures[index]->y = toY;
		removeUnit(enemy);
		QModelIndex bottomRight = createIndex(figures.size(), 0);
		QModelIndex topLeft = createIndex(0, 0);
		emit dataChanged(topLeft, bottomRight);
		return true;
	}
	return false;
}

void	GameHandler::moveToEmptyCell(int fromX, int fromY, int toX, int toY, int index) {
	turn = !turn;
	history.addMoveToHistory(fromX, fromY, toX, toY, undef, def);
	figures[index]->x = toX;
	figures[index]->y = toY;
	QModelIndex modIndex = createIndex(index, 0);
	emit dataChanged(modIndex, modIndex);
}

bool GameHandler::move(int fromX, int fromY, int toX, int toY) {
	int index = findByPosition(fromX, fromY);
	int enemy = findByPosition(toX, toY);

	if (index < 0) return false;

	if (figures[index]->type == pawn && enemy >= 0)
		((Pawn *)figures[index])->attack = true;
	if (figures[index]->moveChess(fromX, fromY, toX, toY)
			&& ((figures[index]->PlayerColor == white && !turn)
			|| (figures[index]->PlayerColor == black && turn))
			&& access(fromX, fromY, toX, toY)) {
		if (enemy >= 0) {
			if (moveToEnemy(fromX, fromY, toX, toY, index, enemy))
				return true;
		}
		else {
			moveToEmptyCell(fromX, fromY, toX, toY, index);
			return true;
		}
	}
	figures[index]->x = fromX;
	figures[index]->y = fromY;
	QModelIndex modIndex = createIndex(index, 0);
	emit dataChanged(modIndex, modIndex);
	return false;
}
