#pragma once
#include "Settings.hpp"


const QDir appDir = QDir(QDir::homePath() + "/Documents/RecordingStudio/");

static Settings settings(appDir.absoluteFilePath("rec.conf"));
