//  Author: R. Schiffers

#include "SolidBlock.h"

SolidBlock::SolidBlock (int blockSize, int X, int Y) 
: GameObject (blockSize, X, Y)
{
  this->type = "SOLID";
  setPixmap (* new QPixmap (":/res/images/Solid.png"));
  setScale ((double) blockSize / 100);
  setPos (blockSize * X, blockSize * Y);
  setZValue (0);
}

QString
SolidBlock::blockType ()
{
  return this->type;
}