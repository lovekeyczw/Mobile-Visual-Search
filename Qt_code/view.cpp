#include "view.h"

View::View(QWidget *parent) :
    QListWidget(parent)
{

    setSpacing(12);
    setViewMode(QListView::IconMode);
    setFlow(QListView::TopToBottom);
}

void View::addPic(QString file)
{
    QLabel *newLabel = new QLabel(this);
    newLabel->setPixmap(QPixmap(file).scaled(200,200));
    QListWidgetItem *newItem = new QListWidgetItem(this);
    newItem->setSizeHint(QSize(200,200));
    this->setItemWidget(newItem, newLabel);
}
