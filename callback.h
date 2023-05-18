#ifndef CALLBACK_H
#define CALLBACK_H

#include <QProgressBar>
class Callback{

public:
    virtual void updatePercentage(int percentage, QString finishedBytes, QProgressBar* progressBar) = 0;
};

#endif // CALLBACK_H
