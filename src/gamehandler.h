#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H

#include <memory>
#include <QAbstractListModel>
#include <QFile>
#include <QDebug>

#include "history.h"

#define BOARD_SIZE 8

class Unit;

class GameHandler : public QAbstractListModel
{
	Q_OBJECT
public:
	enum Roles {
		Type = Qt::UserRole,
		PositionX,
		PositionY,
		Color,
	};

	explicit GameHandler(QObject *parent = 0);
	~GameHandler();

	Q_PROPERTY			(int boardSize READ boardSize CONSTANT)
	int					boardSize() const;

	History				history;

	/*	Methods available in QML */
	Q_INVOKABLE bool	move(int fromX, int fromY, int toX, int toY);
	Q_INVOKABLE void	start();
	Q_INVOKABLE void	clear();
	Q_INVOKABLE void	prevBtn();
	Q_INVOKABLE void	nextBtn();
	Q_INVOKABLE void	saveBtn();
	Q_INVOKABLE void	loadBtn();

protected:
	int					rowCount(const QModelIndex & parent) const override;
	QVariant			data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
	QHash<int, QByteArray> roleNames() const override;

private:
	/*	move methods */
	bool				access(int fromX, int fromY, int toX, int toY);
	bool				moveToEnemy(int fromX, int fromY, int toX, int toY, int index, int enemy);
	void				moveToEmptyCell(int fromX, int fromY, int toX, int toY, int index);

	/*	manage Unit	*/
	void				addNewUnit(int x, int y, color player, shape type);
	void				removeUnit(int unitIndex);

	/*	File I/O */
	bool				loadReadFile(QString downloadedFile);
	bool				saveMove(int fromX, int fromY, int toX, int toY);

	int					findByPosition(int x, int y);

	QList<Unit*>		figures;
	bool turn;
};

#endif // GAMEHANDLER_H
