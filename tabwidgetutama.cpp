#include "tabwidgetutama.h" 

TabWidgetUtama::TabWidgetUtama(QWidget *parent) : QTabWidget(parent) {
  connect(this, SIGNAL(tabCloseRequested(int)), SLOT(emitclosetab(int)));
}

void TabWidgetUtama::manualremovetab(int idx) { Q_EMIT tabCloseRequested(idx); }

TabWidgetUtama::~TabWidgetUtama() {
  while (count()) {
    manualremovetab(0);
  }
}

//void TabWidgetUtama::removetabpenjualan() {
//  for (int i = 0; i < count(); i++) {
//    QWidget *curWidget = widget(i);
//    if (curWidget != NULL) {
//      QVariant val = curWidget->property("jual");
//      if (val.isValid()) {
//        if (val.toBool()) {
//#ifdef DEBUGB
//          qDebug() << "found tab jual idx:" << i;
//#endif
//          asktoremovetabjualorno(curWidget);
//          removeTab(i);
//          curWidget->deleteLater();
//        }
//      }
//    }
//  }
//}

void TabWidgetUtama::emitclosetab(int idx) {
#ifdef DEBUGB
  qDebug() << "tab idx removed: " << idx << __FILE__ << __LINE__;
#endif
  auto curWidget = widget(idx);

  if (curWidget != Q_NULLPTR) { 
    curWidget->disconnect ();
    delete curWidget;
    curWidget=nullptr;
  }
  removeTab(idx);
}

//void TabWidgetUtama::asktoremovetabjualorno(QWidget *widget) { 
//  using namespace form;
//  TransaksiPenjualan *tp = qobject_cast<TransaksiPenjualan *>(widget);
//  if (tp != Q_NULLPTR) {
//    if (tp->tabelbarang()->rowCount() >= 1) {
//      tp->on_pushButton_hold_clicked();
//    }
//  }
//}
