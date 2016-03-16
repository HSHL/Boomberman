#include "FragileBlock.h"

FragileBlock::FragileBlock (int blockSize, int X, int Y)
: GameObject (blockSize, X, Y)
{
  this->type = "FRAGILE";
  setPixmap (* new QPixmap (":/res/images/Fragile.png"));
  setScale ((double) blockSize / 100);
  setPos (blockSize * X, blockSize * Y);
  setZValue (0);
}

QString
FragileBlock::blockType ()
{
  return this->type;
}