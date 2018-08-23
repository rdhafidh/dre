#include "baseskitem.h"

BaseSKItem::BaseSKItem() {}

BaseSKItem::~BaseSKItem() {}

SKItemType BaseSKItem::itemType() const { return SKItemType::ITEM_IS_INVALID; }
