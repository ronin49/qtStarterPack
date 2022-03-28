import QtQuick 2.3
import QtQuick 2.15
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.0
ApplicationWindow {
    width: 300
    height: 300
    visible: true
    Frame{
        width: 3000
        height: 300
        TableView {
            anchors.fill: parent
            columnSpacing: 1
            rowSpacing: 1
            clip: true

            model: mm2

            delegate: Rectangle {
                implicitWidth: 100
                implicitHeight: 50
                Text {
                    text: model.name
                }
            }
        }
    }
Frame{
    width: 300
    height: 300
    anchors.centerIn: parent
    ListView {
        id: listView
        anchors.fill: parent
        anchors.margins: 10
        model: mm

        delegate: RowLayout {
            Button{
            onClicked: mm.g(index)
            }
            width: listView.width

            TextField {
                text: model.name
                horizontalAlignment: Text.AlignHCenter

                Layout.preferredWidth: 1
                Layout.fillWidth: true

                onAccepted: model.name = text
            }

            Text {
                text: model.age

                Layout.preferredWidth: 1
                Layout.fillWidth: true

                horizontalAlignment: Text.AlignHCenter
            }
        }
    }
}
}
