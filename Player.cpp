//  Author: R. Schiffers

#include "Player.h"

Player::Player (int blockSize, int posX, int posY, QGraphicsScene *scene)
: GameObject (blockSize, posX, posY)
{
  this->type = "PLAYER";
  this->posX = posX;
  this->posY = posY;
  this->scene = scene;
  this->X = scene->width () / blockSize;
  this->Y = scene->height () / blockSize;
  this->bombNumber = 1;
  this->bombCounter = 0;
  this->bombRadius = 1;
  this->health = 1;

  setPixmap (* new QPixmap (":/res/images/RoboUp.png"));
  setScale ((double) blockSize / 105);
  setPos (blockSize * posX + 1, blockSize * posY + 1);
  setZValue (2);

  collectItem ();
}

QString
Player::blockType ()
{
  return this->type;
}

bool
Player::collider (int X, int Y, QString type)
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

int
Player::getHealth ()
{
  return this->health;
}

void
Player::decreaseHealth ()
{
  this->health--;
  emit getHurt ();
}

void
Player::increaseBombNumber ()
{
  this->bombNumber++;
}

void
Player::increaseBombRadius ()
{
  this->bombRadius++;
}

bool
Player::collisionTerms (QString direction)
{
  if (!collider (pos ().x (), pos ().y () - blockSize, "SOLID")
      && !collider (pos ().x (), pos ().y () - blockSize, "BOMB")
      && !collider (pos ().x (), pos ().y () - blockSize, "FRAGILE")
      && direction == "UP")
    {
      return true;
    }
  else if (!collider (pos ().x (), pos ().y () + blockSize, "SOLID")
           && !collider (pos ().x (), pos ().y () + blockSize, "BOMB")
           && !collider (pos ().x (), pos ().y () + blockSize, "FRAGILE")
           && direction == "DOWN")
    {
      return true;
    }

  else if (!collider (pos ().x () - blockSize, pos ().y (), "SOLID")
           && !collider (pos ().x () - blockSize, pos ().y (), "BOMB")
           && !collider (pos ().x () - blockSize, pos ().y (), "FRAGILE")
           && direction == "LEFT")
    {
      return true;
    }
  else if (!collider (pos ().x () + blockSize, pos ().y (), "SOLID")
           && !collider (pos ().x () + blockSize, pos ().y (), "BOMB")
           && !collider (pos ().x () + blockSize, pos ().y (), "FRAGILE")
           && direction == "RIGHT")
    {
      return true;
    }
  else
    {
      return false;
    }
}

void
Player::idle ()
{
  setPos (x (), y ());
}

void
Player::moveUp ()
{
  if (pos ().y () > 0 + blockSize && collisionTerms ("UP"))
    {
      setPos (x (), y () - blockSize);
      collectItem ();
    }
}

void
Player::moveDown ()
{
  if (pos ().y () < blockSize * Y - blockSize && collisionTerms ("DOWN"))
    {
      setPos (x (), y () + blockSize);
      collectItem ();
    }
}

void
Player::moveLeft ()
{
  if (pos ().x () - 1 > 0 && collisionTerms ("LEFT"))
    {
      setPos (x () - blockSize, y ());
      collectItem ();
    }
}

void
Player::moveRight ()
{
  if (pos ().x () < blockSize * X - blockSize && collisionTerms ("RIGHT"))
    {
      setPos (x () + blockSize, y ());
      collectItem ();
    }

}

void
Player::setBomb ()
{
  if (!collider (pos ().x (), pos ().y (), "BOMB")
      && bombCounter < bombNumber)
    {
      QString soundPath = QDir::currentPath ();
      soundPath += "/res/sound/effects/pop.wav";
      QSound *sound = new QSound (soundPath, this);
      sound->play ();

      Bomb *bomb = new Bomb (blockSize, x (), y (), bombRadius, this->scene);
      connect (bomb, SIGNAL (explosion ()), this, SLOT (decreaseBombCount ()));
      this->scene->addItem (bomb);

      bombCounter++;
    }
}

void
Player::keyPressEvent (QKeyEvent* event)
{
  if (event->key () == Qt::Key_Left)
    {
      moveLeft ();
      setPixmap (* new QPixmap (":/res/images/RoboLeft.png"));

    }

  else if (event->key () == Qt::Key_Right)
    {
      moveRight ();
      setPixmap (* new QPixmap (":/res/images/RoboRight.png"));

    }

  else if (event->key () == Qt::Key_Up)
    {
      moveUp ();
      setPixmap (* new QPixmap (":/res/images/RoboDown.png"));

    }

  else if (event->key () == Qt::Key_Down)
    {
      moveDown ();
      setPixmap (* new QPixmap (":/res/images/RoboUp.png"));

    }

  else if (event->key () == Qt::Key_Space)
    {
      setBomb ();
    }
}

void
Player::collectItem ()
{
  if (collider (x (), y (), "ITEM_COUNT") || collider (x (), y (), "ITEM_RAD"))
    {
      if (collider (x (), y (), "ITEM_COUNT"))
        {
          QString soundPath = QDir::currentPath ();
          soundPath += "/res/sound/effects/item1.wav";
          QSound *sound = new QSound (soundPath, this);
          sound->play ();

          GameObject* tmp = getObject ("ITEM_COUNT");
          this->scene->removeItem (tmp);
          delete tmp;
          this->increaseBombNumber ();
        }
      else
        {
          QString soundPath = QDir::currentPath ();
          soundPath += "/res/sound/effects/item2.wav";
          QSound *sound = new QSound (soundPath, this);
          sound->play ();

          GameObject* tmp = getObject ("ITEM_RAD");
          this->scene->removeItem (tmp);
          delete tmp;
          this->increaseBombRadius ();
        }
    }
}

GameObject*
Player::getObject (QString type)
{
  CollisionBlock* colliderBlock = new CollisionBlock (blockSize, x (), y ());
  this->scene->addItem (colliderBlock);

  QList <QGraphicsItem*> tmp = colliderBlock->collidingItems ();

  for (int i = 0; i < tmp.size (); i++)
    {
      GameObject* tmpBlock = (GameObject*) tmp[i];
      if (tmpBlock->blockType () == type)
        {
          delete colliderBlock;
          return tmpBlock;
        }
    }

  return colliderBlock;
}

void
Player::decreaseBombCount ()
{
  this->bombCounter--;
}