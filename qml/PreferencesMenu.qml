import QtQuick 2.0
import "common"
import "text"
import "preferenceMenus"

TabMenu {
    id: preferencesMenu
    color: "transparent"
    menus: [
        { "title": "Recording", "component": recordingPreferences } ,
        { "title": "Playback", "component": playbackPreferences },
        { "title": "Shortcuts", "component": shortcutsPreferences },
    ]
    Component {
        id: recordingPreferences
        RecordingPreferences {}
    }
    Component {
        id: playbackPreferences
        PlaybackPreferences {}
    }
    Component {
        id: shortcutsPreferences
        KeyboardShortcutPreferences {}
    }
}
