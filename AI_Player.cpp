#include "AI_Player.h"

AI_Player::AI_Player (int blockSize, int posX, int posY, QGraphicsScene *scene)
: Player (blockSize, posX, posY, scene)
{
  this->AI_timer = NULL;
  setPixmap (* new QPixmap (":/res/images/propKopUp.png"));
  gotEnemy = false;
}

void
AI_Player::getEnemy ()
{
  int xBlocks = scene->width ();
  int yBlocks = scene->height ();


  for (int x = 0; x < xBlocks; x += blockSize)
    {
      for (int y = 0; y < yBlocks; y += blockSize)
        {
          if (collider (x, y, "PLAYER"))
            {
              CollisionBlock* colliderBlock = new CollisionBlock (blockSize, x, y);
              this->scene->addItem (colliderBlock);

              QList <QGraphicsItem*> tmp = colliderBlock->collidingItems ();

              for (int k = 0; k < tmp.size (); k++)
                {
                  Player* tmpBlock = (Player*) tmp[k];
                  if (tmpBlock->blockType () == "PLAYER" && tmpBlock != this)
                    {
                      qDebug () << "###Enemy found###";

                      enemy = tmpBlock;
                      gotEnemy = true;
                    }
                }
              delete colliderBlock;
            }
        }
    }
}

void
AI_Player::getDirection ()
{
  left = false, right = false, up = false, down = false;


  if (collisionTerms ("LEFT"))
    {
      left = true;
      //qDebug () << "left TRUE";
    }
  if (collisionTerms ("RIGHT"))
    {
      right = true;
      //qDebug () << "right TRUE";
    }
  if (collisionTerms ("UP"))
    {
      up = true;
      //qDebug () << "up TRUE";
    }
  if (collisionTerms ("DOWN"))
    {
      down = true;
      //qDebug () << "down TRUE";
    }
}

void
AI_Player::getDistance ()
{
  if (enemy != NULL)
    {
      int dist = sqrt (pow ((enemy->x () - x ()), 2) + pow ((enemy->y () - y ()), 2));
      qDebug () << enemy->pos () << "Distanz: " << dist / blockSize;
      this->distance = dist;
    }
}

int
AI_Player::getDistance (int posX, int posY)
{
  int dist = sqrt (pow ((enemy->x () - posX), 2) + pow ((enemy->y () - posY), 2));
  return dist;

}

void
AI_Player::AI ()
{
  this->AI_timer = new QTimer ();
  AI_timer->start (1000);
  connect (AI_timer, SIGNAL (timeout ()), this, SLOT (AImove ()));
}

void
AI_Player::removeAI ()
{
  if (AI_timer != NULL)
    {
      AI_timer->stop ();
      disconnect (AI_timer, SIGNAL (timeout ()), this, SLOT (AImove ()));
    }
}


//    NOT FINISHED

void
AI_Player::AImove ()
{
  getDirection ();

  if (this->health <= 0)
    {
      AI_timer->stop ();
    }

  else if (left)
    {
      moveLeft ();
      setPixmap (* new QPixmap (":/res/images/propKopLeft.png"));

      //setBomb ();

      collectItem ();
      //qDebug () << "Left";
    }

  else if (right)
    {
      moveRight ();
      setPixmap (* new QPixmap (":/res/images/propKopRight.png"));


      collectItem ();
      //qDebug () << "Right";
    }

  else if (up)
    {
      moveUp ();
      setPixmap (* new QPixmap (":/res/images/propKopDown.png"));

      collectItem ();
      //qDebug () << "Up";
      //setBomb ();
    }

  else if (down)
    {
      moveDown ();
      setPixmap (* new QPixmap (":/res/images/propKopUp.png"));

      collectItem ();
      //qDebug () << "Down";
    }

  if (enemy != NULL)
    {
      getDistance ();
      qDebug () << this->distance;
      qDebug () << "Distance on Position: [" << x () - blockSize << ":" << y ()
              << "] ->" << getDistance (x () - blockSize, y ());
    }

  else
    {
      getEnemy ();
      getDistance ();
    }
}