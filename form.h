#ifndef FORM_H
#define FORM_H

#include <QSortFilterProxyModel>
#include <QTransposeProxyModel>
#include <QWidget>

#include "custommodel.h"
#include "examplemodel.h"

namespace Ui
{
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

   public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

   private slots:
    void loadFile();
    void saveFile();
    void addRow();
    void deleteRow();

    void on_lineEdit_textChanged(const QString &arg1);

   private:
    Ui::Form *ui;
    size_t _shownDetailsColumn;
    exampleModel *_exampleModel;
    QTransposeProxyModel *_transposeModel;
    QSortFilterProxyModel *proxyModel;
    QSortFilterProxyModel *proxyModel2;
    QSortFilterProxyModel *proxyModel3;
    CustomProxyModel *proxyModelOverall;
};

#endif  // FORM_H
