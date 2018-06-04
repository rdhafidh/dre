#ifndef CONSTVALUE_H
#define CONSTVALUE_H


#include <QGraphicsItem>

namespace ItemConst {
    enum class Tipe{ KOTAK=QGraphicsItem::UserType+1,
                    BULAT=QGraphicsItem::UserType+2,
                    GARIS=QGraphicsItem::UserType+3,
                    SEGITIGA=QGraphicsItem::UserType+4,
                    GAMBAR=QGraphicsItem::UserType+5,
                    BARCODE=QGraphicsItem::UserType+6,
                     TEKS=QGraphicsItem::UserType+7
       };
    enum class CekMelebihiPageItem{
        ATAS=0x1,BAWAH,KIRI,KANAN
    };
    
    enum class ModeItemDesignOrPreview{
        MODE_PREVIEW=0x2,MODE_DESIGN
    };
}
#endif // CONSTVALUE_H
