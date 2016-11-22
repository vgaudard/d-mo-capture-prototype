#ifndef CAPTUREDIALOG_H
#define CAPTUREDIALOG_H

#include <QObject>
#include <QDialog>

#include <iostream>
#include "Leap.h"

#include "PrototypeListener.h"

namespace Ui {
class CaptureDialog;
}

class CaptureDialog : public QDialog
{
    Q_OBJECT

private:
    enum State
    {
        STARTED = 0,
        STOPPED = 1
    };

public:
    explicit CaptureDialog(QWidget *parent = 0);
    ~CaptureDialog();
    void show();
    void setId(const QString& id);

private slots:
    void toggleStartStop();

private:
    void start();
    void stop();

    Leap::Controller controller;
    DMO_Prototype::PrototypeListener listener;
    State state;
    QString id;
    std::ofstream* stream;
    int visualizerPID;
    bool displayedWarning;

    Ui::CaptureDialog *ui;



    static State invertedState[];
    static QString invertedStateString[];
};

#endif // CAPTUREDIALOG_H
