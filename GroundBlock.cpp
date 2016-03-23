//  Author: R. Schiffers

#include "GroundBlock.h"

GroundBlock::GroundBlock (int blockSize, int X, int Y) 
: GameObject (blockSize, X, Y)
{
  this->type = "GROUND";
  setPixmap (* new QPixmap (":/res/images/Ground.png"));
  setScale ((double) blockSize / 185);
  setPos (blockSize * X, blockSize * Y);
  setZValue (-1);
}

QString
GroundBlock::blockType ()
{
  return this->type;
}