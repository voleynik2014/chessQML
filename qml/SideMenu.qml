import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.2

Item
{

	Button {
		id: startButton

		visible: true
		anchors.left: mainMenu.left
		anchors.right: mainMenu.right
		anchors.leftMargin: 10
		anchors.rightMargin: 10
		text: "Start"

		onClicked: {
			gameHandler.start()
			saveButton.visible = true
			stopButton.visible = true
			startButton.visible = false
			loadMenu.visible = false
		}
	}

	Button {
		id: loadButton
		anchors.left: mainMenu.left
		anchors.right: mainMenu.right
		anchors.leftMargin: 10
		anchors.rightMargin: 10
		visible: true
		y: 30
		text: "Load"

		onClicked: {
			gameHandler.loadBtn()
			loadMenu.visible = true
			startButton.visible = true
			loadButton.visible = true
		}
	}

	Button {
		id: saveButton
		anchors.left: mainMenu.left
		anchors.right: mainMenu.right
		anchors.leftMargin: 10
		anchors.rightMargin: 10
		visible: false
		y: 30
		text: "Save"

		onClicked: {
			gameHandler.saveBtn()
		}
	}

	Button {
		id: stopButton
		anchors.left: mainMenu.left
		anchors.right: mainMenu.right
		anchors.leftMargin: 10
		anchors.rightMargin: 10
		visible: false
		text: "Stop"

		onClicked: {
			gameHandler.clear()
			startButton.visible = true
			loadButton.visible = true
			stopButton.visible = false
			saveButton.visible = false
		}
	}

	Item
	{
		id : loadMenu
		visible: false
		y: 70

		Item {
			id: navMenu
			anchors.top: parent.bottom
			anchors.leftMargin: 10
			anchors.topMargin: 10
			anchors.rightMargin: 10

			Button {
				id: prevButton
				anchors.left: navMenu.right
				text: "Prev"

				onClicked: {
					gameHandler.prevBtn()
				}
			}

			Button {
				id: nextButton
				anchors.leftMargin: 10
				anchors.left: prevButton.right
				text: "Next"

				onClicked: {
					gameHandler.nextBtn()
				}
			}
		}
	}
}

