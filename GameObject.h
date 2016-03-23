//  Author: R. Schiffers

#ifndef BLOCK_H
#define	BLOCK_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QString>

class GameObject : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

protected:
    int blockSize, X, Y;
    QString type;

public:
    GameObject(int blockSize, int X, int Y);

    virtual QString blockType() = 0;
};

#endif	/* BLOCK_H */