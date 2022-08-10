import QtQuick 2.0
import "common"
import "text"
import "preferenceMenus"

TabMenu {
    id: preferencesMenu
    color: "transparent"
    menuTitles: ["Recording", "Shortcuts"]
    menuComponents: [
        Component { RecordingPreferences {} },
        Component { KeyboardShortcutPreferences {} }
    ]
}
