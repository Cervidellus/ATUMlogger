#include "databasemanager.h"

#include <QSqlQuery>
#include <QDebug>

#include <QSqlRecord>
#include <QSqlError>
#include <QDateTime>

DatabaseManager::DatabaseManager() : m_databasePath("database.db")
{
    qDebug() << "DatabaseManager constructor called";
}

bool DatabaseManager::init()
{
    //Connect to the database. In this case, it is opening a file.
    //TODO: pass the path to it in the form of a QPATH
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(m_databasePath.absolutePath());
    if (!db.open()){
        qDebug() << "Failed to open database.";
        return false;
    }

    //Initialize all of the tables
    tableModel = initTable(m_table, db);

    qDebug() << "Database initialized.";
    return true;
}

QSqlRelationalTableModel* DatabaseManager::initTable(const QList<QString> tables, QSqlDatabase &db)
{
    QSqlRelationalTableModel *tablemodel = new QSqlRelationalTableModel(nullptr, db);
    QString tableName = tables.first();

    //If the table is not in the database, create the table
    QString queryString = "CREATE TABLE IF NOT EXISTS " + tableName + " (";
    for (int i = 1; i < tables.count(); i++){
        queryString.append(tables[i]);
        if (i!=tables.count()-1) queryString.append(", ");
        else queryString.append(")");
    }

    QSqlQuery query(db);
    query.exec(queryString);

    //setup the table model and return
    tablemodel->setTable(tableName);
    tablemodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tablemodel->select();//populates table with data from database. Eventually, I may want to do this with a filter.
    return tablemodel;
}

void DatabaseManager::testSlot()
{
    qDebug() << "testslot in databasemanager called";
}

void DatabaseManager::insertNote(QString entry)
{
    //todo:: change so that it checks for null first, or provide 0 default values for ints and floats
    QSqlRecord record = tableModel->record();
    record.setValue(tableModel->fieldIndex("SectioningSessionID"), m_SectioningSessionID);
    record.setValue(tableModel->fieldIndex("TapeID"), m_TapeID);
    record.setValue(tableModel->fieldIndex("SpecimenID"), m_SpecimenID);
    record.setValue(tableModel->fieldIndex("KnifeID"), m_KnifeID);
    record.setValue(tableModel->fieldIndex("EntryDateTime"), QDateTime::currentDateTime());
    record.setValue(tableModel->fieldIndex("CuttingWindowTop"), m_cuttingWindowTop);
    record.setValue(tableModel->fieldIndex("CuttingWindowBottom"), m_cuttingWindowBottom);
    record.setValue(tableModel->fieldIndex("CuttingSpeed"), m_cuttingSpeed);
    record.setValue(tableModel->fieldIndex("CuttingThickness"), m_cuttingThickness);
    record.setValue(tableModel->fieldIndex("PhaseSyncValue"), m_phaseSyncValue);
    record.setValue(tableModel->fieldIndex("KnifeIonizerSetting"), m_knifeIonizerSetting);
    record.setValue(tableModel->fieldIndex("PrimaryOperator"), m_PrimaryOperator);
    record.setValue(tableModel->fieldIndex("SecondaryOperator"), m_SecondaryOperator);
    //    "ApertureNumberAtBarcodeReader INT"
    record.setValue(tableModel->fieldIndex("Note"), entry);
    tableModel->insertRecord(-1, record);
    tableModel->submitAll();
    qDebug() << "Entered note " << entry << " into database";
}

QString DatabaseManager::sectioningSessionID()
{
    return m_SectioningSessionID;
}

void DatabaseManager::setSectioningSessionID(const QString id)
{
    m_SectioningSessionID = id;
    qDebug() << "Sectioning Session ID set to " << id;
}

QString DatabaseManager::specimenID()
{
    return m_SpecimenID;
}

void DatabaseManager::setSpecimenID(const QString id)
{
    m_SpecimenID = id;
    qDebug() << "Specimen ID set to " << id;
}
//QString tapeID();
QString DatabaseManager::tapeID()
{
    return m_TapeID;
}

void DatabaseManager::setTapeID(const QString id)
{
    m_TapeID = id;
    qDebug() << "Tape ID set to " << id;
}
//QString knifeID();
QString DatabaseManager::knifeID()
{
    return m_KnifeID;
}

void DatabaseManager::setKnifeID(const QString id)
{
    m_KnifeID = id;
    qDebug() << "Knife ID set to " << id;
}

//QString primaryOperator();
QString DatabaseManager::primaryOperator()
{
    return m_PrimaryOperator;
}

void DatabaseManager::setPrimaryOperator(const QString id)
{
    m_PrimaryOperator = id;
    qDebug() << "Primary Operator ID set to " << id;
}
//QString secondaryOperator();
QString DatabaseManager::secondaryOperator()
{
    return m_SecondaryOperator;
}

void DatabaseManager::setSecondaryOperator(const QString id)
{
    m_SecondaryOperator = id;
    qDebug() << "Secondary Operator ID set to " << id;
}

//int cuttingWindowTop();
int DatabaseManager::cuttingWindowTop()
{
    return m_cuttingWindowTop;
}

void DatabaseManager::setCuttingWindowTop(const int value)
{
    m_cuttingWindowTop = value;
    qDebug() << "Cutting Window Top set to " << value;
}

//int cuttingWindowBottom();
//int cuttingWindowTop();
int DatabaseManager::cuttingWindowBottom()
{
    return m_cuttingWindowBottom;
}

void DatabaseManager::setCuttingWindowBottom(const int value)
{
    m_cuttingWindowBottom = value;
    qDebug() << "Cutting Window Bottom set to " << value;
}

//float cuttingSpeed();
float DatabaseManager::cuttingSpeed()
{
    return m_cuttingSpeed;
}

void DatabaseManager::setCuttingSpeed(const float value)
{
    m_cuttingSpeed = value;
    qDebug() << "Cutting Speed set to " << value;
}

//int cuttingThickness();
int DatabaseManager::cuttingThickness()
{
    return m_cuttingThickness;
}

void DatabaseManager::setCuttingThickness(const int value)
{
    m_cuttingThickness = value;
    qDebug() << "Cutting Thickness set to " << value;
}
//float phaseSyncValue();
float DatabaseManager::phaseSyncValue()
{
    return m_phaseSyncValue;
}

void DatabaseManager::setPhaseSyncValue(const float value)
{
    m_phaseSyncValue = value;
    qDebug() << "Phase Sync set to " << value;
}
//float knifeIonizerSetting();
float DatabaseManager::knifeIonizerSetting()
{
    return m_knifeIonizerSetting;
}

void DatabaseManager::setKnifeIonizerSetting(const float value)
{
    m_knifeIonizerSetting = value;
    qDebug() << "Knife Ionizer Setting set to " << value;
}


