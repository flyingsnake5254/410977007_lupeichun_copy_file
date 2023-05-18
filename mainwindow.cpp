#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFont>
#include <QFileDialog>
#include "caller.h"
#include "callback.h"
#include "copyFileCallback.h"
#include <fstream>
#include <QMessageBox>
#include <filesystem>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 添加最大化、最小化按鈕
    setWindowFlags(windowFlags() | Qt::WindowMaximizeButtonHint | Qt::WindowMinimizeButtonHint);
    setWindowTitle("複製檔案");
    resize(1000, 600);



    // 標題 label
    QHBoxLayout* layoutTitle = new QHBoxLayout(this);
    lTitle = new QLabel(this);
    lTitle->setText("複製檔案");
    QFont titleFont = lTitle->font();
    titleFont.setPointSize(30);
    lTitle->setFont(titleFont);
    lTitle->setAlignment(Qt::AlignCenter);
    lTitle->setFixedSize(500,100);
    layoutTitle->addWidget(lTitle);


    // 選擇複製檔案
    QHBoxLayout* layoutChooseFile = new QHBoxLayout(this);
    layoutChooseFile->setSpacing(20);
    lChooseFile = new QLabel(this);
    lChooseFile->setText("選擇來源檔案");
    QFont chooseFileFont = lChooseFile->font();
    chooseFileFont.setPointSize(20);
    lChooseFile->setFont(chooseFileFont);

    lSrcPath = new QLabel(this);
    QFont srcPathFont = lSrcPath->font();
    srcPathFont.setPointSize(20);
    lSrcPath->setFont(srcPathFont);

    bChooseFile = new QPushButton(this);
    bChooseFile->setIcon(QIcon("/home/sherloxk/Documents/Cpp_project/QT/test8/file_icon.png"));
    bChooseFile->setIconSize(QSize(50,50));
    bChooseFile->setFixedSize(70,70);
    connect(bChooseFile, SIGNAL(clicked(bool)), this, SLOT(selectFile()));

    layoutChooseFile->addWidget(lChooseFile);
    layoutChooseFile->addWidget(lSrcPath);
    layoutChooseFile->addWidget(bChooseFile);


    // 設定檔案路徑
    QHBoxLayout* layoutDesPath = new QHBoxLayout(this);
    layoutDesPath->setSpacing(20);

    lDesPath = new QLabel(this);
    lDesPath->setText("設定目的路徑");
    QFont desPathFont = lDesPath->font();
    desPathFont.setPointSize(20);
    lDesPath->setFont(desPathFont);

    eDesPath = new QLineEdit(this);
    QFont eDesPathFont = eDesPath->font();
    eDesPathFont.setPixelSize(20);
    eDesPath->setFont(eDesPathFont);

    bCopy = new QPushButton(this);
    bCopy->setText("複製");
    QFont bCopyFont = bCopy->font();
    bCopyFont.setPixelSize(20);
    bCopy->setFont(bCopyFont);
    connect(bCopy, SIGNAL(clicked(bool)), this, SLOT(copyFile()));

    layoutDesPath->addWidget(lDesPath);
    layoutDesPath->addWidget(eDesPath);
    layoutDesPath->addWidget(bCopy);

    // Progress Bar
    copyProgress = new QProgressBar(this);
    copyProgress->setMaximum(100);
    copyProgress->setMinimum(0);
    copyProgress->setVisible(false);
    copyProgress->setValue(0);
    copyProgress->setStyleSheet("QProgressBar { border: 2px solid grey; border-radius: 5px; text-align: center; color:#778899;} "
                                "QProgressBar::chunk { background-color: #77FFCC; width: 20px;}");

    // 添加 widget 到 layout
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->addLayout(layoutTitle);
    mainLayout->addLayout(layoutChooseFile);
    mainLayout->addLayout(layoutDesPath);
    mainLayout->addWidget(copyProgress);

    QWidget* mainWidget = new QWidget(this);
    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);


}

MainWindow::~MainWindow()
{
}

void MainWindow::selectFile(){
    QString srcPath = QFileDialog::getOpenFileName(this, "選擇來源檔案");
    lSrcPath->setText(srcPath);
}

void MainWindow::copyFile(){
    QString src = lSrcPath->text();
    QString des = eDesPath->text();
    std::cout<<"src : "<<src.toStdString()<<" , des : "<<des.toStdString()<<std::endl;
    std::ifstream srcFile(src.toStdString(), std::ios::binary);
    std::ofstream desFile(des.toStdString(), std::ios::binary);

    if(!srcFile){
        QMessageBox msgBox;
        msgBox.setWindowTitle("錯誤");
        msgBox.setText("來源端出現錯誤");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
    }
    else if(!desFile){
        QMessageBox msgBox;
        msgBox.setWindowTitle("錯誤");
        msgBox.setText("目的端出現錯誤");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();

    }
    else{
        Caller* caller = new Caller();
        CopyFileCallback cpCallback;
        Callback* copyFileCallback = &cpCallback;
        caller->setCallback(copyFileCallback);

        long totalBytes = std::filesystem::file_size(src.toStdString());
        long finishedBytes = 0;
        int lastPercentage = 0;
        int currentPercentage = 0;

        copyProgress->setVisible(true);
        QString qFinishedBytes;
        std::cout<<"file size : "<<totalBytes<<" bytes"<<std::endl;

        int buffSize = 1024;
        std::vector<char> buff(buffSize);
        while(srcFile.read(&buff[0], buffSize)){
            desFile.write(&buff[0], buffSize);
            finishedBytes += buffSize;
            currentPercentage = finishedBytes * 100 / totalBytes;
            if (currentPercentage != lastPercentage){
                lastPercentage = currentPercentage;
                qFinishedBytes.setNum(finishedBytes);
                caller->getCallback()->updatePercentage(currentPercentage, qFinishedBytes, copyProgress);
            }
        }
        std::streamsize lastBuff = srcFile.gcount();
        if(lastBuff > 0){

            desFile.write(&buff[0], lastBuff);
            finishedBytes += buffSize;
            currentPercentage = finishedBytes * 100 / totalBytes;
            if (currentPercentage != lastPercentage){
                lastPercentage = currentPercentage;
                qFinishedBytes.setNum(finishedBytes);
                caller->getCallback()->updatePercentage(currentPercentage, qFinishedBytes, copyProgress);
            }
        }

        srcFile.close();
        desFile.close();


        QMessageBox msgBox;
        msgBox.setWindowTitle("訊息");
        msgBox.setText("複製完成");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();

    }



}





