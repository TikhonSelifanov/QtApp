#include "dialog.h"

#include <QPainter>

#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog() { delete ui; }

void Dialog::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen;
    pen.setWidth(20);
    pen.setColor(Qt::yellow);
    painter.setPen(pen);
    painter.setBrush(Qt::green);
    painter.drawEllipse(1, 0, 125, 125);
    QWidget::paintEvent(event);
}
