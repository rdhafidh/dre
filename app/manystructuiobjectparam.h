#ifndef MANYSTRUCTUIOBJECTPARAM_H
#define MANYSTRUCTUIOBJECTPARAM_H
#include <QString>
#include <QVariant> 
#include <QIcon>
class QStandardItem;
namespace ManyStructUiObjectParam {
struct SinglePropertyParamItemEdit
{
    QVariant value_display;
    QIcon icon;
    bool use_icon=false;
    bool is_editable=true;
};
struct SingleRowPropertyParamItemEdit{
        SinglePropertyParamItemEdit colom0;
        SinglePropertyParamItemEdit colom1;
        bool use_second_colom=true;
};
struct RecordedSingleRowItem{
   QStandardItem *model1;
   QStandardItem *model2;
   bool use_second_colom=true;
};
SingleRowPropertyParamItemEdit makePropertyItemSingleRow(const QVariant &value_col1,
                                                         const QIcon &icon_col1, bool use_icon_col1,
                                                         const QVariant &value_col2,const QIcon &icon_col2,
                                                         bool use_icon_col2,bool col2_is_editable,bool use_second_colom=true);
}
#endif // MANYSTRUCTUIOBJECTPARAM_H
