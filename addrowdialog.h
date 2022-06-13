#ifndef ADDROWDIALOG_H
#define ADDROWDIALOG_H

#include <QDialog>

namespace Ui
{
class addRowDialog;
}

class addRowDialog : public QDialog
{
    Q_OBJECT

   public:
    explicit addRowDialog(QWidget *parent = nullptr);
    ~addRowDialog();
    const QList<QVariant> &getNewRow();

   private slots:
    void saveRow();

   private:
    QList<QVariant> newRow;
    Ui::addRowDialog *ui;
};

#endif  // ADDROWDIALOG_H
