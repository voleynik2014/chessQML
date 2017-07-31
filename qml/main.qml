import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2

ApplicationWindow {
	title: qsTr("Chess")
	visible: true
	width: 800
	height: 600

	property int squareSize: 70

	Repeater {
		model: 2

		Row {
		x: 20 + (squareSize / 2 - 5)
		y: index == 1 ? 5 : (squareSize * 8 + 20)

			Repeater {
				model: ["A","B","C","D","E","F","G","H"]

				Text{
					height: squareSize
					width: squareSize
					text: modelData
				}
			}
		}
	}
	Repeater {
		model: 2

		Column {
		x: index == 1 ? 10 : (squareSize * 8 + 25)
		y: 20 + (squareSize / 2 - 5)

			Repeater {
				model: 8

				Text{
					height: squareSize
					width: squareSize
					text: 8 - index
				}
			}
		}
	}

	Item {
		id: gameBoard
		x: 20
		y: 20
		width : gameHandler.boardSize * squareSize
		height: gameHandler.boardSize * squareSize

		Image {
			source: "/images/chess_board.jpg"
			height: gameBoard.height
			width: gameBoard.width
		}
	}

	Item {
		id: figures
		x: gameBoard.x
		y: gameBoard.y
		width : gameHandler.boardSize * squareSize
		height: gameHandler.boardSize * squareSize

		Repeater {
			id : asd
			model: gameHandler

			Image {
				height: squareSize
				width : squareSize
				x: squareSize * positionX
				y: squareSize * positionY
				source: "images/" + color + "_" + type + ".svg"

				MouseArea {
					anchors.fill: parent
					drag.target: parent

					property int startX: 0
					property int startY: 0

					onPressed: {
						startX = parent.x;
						startY = parent.y;
					}

					onReleased: {
						var fromX = startX / squareSize;
						var fromY = startY / squareSize;
						var toX   = (parent.x + mouseX) / squareSize;
						var toY   = (parent.y + mouseY) / squareSize;
						gameHandler.move(fromX, fromY, toX, toY)
					}
				}
			}
		}
	}

	SideMenu {
		id: mainMenu
		width: 150
		x: gameBoard.width + 50
		y: 20
		anchors.leftMargin: 30
		anchors.rightMargin: 10
	}
}


