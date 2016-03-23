//  Author: R. Schiffers

#ifndef FRAGILEBLOCK_H
#define	FRAGILEBLOCK_H

#include <QObject>

#include "GameObject.h"

class FragileBlock : public GameObject {
    Q_OBJECT

private:


public:
    FragileBlock(int blockSize, int X, int Y);

    virtual QString blockType();


};

#endif	/* FRAGILEBLOCK_H */