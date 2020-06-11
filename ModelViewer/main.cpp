// main.cpp-------------------------------------------------------------------
#include <QApplication>
#include <QSurfaceFormat>
#include <QVTKOpenGLWidget.h>

#include "mainwindow.h"

/** @file
 * Main executable that initiates the QVTK application and MainWindow
 */

/** main program initialize function
 */
int main( int argc, char** argv )
{
  // needed to ensure appropriate OpenGL context is created for VTK rendering.
  QSurfaceFormat::setDefaultFormat( QVTKOpenGLWidget::defaultFormat() );

  QApplication a( argc, argv );

  MainWindow window;
  window.show();

  return a.exec();
}
// /main.cpp------------------------------------------------------------------
