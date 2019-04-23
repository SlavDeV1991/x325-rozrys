#ifndef VIEWINTERFACE_H
#define VIEWINTERFACE_H

#include <QWidget>

class ViewInterface : public QWidget
{
    Q_OBJECT
public:
    explicit ViewInterface(QWidget *parent = 0);

signals:

public slots:
};

#endif // VIEWINTERFACE_H