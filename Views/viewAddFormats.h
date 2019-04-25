#ifndef VIEWADDFORMATS_H
#define VIEWADDFORMATS_H
#include "Views/viewInterface.h"
#include <QTreeView>
#include "ui_viewaddformatsUI.h"
#include <QSqlTableModel>
#include <QDataWidgetMapper>
class ViewAddFormats : public ViewInterface, public Ui_Form
{
    Q_OBJECT
public:
    explicit ViewAddFormats();
private:
    QSqlTableModel *m_tbl_model_materials;
    QSqlTableModel *m_tbl_model_furnitures;
    QDataWidgetMapper *m_mapper;
    QGraphicsScene *m_image_scene;
private slots:
    void on_idx_materials_changed(QModelIndex idx);
};

#endif // VIEWADDFORMATS_H
