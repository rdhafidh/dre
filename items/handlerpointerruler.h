#ifndef HANDLERPOINTERRULER_H
#define HANDLERPOINTERRULER_H

#include <QPointF>

enum class PointerModeRulerOfItem{
    POINTER_MODE_IS_UNDEFINED,
    POINTER_MODE_TOPLEFT,
    POINTER_MODE_TOP,
    POINTER_MODE_TOPRIGHT,
    POINTER_MODE_RIGHT,
    POINTER_MODE_BOTTOMRIGHT,
    POINTER_MODE_BOTTOM,
    POINTER_MODE_BOTTOMLEFT,
    POINTER_MODE_LEFT
};
class BaseAllItems;
class LineItem;

class HandlerPointerRuler
{
public:
    HandlerPointerRuler(const PointerModeRulerOfItem &mode,BaseAllItems *fromParent);
    ~HandlerPointerRuler();
    void updateCentralPos(const QPointF &pos);
    LineItem *singleLineItem();
    
private:
    void buildSingleLine(BaseAllItems *fromParent); 
    void updatePosCentralAtas(const QPointF &p);
    void updatePosCentralKiri(const QPointF &p);
    void updatePosCentralBawah(const QPointF&p);
    void updatePosCentralKanan(const QPointF &p);
    
    LineItem *m_single_line;
    PointerModeRulerOfItem m_mode;
};

#endif // HANDLERPOINTERRULER_H