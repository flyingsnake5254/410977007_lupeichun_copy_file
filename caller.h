#ifndef CALLER_H
#define CALLER_H
#include "callback.h"
#include <QString>
class Caller{

public:
    void callerRegister(int percentage, QString finishedBytes, QProgressBar* progressBar){
        callback->updatePercentage(percentage, finishedBytes, progressBar);
    }

    void setCallback(Callback* cb){
        this->callback = cb;
    }

    Callback* getCallback(){
        return this->callback;
    }


private:
    Callback* callback;
};

#endif // CALLER_H
