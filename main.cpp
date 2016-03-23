//  Author: R. Schiffers

#include <QApplication>
#include <QTime>
#include "Game.h"

int
main (int argc, char *argv[])
{  
  QApplication app (argc, argv);
  
  QTime time = QTime::currentTime ();
  qsrand ((uint) time.msec ());
  
  Game game (50, 13, 15);
  game.show ();

  return app.exec ();
}