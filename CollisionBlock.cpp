#include "CollisionBlock.h"

CollisionBlock::CollisionBlock (int blockSize, int X, int Y)
: GameObject (blockSize, X, Y)
{
  this->type = "COLLIDER";
  setPixmap (* new QPixmap (":/res/images/CollisionBlock.png"));
  setScale ((double) blockSize / 130);
  setPos (X + blockSize/20, Y + blockSize/20);
}


QString
CollisionBlock::blockType ()
{
  return this->type;
}