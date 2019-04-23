#include "viewAddFormats.h"
#include "dbManager.h"


ViewAddFormats::ViewAddFormats():
    ViewInterface(), Ui_Form()
{
    this->setupUi(this);
    m_tbl_model_materials = new QSqlTableModel(this, *DBManager::Connection());
    m_tbl_model_materials->setTable("materials");
    m_tbl_model_materials->setEditStrategy(QSqlTableModel::OnRowChange);
    m_tbl_model_materials->select();
    m_tbl_model_materials->setHeaderData(0, Qt::Horizontal, tr("Nazwa"));
    m_tbl_model_materials->setHeaderData(1, Qt::Horizontal, tr("Ścieżka"));
    lv_materials->setModel(m_tbl_model_materials);
    m_tbl_model_furnitures = new QSqlTableModel(this, *DBManager::Connection());
    m_tbl_model_furnitures->setTable("furnitures");
    m_tbl_model_furnitures->setEditStrategy(QSqlTableModel::OnRowChange);
    m_tbl_model_furnitures->select();
    m_tbl_model_furnitures->setHeaderData(0, Qt::Horizontal, tr("Nazwa"));
    m_tbl_model_furnitures->setHeaderData(1, Qt::Horizontal, tr("Ścieżka"));
    lv_furnitures->setModel(m_tbl_model_furnitures);
}
