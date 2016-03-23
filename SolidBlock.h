//  Author: R. Schiffers

#ifndef SOLIDBLOCK_H
#define	SOLIDBLOCK_H

#include <QObject>

#include "GameObject.h"

class SolidBlock : public GameObject {
    Q_OBJECT

private:


public:
    SolidBlock(int, int, int);
    virtual QString blockType();
};

#endif	/* SOLIDBLOCK_H */