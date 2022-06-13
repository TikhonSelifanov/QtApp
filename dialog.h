#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPaintEvent>

namespace Ui
{
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
   protected:
    void paintEvent(QPaintEvent *event);

   public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

   private:
    QPaintEvent *event;
    Ui::Dialog *ui;
};

#endif  // DIALOG_H
