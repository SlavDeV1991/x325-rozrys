#include "viewMaterials.h"
#include "ui_viewMaterials.h"
#include "dbManager.h"
#include <commonLogger.h>
#include <QFileDialog>
#include <QDir>
#include <undoStack.h>
#define NOT_FOUND -1



ViewMaterials::ViewMaterials(QWidget *parent) :
    ViewInterface(parent)
{
    setupUi(this);
    m_tbl_model = new QSqlTableModel(this, *DBManager::Connection());
    m_tbl_model->setTable("materials");
    m_tbl_model->setEditStrategy(QSqlTableModel::OnRowChange);
    m_tbl_model->select();
    m_tbl_model->setHeaderData(0, Qt::Horizontal, tr("Nazwa"));
    m_tbl_model->setHeaderData(1, Qt::Horizontal, tr("Ścieżka"));
    lv_materials->setModel(m_tbl_model);

    m_mapper = new QDataWidgetMapper;
    m_mapper->setModel(m_tbl_model);
    m_mapper->addMapping(le_dir, 1);
    m_mapper->addMapping(le_prise, 2);
    m_mapper->addMapping(le_width, 3);
    m_mapper->addMapping(le_height, 4);
    m_mapper->addMapping(le_thickness, 5);

    connect(lv_materials->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), m_mapper, SLOT(setCurrentModelIndex(QModelIndex)));
    connect(lv_materials->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(on_current_idx_changed(QModelIndex)));
    connect(pb_addMaterial, SIGNAL(pressed()), this, SLOT(addMaterial()));
    connect(pb_removeMaterial, SIGNAL(pressed()), this, SLOT(removeMaterial()));
    connect(pb_path, SIGNAL(pressed()), this, SLOT(setPath()));
    m_image_scene = new QGraphicsScene(this);
    gv_image->setScene(m_image_scene);
}

ViewMaterials::~ViewMaterials()
{

}

void ViewMaterials::on_current_idx_changed(QModelIndex idx)
{
    Q_UNUSED(idx)
    m_image_scene->clear();
    QPixmap pixmap(le_dir->text());
    m_image_scene->addPixmap(pixmap);
}

void ViewMaterials::addMaterial()
{
    m_tbl_model->insertRow(0);
    m_tbl_model->setData(m_tbl_model->index(0,0),tr("materiał"));
    //m_tbl_model->submitAll();
}

void ViewMaterials::removeMaterial()
{
    m_tbl_model->removeRow(lv_materials->currentIndex().row());
    //m_tbl_model->submitAll();
}

void ViewMaterials::setPath()
{
    QModelIndex _cur = lv_materials->currentIndex();
    if(_cur.row() == NOT_FOUND)
        return;
    QDir _dir(QDir::currentPath());
    QString _path = QFileDialog::getOpenFileName();

    QString _rel_path = _dir.relativeFilePath(_path);
    CommonLogger::Logger()->Info(_rel_path);
    m_tbl_model->setData(m_tbl_model->index(_cur.row(), 1), _rel_path);
    on_current_idx_changed(_cur);
    //m_tbl_model->submitAll();
}

UndoableSqlTableModel::UndoableSqlTableModel(QObject *parent, QSqlDatabase db):
    QSqlTableModel(parent, db)
{

}

bool UndoableSqlTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    //UndoStack::Stack().push(new UndoableSqlTableModel::CommandSetData(index,value,role, this));
    return true;
}

bool UndoableSqlTableModel::setDataProperly(const QModelIndex &index, const QVariant &value, int role)
{
    return QSqlTableModel::setData(index,value,role);
}

UndoableSqlTableModel::CommandSetData::CommandSetData(QModelIndex &index, QVariant &new_value, int role, UndoableSqlTableModel *model):
    QUndoCommand(),
    m_idx(index),
    m_new_value(new_value),
    m_role(role)
{
    m_old_value = index.data();
    m_model = model;
}

void UndoableSqlTableModel::CommandSetData::redo()
{
    m_model->setDataProperly(m_idx, m_new_value, m_role);
}

void UndoableSqlTableModel::CommandSetData::undo()
{
    m_model->setDataProperly(m_idx, m_old_value, m_role);
}
