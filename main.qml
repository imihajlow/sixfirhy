import QtQuick 2.12
import QtQuick.Window 2.12
import Qt.labs.folderlistmodel 2.12
import QtQuick.Dialogs 1.3

Window {
    visible: true
    width: 640
    height: 480
    title: view.currentFile
    flags: Qt.WindowFullscreenButtonHint

    ImgView {
        id: view
        anchors.fill: parent
    }
}
