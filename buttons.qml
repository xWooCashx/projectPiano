import QtQuick 2.0

Item {
    id: item1
    width: 27
    height: 15

    Rectangle {
        id: rectangle
        border.width: 0
        anchors.fill: parent
        clip: true
        gradient: Gradient {
            GradientStop {
                id: gradientStop1
                position: 0
                color: "#ed8080"
            }

            GradientStop {
                id: gradientStop
                position: 0.52
                color: "#ff4400"
            }

            GradientStop {
                position: 0.82
                color: "#ff4400"
            }

            GradientStop {
                position: 1
                color: "#000000"
            }


        }
    }

    Connections {
        target: item1
        onClicked: item.clicked()
        signal clicked
    }
    states: [
        State {
            name: "CLicked"

            PropertyChanges {
                target: gradientStop
                position: 0.378
                color: "#fee2d7"
            }

            PropertyChanges {
                target: rectangle
                color: "#ffffff"
                border.width: 0
            }

            PropertyChanges {
                target: gradientStop1
                color: "#ffffff"
            }
        }
    ]

}
