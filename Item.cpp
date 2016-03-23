//  Author: R. Schiffers

#include "Item.h"

Item::Item (int blockSize, int X, int Y, int typeDef)
: GameObject (blockSize, X, Y)
{
  setItemType(typeDef);
  setScale ((double) blockSize / 100);
  setPos (blockSize * X, blockSize * Y);
  setZValue (0);
}

QString
Item::blockType ()
{
  return this->type;
}

void
Item::setItemType (int typeDef)
{
  if (typeDef == 0)
    {
      this->type = "ITEM_COUNT";
      setPixmap (* new QPixmap (":/res/images/Item_count.png"));
    }
  else
    {
      this->type = "ITEM_RAD";
      setPixmap (* new QPixmap (":/res/images/Item_rad.png"));
    }
}