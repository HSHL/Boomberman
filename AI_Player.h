//  Author: R. Schiffers

#ifndef AI_PLAYER_H
#define	AI_PLAYER_H

#include <QTimer>
#include <cmath>

#include "Player.h"

class AI_Player : public Player {
    Q_OBJECT

private:
    QTimer* AI_timer;
    bool left, right, up, down, gotEnemy;
    int distance;
    Player* enemy = NULL;

public:
    AI_Player(int blockSize, int X, int Y, QGraphicsScene *);
    void getEnemy();
    void getDirection();
    void getDistance();
    int getDistance(int, int);
    
    //    NOT FINISHED
    void AI();
    void removeAI();

public slots:
    void AImove();

};

#endif	/* AI_PLAYER_H */