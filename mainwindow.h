#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QPushButton>
#include <QProgressBar>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    // 標題
    QLabel* lTitle;

    // 選擇來源檔案
    QLabel* lChooseFile;
    QLabel* lSrcPath;
    QPushButton* bChooseFile;

    // 選擇目的路徑
    QLabel* lDesPath;
    QLineEdit* eDesPath;
    QPushButton* bCopy;

    // Progress Bar
    QProgressBar* copyProgress;

    // button event
private slots:
    void selectFile();
    void copyFile();
};
#endif // MAINWINDOW_H
