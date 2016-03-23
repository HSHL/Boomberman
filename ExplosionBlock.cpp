//  Author: R. Schiffers

#include "ExplosionBlock.h"
#include "Player.h"

ExplosionBlock::ExplosionBlock (int blockSize, int X, int Y, QGraphicsScene *scene)
: GameObject (blockSize, X, Y)
{
  this->type = "EXPLOSION";
  this->scene = scene;
  this->blockSize = blockSize;

  this->setPixmap (* new QPixmap (":/res/images/Explosion.png"));
  this->setScale ((double) blockSize / 100);
  this->setPos (X, Y);
  setZValue (3);

  bombDetection ();

  this->destroyTimer = new QTimer ();
  connect (destroyTimer, SIGNAL (timeout ()), this, SLOT (destroy ()));
  this->destroyTimer->start (300);
}

QString
ExplosionBlock::blockType ()
{
  return this->type;
}

bool
ExplosionBlock::collider (QString type)
{
  CollisionBlock* colliderBlock = new CollisionBlock (blockSize, x (), y ());
  this->scene->addItem (colliderBlock);

  QList <QGraphicsItem*> tmp = colliderBlock->collidingItems ();

  for (int i = 0; i < tmp.size (); i++)
    {
      GameObject* tmpBlock = (GameObject*) tmp[i];

      if (tmpBlock->blockType () == type)
        {
          this->scene->removeItem (colliderBlock);
          delete colliderBlock;
          return true;
        }
    }
  this->scene->removeItem (colliderBlock);
  delete colliderBlock;
  return false;
}

void
ExplosionBlock::damage ()
{
  int itemRandom = getRandomInt (1, 300);

  QList <QGraphicsItem*> tmp = getCollision ();

  if (collider ("FRAGILE"))
    {
      for (int i = 0, n = tmp.size (); i < n; i++)
        {
          GameObject* tmpBLOCK = (GameObject*) tmp[i];

          if (tmpBLOCK->blockType () == "FRAGILE")
            {
              GroundBlock* block = new GroundBlock (blockSize, tmpBLOCK->pos ().x () / blockSize, tmpBLOCK->pos ().y () / blockSize);
              this->scene->addItem (block);

              if (itemRandom > 200)
                {
                  int typeDef = (itemRandom <= 250) ? 0 : 1;
                  Item* item = new Item (blockSize, tmpBLOCK->pos ().x () / blockSize, tmpBLOCK->pos ().y () / blockSize, typeDef);

                  this->scene->addItem (item);
                }

              this->scene->removeItem (tmpBLOCK);
              delete tmpBLOCK;
            }
        }
    }


  if (collider ("PLAYER"))
    {
      for (int i = 0, n = tmp.size (); i < n; i++)
        {
          GameObject* tmpBLOCK = (GameObject*) tmp[i];

          if (tmpBLOCK->blockType () == "PLAYER")
            {
              Player *tmpPLAYER = (Player*) tmpBLOCK;
              tmpPLAYER->decreaseHealth ();
            }
        }
    }
}

void
ExplosionBlock::bombDetection ()
{
  QList <QGraphicsItem*> tmp = getCollision ();

  if (collider ("BOMB"))
    {
      for (int i = 0, n = tmp.size (); i < n; i++)
        {
          GameObject* tmpBLOCK = (GameObject*) tmp[i];

          if (tmpBLOCK->blockType () == "BOMB")
            {
              Bomb* tmpBOMB = (Bomb*) tmpBLOCK;
              tmpBOMB->setTimer (0);
            }
        }
    }
}

void
ExplosionBlock::stopTimer ()
{
  this->destroyTimer->stop ();
}

QList <QGraphicsItem*>
ExplosionBlock::getCollision ()
{
  CollisionBlock *colliderBlock = new CollisionBlock (blockSize, x (), y ());
  this->scene->addItem (colliderBlock);
  QList <QGraphicsItem*> tmp = colliderBlock->collidingItems ();
  this->scene->removeItem (colliderBlock);
  delete colliderBlock;

  return tmp;
}

int
ExplosionBlock::getRandomInt (int min, int max)
{
  int random = qrand () % ((max + 1) - min) + min;
  return random;
}

void
ExplosionBlock::destroy ()
{
  damage ();

  this->scene->removeItem (this);
  delete this;
}