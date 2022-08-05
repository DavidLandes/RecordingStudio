#pragma once

#include <QObject>
#include <QMap>
#include "Theme.hpp"

class Palette : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(Theme* appTheme READ appTheme WRITE setAppTheme NOTIFY appThemeChanged)

    explicit Palette(QObject *parent = nullptr);

    enum class Color
    {
        Mahogany,
        Red_80,
        Red_100,
        Black,
        Grey_10,
        Grey_15,
        Grey_20,
        Grey_25,
        Grey_30,
        Grey_35,
        Grey_40,
        Grey_45,
        Grey_50,
        Grey_55,
        Grey_60,
        Grey_65,
        Grey_70,
        Grey_75,
        Grey_80,
        Grey_85,
        Grey_90,
        Grey_95,
        White,
    };
    Q_ENUM(Color)

    Q_INVOKABLE QString get(Color color);

    Theme* appTheme() const;
    void setAppTheme(Theme* appTheme);

signals:
    void appThemeChanged(Theme* appTheme);

private:
    QMap<Color, QString> m_colors;
    Theme* m_appTheme;
};


