#include "handlerpointerruler.h"
#include <baseallitems.h>
#include <lineitem.h>

HandlerPointerRuler::HandlerPointerRuler(const PointerModeRulerOfItem &mode,
                                         BaseAllItems *fromParent) {
  m_single_line=nullptr;
  m_mode = mode;
  switch (m_mode) {
    case PointerModeRulerOfItem::POINTER_MODE_BOTTOM:
    case PointerModeRulerOfItem::POINTER_MODE_LEFT:
    case PointerModeRulerOfItem::POINTER_MODE_RIGHT:
    case PointerModeRulerOfItem::POINTER_MODE_TOP: 
      this->buildSingleLine (fromParent);
      break;
  }
}

HandlerPointerRuler::~HandlerPointerRuler() {
  switch (m_mode) {
    case PointerModeRulerOfItem::POINTER_MODE_BOTTOM:
    case PointerModeRulerOfItem::POINTER_MODE_LEFT:
    case PointerModeRulerOfItem::POINTER_MODE_RIGHT:
    case PointerModeRulerOfItem::POINTER_MODE_TOP:
      if(m_single_line){
          delete m_single_line;
      }
      break;
  }
}

void HandlerPointerRuler::updateCentralPos(const QPointF &pos)
{
    if(m_single_line){ 
        switch (m_mode) {
          case PointerModeRulerOfItem::POINTER_MODE_BOTTOM:
            this->updatePosCentralBawah (pos);
            break;
          case PointerModeRulerOfItem::POINTER_MODE_LEFT:
            this->updatePosCentralKiri (pos);
            break;
          case PointerModeRulerOfItem::POINTER_MODE_RIGHT:
            this->updatePosCentralKanan (pos);
            break;
          case PointerModeRulerOfItem::POINTER_MODE_TOP: 
            this->updatePosCentralAtas (pos);
            break;
        }
    }
}

LineItem *HandlerPointerRuler::singleLineItem()
{
    return m_single_line;
}

void HandlerPointerRuler::buildSingleLine (BaseAllItems *fromParent) {
  m_single_line = new LineItem(fromParent);
  m_single_line->setWidth (2.0); 
  m_single_line->setStartPoint (fromParent->rect ().topLeft ());
  m_single_line->setEndPoint (fromParent->rect ().topRight ());
  
}

void HandlerPointerRuler::updatePosCentralAtas(const QPointF &p)
{
    // yang diupdate hanya sumbu y saja
    //disini tetap compute topleft darn topright lagi
    QPointF topleft(m_single_line->startPoint ().x (),p.y ()-(m_single_line->width ()/2));
    m_single_line->setStartPoint (topleft);
    QPointF bottomright(m_single_line->startPoint ().x (),p.y ()+(m_single_line->width ()/2));
    m_single_line->setEndPoint (bottomright);
}

void HandlerPointerRuler::updatePosCentralKiri(const QPointF &p)
{
    
}

void HandlerPointerRuler::updatePosCentralBawah(const QPointF &p)
{
    
}

void HandlerPointerRuler::updatePosCentralKanan(const QPointF &p)
{
    
}
 