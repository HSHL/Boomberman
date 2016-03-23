//  Author: R. Schiffers

#include "Arena.h"

Arena::Arena (int blockSize, int X, int Y)
{
  this->blockSize = blockSize;
  this->X = X;
  this->Y = Y;

  setGame ();
}

Arena::~Arena ()
{
  stopAI ();
  stopBombs ();
  delete this;
}

void
Arena::setGame ()
{
  setBlocks ();

  player_1 = new Player (this->blockSize, 1, 3, this);
  player_1->setFlag (QGraphicsItem::ItemIsFocusable);
  player_1->setFocus ();

  player_2 = new AI_Player (this->blockSize, 11, 11, this);

  //    NOT FINISHED
  player_2->AI ();

  this->addItem (player_1);
  this->addItem (player_2);
}

void
Arena::setBlocks ()
{
  for (int i = 0; i < this->X; i++)
    {
      for (int j = 0; j < this->Y; j++)
        {
          if (i == 0 || i == X - 1 || j == 0 || j == Y - 1)
            {
              SolidBlock *solBlock = new SolidBlock (blockSize, i, j);
              this->addItem (solBlock);
            }
          else if (i % 2 == 0 && j % 2 == 0)
            {
              SolidBlock *solBlock = new SolidBlock (blockSize, i, j);
              this->addItem (solBlock);
            }
          else if ((int) pow (i, 3) % 3 == 0 || (int) pow (j, 3) % 3 == 1)
            {
              FragileBlock *fragBlock = new FragileBlock (blockSize, i, j);
              this->addItem (fragBlock);
            }
          else
            {
              GroundBlock *grndBlock = new GroundBlock (blockSize, i, j);
              this->addItem (grndBlock);
            }
        }
    }
}

int
Arena::getX ()
{
  return this->X;
}

int
Arena::getY ()
{
  return this->Y;
}

bool
Arena::detector (int X, int Y, QString type)
{
  CollisionBlock* colliderBlock = new CollisionBlock (blockSize, X, Y);
  addItem (colliderBlock);

  QList <QGraphicsItem*> tmp = colliderBlock->collidingItems ();

  for (int i = 0; i < tmp.size (); i++)
    {
      GameObject* tmpBlock = (GameObject*) tmp[i];
      if (tmpBlock->blockType () == type)
        {
          removeItem (colliderBlock);
          delete colliderBlock;
          return true;
        }
    }
  
  removeItem (colliderBlock);
  delete colliderBlock;
  return false;
}

void
Arena::stopAI ()
{
  player_2->removeAI ();
}

void
Arena::stopBombs ()
{
  int xBlocks = width ();
  int yBlocks = height ();

  for (int i = 0; i < xBlocks; i += blockSize)
    {
      for (int j = 0; j < yBlocks; j += blockSize)
        {
          if (detector (i, j, "BOMB"))
            {
              CollisionBlock* colliderBlock = new CollisionBlock (blockSize, i, j);
              addItem (colliderBlock);

              QList <QGraphicsItem*> tmp = colliderBlock->collidingItems ();

              for (int k = 0; k < tmp.size (); k++)
                {
                  GameObject* tmpBlock = (GameObject*) tmp[k];

                  if (tmpBlock->blockType () == "BOMB")
                    {
                      Bomb* tmp = (Bomb*) tmpBlock;
                      tmp->stopTimer ();
                      removeItem (tmp);
                    }
                  else if (tmpBlock->blockType () == "EXPLOSION")
                    {
                      ExplosionBlock* tmp = (ExplosionBlock*) tmpBlock;
                      tmp->stopTimer ();
                      removeItem (tmp);
                    }
                }
              delete colliderBlock;
            }
        }
    }
}

Player*
Arena::getPlayer (int number)
{
  if (number == 1)
    {
      return this->player_1;
    }
  else
    {
      return this->player_2;
    }
}