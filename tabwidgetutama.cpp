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

void TabWidgetUtama::emitclosetab(int idx) {
#ifdef DEBUGGING_ENABLED
  qDebug() << "tab idx removed: " << idx << __FILE__ << __LINE__;
#endif
  auto curWidget = widget(idx);

  if (curWidget != Q_NULLPTR) {
    curWidget->disconnect();
    delete curWidget;
    curWidget = nullptr;
  }
  removeTab(idx);
} 