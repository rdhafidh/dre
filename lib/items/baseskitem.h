#ifndef BASESKITEM_H
#define BASESKITEM_H

#include <core/sKCanvas.h>

enum class SKItemType{
    ITEM_IS_INVALID,
    ITEM_IS_TEXT,
    ITEM_IS_IMAGE,
    ITEM_IS_LINE,
    ITEM_IS_TRIANGLE,
    ITEM_IS_ELLIPSE
};

class BaseSKItem
{
public:
    BaseSKItem();
      ~BaseSKItem();
protected:
    virtual SKItemType itemType()const;
    virtual void draw(SkCanvas *canvas)=0;
};

#endif // BASESKITEM_H