#include "Game.h"

Game::Game (int blockSize, int X, int Y)
{
  this->blockSize = blockSize;
  this->X = X;
  this->Y = Y;

  setHorizontalScrollBarPolicy (Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy (Qt::ScrollBarAlwaysOff);

  setFixedSize (X * blockSize + 20, Y * blockSize + 20);

  startMenu ();
}

void
Game::startGame ()
{
  setBackgroundBrush (*new QBrush (Qt::black));

  this->menu = NULL;
  this->arena = new Arena (blockSize, X, Y);
  this->setSceneRect (0, 0, X*blockSize, Y * blockSize);

  setScene (this->arena);

  connect (this->arena->getPlayer (1), SIGNAL (getHurt ()), this, SLOT (gameOver ()));
  connect (this->arena->getPlayer (2), SIGNAL (getHurt ()), this, SLOT (gameOver ()));
}

void
Game::startMenu ()
{
  setBackgroundBrush (*new QBrush (Qt::NoBrush));

  this->menu = new Menu (this->width (), this->height ());
  setSceneRect (0, 0, X*blockSize, Y * blockSize);
  setScene (this->menu);

  connect (this->menu->getStartButton (), SIGNAL (clicked ()), this, SLOT (startGame ()));
}

void
Game::gameOver ()
{
  this->arena->stopAI ();
  this->arena->stopBombs ();
  this->arena->removeItem (this->arena->getPlayer (1));
  this->arena->removeItem (this->arena->getPlayer (2));  

  QString soundPath = QDir::currentPath ();
  soundPath += "/res/sound/effects/funny.wav";
  QSound *sound = new QSound (soundPath, this);
  sound->play ();

  startMenu ();  
}