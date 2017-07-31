#include "history.h"
#include <iostream>
#include <cstdlib>
#include <stdlib.h>

History::History(QObject *parent) : QAbstractListModel(parent) {
	index = 0;
}

void	History::clear() {
		index = 0;
	beginResetModel();
	for(int i = 0; i < history.size(); i++)
		delete history[i];
	history.clear();
	endResetModel();
}

History::~History() {
	clear();
}

void	History::addMoveToHistory(int fromX, int fromY, int toX,
						int toY, color playerColor, shape type) {
	beginResetModel();
	int size = history.size();
	for (int i = index; i < size; i++) {
		delete history[index];
		history.removeAt(index);
	}
	endResetModel();
	QString tmp = QChar(fromX + 65) + QString::number(8 - fromY) + "-"
			+ QChar(toX + 65) + QString::number(8 - toY);
	beginInsertRows(QModelIndex(), 0, 0);
	history << new moveProt {fromX, fromY, toX, toY, tmp, playerColor, type};
	endInsertRows();
	QModelIndex left = createIndex(0, 0);
	QModelIndex right = createIndex(history.size(), 0);
	emit dataChanged(left, right);
	index++;
}

void	History::saveHistory(QFile *file) {
	file->write("\nhistory save:\n", 15);

	int size = history.size();
	for (int i = 0; i < size; i++) {
		if (i % 5 == 0 && i != 0) {
			file->write("\n", 1);
		}
		char tmp[7];
		tmp[0] = history[i]->type + 48;
		tmp[1] = history[i]->player + 48;
		tmp[2] = history[i]->fromX + 48;
		tmp[3] = history[i]->fromY + 48;
		tmp[4] = history[i]->toX + 48;
		tmp[5] = history[i]->toY + 48;
		i + 1 < size ? tmp[6] = ',' : tmp[6] = '\n';
		file->write(tmp, 7);
	}
	file->write("\nhistory pos:\n", 14);
	file->write(std::to_string(index).c_str(), std::to_string(index).size());
}

moveProt *History::getMove(int index) {
	if (index < history.size() && index >= 0)
		return (history.at(index));
	return (NULL);
}

int		History::getIndex() {
	return (index);
}

int	History::setIndex(int newIndex) {
	if (newIndex >= 0 && newIndex <= history.size()) {
		index = newIndex;
	}
	return index;
}

int History::rowCount(const QModelIndex &parent) const {
	Q_UNUSED(parent);
	return (history.size());
}

QVariant History::data(const QModelIndex & modelIndex, int role) const {
	if (!modelIndex.isValid()) {
	  return QVariant();
	}

	int index = static_cast<int>(modelIndex.row());
	if (index >= history.size()  || index < 0) {
	  return QVariant();
	}
	switch (role) {
		case Roles::Desc     : return history.at(index)->coords;
		default :
			return QVariant();
	}
	return QVariant();
}

QHash<int, QByteArray> History::roleNames() const {
	QHash<int, QByteArray> names;
	names.insert(Roles::Desc      , "desc");
	return names;
}
