#include "Palette.hpp"

Palette::Palette(QObject *parent) : QObject(parent)
{
    m_appTheme = new Theme((int)Color::Grey_20, (int)Color::Grey_40, (int)Color::Mahogany);

    m_colors[Color::Mahogany]   = "#c04000";
    m_colors[Color::Red_80]     = "#cc0000";
    m_colors[Color::Red_100]    = "#ff0000";
    m_colors[Color::Black]      = "#000000";
    m_colors[Color::Grey_10]    = "#1a1a1a";
    m_colors[Color::Grey_15]    = "#262626";
    m_colors[Color::Grey_16]    = "#292929";
    m_colors[Color::Grey_17]    = "#2b2b2b";
    m_colors[Color::Grey_18]    = "#2e2e2e";
    m_colors[Color::Grey_19]    = "#303030";
    m_colors[Color::Grey_20]    = "#333333";
    m_colors[Color::Grey_21]    = "#363636";
    m_colors[Color::Grey_22]    = "#383838";
    m_colors[Color::Grey_23]    = "#3b3b3b";
    m_colors[Color::Grey_24]    = "#3d3d3d";
    m_colors[Color::Grey_25]    = "#404040";
    m_colors[Color::Grey_30]    = "#4d4d4d";
    m_colors[Color::Grey_35]    = "#595959";
    m_colors[Color::Grey_40]    = "#666666";
    m_colors[Color::Grey_45]    = "#737373";
    m_colors[Color::Grey_50]    = "#343434";
    m_colors[Color::Grey_55]    = "#8c8c8c";
    m_colors[Color::Grey_60]    = "#999999";
    m_colors[Color::Grey_65]    = "#a6a6a6";
    m_colors[Color::Grey_70]    = "#b3b3b3";
    m_colors[Color::Grey_75]    = "#bfbfbf";
    m_colors[Color::Grey_80]    = "#cccccc";
    m_colors[Color::Grey_85]    = "#d9d9d9";
    m_colors[Color::Grey_90]    = "#e6e6e6";
    m_colors[Color::Grey_95]    = "#f2f2f2";
    m_colors[Color::White]      = "#ffffff";
}

QString Palette::get(Palette::Color color)
{
    return m_colors[color];
}

Theme* Palette::appTheme() const
{
    return m_appTheme;
}

void Palette::setAppTheme(Theme* appTheme)
{
    if (m_appTheme != appTheme)
    {
        m_appTheme = appTheme;
        emit appThemeChanged(m_appTheme);
    }
}

