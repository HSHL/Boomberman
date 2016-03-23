//  Author: R. Schiffers

#ifndef BOMB_H
#define	BOMB_H

#include <cstdio>

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QString>
#include <QDir>
#include <QSound>

#include "GameObject.h"
#include "ExplosionBlock.h"
#include "CollisionBlock.h"

class Bomb : public GameObject {
    Q_OBJECT

private:
    int radius;

    QTimer* explosionTimer;
    QGraphicsScene *scene;


public:
    Bomb(int blockSize, int X, int Y, int radius, QGraphicsScene *scene);

    virtual QString blockType();

    void setTimer(int time);
    void stopTimer();
    bool collider(int X, int Y, QString);

public slots:
    void explode();

signals:
    void explosion();


};

#endif	/* BOMB_H */