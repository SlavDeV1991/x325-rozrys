#ifndef VIEWMATERIALS_H
#define VIEWMATERIALS_H

#include <QWidget>
#include <Views/viewInterface.h>
#include <ui_viewMaterials.h>
#include <QSqlTableModel>
#include <QDataWidgetMapper>
#include <QGraphicsScene>
#include <QSortFilterProxyModel>
#include <QUndoCommand>
class UndoableSqlTableModel : public QSqlTableModel
{
   //TODO:: zapis bazy danych przed wyłączeniem programu
    Q_OBJECT
    class CommandSetData : public QUndoCommand
    {

    public:
        explicit CommandSetData(QModelIndex &index, QVariant &new_value, int role, UndoableSqlTableModel *model);
        virtual void redo() override;
        virtual void undo() override;
    private:
        QModelIndex m_idx;
        QVariant m_new_value;
        QVariant m_old_value;
        int m_role;
        UndoableSqlTableModel* m_model;
    };

public:
    explicit UndoableSqlTableModel(QObject *parent = Q_NULLPTR, QSqlDatabase db = QSqlDatabase());
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    bool setDataProperly(const QModelIndex &index, const QVariant &value, int role);
};

namespace Ui {
class ViewMaterials;
}

class ViewMaterials : public ViewInterface, public Ui_ViewMaterials
{
    Q_OBJECT

public:
    explicit ViewMaterials(QWidget *parent = 0);
    ~ViewMaterials();

private:
    QSqlTableModel *m_tbl_model;
    QDataWidgetMapper *m_mapper;
    QGraphicsScene *m_image_scene;
private slots:
    void on_current_idx_changed(QModelIndex);
    void addMaterial(void);
    void removeMaterial(void);
    void setPath(void);
};

#endif // VIEWMATERIALS_H
