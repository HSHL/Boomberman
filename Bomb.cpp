#include "Bomb.h"

Bomb::Bomb (int blockSize, int X, int Y, int radius, QGraphicsScene *scene)
: GameObject (blockSize, X, Y)
{
  this->type = "BOMB";
  this->radius = radius;
  this->scene = scene;
  setPixmap (*new QPixmap (":/res/images/Bombe.png"));
  setScale ((double) blockSize / 100);
  setPos (X, Y);

  explosionTimer = new QTimer ();
  explosionTimer->start (3000);
  connect (explosionTimer, SIGNAL (timeout ()), this, SLOT (explode ()));

  setZValue (1);
}

QString
Bomb::blockType ()
{
  return this->type;
}

void
Bomb::setTimer (int time)
{
  this->explosionTimer->start (time);
}

void
Bomb::stopTimer ()
{
  this->explosionTimer->stop ();
}

void
Bomb::explode ()
{
  bool left = true;
  bool right = true;
  bool up = true;
  bool down = true;

  QString soundPath = QDir::currentPath ();
  soundPath += "/res/sound/effects/explosion.wav";
  QSound *sound = new QSound (soundPath, this);
  sound->play ();

  this->scene->removeItem (this);
  //    CREATING EXPLOSIONS DEPENEDED ON RADIUS: 
  for (int i = 0; i < radius * 4; i++)
    {
      int j = i / 4 + 1;

      if (i % 4 == 0)
        {
          if (!collider (x () + j * blockSize, y (), "SOLID")
              && !collider (x () + j * blockSize, y (), "Explosion")
              && right == true)
            {
              ExplosionBlock* explosionBlock = new ExplosionBlock (blockSize, x () + j * blockSize, y (), this->scene);
              this->scene->addItem (explosionBlock);

              if (explosionBlock->collider ("FRAGILE"))
                {
                  right = false;
                }
            }
          else
            {
              right = false;
            }
        }
      else if (i % 4 == 1)
        {
          if (!collider (x () - j * blockSize, y (), "SOLID")
              && !collider (x () - j * blockSize, y (), "EXPLOSION")
              && left == true)
            {
              ExplosionBlock * explosionBlock = new ExplosionBlock (blockSize, x () - j * blockSize, y (), this->scene);
              this->scene->addItem (explosionBlock);

              if (explosionBlock->collider ("FRAGILE"))
                {
                  left = false;
                }
            }
          else
            {
              left = false;
            }
        }
      else if (i % 4 == 2)
        {
          if (!collider (x (), y () + (j * blockSize), "SOLID")
              && !collider (x (), y () + (j * blockSize), "EXPLOSION")
              && down == true)
            {
              ExplosionBlock* explosionBlock = new ExplosionBlock (blockSize, x (), y () + (j * blockSize), this->scene);
              this->scene->addItem (explosionBlock);

              if (explosionBlock->collider ("FRAGILE"))
                {
                  down = false;
                }
            }
          else
            {
              down = false;
            }
        }
      else if (i % 4 == 3)
        {
          if (!collider (x (), y () - j * blockSize, "SOLID")
              && !collider (x (), y () - j * blockSize, "EXPLOSION")
              && up == true)
            {
              ExplosionBlock* explosionBlock = new ExplosionBlock (blockSize, x (), y () - j * blockSize, this->scene);
              this->scene->addItem (explosionBlock);

              if (explosionBlock->collider ("FRAGILE"))
                {
                  up = false;
                }
            }
          else
            {
              up = false;
            }
        }
    }
  ExplosionBlock* explosionBlock = new ExplosionBlock (blockSize, x (), y (), this->scene);
  this->scene->addItem (explosionBlock);

  emit explosion ();
  delete this;
}

bool
Bomb::collider (int X, int Y, QString type)
{
  CollisionBlock* colliderBlock = new CollisionBlock (blockSize, X, Y);
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