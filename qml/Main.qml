import QtQuick
import QtQuick.Controls
import QtQuick.Window


Window {
    id: window

    width: Math.min(Screen.width * 0.4, 600) + 80
    height: Math.min(Screen.height * 0.1, 120) + 80

    visible: true

    flags: Qt.FramelessWindowHint
    color: "transparent"


    function showPulse() {
        window.show()
        window.raise()
        window.requestActivate()

        panel.opacity = 0
        panel.scale = 0.85

        searchField.opacity = 0
        searchField.scale = 0.95

        openAnimation.restart()
        fieldAnimation.restart()

        searchField.forceActiveFocus()
    }


    function hidePulse() {
        closeAnimation.restart()
    }


    Item {
        anchors.fill: parent
        focus: true

        Keys.onEscapePressed: {
            closeAnimation.restart()
        }


        Rectangle {
            id: panel

            anchors.centerIn: parent

            width: window.width - 80
            height: window.height - 80

            radius: 25
            color: "#F5F5F7"

            opacity: 0
            scale: 0.85

            transformOrigin: Item.Center


            Component.onCompleted: {
                openAnimation.start()
                fieldAnimation.start()
            }


            ParallelAnimation {
                id: openAnimation

                NumberAnimation {
                    target: panel
                    property: "opacity"

                    from: 0
                    to: 1

                    duration: 300

                    easing.type: Easing.OutCubic
                }

                NumberAnimation {
                    target: panel
                    property: "scale"

                    from: 0.85
                    to: 1

                    duration: 450

                    easing.type: Easing.OutBack
                }
            }

            ParallelAnimation {
                id: closeAnimation

                NumberAnimation {
                    target: panel
                    property: "opacity"

                    from: 1
                    to: 0

                    duration: 220

                    easing.type: Easing.InCubic
                }

                NumberAnimation {
                    target: panel
                    property: "scale"

                    from: 1
                    to: 0.85

                    duration: 350

                    easing.type: Easing.InBack
                }


                onFinished: {
                    window.hide()
                }
            }


            Rectangle {
                id: pulseDot

                width: 12
                height: 12

                radius: 6

                color: "red"

                anchors {
                    left: parent.left
                    top: parent.top
                    margins: 20
                }


                SequentialAnimation on opacity {
                    running: true
                    loops: Animation.Infinite

                    NumberAnimation {
                        to: 0.2
                        duration: 200
                    }

                    NumberAnimation {
                        to: 1
                        duration: 700
                    }
                }
            }


            TextField {
                id: searchField

                width: parent.width * 0.85
                height: parent.height * 0.55

                anchors.centerIn: parent

                verticalAlignment: TextInput.AlignVCenter

                font.pixelSize: 18
                font.family: "Inter"

                color: "#222222"
                placeholderTextColor: "#888888"

                leftPadding: 20
                rightPadding: 20

                opacity: 0
                scale: 0.95

                onTextChanged: {
                    appModel.search(text)
                }

                Keys.onReturnPressed: {
                    if (appModel.hasResult) {
                        appModel.launchCurrent()

                        searchField.clear()
                        closeAnimation.restart()
                    }
                }

                Keys.onEnterPressed: {
                    if (appModel.hasResult) {
                        appModel.launchCurrent()

                        searchField.clear()
                        closeAnimation.restart()
                    }
                }

                Image {
                    id: appIcon

                    anchors.right: parent.right
                    anchors.rightMargin: 16
                    anchors.verticalCenter: parent.verticalCenter

                    width: 32
                    height: 32

                    source: appModel.hasResult
                            ? "image://appicon/current"
                            : ""

                    cache: false

                    visible: appModel.hasResult
                    fillMode: Image.PreserveAspectFit
                }

                background: Rectangle {

                                    radius: 18

                                    color: "#EEEEF0"

                                    border.width: 1
                                    border.color: "#D5D5D8"


                                    Rectangle {
                                        id: focusBorder

                                        anchors.fill: parent

                                        radius: parent.radius

                                        color: "transparent"

                                        border.width: 2
                                        border.color: "#007AFF"

                                        opacity: searchField.activeFocus ? 1 : 0
                                        scale: searchField.activeFocus ? 1 : 0.96


                                        Behavior on opacity {
                                            NumberAnimation {
                                                duration: 180
                                                easing.type: Easing.OutCubic
                                            }
                                        }


                                        Behavior on scale {
                                            NumberAnimation {
                                                duration: 250
                                                easing.type: Easing.OutBack
                                            }
                                        }
                                    }
                                }


                                ParallelAnimation {
                                    id: fieldAnimation

                                    PauseAnimation {
                                        duration: 120
                                    }


                                    NumberAnimation {
                                        target: searchField
                                        property: "opacity"

                                        from: 0
                                        to: 1

                                        duration: 250

                                        easing.type: Easing.OutCubic
                                    }


                                    NumberAnimation {
                                        target: searchField
                                        property: "scale"

                                        from: 0.95
                                        to: 1

                                        duration: 300

                                        easing.type: Easing.OutBack
                                    }
                                }
                            }
                        }
                    }
                }