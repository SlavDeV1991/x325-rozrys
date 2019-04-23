#ifndef VIEWFURNITURES_H
#define VIEWFURNITURES_H

#include "Views/viewInterface.h"
#include "ui_viewFurnitures.h"


class ViewFurnitures : public ViewInterface, public Ui_ViewFurnitures
{
    Q_OBJECT

public:
    explicit ViewFurnitures(QWidget *parent = 0);
    ~ViewFurnitures();

private:
    Ui::ViewFurnitures *ui;
};

#endif // VIEWFURNITURES_H
