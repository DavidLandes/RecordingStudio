import QtQuick 2.0
import com.studio.Theme 1.0
import "common"
import "popups"

Toolbar {
    id: projectToolbarBase
    width: parent.width
    height: 40
    toolbarMenus: [
        ToolbarMenu {
            title: "File"
            menuItems: [
                { "title": "New Project" },
                { "title": "Open Project" },
            ]
            onSubmenuClicked: {
                switch(submenu) {
                case "New Project":
                    showCreateProject();
                    break;
                case "Open Project":
                    projects.open();
                    break;
                }
            }
        },
        ToolbarMenu {
            title: "Edit"
            menuItems: [
                { "title": "New Track" },
            ]
            onSubmenuClicked: {
                switch(submenu) {
                case "New Track":
                    projects.current.createTrack();
                    break;
                }
            }
        }
    ]
    function showCreateProject() {
        var c = Qt.createComponent("popups/NewProjectPopup.qml");
        c.createObject(mainWindow, {});
    }
}
