#ifndef MENUBUTTON_H
#define MENUBUTTON_H
#include <QToolButton>

class MenuButton : public QToolButton
{
    enum Actions{Rozrys1, Rozrys2, Rozrys3, Rozrys4, Wyjscie};
    Q_OBJECT
public:
    static MenuButton *createButton(const int index, QWidget *parent = nullptr );
    static const int btnsCount=5;
    virtual QSize sizeHint() const override;
signals:
    void clicked(const QString &);
private:
    MenuButton(QString text, QWidget *parent = nullptr );
    static QList<QString> m_txts;
    void collapse();
    void expand();
    QString m_txt;
private slots:
    void onToggled(bool checked);
protected:
    virtual bool event(QEvent *e) override;

};

#endif // MENUBUTTON_H
