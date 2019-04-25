#include "viewFurnitures.h"
#include "ui_viewFurnitures.h"

ViewFurnitures::ViewFurnitures(QWidget *parent) :
    ViewInterface(parent)
{
    ui->setupUi(this);
}

ViewFurnitures::~ViewFurnitures()
{
    delete ui;
}
