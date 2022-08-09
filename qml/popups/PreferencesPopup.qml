import QtQuick 2.0
import com.studio.Theme 1.0
import "../common"
import "../text"

BasePopup {
    height: 480
    width: 896
    TabMenu {
        id: preferencesMenu
        color: "transparent"
        anchors.fill: parent
        menuTitles: ["menu1", "menu2"]
        menuComponents: [
            Component {
                Item {
                    LargeText {
                        text: "Coming Soon!"
                        anchors.centerIn: parent
                    }
                }
            },
            Component {
                Item {
                    LargeText {
                        text: "Coming Soon!"
                        anchors.centerIn: parent
                    }
                }
            }
        ]
    }
}
