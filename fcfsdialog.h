#ifndef FCFSDIALOG_H
#define FCFSDIALOG_H

#include <QDialog>
#include <vector>
#include <tuple>
#include <QTimer>

namespace Ui { class FCFSDialog; }

class FCFSDialog : public QDialog {
    Q_OBJECT
public:
    explicit FCFSDialog(QWidget *parent = nullptr);
    ~FCFSDialog();
    void setMode(int mode); // 0:FCFS, 1:SJF, 2:Priority, 3:RR

private slots:
    void on_addProcessButton_clicked();
    void on_startButton_clicked();
    void updateSimulation();
    void on_calculateButton_clicked();
    void on_backButton_clicked();

private:
    Ui::FCFSDialog *ui;
    std::vector<std::tuple<int, int, int, int, int>> processes;
    int processCounter = 1;
    QTimer *timer;
    int currentTime = 0;
    int currentProcess = 0;
    int schedulingMode = 0;
    QString gantt;
};
#endif