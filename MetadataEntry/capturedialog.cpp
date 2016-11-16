#include "capturedialog.h"
#include "ui_capturedialog.h"

#include <fstream>
#include <QDir>

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
        // Yeah memory leaks
        // Please close your eyes when reading the next line, at least until the next commit (I hope)
        // TODO Fix memory leak below
        // Uhhh, if you closed your eyes, I meant the line below this one, and not the TODO
        // Go read the TODO, then read the next line
        // Uhhh, you closed your eyes again, didn't you ?
        // I'll let you guess which one you should not have read
        std::ofstream* ofstream = new std::ofstream((dir.path() + "/" + ui->nextTryNameLineEdit->text() + ".xml").toUtf8()); // TODO set actual try number
        listener.setStream(ofstream);
        listener.startRecording();
        system("Visualizer &");
        controller.addListener(listener);

        // About the "close your eyes until the next commit" thing, please open them when you go outside
        // I'm not responsible for any injury caused by walking/driving/flying into a wall.
    }
}

void CaptureDialog::stop()
{
    controller.removeListener(listener);
    system("pkill Visualizer"); // Brutish way
    // TODO Kill only those who deserve it
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
