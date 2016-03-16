#ifndef MENU_H
#define	MENU_H

#include <QGraphicsScene>
#include <QBrush>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QPushButton>


class Menu : public QGraphicsScene {
private:
    QGraphicsPixmapItem* backGround;
    QPushButton* startButton;

public:
    Menu(int width, int height);
    QPushButton* getStartButton();


};

#endif	/* MENU_H */