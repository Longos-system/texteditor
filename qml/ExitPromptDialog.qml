/*
 * Copyright (C) 2023 LongOS Team.
 */

import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.12
import LongUI 1.0 as LongUI

LongUI.Window {
    id: control

    property var contentWidth: _mainLayout.implicitWidth + LongUI.Units.largeSpacing * 2
    property var contentHeight: _mainLayout.implicitHeight + header.height + LongUI.Units.largeSpacing * 2

    flags: Qt.WindowStaysOnTopHint | Qt.Dialog | Qt.FramelessWindowHint
    modality: Qt.WindowModal
    visible: false

    width: contentWidth
    height: contentHeight
    minimumWidth: contentWidth
    minimumHeight: contentHeight
    maximumWidth: contentWidth
    maximumHeight: contentHeight
    minimizeButtonVisible: false

    background.color: LongUI.Theme.secondBackgroundColor

    signal okBtnClicked

    ColumnLayout {
        id: _mainLayout
        anchors.fill: parent
        spacing: LongUI.Units.largeSpacing
        anchors.margins: LongUI.Units.largeSpacing

        Label {
            text: qsTr("Document unsaved, are you sure you want to close it?")
        }

        RowLayout {
            spacing: LongUI.Units.largeSpacing

            Button {
                text: qsTr("Cancel")
                Layout.fillWidth: true
                onClicked: control.visible = false
            }

            Button {
                text: qsTr("OK")
                Layout.fillWidth: true
                flat: true
                onClicked: {
                    control.visible = false
                    control.okBtnClicked()
                }
            }
        }
    }
}
