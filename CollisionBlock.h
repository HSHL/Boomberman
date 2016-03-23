//  Author: R. Schiffers

#ifndef COLLISIONBLOCK_H
#define	COLLISIONBLOCK_H


#include <QObject>

#include "GameObject.h"

class CollisionBlock : public GameObject {
    Q_OBJECT
private:


public:
    CollisionBlock(int blockSize, int X, int Y);

    virtual QString blockType();
};

#endif	/* COLLISIONBLOCK_H */