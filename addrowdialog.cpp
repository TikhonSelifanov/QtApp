#include "addrowdialog.h"

#include <QMessageBox>
#include <QSpinBox>

#include "examplemodel.h"
#include "ui_addrowdialog.h"
addRowDialog::addRowDialog(QWidget* parent)
    : QDialog(parent), ui(new Ui::addRowDialog)
{
    ui->setupUi(this);

    QObject::connect(ui->okButton, SIGNAL(clicked()), this, SLOT(saveRow()));
    QObject::connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

void addRowDialog::saveRow()
{
    newRow.push_back(ui->cityLine->text());
    newRow.push_back(ui->peopleBox->text());
    newRow.push_back(ui->planetBox->text());
    newRow.push_back(ui->profitBox->text());
    newRow.push_back(ui->overallBox->text());
    newRow.push_back(ui->countryBox->text());
    newRow.push_back(ui->contBox->text());
    accept();
}

const QList<QVariant>& addRowDialog::getNewRow() { return newRow; }

addRowDialog::~addRowDialog() { delete ui; }
