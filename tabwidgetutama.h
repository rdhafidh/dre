#ifndef TABWIDGETUTAMA_H
#define TABWIDGETUTAMA_H

#include <QTabWidget>

class TabWidgetUtama : public QTabWidget {
  Q_OBJECT
public:
  explicit TabWidgetUtama(QWidget *parent) ;
  void manualremovetab(int idx) ;

  ~TabWidgetUtama();
//  void removetabpenjualan() ;

private Q_SLOTS:
  void emitclosetab(int idx);

private:
//  void asktoremovetabjualorno(QWidget *widget) ;
};

#endif // TABWIDGETUTAMA_H
