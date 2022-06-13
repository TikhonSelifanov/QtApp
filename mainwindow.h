#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "form.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

   public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

   private slots:
    void on_aboutButton_clicked();

    void on_startButton_clicked();

    void on_actionDark_mode_triggered();

    void on_actionLight_mode_triggered();

   private:
    Ui::MainWindow *ui;
    Form table;
};
#endif  // MAINWINDOW_H
