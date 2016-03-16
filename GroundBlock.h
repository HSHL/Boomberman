#ifndef GROUNDBLOCK_H
#define	GROUNDBLOCK_H

#include <QObject>

#include "GameObject.h"

class GroundBlock : public GameObject {
    Q_OBJECT

private:

public:
    GroundBlock(int blockSize, int X, int Y);

    virtual QString blockType();


};

#endif	/* GROUNDBLOCK_H */