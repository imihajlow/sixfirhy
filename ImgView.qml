import QtQuick 2.12
import QtQuick.Window 2.12
import Qt.labs.folderlistmodel 2.12
import QtQuick.Dialogs 1.3
import com.example 1.0

Rectangle {
    id: root
    focus: true
    color: "black"
    state: "user"

    property string folder: "/"
    property int index: 0
    property url currentFile: {
        if (modelCount() > 0) {
            var boundedIndex = Math.min(index, modelCount() - 1);
            return getFileUrl(boundedIndex);
        } else {
            return "";
        }
    }
    property bool fit: true

    property int imageX: mouse2img(mouseArea.mouseX, root.width, image.sourceSize.width)
    property int imageY: mouse2img(mouseArea.mouseY, root.height, image.sourceSize.height)

    function mouse2img(mouseX, windowW, imgW) {
        if (imgW > windowW)
        {
            return -(imgW - windowW) * mouseX / windowW;
        }
        else
        {
            return (windowW - imgW) / 2;
        }
    }

    function modelCount() {
        if (root.state === "files") {
            return ArgsProvider.files.length;
        } else {
            return folderModel.count;
        }
    }

    function getFileUrl(index) {
        if (root.state === "files") {
            return "file://" + encodeURIComponent(ArgsProvider.files[index]);
        } else {
            return folderModel.get(index, "fileURL");
        }
    }

    function nextImage(inc) {
        var newIndex = index + inc;
        index = Math.max(0, Math.min(modelCount() - 1, newIndex));
    }

    function prevImage(inc) {
        if (index >= folderModel.count) {
            index = Math.max(0, modelCount() - 1 - inc);
        } else if (index > 0) {
            var newIndex = index - inc;
            index = Math.max(0, newIndex);
        }
    }

    function lastImage() {
        index = Math.max(0, modelCount() - 1);
    }

    function firstImage() {
        index = 0;
    }

    FolderListModel {
        id: folderModel
        caseSensitive: false
        nameFilters: ["*.jpg", "*.png", "*.jpeg", "*.bmp", "*.tiff", "*.svg"]
        showOnlyReadable: true
        showDirs: false
        folder: "file://" + encodeURIComponent(root.folder)
        onFolderChanged: {
            root.index = 0;
        }
    }

    FileDialog {
        id: dialog
        folder: shortcuts.pictures
        selectFolder: true
        onAccepted: {
            root.folder = folder;
            root.state = "user";
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
    }

    Image {
        id: image
        fillMode: root.fit ? Image.PreserveAspectFit : Image.Pad
        source: currentFile
        autoTransform: true
        mipmap: false

        states: [
            State {
                name: "fit"
                when: root.fit
                PropertyChanges {
                    target: image
                    x: 0
                    y: 0
                    width: root.width
                    height: root.height
                }
            },
            State {
                name: "original"
                when: !root.fit
                PropertyChanges {
                    target: image
                    x: root.imageX
                    y: root.imageY
                    width: image.sourceSize.width
                    height: image.sourceSizeheight
                }
            }
        ]
    }

    TagDisplay {
        id: tagDisplay
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.leftMargin: 20
        anchors.topMargin: 20
        model: tagProvider.tags
    }

    TagProvider {
        id: tagProvider
        url: currentFile
    }

    Keys.onPressed: {
        if (event.key === Qt.Key_Right || event.key === Qt.Key_Space) {
            nextImage((event.modifiers & Qt.ShiftModifier) ? 10 : 1);
        } else if (event.key === Qt.Key_Left || event.key === Qt.Key_Backspace) {
            prevImage((event.modifiers & Qt.ShiftModifier) ? 10 : 1);
        } else if (event.key === Qt.Key_End) {
            lastImage();
        } else if (event.key === Qt.Key_Home) {
            firstImage();
        } else if (event.key === Qt.Key_O) {
            dialog.open();
        } else if (event.key === Qt.Key_F) {
            root.fit = !root.fit;
        } else if (event.key === Qt.Key_T) {
            tagDisplay.visible = !tagDisplay.visible;
        } else if (event.key === Qt.Key_S) {
            image.smooth = !image.smooth;
        } else if (event.key === Qt.Key_1) {
            tagProvider.toggleTag(1);
        } else if (event.key === Qt.Key_2) {
            tagProvider.toggleTag(2);
        } else if (event.key === Qt.Key_3) {
            tagProvider.toggleTag(3);
        } else if (event.key === Qt.Key_4) {
            tagProvider.toggleTag(4);
        } else if (event.key === Qt.Key_5) {
            tagProvider.toggleTag(5);
        } else if (event.key === Qt.Key_6) {
            tagProvider.toggleTag(6);
        } else if (event.key === Qt.Key_7) {
            tagProvider.toggleTag(7);
        }
    }

    Component.onCompleted: {
        switch (ArgsProvider.mode) {
        default:
        case ArgsProvider.Empty:
            dialog.open();
            break;
        case ArgsProvider.Folder:
            root.state = "folder";
            root.folder = ArgsProvider.folder;
            break;
        case ArgsProvider.Files:
            root.state = "files";
            break;
        }
    }
}
