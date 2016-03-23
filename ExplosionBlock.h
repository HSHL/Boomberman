//  Author: R. Schiffers

#ifndef EXPLOSIONBLOCK_H
#define	EXPLOSIONBLOCK_H

#include <QObject>
#include <QTimer>

#include "GameObject.h"
#include "CollisionBlock.h"
#include "GroundBlock.h"
#include "Bomb.h"
#include "Item.h"

class ExplosionBlock : public GameObject {
    Q_OBJECT

private:
    int blockSize, X, Y;

    QTimer* destroyTimer;
    QGraphicsScene *scene;

public:
    ExplosionBlock(int blockSize, int X, int Y, QGraphicsScene*);

    virtual QString blockType();
    bool collider(QString type);
    void damage();
    void bombDetection();
    void stopTimer();
    QList <QGraphicsItem*> getCollision();
    int getRandomInt(int min, int max);
    
    
public slots:
    void destroy();

};

#endif	/* EXPLOSIONBLOCK_H */