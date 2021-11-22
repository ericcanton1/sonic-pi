//--
// This file is part of Sonic Pi: http://sonic-pi.net
// Full project source: https://github.com/samaaron/sonic-pi
// License: https://github.com/samaaron/sonic-pi/blob/main/LICENSE.md
//
// Copyright 2013, 2014, 2015, 2016 by Sam Aaron (http://sam.aaron.name).
// All rights reserved.
//
// Permission is granted for use, copying, modification, and
// distribution of modified versions of this work as long as this
// notice is included.
//++

#include <iostream>

#include <QApplication>
#include <QSplashScreen>
#include <QPixmap>
#include <QBitmap>
#include <QLabel>
#include <QLibraryInfo>

#include "mainwindow.h"

#include "widgets/sonicpilog.h"

#include "dpi.h"

#ifdef _WIN32
#include <QtPlatformHeaders\QWindowsWindowFunctions>
#endif

#ifdef Q_OS_MAC
    #include "platform/macos.h"
#endif

int main(int argc, char *argv[])
{
  std::cout << "Starting Sonic Pi..." << std::endl;
#ifndef Q_OS_MAC
  Q_INIT_RESOURCE(SonicPi);
#endif

  QApplication app(argc, argv);

  QApplication::setAttribute(Qt::AA_DontShowIconsInMenus, true);

  QFontDatabase::addApplicationFont(":/fonts/Hack-Regular.ttf");
  QFontDatabase::addApplicationFont(":/fonts/Hack-Italic.ttf");
  QFontDatabase::addApplicationFont(":/fonts/Hack-Bold.ttf");
  QFontDatabase::addApplicationFont(":/fonts/Hack-BoldItalic.ttf");

  qRegisterMetaType<SonicPiLog::MultiMessage>("SonicPiLog::MultiMessage");

  app.setApplicationName(QObject::tr("Sonic Pi"));
  app.setStyle("gtk");

#ifdef __linux__
  //linux code goes here
  QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
  QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#elif _WIN32
  // windows code goes here

  // A temporary fix, until stylesheets are removed.
  // Only do the dpi scaling when the platform is high dpi

  if (GetDisplayScale().width() > 1.1f)
    {
      QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
      QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    }
#elif __APPLE__
  // macOS code goes here
  SonicPi::removeMacosSpecificMenuItems();
  QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif

  QPixmap pixmap(":/images/splash@2x.png");

  QSplashScreen *splash = new QSplashScreen(pixmap);
  splash->show();
  app.processEvents();

  MainWindow mainWin(app, splash);

#ifdef __linux__

#elif _WIN32
    // Fix for full screen mode. See: https://doc.qt.io/qt-5/windows-issues.html#fullscreen-opengl-based-windows
  QWindowsWindowFunctions::setHasBorderInFullScreen(mainWin.windowHandle(), true);

#elif __APPLE__

#endif
  return app.exec();

}
