#include <manystructuiobjectparam.h>

ManyStructUiObjectParam::SingleRowPropertyParamItemEdit
ManyStructUiObjectParam::makePropertyItemSingleRow(
    const QVariant &value_col1, const QIcon &icon_col1, bool use_icon_col1,
    const QVariant &value_col2, const QIcon &icon_col2, bool use_icon_col2,
    bool col2_is_editable, bool use_second_colom) {
  SingleRowPropertyParamItemEdit row;
  SinglePropertyParamItemEdit singlecol1;
  singlecol1.is_editable = false;  // default col1 readonly;
  singlecol1.use_icon = use_icon_col1;
  singlecol1.icon=icon_col1;
  singlecol1.value_display = value_col1;
  SinglePropertyParamItemEdit singlecol2;
  if (use_second_colom) {
    singlecol2.is_editable = col2_is_editable;
    singlecol2.use_icon = use_icon_col2;
    singlecol2.value_display = value_col2;
    singlecol2.icon = icon_col2;
  }
  row.colom0=singlecol1;
  row.colom1=singlecol2;
  row.use_second_colom=use_second_colom;
  return row;
}
