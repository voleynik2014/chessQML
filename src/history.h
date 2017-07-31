#ifndef HISTORY_H
#define HISTORY_H

#include <QAbstractListModel>
#include "unit.h"
#include <QFile>

struct moveProt {
	int fromX;
	int fromY;
	int toX;
	int toY;
	QString coords;
	color player;
	shape type;
};

class History :  public QAbstractListModel
{
	Q_OBJECT
	enum Roles {
		Desc = Qt::UserRole
	};
public:
	explicit			History(QObject *parent = nullptr);
	~History();

	void				saveHistory(QFile *file);
	moveProt			*getMove(int index);
	int					getIndex();
	int					setIndex(int newIndex);
	void				clear();
	void				addMoveToHistory(int fromX, int fromY, int toX, int toY, color playerColor, shape type);

protected:
	int					rowCount(const QModelIndex & parent) const override;
	QVariant			data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
	QHash<int, QByteArray> roleNames() const override;

public:
	QList<moveProt *>	history;

private:
	int					index;
};

#endif // HISTORY_H
