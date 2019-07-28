#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QDir>
#include <QSqlRelationalTableModel>

//bool connectDatabase(QDir databasePath);

class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    DatabaseManager();

    bool init();//initializes database, checks for each table, creates them if they do not exist.
    //Public QSqlTableModels for each table
    QSqlRelationalTableModel *tableModel;

    QString sectioningSessionID();
    QString specimenID();
    QString tapeID();
    QString knifeID();
    QString primaryOperator();
    QString secondaryOperator();

    int cuttingWindowTop();
    int cuttingWindowBottom();
    float cuttingSpeed();
    int cuttingThickness();
    float phaseSyncValue();
    float knifeIonizerSetting();


    void setSectioningSessionID(const QString id);
    void setSpecimenID(const QString id);
    void setTapeID(const QString id);
    void setKnifeID(const QString id);
    void setPrimaryOperator(const QString id);
    void setSecondaryOperator(const QString id);

    void setCuttingWindowTop(const int value);
    void setCuttingWindowBottom(const int value);
    void setCuttingSpeed(const float value);
    void setCuttingThickness(const int value);
    void setPhaseSyncValue(const float value);
    void setKnifeIonizerSetting(const float value);


private:
    //called by each table initializer. Checks for table in the database, and creates it if it is not there.
    QSqlRelationalTableModel* initTable(const QList<QString> tables, QSqlDatabase &db);//sqlTables is a list of tables and associated types in sql format

    QDir m_databasePath;

    //lists for generating tables in databse. First item on list is the table name.
    const QList<QString> m_table = {
        "LoggingTable",
        "ID INTEGER PRIMARY KEY AUTOINCREMENT",
        "SectioningSessionID VARCHAR(20)",
        "TapeID VARCHAR(20)",
        "SpecimenID VARCHAR(20)",
        "KnifeID VARCHAR(20)",
        "EntryDateTime TIMESTAMP",
        "CuttingWindowTop INT",
        "CuttingWindowBottom INT",
        "CuttingSpeed FLOAT",
        "CuttingThickness INT",
        "PhaseSyncValue FLOAT",
        "KnifeIonizerSetting FLOAT",
        "PrimaryOperator VARCHAR(100)",
        "SecondaryOperator VARCHAR(100)",
        "Note VARCHAR(1000)",
        "ApertureNumberAtBarcodeReader INT"
    };

    QString m_SectioningSessionID;
    QString m_SpecimenID;
    QString m_TapeID;
    QString m_KnifeID;
    QString m_PrimaryOperator;
    QString m_SecondaryOperator;
    int m_cuttingWindowTop;
    int m_cuttingWindowBottom;
    float m_cuttingSpeed;
    int m_cuttingThickness;
    float m_phaseSyncValue;
    float m_knifeIonizerSetting;


public slots:
    void insertNote(const QString entry);
    void testSlot();
    //I will make slots for CRUD options for each table. Or do I make DAO's for that?

signals:
    void testSignal();

};

#endif // DATABASEMANAGER_H
