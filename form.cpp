#include "form.h"

#include <QFile>
#include <QFileDialog>
#include <QItemSelectionModel>
#include <QSortFilterProxyModel>
#include <QTextStream>
#include <QTranslator>

#include "addrowdialog.h"
#include "custommodel.h"
#include "ui_form.h"

Form::Form(QWidget* parent) : QWidget(parent), ui(new Ui::Form)
{
    ui->setupUi(this);
    //    QTranslator translator;
    //    translator.load("");
    //    ui->loadDataButton->tr("Загрузить");
    connect(ui->loadDataButton, SIGNAL(clicked()), this, SLOT(loadFile()));
    connect(ui->saveDataButton, SIGNAL(clicked()), this, SLOT(saveFile()));
    connect(ui->addRowButton, SIGNAL(clicked()), this, SLOT(addRow()));
    connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(deleteRow()));

    _exampleModel = new exampleModel(this);
    ui->model->setModel(_exampleModel);

    _transposeModel = new QTransposeProxyModel(this);
    _transposeModel->setSourceModel(_exampleModel);
    ui->details->setModel(_transposeModel);

    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(_exampleModel);

    proxyModel2 = new QSortFilterProxyModel(this);

    proxyModel3 = new QSortFilterProxyModel(this);
    proxyModel3->setSourceModel(proxyModel);

    ui->model->setModel(proxyModelOverall);
    ui->model->setSortingEnabled(true);

    proxyModelOverall = new CustomProxyModel(this);
    proxyModelOverall->setSourceModel(proxyModel3);
    proxyModel->setFilterKeyColumn(4);
    proxyModel3->setFilterKeyColumn(6);

    for (int i = 1; i < _transposeModel->columnCount(); ++i)
    {
        ui->details->hideColumn(i);
    }
    _shownDetailsColumn = 0;
}

void Form::loadFile()
{
    delete _exampleModel;

    _exampleModel = new exampleModel(this);
    QString fileName =
        QFileDialog::getOpenFileName(this, "Open File", "../", "Data (*.csv)");
    _exampleModel->fillDataTableFromFile(fileName);
    proxyModel->setSourceModel(_exampleModel);
    proxyModel2->setSourceModel(_exampleModel);
    ui->model->setModel(proxyModel);
    _transposeModel->setSourceModel(_exampleModel);
    for (int i = 1; i < _transposeModel->columnCount(); ++i)
    {
        ui->details->hideColumn(i);
    }
    _shownDetailsColumn = 0;
}

void Form::saveFile()
{
    QString fileName =
        QFileDialog::getSaveFileName(this, "Open File", "../", "Data (*.csv)");
    _exampleModel->saveDataToFile(fileName);
}
Form::~Form() { delete ui; }

void Form::addRow()
{
    addRowDialog d(this);
    if (d.exec() == QDialog::Accepted)
    {
        _exampleModel->appendRow(d.getNewRow());
        ui->details->hideColumn(_transposeModel->columnCount());
    }
}

void Form::deleteRow()
{
    QModelIndex idx1 = ui->model->currentIndex();
    QModelIndex idx4 = proxyModel->mapToSource(idx1);
    _exampleModel->removeRow(idx4.row());
}

void Form::on_lineEdit_textChanged(const QString& arg1)
{
    proxyModel2->setFilterRegularExpression(QRegularExpression(arg1));
    _transposeModel->setSourceModel(proxyModel2);
}
