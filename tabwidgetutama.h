#ifndef TABWIDGETUTAMA_H
#define TABWIDGETUTAMA_H

#include <QTabWidget>

class TabWidgetUtama : public QTabWidget {
  Q_OBJECT
 public:
  explicit TabWidgetUtama(QWidget *parent);
  void manualremovetab(int idx);

  ~TabWidgetUtama(); 

 private Q_SLOTS:
  void emitclosetab(int idx);

 private: 
};

#endif  // TABWIDGETUTAMA_H
