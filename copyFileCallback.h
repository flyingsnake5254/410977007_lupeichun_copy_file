#ifndef COPYFILECALLBACK_H
#define COPYFILECALLBACK_H
#include "callback.h"
#include <iostream>
class CopyFileCallback : public Callback{

public:
    void updatePercentage(int percentage, QString finishedBytes, QProgressBar* progressBar) override{
        progressBar->setValue(percentage);
        std::cout<<"percentage : "<<percentage<<"% , finished bytes : "<<finishedBytes.toStdString()<<std::endl;
    }
};

#endif // COPYFILECALLBACK_H
