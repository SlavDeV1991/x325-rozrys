#include "viewAddFormats.h"
#include "dbManager.h"
#include <commonLogger.h>


ViewAddFormats::ViewAddFormats():
    ViewInterface(), Ui_Form()
{
    this->setupUi(this);
    m_tbl_model_materials = new QSqlTableModel(this, *DBManager::Connection());
    m_tbl_model_materials->setTable("materials");
    m_tbl_model_materials->setEditStrategy(QSqlTableModel::OnManualSubmit);
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

    m_mapper = new QDataWidgetMapper;
    m_mapper->setModel(m_tbl_model_materials);
    m_mapper->addMapping(le_prise, 2);
    m_mapper->addMapping(le_width, 3);
    m_mapper->addMapping(le_height, 4);
    m_mapper->addMapping(le_thickness, 5);
    m_image_scene = new QGraphicsScene(this);
    gv_image->setScene(m_image_scene);
    connect(lv_materials->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), m_mapper, SLOT(setCurrentModelIndex(QModelIndex)));
    connect(lv_materials->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(on_idx_materials_changed(QModelIndex)));
    //TODO::refactoring kodu
}

void ViewAddFormats::on_idx_materials_changed(QModelIndex idx)
{
    m_image_scene->clear();
    CommonLogger::Logger()->Info("ViewAddFormatsLL on idx materials changed");
    int row = idx.row();
    int column = 1;
    CommonLogger::Logger()->Info(QString::number(idx.column()));
    QPixmap pixmap(idx.model()->index(row, column).data().toString());
    m_image_scene->addPixmap(pixmap);
}
