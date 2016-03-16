#ifndef ARENA_H
#define ARENA_H

#include <QObject>
#include <QPainter>
#include <QBrush>
#include <QSound>
#include <cmath>

#include "AI_Player.h"
#include "ExplosionBlock.h"
#include "GroundBlock.h"
#include "SolidBlock.h"
#include "FragileBlock.h"

class Arena : public QGraphicsScene {
    Q_OBJECT

private:
    Player *player_1;
    AI_Player *player_2;
    int blockSize;
    int X;
    int Y;

public:
    Arena(int blockSize, int x, int y);
    ~Arena();

    void setGame();
    void setBlocks();
    int getX();
    int getY();
    void stopAI();
    void stopBombs();
    bool detector(int X, int Y, QString type);
    Player* getPlayer(int);
};

#endif /* RASTER_H */