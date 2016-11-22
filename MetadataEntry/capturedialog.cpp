#include "capturedialog.h"
#include "ui_capturedialog.h"

#include <fstream>
#include <QDir>
#include <QMessageBox>

QString CaptureDialog::invertedStateString[] = {
    "Stop",
    "Start"
};

CaptureDialog::State CaptureDialog::invertedState[] = {
    CaptureDialog::State::STOPPED,
    CaptureDialog::State::STARTED
};

CaptureDialog::CaptureDialog(QWidget *parent) :
    QDialog(parent),
    controller(),
    listener(std::cout),
    state(STOPPED),
    stream(NULL),
    visualizerPID(-1),
    displayedWarning(false),
    ui(new Ui::CaptureDialog)
{
    ui->setupUi(this);

    QObject::connect(ui->startStopButton, SIGNAL(clicked()),
                     this, SLOT(toggleStartStop()));
}

CaptureDialog::~CaptureDialog()
{
    delete ui;
}

void CaptureDialog::show()
{
    state = STOPPED;
    QDialog::show();
}

void CaptureDialog::setId(const QString &id)
{
    this->id = id;
}

void CaptureDialog::start()
{
    QDir dir(".");
    if (dir.mkpath("gestures/" + id) && dir.cd("gestures/"  + id))
    {
        if (stream != NULL)
        {
            delete stream;
        }
        stream = new std::ofstream((dir.path() + "/" + ui->nextTryNameLineEdit->text() + ".xml").toUtf8()); // TODO set actual try number
        listener.setStream(stream);
        listener.startRecording();
        visualizerPID = system("Visualizer &");
        if (!displayedWarning && visualizerPID <= 0)
        {
            QMessageBox::warning(this,
                    "Could not open visualizer",
                    "Could not open visualizer. Further warnings won't be displayed.");
            displayedWarning = true;
        }
        controller.addListener(listener);
    }
}

void CaptureDialog::stop()
{
    controller.removeListener(listener);
    if (visualizerPID > 0)
    {
        char cmd[32];
        sprintf(cmd, "kill %d", visualizerPID);
        if (system(cmd) != 0)
        {
            QMessageBox::warning(this,
                    "Could not close visualizer",
                    "Could not close visualizer");
        }
        visualizerPID = 0;
    }
}

void CaptureDialog::toggleStartStop()
{
    switch (state)
    {
    case STARTED:
        stop();
        break;
    case STOPPED:
        start();
        break;
    default:
        return; // Should not happen
    }
    state = invertedState[state];
    ui->startStopButton->setText(invertedStateString[state]);
}
