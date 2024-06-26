#ifndef DEBUG_CONSOLE_H
#define DEBUG_CONSOLE_H

#include <QDialog>
#include <QDebug>
#include <QByteArray>
#include <QString>
#include <QIODevice>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDateTime>
#include <QFileDialog>
#include <QMessageBox>
#include <QTimer>
#include <QSize>
#include <QBrush>

namespace Ui {
class debug_console;
}

class debug_console : public QDialog
{
    Q_OBJECT

public:
    explicit debug_console(QWidget *parent = nullptr);
    ~debug_console();
    QString debugModeHeader = "DEBUG Mode Console";
    void DebugModeParamInit( void );

signals:
    void DebugPortConnectStatus( bool );
    void SendDataToDebugConsole(QString data);
    void SendDataToMainConsole(QString Data);

public slots:

private slots:

    void ShowSerialPortErrors( QSerialPort::SerialPortError );

    void SerialPortDataRead( void );

    void CheckAvailabePorts( void );
    void SetPortName(int index);
    void SetBaudRate( int index );
    void SetNBits( int index );
    void SetParity( int index );
    void SetStopBits( int index );

    void SerialPortConnection( void );

    void SerialRxClear( void );
    void SerialRxSave( void );

    void SerialDataFromMainWindow(QString data);
    void ConnectMainWindowToDebugConsole();

    void SerialTxCMDSend( void );
    void SerialTxCMDClear( void );

private:
    Ui::debug_console *ui;

    QSerialPort *debugSerialPort = new QSerialPort(this);
    QSerialPortInfo debugSerialPortInfo;
    QMessageBox *debugModeMessageBox =  new QMessageBox( this );
    QTimer *serialSpecUpdate = new QTimer(this);

    void DebugModeConnectingFunctions( void );
    void SerialPortReset( void );

    struct{
        QString portName;
        int portIndexNumber;
        qint32 baudrate;
        QSerialPort::DataBits dataBits;
        QSerialPort::StopBits stopBits;
        QSerialPort::Parity parity;
        QSize labelSize;
    }serial_spec;

    bool mainConsoleConnectionStatus = false;

};

#endif // DEBUG_CONSOLE_H
