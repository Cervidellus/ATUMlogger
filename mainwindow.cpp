#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "databasemanager.h"

#include <QDebug>
#include <QSqlRecord>
#include <QTableView>
#include <QIntValidator>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    timer(new QTimer),
    database(new DatabaseManager)
{
    ui->setupUi(this);
    database->init();
    setInfoText();

    timerMinsLeft = 2;
    timerSecsLeft = 0;
    QTime initTime = QTime(0, timerMinsLeft, timerSecsLeft);
    QString text = initTime.toString("mm:ss");
    ui->lcdNumber->display(text);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateCountdown);

    //edit button and field properties
    QIntValidator *intValidator = new QIntValidator();
    QDoubleValidator *doubleValidator = new QDoubleValidator();
//    ui->cuttingTopLineEdit->setInputMask("00000");
    ui->cuttingTopLineEdit->setValidator(intValidator);
    ui->cuttingWindowBottomLineEdit->setValidator(intValidator);
    ui->cuttingThicknessLineEdit->setValidator(intValidator);
    ui->cuttingSpeedLineEdit->setValidator(doubleValidator);
    ui->phaseSyncLineEdit->setValidator(doubleValidator);
    ui->knifeIonizerSettingLineEdit->setValidator(doubleValidator);



    //Connect settings info fields to update defaults in database.
    //TODO: there is no checking for correct type of text entry.
    connect(ui->sessionLineEdit, &QLineEdit::returnPressed, database, [this](){
        database->setSectioningSessionID(ui->sessionLineEdit->text());
        database->insertNote("Sectioning Session ID changed to " + ui->sessionLineEdit->text());});
    connect(ui->specimenLineEdit, &QLineEdit::returnPressed, database, [this](){
        database->setSpecimenID(ui->specimenLineEdit->text());
        database->insertNote("Specimen ID changed to " + ui->specimenLineEdit->text());});
    connect(ui->tapeLineEdit, &QLineEdit::returnPressed, database, [this](){
        database->setTapeID(ui->tapeLineEdit->text());
        database->insertNote("Tape ID changed to " + ui->tapeLineEdit->text());});
    connect(ui->knifeLineEdit, &QLineEdit::returnPressed, database, [this](){
        database->setKnifeID(ui->knifeLineEdit->text());
        database->insertNote("Knife ID changed to " + ui->knifeLineEdit->text());});
    connect(ui->cuttingTopLineEdit, &QLineEdit::returnPressed, database, [this](){
//        int value = ui->cuttingTopLineEdit->text().toInt();
        database->setCuttingWindowTop(ui->cuttingTopLineEdit->text().toInt());
        database->insertNote("Cutting Window Top changed to " + ui->cuttingTopLineEdit->text());});
    connect(ui->cuttingWindowBottomLineEdit, &QLineEdit::returnPressed, database, [this](){
        database->setCuttingWindowBottom(ui->cuttingWindowBottomLineEdit->text().toInt());
        database->insertNote("Cutting Window Bottom changed to " + ui->cuttingWindowBottomLineEdit->text());});
    connect(ui->cuttingSpeedLineEdit, &QLineEdit::returnPressed, database, [this](){
        database->setCuttingSpeed(ui->cuttingSpeedLineEdit->text().toFloat());
        database->insertNote("Cutting Speed changed to " + ui->cuttingSpeedLineEdit->text());});
    connect(ui->cuttingThicknessLineEdit, &QLineEdit::returnPressed, database, [this](){
        database->setCuttingThickness(ui->cuttingThicknessLineEdit->text().toInt());
        database->insertNote("Cutting Thickness changed to " + ui->cuttingThicknessLineEdit->text());});
    connect(ui->phaseSyncLineEdit, &QLineEdit::returnPressed, database, [this](){
        database->setPhaseSyncValue(ui->phaseSyncLineEdit->text().toFloat());
        database->insertNote("Phase Sync changed to " + ui->phaseSyncLineEdit->text());});
    connect(ui->knifeIonizerSettingLineEdit, &QLineEdit::returnPressed, database, [this](){
        database->setKnifeIonizerSetting(ui->knifeIonizerSettingLineEdit->text().toFloat());
        database->insertNote("Knife Ionizer Setting changed to " + ui->knifeIonizerSettingLineEdit->text());});
    connect(ui->primaryOperatorLineEdit, &QLineEdit::returnPressed, database, [this](){
        database->setPrimaryOperator(ui->primaryOperatorLineEdit->text());
        database->insertNote("Primary Operator changed to " + ui->primaryOperatorLineEdit->text());});
    connect(ui->secondaryOperatorLineEdit, &QLineEdit::returnPressed, database, [this](){
        database->setSecondaryOperator(ui->secondaryOperatorLineEdit->text());
        database->insertNote("Secondary Operator changed to " + ui->secondaryOperatorLineEdit->text());});
    connect(ui->loggingLineEdit, &QLineEdit::returnPressed, database, [this](){
        database->insertNote(ui->loggingLineEdit->text());});

    //connect fault buttons to database entry items. For now we just use text entry, eventually we can use bools to make searching more robust.
    connect(ui->lostSectionButton, &QPushButton::pressed, database, [this](){
        database->insertNote("Lost Section Button Pressed");});
    connect(ui->slippedSectionButton, &QPushButton::pressed, database, [this](){
        database->insertNote("Slipped Section Button Pressed");});
    connect(ui->offApertureButton, &QPushButton::pressed, database, [this](){
        database->insertNote("Off Aperture Button Pressed");});
    connect(ui->splitSectionButton, &QPushButton::pressed, database, [this](){
        database->insertNote("Split Section Button Pressed");});
    connect(ui->stuckOnKnifeButton, &QPushButton::pressed, database, [this](){
        database->insertNote("Stuck On Knife Button Pressed");});
    connect(ui->partialSectionButton, &QPushButton::pressed, database, [this](){
        database->insertNote("Partial Section Button Pressed");});
    connect(ui->thinSectionButton, &QPushButton::pressed, database, [this](){
        database->insertNote("Thin Section Button Pressed");});
    connect(ui->thickSectionButton, &QPushButton::pressed, database, [this](){
        database->insertNote("Thick Section Button Pressed");});
    connect(ui->chatterButton, &QPushButton::pressed, database, [this](){
        database->insertNote("Chatter Button Pressed");});

    connect(ui->stoppedForCleaningButton, &QPushButton::pressed, database, [this](){
        database->insertNote("Stopped For Cleaning Button Pressed");});
    connect(ui->finishedCleaningButton, &QPushButton::pressed, database, [this](){
        database->insertNote("Cleaning Button Pressed");});
    connect(ui->overfilledBoatButton, &QPushButton::pressed, database, [this](){
        database->insertNote("Overfilled Boat Button Pressed");
        timerMinsLeft = 2;
        timerSecsLeft = 0;
        timer->start(1000);});
    connect(this, &MainWindow::countdownFinished, database, [this](){
        database->insertNote("Overfilled Boat Timer Finished");
        QTime initTime = QTime(0, 0, 0);
        QString text = initTime.toString("mm:ss");
        ui->lcdNumber->display(text);
        timer->stop();
    });

}

void MainWindow::setInfoText()
{
    //check to see if there are any records in the table.
    if(database->tableModel->rowCount() != 0){
        //Set all of the defaults in database to what was in the last record, and update GUI
        int lastRow = (database->tableModel->rowCount()) - 1;
        QSqlRecord lastRecord(database->tableModel->record(lastRow));

        QString sessionString(lastRecord.value(database->tableModel->fieldIndex("SectioningSessionID")).toString());
        database->setSectioningSessionID(sessionString);
        ui->sessionLineEdit->setText(sessionString);

        QString specimen(lastRecord.value(database->tableModel->fieldIndex("SpecimenID")).toString());
        database->setSpecimenID(specimen);
        ui->specimenLineEdit->setText(specimen);

        QString tape(lastRecord.value(database->tableModel->fieldIndex("TapeID")).toString());
        database->setTapeID(tape);
        ui->tapeLineEdit->setText(tape);

        QString knifeID(lastRecord.value(database->tableModel->fieldIndex("KnifeID")).toString());
        database->setKnifeID(knifeID);
        ui->knifeLineEdit->setText(knifeID);

        int cuttop(lastRecord.value(database->tableModel->fieldIndex("CuttingWindowTop")).toInt());
        database->setCuttingWindowTop(cuttop);
        ui->cuttingTopLineEdit->setText(QString::number(cuttop));

        int cutbottom(lastRecord.value(database->tableModel->fieldIndex("CuttingWindowBottom")).toInt());
        database->setCuttingWindowBottom(cutbottom);
        ui->cuttingWindowBottomLineEdit->setText(QString::number(cutbottom));

        float cutspeed(lastRecord.value(database->tableModel->fieldIndex("CuttingSpeed")).toFloat());
        database->setCuttingSpeed(cutspeed);
        ui->cuttingSpeedLineEdit->setText(QString::number(cutspeed));

        int cutthick(lastRecord.value(database->tableModel->fieldIndex("CuttingThickness")).toInt());
        database->setCuttingThickness(cutthick);
        ui->cuttingThicknessLineEdit->setText(QString::number(cutthick));

        float phasesync(lastRecord.value(database->tableModel->fieldIndex("PhaseSyncValue")).toFloat());
        database->setPhaseSyncValue(phasesync);
        ui->phaseSyncLineEdit->setText(QString::number(phasesync));

        float ionizer(lastRecord.value(database->tableModel->fieldIndex("KnifeIonizerSetting")).toFloat());
        database->setKnifeIonizerSetting(ionizer);
        ui->knifeIonizerSettingLineEdit->setText(QString::number(ionizer));

        QString primaryop(lastRecord.value(database->tableModel->fieldIndex("PrimaryOperator")).toString());
        database->setPrimaryOperator(primaryop);
        ui->primaryOperatorLineEdit->setText(primaryop);

        QString secondaryop(lastRecord.value(database->tableModel->fieldIndex("SecondaryOperator")).toString());
        database->setSecondaryOperator(secondaryop);
        ui->secondaryOperatorLineEdit->setText(secondaryop);

//        "Note VARCHAR(1000)",
//        "ApertureNumberAtBarcodeReader INT"

    }


}

void MainWindow::updateCountdown()
{
    if (timerMinsLeft == 0 && timerSecsLeft == 0) {
        timerMinsLeft = 0;
        timerSecsLeft = 0;
        emit countdownFinished();
    } else if (timerSecsLeft == 0) {
        timerMinsLeft--;
        timerSecsLeft = 59;
    } else {
        timerSecsLeft--;
    }

    QTime time = QTime(0, timerMinsLeft, timerSecsLeft);
    QString text = time.toString("mm:ss");
    ui->lcdNumber->display(text);
}

MainWindow::~MainWindow()
{
    delete ui;
}
