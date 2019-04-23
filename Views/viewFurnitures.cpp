#include "viewFurnitures.h"


ViewFurnitures::ViewFurnitures(QWidget *parent) :
    ViewInterface(),
    Ui_ViewFurnitures(parent)
{
    ui->setupUi(this);
}

ViewFurnitures::~ViewFurnitures()
{
    delete ui;
}
