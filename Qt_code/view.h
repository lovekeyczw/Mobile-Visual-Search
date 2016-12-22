#ifndef VIEW_H
#define VIEW_H

#include <QtWidgets>

class View : public QListWidget
{
    Q_OBJECT
public:
    explicit View(QWidget *parent = 0);
    void addPic(QString file);
signals:
    
public slots:
private:

};

#endif // VIEW_H
