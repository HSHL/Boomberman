#include "GameObject.h"

GameObject::GameObject (int blockSize, int X, int Y)
: QGraphicsPixmapItem ()
{
  this->blockSize = blockSize;
  this->X = X;
  this->Y = Y;
}