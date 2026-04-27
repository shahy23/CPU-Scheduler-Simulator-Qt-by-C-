#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fcfsdialog.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setStyleSheet("QMainWindow { background-color: #121212; }");
    QString btnStyle = "QPushButton { background-color: #cc0000; color: white; font-weight: bold; padding: 10px; border-radius: 5px; }";
    ui->fcfsButton->setStyleSheet(btnStyle);
    ui->sjfButton->setStyleSheet(btnStyle);
    ui->priorityButton->setStyleSheet(btnStyle);
    ui->rrButton->setStyleSheet(btnStyle);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_fcfsButton_clicked() { FCFSDialog d; d.setMode(0); d.exec(); }
void MainWindow::on_sjfButton_clicked() { FCFSDialog d; d.setMode(1); d.exec(); }
void MainWindow::on_priorityButton_clicked() { FCFSDialog d; d.setMode(2); d.exec(); }
void MainWindow::on_rrButton_clicked() { FCFSDialog d; d.setMode(3); d.exec(); }
