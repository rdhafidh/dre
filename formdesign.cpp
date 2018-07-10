#include "formdesign.h"
#include <imageitem.h>
#include <lineitem.h>
#include <pageitem.h>
#include <propertyedititemdelegate.h>
#include <ruleritem.h>
#include <sceneview.h>
#include <textitem.h>
#include <undocommand.h>

#ifdef DEBUGGING_ENABLED
#include <QDebug>
#endif
#include <QStandardItemModel>
#include <QTreeView>
#include "ui_formdesign.h"

FormDesign::FormDesign(QWidget *parent)
    : QWidget(parent), ui(new Ui::FormDesign) {
  ui->setupUi(this);
  delegate_obj_editor = new PropertyEditItemDelegate;
  ui->graphicsView->grabGesture(Qt::PinchGesture);
  ui->graphicsView->grabGesture(Qt::SwipeGesture);
  scnview = new SceneView(this);
  scnview->setMainPageDesign(this);
  scnview->buildNewItemPage();
  scnview->buildNewRuler(
      Qt::Horizontal, QSizeF(scnview->pageItemDesign()->getRect().width(), 0));
  scnview->rulerAtas()->setRatioUnit(
      scnview->pageItemDesign()->getRect().width() /
      scnview->pageItemDesign()->gridSize());
  scnview->buildNewRuler(
      Qt::Vertical, QSizeF(0, scnview->pageItemDesign()->getRect().height()));
  scnview->rulerKiri()->setRatioUnit(
      scnview->pageItemDesign()->getRect().height() /
      scnview->pageItemDesign()->gridSize());
  connect(scnview, &SceneView::itemRemovedFromScene,
          [this](BaseAllItems *) { this->resetPropertyItemObj(); });
  connect(scnview, SIGNAL(itemSelected(BaseAllItems *)),
          SLOT(handleItemSelection(BaseAllItems *)));
  ui->graphicsView->setScene(scnview);
  scnview->setupMouseRulerPointers();
  model_item_prop = new QStandardItemModel(this);
  model_obj_tree = new QStandardItemModel(this);
  ui->graphicsView->resetMatrix();
  ui->graphicsView->centerOn(0, 0);
  ui->graphicsView->scale(0.4, 0.4);

  this->resetPropertyItemObj();
  ui->treeView_prop_item->setModel(model_item_prop);
}

FormDesign::~FormDesign() {
  scnview->disconnect();
  delegate_obj_editor->disconnect();
  delete delegate_obj_editor;
  delete scnview;
  delete ui;
}

SceneView *FormDesign::getScene() { return scnview; }

void FormDesign::resetPropertyItemObj() {
  model_item_prop->clear();
  recorded_item_prop.clear();
  ui->treeView_prop_item->setItemDelegate(delegate_obj_editor);
  ui->treeView_prop_item->header()->setDefaultSectionSize(89);
  model_item_prop->setHorizontalHeaderLabels(
      QStringList() << tr("Nama Properti") << tr("Nilai Properti"));
}

void FormDesign::handleItemPropertyUpdate() {
  const BaseAllItems *fromitem = qobject_cast<BaseAllItems *>(sender());
  if (!fromitem) {
#ifdef DEBUGGING_ENABLED
    qDebug() << "warning cast failed property req update";
#endif
    return;
  }
  switch (fromitem->getItemType()) {
    case ItemConst::Tipe::TEKS:
      this->updateItemPropertySeletionTeks(fromitem);
      break;
    case ItemConst::Tipe::GAMBAR:
      this->updateItemPropertySeletionGambar(fromitem);
      break;
    case ItemConst::Tipe::GARIS:
      this->updateItemPropertySeletionLine(fromitem);
      break;
    default:
      break;
  }
}

void FormDesign::handleItemSelection(BaseAllItems *item) {
  currentitem = item;
  this->resetPropertyItemObj();

  switch (item->getItemType()) {
    case ItemConst::Tipe::TEKS:
      this->buildItemPropertySelectionTeks(item);
      break;
    case ItemConst::Tipe::GAMBAR:
      this->buildItemPropertySelectionGambar(item);
      break;
    case ItemConst::Tipe::GARIS:
      this->buildItemPropertySelectionLine(item);
      break;
    default:
      break;
  }
}

void FormDesign::buildItemPropertySelectionTeks(BaseAllItems *item) {
  TextItem *itm = qobject_cast<TextItem *>(item);
  if (itm) {
    QStandardItem *last_parent = nullptr;
    QStandardItem *parent = model_item_prop->invisibleRootItem();
    last_parent = insertNewPropertyItemFromParent(
        parent, ManyStructUiObjectParam::makePropertyItemSingleRow(
                    tr("Posisi X"), QIcon(), false, itm->pos().x(), QIcon(),
                    false, false));
    last_parent = insertNewPropertyItemFromParent(
        parent, ManyStructUiObjectParam::makePropertyItemSingleRow(
                    tr("Posisi Y"), QIcon(), false, itm->pos().y(), QIcon(),
                    false, false));
    last_parent = insertNewPropertyItemFromParent(
        parent, ManyStructUiObjectParam::makePropertyItemSingleRow(
                    tr("Rotasi"), QIcon(), false,
                    item->property("rotasi").toInt(), QIcon(), false, true));
  }
}

void FormDesign::buildItemPropertySelectionGambar(BaseAllItems *item) {
  ImageItem *img = qobject_cast<ImageItem *>(item);
  if (img) {
    QStandardItem *last_parent = nullptr;
    QStandardItem *parent = model_item_prop->invisibleRootItem();
    last_parent = insertNewPropertyItemFromParent(
        parent, ManyStructUiObjectParam::makePropertyItemSingleRow(
                    tr("Posisi X"), QIcon(), false, img->pos().x(), QIcon(),
                    false, false));
    last_parent = insertNewPropertyItemFromParent(
        parent, ManyStructUiObjectParam::makePropertyItemSingleRow(
                    tr("Posisi Y"), QIcon(), false, img->pos().y(), QIcon(),
                    false, false));
  }
}

void FormDesign::buildItemPropertySelectionLine(BaseAllItems *item) {
  LineItem *ln = qobject_cast<LineItem *>(item);
  if (ln) {
    QStandardItem *last_parent = nullptr;
    QStandardItem *parent = model_item_prop->invisibleRootItem();
    last_parent = insertNewPropertyItemFromParent(
        parent, ManyStructUiObjectParam::makePropertyItemSingleRow(
                    tr("Posisi X"), QIcon(), false, ln->pos().x(), QIcon(),
                    false, false));
    last_parent = insertNewPropertyItemFromParent(
        parent, ManyStructUiObjectParam::makePropertyItemSingleRow(
                    tr("Posisi Y"), QIcon(), false, ln->pos().y(), QIcon(),
                    false, false));
  }
}

void FormDesign::updateItemPropertySeletionTeks(const BaseAllItems *item) {
  const TextItem *itm = qobject_cast<const TextItem *>(item);
  if (itm) {
    auto item_to_edit =
        lookUpSecondColumnPropItemFromKeyStringCol1(tr("Posisi X"));
    if (item_to_edit != nullptr) {
      item_to_edit->setText(tr("%1").arg(itm->pos().x()));
    }
    item_to_edit = lookUpSecondColumnPropItemFromKeyStringCol1(tr("Posisi Y"));
    if (item_to_edit != nullptr) {
      item_to_edit->setText(tr("%1").arg(itm->pos().y()));
    }
  }
}

void FormDesign::updateItemPropertySeletionGambar(const BaseAllItems *item) {
  const ImageItem *itm = qobject_cast<const ImageItem *>(item);
  if (itm) {
    auto item_to_edit =
        lookUpSecondColumnPropItemFromKeyStringCol1(tr("Posisi X"));
    if (item_to_edit != nullptr) {
      item_to_edit->setText(tr("%1").arg(itm->pos().x()));
    }
    item_to_edit = lookUpSecondColumnPropItemFromKeyStringCol1(tr("Posisi Y"));
    if (item_to_edit != nullptr) {
      item_to_edit->setText(tr("%1").arg(itm->pos().y()));
    }
  }
}

void FormDesign::updateItemPropertySeletionLine(const BaseAllItems *item) {
  const LineItem *itm = qobject_cast<const LineItem *>(item);
  if (itm) {
    auto item_to_edit =
        lookUpSecondColumnPropItemFromKeyStringCol1(tr("Posisi X"));
    if (item_to_edit != nullptr) {
      item_to_edit->setText(tr("%1").arg(itm->pos().x()));
    }
    item_to_edit = lookUpSecondColumnPropItemFromKeyStringCol1(tr("Posisi Y"));
    if (item_to_edit != nullptr) {
      item_to_edit->setText(tr("%1").arg(itm->pos().y()));
    }
  }
}

QStandardItem *FormDesign::insertNewPropertyItemFromParent(
    QStandardItem *parent,
    const ManyStructUiObjectParam::SingleRowPropertyParamItemEdit &in) {
  QStandardItem *item1 = new QStandardItem;
  QStandardItem *item2 = new QStandardItem;
  item1->setText(in.colom0.value_display.toString());
  if (in.colom0.is_editable) {
    item1->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled |
                    Qt::ItemIsSelectable);
  } else {
    item1->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
  }
  if (in.colom0.use_icon) {
    item1->setData(in.colom0.icon, Qt::DecorationRole);
  }
  if (in.use_second_colom) {
    item2->setText(in.colom1.value_display.toString());
    if (in.colom1.use_icon) {
      item2->setData(in.colom1.icon, Qt::DecorationRole);
    }
    if (in.colom1.is_editable) {
      item2->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled |
                      Qt::ItemIsSelectable);
    } else {
      item2->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    }
  } else {
    item2->setFlags(Qt::ItemIsEnabled);
  }
  ManyStructUiObjectParam::RecordedSingleRowItem record_per_row;
  record_per_row.model1 = item1;
  record_per_row.model2 = item2;
  record_per_row.use_second_colom = in.use_second_colom;

  recorded_item_prop << record_per_row;
  parent->appendRow(QList<QStandardItem *>() << item1 << item2);
  return item1;
}

QStandardItem *FormDesign::lookUpSecondColumnPropItemFromKeyStringCol1(
    const QString &key) {
  for (auto row : recorded_item_prop) {
    if (row.model1 && row.model2) {
      if (row.model1->text() == key) {
        return row.model2;
      }
    }
  }
  return nullptr;
}
