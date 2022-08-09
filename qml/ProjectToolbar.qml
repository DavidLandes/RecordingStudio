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
                    showOpenProject();
                    break;
                }
            }
        },
        ToolbarMenu {
            title: "Edit"
            menuItems: [
                { "title": "New Track" },
                { "title": "Preferences" },
            ]
            onSubmenuClicked: {
                switch(submenu) {
                case "New Track":
                    projects.current.createTrack();
                    break;
                case "Preferences":
                    showPreferencesMenu();
                    break;
                }
            }
        },
        ToolbarMenu {
            title: "Audio"
            menuItems: [
                { "title": "Play All" },
                { "title": "Stop All" },
            ]
            onSubmenuClicked: {
                switch(submenu) {
                case "Play All":
                    projects.current.playAll();
                    break;
                case "Stop All":
                    projects.current.stopAll();
                    break;
                }
            }
        }
    ]
    function showCreateProject() {
        var c = Qt.createComponent("popups/NewProjectPopup.qml");
        c.createObject(mainWindow, {});
    }
    function showOpenProject() {
        var c = Qt.createComponent("popups/OpenDeleteProjectPopup.qml");
        c.createObject(mainWindow, {});
    }
    function showPreferencesMenu() {
        console.log("preferences")
        var c = Qt.createComponent("popups/PreferencesPopup.qml");
        c.createObject(mainWindow, {});
    }
}
