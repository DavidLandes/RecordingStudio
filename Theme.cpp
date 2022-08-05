#include "Theme.hpp"

Theme::Theme(QObject *parent) : QObject(parent)
{

}

Theme::Theme(int background, int foreground, int accent, QObject* parent) : QObject(parent)
  , m_background(background)
  , m_foreground(foreground)
  , m_accent(accent)
{

}

int Theme::background() const
{
    return m_background;
}

int Theme::foreground() const
{
    return m_foreground;
}

int Theme::accent() const
{
    return m_accent;
}

void Theme::setBackground(int background)
{
    if (m_background != background)
    {
        m_background = background;
        emit backgroundChanged(m_background);
    }
}

void Theme::setForeground(int foreground)
{
    if (m_foreground != foreground)
    {
        m_foreground = foreground;
        emit foregroundChanged(m_foreground);
    }
}

void Theme::setAccent(int accent)
{
    if (m_accent != accent)
    {
        m_accent = accent;
        emit accentChanged(m_accent);
    }
}
