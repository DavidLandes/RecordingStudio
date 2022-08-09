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
        Grey_11,
        Grey_12,
        Grey_13,
        Grey_14,
        Grey_15,
        Grey_16,
        Grey_17,
        Grey_18,
        Grey_19,
        Grey_20,
        Grey_21,
        Grey_22,
        Grey_23,
        Grey_24,
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
        Green_70,
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


