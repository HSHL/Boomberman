#ifndef PLAYER_H
#define	PLAYER_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QDir>
#include <QString>


#include <QMessageBox>

#include <QDebug>

#include "Bomb.h"
#include "CollisionBlock.h"

class Player : public GameObject {
    Q_OBJECT

protected:
    int posX, posY, bombNumber, bombCounter, bombRadius, health;
    QGraphicsScene *scene;

public:
    Player(int blockSize, int posX, int posY, QGraphicsScene *);

    virtual QString blockType();
    bool collider(int X, int Y, QString);
    int getHealth();
    void decreaseHealth();
    void increaseBombNumber();
    void increaseBombRadius();
    bool collisionTerms(QString direction);
    void idle();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void setBomb();
    void keyPressEvent(QKeyEvent* event);
    void collectItem();
    GameObject* getObject(QString type);


public slots:
    void decreaseBombCount();

signals:
    void getHurt();
};

#endif	/* PLAYER_H */