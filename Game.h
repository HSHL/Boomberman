#ifndef GAME_H
#define	GAME_H

#include <QGraphicsView>
#include <QObject>
#include <QDir>
#include <QString>

#include "Arena.h"
#include "Menu.h"

class Game : public QGraphicsView {
    Q_OBJECT
private:
    Arena* arena; 
    Menu* menu;
    int blockSize;
    int X;
    int Y;
    
public:
    Game(int blockSize, int X, int Y);
    
    void startMenu();


public slots:
   void startGame(); 
   void gameOver();
};

#endif	/* GAME_H */