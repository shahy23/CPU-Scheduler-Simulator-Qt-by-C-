#include "fcfsdialog.h"
#include "ui_fcfsdialog.h"
#include <algorithm>

FCFSDialog::FCFSDialog(QWidget *parent) : QDialog(parent), ui(new Ui::FCFSDialog) {
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &FCFSDialog::updateSimulation);

    this->setStyleSheet("background-color: #121212; color: white;");
    ui->tableWidget->setStyleSheet(
        "QTableWidget { background-color: #121212; color: white; gridline-color: red; border: 1px solid red; }"
        "QHeaderView::section { background-color: #333; color: white; border: 1px solid red; }"
        "QTableWidget::item { color: white; }"
        );

    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setHorizontalHeaderLabels({"Arr", "Burst", "Rem", "Wait", "Turn"});
}

FCFSDialog::~FCFSDialog() { delete ui; }

void FCFSDialog::setMode(int mode) {
    schedulingMode = mode;
    bool isPriority = (mode == 2);
    bool isRR = (mode == 3);

    ui->prioLabel->setVisible(isPriority);
    ui->priorityLineEdit->setVisible(isPriority);
    ui->qLabel->setVisible(isRR);
    ui->quantumLineEdit->setVisible(isRR);
}

void FCFSDialog::on_addProcessButton_clicked() {
    int b = ui->burstLineEdit_2->text().toInt();
    int a = ui->arrivalLineEdit->text().toInt();
    int p = ui->priorityLineEdit->isVisible() ? ui->priorityLineEdit->text().toInt() : 0;

    if (b <= 0) return;

    processes.push_back({a, b, processCounter++, p, b});
    int r = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(r);
    ui->tableWidget->setItem(r, 0, new QTableWidgetItem(QString::number(a)));
    ui->tableWidget->setItem(r, 1, new QTableWidgetItem(QString::number(b)));
    ui->tableWidget->setItem(r, 2, new QTableWidgetItem(QString::number(b)));
}

void FCFSDialog::on_startButton_clicked() {
    if (processes.empty()) return;
    currentTime = 0; currentProcess = 0; gantt = "|";

    if (schedulingMode == 1) { // SJF
        std::sort(processes.begin(), processes.end(), [](const auto& a, const auto& b){
            return std::get<1>(a) < std::get<1>(b);
        });
    } else if (schedulingMode == 2) { // Priority
        std::sort(processes.begin(), processes.end(), [](const auto& a, const auto& b){
            return std::get<3>(a) < std::get<3>(b);
        });
    } else { std::sort(processes.begin(), processes.end()); }

    timer->start(1000);
}

void FCFSDialog::updateSimulation() {
    if (currentProcess >= (int)processes.size()) {
        timer->stop();
        ui->finish->setText("🔴 TASK COMPLETED");
        on_calculateButton_clicked();
        return;
    }

    int &rem = std::get<4>(processes[currentProcess]);
    int pID = std::get<2>(processes[currentProcess]);

    ui->timeLabel->setText("⏱ Time: " + QString::number(currentTime) + "s");

    if (rem > 0) {
        rem--;
        ui->tableWidget->item(currentProcess, 2)->setText(QString::number(rem));

        gantt += " P" + QString::number(pID) + " | " + QString::number(currentTime + 1);
        ui->ganttLabel->setText(gantt);
    }

    if (rem == 0) currentProcess++;

    currentTime++;
}

void FCFSDialog::on_calculateButton_clicked() {}
void FCFSDialog::on_backButton_clicked() { this->close(); }