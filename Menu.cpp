#include "Menu.h"

Menu::Menu (int width, int height) : QGraphicsScene ()
{
  QPixmap* pix = new QPixmap (":res/images/Menu.jpg");
  *pix = pix->scaledToWidth (width);
  this->setBackgroundBrush (*new QBrush (*pix));

  QPixmap* buttonPix = new QPixmap (":res/images/StartButton.png");

  QPalette* palette = new QPalette ();
  palette->setColor (QPalette::Button, Qt::black);

  startButton = new QPushButton ();
  startButton->setPalette (*palette);
  startButton->setIcon (*buttonPix);
  startButton->setIconSize (startButton->size ());
  startButton->setGeometry (0, height - height * 0.12, width * 0.97, height * 0.1);
  addWidget (startButton);
}

QPushButton*
Menu::getStartButton ()
{
  return this->startButton;
}