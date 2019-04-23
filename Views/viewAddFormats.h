#ifndef VIEWADDFORMATS_H
#define VIEWADDFORMATS_H
#include "Views/viewInterface.h"
#include <QTreeView>
#include "ui_viewaddformatsUI.h"
#include <QSqlTableModel>
class ViewAddFormats : public ViewInterface, public Ui_Form
{
public:
    explicit ViewAddFormats();
private:
    QSqlTableModel *m_tbl_model_materials;
    QSqlTableModel *m_tbl_model_furnitures;
};

#endif // VIEWADDFORMATS_H
