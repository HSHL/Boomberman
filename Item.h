#ifndef ITEM_H
#define	ITEM_H

#include <QObject>

#include "GameObject.h"

class Item : public GameObject {
private:
    QString itemType;

public:
    Item(int, int, int, int);

   virtual QString blockType();
   void setItemType(int typeDef);
   void affectPlayer();

};

#endif	/* ITEM_H */