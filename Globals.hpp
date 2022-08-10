#pragma once
#include <QSettings>

// Create app settings.
#define RECORDING_CONF "Recording/"
inline QSettings settings("studio.conf", QSettings::IniFormat);
