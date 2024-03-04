#include "quadcopter_mainwindow.h"
#include "ui_quadcopter_mainwindow.h"

Quadcopter_MainWindow::Quadcopter_MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Quadcopter_MainWindow)
{
    ui->setupUi(this);

    lostConnectionGif->setFileName("D:/Projects/STP/Quadcopter/Application/Resources/Gifs/LostConnection.gif");
    lostConnectionGif->setFormat("gif");
    qDebug() << lostConnectionGif->isValid();
    ui->label_DroneCameraView->setMovie(lostConnectionGif);
    ui->label_DroneCameraView->setVisible(false);
    ui->label_Camera1_2->setMovie(lostConnectionGif);
    ui->label_Camera1_2->setVisible(false);
    ui->label_Camera2_2->setMovie(lostConnectionGif);
    ui->label_Camera2_2->setVisible(false);
    ui->label_Camera3_2->setMovie(lostConnectionGif);
    ui->label_Camera3_2->setVisible(false);
    ui->label_Camera4_2->setMovie(lostConnectionGif);
    ui->label_Camera4_2->setVisible(false);
    ui->label_Camera5_2->setMovie(lostConnectionGif);
    ui->label_Camera5_2->setVisible(false);

    ConnectFunctions();

    NoisyTVGifControl(true, 1);
    NoisyTVGifControl(true, 2);
    NoisyTVGifControl(true, 3);
    NoisyTVGifControl(true, 4);
    NoisyTVGifControl(true, 5);
    NoisyTVGifControl(true, 6);

    qcopter.PixmapButtonOn.load("D:/Projects/STP/Quadcopter/Application/Resources/Textures/Circle_FilledGreen.png");
    qcopter.PixmapButtonOff.load("D:/Projects/STP/Quadcopter/Application/Resources/Textures/Circle_Empty.png");
    qcopter.lockPanel = false;

    ClockInit();
    QuadcopterParamInit();
    qcopterGeneralTimer->start(500);
    qcopterButtonTimer->start(100); // 100 miliseconds

}

Quadcopter_MainWindow::~Quadcopter_MainWindow()
{
    delete ui;
}

void Quadcopter_MainWindow::MQTTConsole()
{
    qcopterConsole->ObjectsInit();
    qcopterConsole->setModal(true);
    qcopterConsole->exec();
}

void Quadcopter_MainWindow::MQTTReceivedMsg(QMqttMessage msg)
{
    QString tempMsg;
    QPalette mqttTxtPallete;
    QByteArray tempJsonDataInput = msg.payload();
    qcopter.time = QDateTime::currentDateTime();

    mqttTxtPallete.setColor( foregroundRole(), QColor(0,255,0));
    ui->plainTextEdit_LogPanel->setPalette(mqttTxtPallete);

    tempMsg.append(qcopter.time.toString("yyyy-MM-dd HH:mm:ss") + ": " + tempJsonDataInput);
    ui->plainTextEdit_LogPanel->appendPlainText(tempMsg);

    ui->label_MQTTTopic->setText("Topic: " + msg.topic().name());

    ui->label_MQTTQoS->setText("QoS: " + QString::number(msg.qos()));

    qcopter.jsonDocStatus = QJsonDocument::fromJson(tempJsonDataInput);
    QuadcopterParamUpdate(qcopter.jsonDocStatus.object());
}

void Quadcopter_MainWindow::ButtonForward( void )
{
    if(qcopter.lockPanel == true)
    {
        return;
    }
    qcopter.jsonObjCommand["Forward"]=1;
    qcopter.jsonDocCommand.setObject(qcopter.jsonObjCommand);

    //qDebug() << qcopter.jsonDocCommand;
    //qDebug() << "Forward has been pressed";

    qcopterConsole->mqttSendMsg(qcopter.jsonDocCommand.toJson());

    qcopter.jsonObjCommand["Forward"] =0;
    qcopter.jsonDocCommand.setObject(qcopter.jsonObjCommand);

    AnimationButtonForward();

    qcopter.lockPanel = true;
}

void Quadcopter_MainWindow::ButtonReverse( void )
{
    if(qcopter.lockPanel == true)
    {
        return;
    }

    qcopter.jsonObjCommand["Reverse"]=1;
    qcopter.jsonDocCommand.setObject(qcopter.jsonObjCommand);

    //qDebug() << qcopter.jsonDocCommand;
    //qDebug() << "Reverse has been pressed";

    qcopterConsole->mqttSendMsg(qcopter.jsonDocCommand.toJson());

    qcopter.jsonObjCommand["Reverse"]=0;
    qcopter.jsonDocCommand.setObject(qcopter.jsonObjCommand);

    AnimationButtonReverse();

    qcopter.lockPanel = true;
}

void Quadcopter_MainWindow::ButtonLeft( void )
{
    if(qcopter.lockPanel == true)
    {
        return;
    }

    qcopter.jsonObjCommand["Left"] =1;
    qcopter.jsonDocCommand.setObject(qcopter.jsonObjCommand);

    //qDebug() << qcopter.jsonDocCommand;
    //qDebug() << "Left has been pressed";

    qcopterConsole->mqttSendMsg(qcopter.jsonDocCommand.toJson());

    qcopter.jsonObjCommand["Left"] =0;
    qcopter.jsonDocCommand.setObject(qcopter.jsonObjCommand);

    AnimationButtonLeft();

    qcopter.lockPanel = true;
}

void Quadcopter_MainWindow::ButtonRight( void )
{
    if(qcopter.lockPanel == true)
    {
        return;
    }

    qcopter.jsonObjCommand["Right"] =1;
    qcopter.jsonDocCommand.setObject(qcopter.jsonObjCommand);

    //qDebug() << qcopter.jsonDocCommand;
    //qDebug() << "Right has been pressed";

    qcopterConsole->mqttSendMsg(qcopter.jsonDocCommand.toJson());

    qcopter.jsonObjCommand["Right"] =0;
    qcopter.jsonDocCommand.setObject(qcopter.jsonObjCommand);

    AnimationButtonRight();

    qcopter.lockPanel = true;
}

void Quadcopter_MainWindow::AnimationButtonForward()
{
    static uint8_t cnt = 0;
    switch(cnt)
    {
    case 0:
        connect( qcopterButtonTimer, SIGNAL(timeout()), this, SLOT(AnimationButtonForward()));

        ui->label_F11->setPixmap(qcopter.PixmapButtonOn);
        ui->label_F12->setPixmap(qcopter.PixmapButtonOn);
        ui->label_F13->setPixmap(qcopter.PixmapButtonOn);
        ui->label_F14->setPixmap(qcopter.PixmapButtonOn);
        ui->label_F15->setPixmap(qcopter.PixmapButtonOn);
        cnt++;
        break;
    case 1:
        ui->label_F21->setPixmap(qcopter.PixmapButtonOn);
        ui->label_F22->setPixmap(qcopter.PixmapButtonOn);
        ui->label_F23->setPixmap(qcopter.PixmapButtonOn);
        ui->label_F24->setPixmap(qcopter.PixmapButtonOn);
        ui->label_F25->setPixmap(qcopter.PixmapButtonOn);
        cnt++;
        break;
    case 2:
        ui->label_F31->setPixmap(qcopter.PixmapButtonOn);
        ui->label_F32->setPixmap(qcopter.PixmapButtonOn);
        ui->label_F33->setPixmap(qcopter.PixmapButtonOn);
        ui->label_F34->setPixmap(qcopter.PixmapButtonOn);
        cnt++;
        break;
    case 3:
        ui->label_F41->setPixmap(qcopter.PixmapButtonOn);
        ui->label_F42->setPixmap(qcopter.PixmapButtonOn);
        ui->label_F43->setPixmap(qcopter.PixmapButtonOn);

        ui->label_F11->setPixmap(qcopter.PixmapButtonOff);
        ui->label_F12->setPixmap(qcopter.PixmapButtonOff);
        ui->label_F13->setPixmap(qcopter.PixmapButtonOff);
        ui->label_F14->setPixmap(qcopter.PixmapButtonOff);
        ui->label_F15->setPixmap(qcopter.PixmapButtonOff);
        cnt++;
        break;
    case 4:
        ui->label_F51->setPixmap(qcopter.PixmapButtonOn);
        ui->label_F52->setPixmap(qcopter.PixmapButtonOn);

        ui->label_F21->setPixmap(qcopter.PixmapButtonOff);
        ui->label_F22->setPixmap(qcopter.PixmapButtonOff);
        ui->label_F23->setPixmap(qcopter.PixmapButtonOff);
        ui->label_F24->setPixmap(qcopter.PixmapButtonOff);
        ui->label_F25->setPixmap(qcopter.PixmapButtonOff);
        cnt++;
        break;
    case 5:
        ui->label_F61->setPixmap(qcopter.PixmapButtonOn);
        ui->label_F62->setPixmap(qcopter.PixmapButtonOn);

        ui->label_F31->setPixmap(qcopter.PixmapButtonOff);
        ui->label_F32->setPixmap(qcopter.PixmapButtonOff);
        ui->label_F33->setPixmap(qcopter.PixmapButtonOff);
        ui->label_F34->setPixmap(qcopter.PixmapButtonOff);
        cnt++;
        break;
    case 6:
        ui->label_F71->setPixmap(qcopter.PixmapButtonOn);

        ui->label_F41->setPixmap(qcopter.PixmapButtonOff);
        ui->label_F42->setPixmap(qcopter.PixmapButtonOff);
        ui->label_F43->setPixmap(qcopter.PixmapButtonOff);
        cnt++;
        break;
    case 7:
        ui->label_F51->setPixmap(qcopter.PixmapButtonOff);
        ui->label_F52->setPixmap(qcopter.PixmapButtonOff);

        ui->label_F61->setPixmap(qcopter.PixmapButtonOff);
        ui->label_F62->setPixmap(qcopter.PixmapButtonOff);
        cnt++;
        break;
    default:
        ui->label_F71->setPixmap(qcopter.PixmapButtonOff);
        cnt = 0;
        disconnect( qcopterButtonTimer, SIGNAL(timeout()), this, SLOT(AnimationButtonForward()));
        break;
    }
}

void Quadcopter_MainWindow::AnimationButtonReverse()
{
    static uint8_t cnt = 0;
    switch(cnt)
    {
    case 0:
        connect( qcopterButtonTimer, SIGNAL(timeout()), this, SLOT(AnimationButtonReverse()));

        ui->label_B11->setPixmap(qcopter.PixmapButtonOn);
        ui->label_B12->setPixmap(qcopter.PixmapButtonOn);
        ui->label_B13->setPixmap(qcopter.PixmapButtonOn);
        ui->label_B14->setPixmap(qcopter.PixmapButtonOn);
        ui->label_B15->setPixmap(qcopter.PixmapButtonOn);
        cnt++;
        break;
    case 1:
        ui->label_B21->setPixmap(qcopter.PixmapButtonOn);
        ui->label_B22->setPixmap(qcopter.PixmapButtonOn);
        ui->label_B23->setPixmap(qcopter.PixmapButtonOn);
        ui->label_B24->setPixmap(qcopter.PixmapButtonOn);
        ui->label_B25->setPixmap(qcopter.PixmapButtonOn);
        cnt++;
        break;
    case 2:
        ui->label_B31->setPixmap(qcopter.PixmapButtonOn);
        ui->label_B32->setPixmap(qcopter.PixmapButtonOn);
        ui->label_B33->setPixmap(qcopter.PixmapButtonOn);
        ui->label_B34->setPixmap(qcopter.PixmapButtonOn);
        cnt++;
        break;
    case 3:
        ui->label_B41->setPixmap(qcopter.PixmapButtonOn);
        ui->label_B42->setPixmap(qcopter.PixmapButtonOn);
        ui->label_B43->setPixmap(qcopter.PixmapButtonOn);

        ui->label_B11->setPixmap(qcopter.PixmapButtonOff);
        ui->label_B12->setPixmap(qcopter.PixmapButtonOff);
        ui->label_B13->setPixmap(qcopter.PixmapButtonOff);
        ui->label_B14->setPixmap(qcopter.PixmapButtonOff);
        ui->label_B15->setPixmap(qcopter.PixmapButtonOff);
        cnt++;
        break;
    case 4:
        ui->label_B51->setPixmap(qcopter.PixmapButtonOn);
        ui->label_B52->setPixmap(qcopter.PixmapButtonOn);

        ui->label_B21->setPixmap(qcopter.PixmapButtonOff);
        ui->label_B22->setPixmap(qcopter.PixmapButtonOff);
        ui->label_B23->setPixmap(qcopter.PixmapButtonOff);
        ui->label_B24->setPixmap(qcopter.PixmapButtonOff);
        ui->label_B25->setPixmap(qcopter.PixmapButtonOff);
        cnt++;
        break;
    case 5:
        ui->label_B61->setPixmap(qcopter.PixmapButtonOn);
        ui->label_B62->setPixmap(qcopter.PixmapButtonOn);

        ui->label_B31->setPixmap(qcopter.PixmapButtonOff);
        ui->label_B32->setPixmap(qcopter.PixmapButtonOff);
        ui->label_B33->setPixmap(qcopter.PixmapButtonOff);
        ui->label_B34->setPixmap(qcopter.PixmapButtonOff);
        cnt++;
        break;
    case 6:
        ui->label_B71->setPixmap(qcopter.PixmapButtonOn);

        ui->label_B41->setPixmap(qcopter.PixmapButtonOff);
        ui->label_B42->setPixmap(qcopter.PixmapButtonOff);
        ui->label_B43->setPixmap(qcopter.PixmapButtonOff);
        cnt++;
        break;
    case 7:
        ui->label_B51->setPixmap(qcopter.PixmapButtonOff);
        ui->label_B52->setPixmap(qcopter.PixmapButtonOff);

        ui->label_B61->setPixmap(qcopter.PixmapButtonOff);
        ui->label_B62->setPixmap(qcopter.PixmapButtonOff);
        cnt++;
        break;
    default:
        ui->label_B71->setPixmap(qcopter.PixmapButtonOff);
        cnt = 0;
        disconnect( qcopterButtonTimer, SIGNAL(timeout()), this, SLOT(AnimationButtonReverse()));
        break;
    }
}

void Quadcopter_MainWindow::AnimationButtonLeft()
{
    static uint8_t cnt = 0;
    switch(cnt)
    {
    case 0:
        connect( qcopterButtonTimer, SIGNAL(timeout()), this, SLOT(AnimationButtonLeft()));

        ui->label_L11->setPixmap(qcopter.PixmapButtonOn);
        ui->label_L12->setPixmap(qcopter.PixmapButtonOn);
        ui->label_L13->setPixmap(qcopter.PixmapButtonOn);
        ui->label_L14->setPixmap(qcopter.PixmapButtonOn);
        ui->label_L15->setPixmap(qcopter.PixmapButtonOn);
        cnt++;
        break;
    case 1:
        ui->label_L21->setPixmap(qcopter.PixmapButtonOn);
        ui->label_L22->setPixmap(qcopter.PixmapButtonOn);
        ui->label_L23->setPixmap(qcopter.PixmapButtonOn);
        ui->label_L24->setPixmap(qcopter.PixmapButtonOn);
        ui->label_L25->setPixmap(qcopter.PixmapButtonOn);
        cnt++;
        break;
    case 2:
        ui->label_L31->setPixmap(qcopter.PixmapButtonOn);
        ui->label_L32->setPixmap(qcopter.PixmapButtonOn);
        ui->label_L33->setPixmap(qcopter.PixmapButtonOn);
        ui->label_L34->setPixmap(qcopter.PixmapButtonOn);
        cnt++;
        break;
    case 3:
        ui->label_L41->setPixmap(qcopter.PixmapButtonOn);
        ui->label_L42->setPixmap(qcopter.PixmapButtonOn);
        ui->label_L43->setPixmap(qcopter.PixmapButtonOn);

        ui->label_L11->setPixmap(qcopter.PixmapButtonOff);
        ui->label_L12->setPixmap(qcopter.PixmapButtonOff);
        ui->label_L13->setPixmap(qcopter.PixmapButtonOff);
        ui->label_L14->setPixmap(qcopter.PixmapButtonOff);
        ui->label_L15->setPixmap(qcopter.PixmapButtonOff);
        cnt++;
        break;
    case 4:
        ui->label_L51->setPixmap(qcopter.PixmapButtonOn);
        ui->label_L52->setPixmap(qcopter.PixmapButtonOn);

        ui->label_L21->setPixmap(qcopter.PixmapButtonOff);
        ui->label_L22->setPixmap(qcopter.PixmapButtonOff);
        ui->label_L23->setPixmap(qcopter.PixmapButtonOff);
        ui->label_L24->setPixmap(qcopter.PixmapButtonOff);
        ui->label_L25->setPixmap(qcopter.PixmapButtonOff);
        cnt++;
        break;
    case 5:
        ui->label_L61->setPixmap(qcopter.PixmapButtonOn);
        ui->label_L62->setPixmap(qcopter.PixmapButtonOn);

        ui->label_L31->setPixmap(qcopter.PixmapButtonOff);
        ui->label_L32->setPixmap(qcopter.PixmapButtonOff);
        ui->label_L33->setPixmap(qcopter.PixmapButtonOff);
        ui->label_L34->setPixmap(qcopter.PixmapButtonOff);
        cnt++;
        break;
    case 6:
        ui->label_L71->setPixmap(qcopter.PixmapButtonOn);

        ui->label_L41->setPixmap(qcopter.PixmapButtonOff);
        ui->label_L42->setPixmap(qcopter.PixmapButtonOff);
        ui->label_L43->setPixmap(qcopter.PixmapButtonOff);
        cnt++;
        break;
    case 7:
        ui->label_L51->setPixmap(qcopter.PixmapButtonOff);
        ui->label_L52->setPixmap(qcopter.PixmapButtonOff);

        ui->label_L61->setPixmap(qcopter.PixmapButtonOff);
        ui->label_L62->setPixmap(qcopter.PixmapButtonOff);
        cnt++;
        break;
    default:
        ui->label_L71->setPixmap(qcopter.PixmapButtonOff);
        cnt = 0;
        disconnect( qcopterButtonTimer, SIGNAL(timeout()), this, SLOT(AnimationButtonLeft()));
        break;
    }
}

void Quadcopter_MainWindow::AnimationButtonRight()
{
    static uint8_t cnt = 0;
    switch(cnt)
    {
    case 0:
        connect( qcopterButtonTimer, SIGNAL(timeout()), this, SLOT(AnimationButtonRight()));

        ui->label_R11->setPixmap(qcopter.PixmapButtonOn);
        ui->label_R12->setPixmap(qcopter.PixmapButtonOn);
        ui->label_R13->setPixmap(qcopter.PixmapButtonOn);
        ui->label_R14->setPixmap(qcopter.PixmapButtonOn);
        ui->label_R15->setPixmap(qcopter.PixmapButtonOn);
        cnt++;
        break;
    case 1:
        ui->label_R21->setPixmap(qcopter.PixmapButtonOn);
        ui->label_R22->setPixmap(qcopter.PixmapButtonOn);
        ui->label_R23->setPixmap(qcopter.PixmapButtonOn);
        ui->label_R24->setPixmap(qcopter.PixmapButtonOn);
        ui->label_R25->setPixmap(qcopter.PixmapButtonOn);
        cnt++;
        break;
    case 2:
        ui->label_R31->setPixmap(qcopter.PixmapButtonOn);
        ui->label_R32->setPixmap(qcopter.PixmapButtonOn);
        ui->label_R33->setPixmap(qcopter.PixmapButtonOn);
        ui->label_R34->setPixmap(qcopter.PixmapButtonOn);
        cnt++;
        break;
    case 3:
        ui->label_R41->setPixmap(qcopter.PixmapButtonOn);
        ui->label_R42->setPixmap(qcopter.PixmapButtonOn);
        ui->label_R43->setPixmap(qcopter.PixmapButtonOn);

        ui->label_R11->setPixmap(qcopter.PixmapButtonOff);
        ui->label_R12->setPixmap(qcopter.PixmapButtonOff);
        ui->label_R13->setPixmap(qcopter.PixmapButtonOff);
        ui->label_R14->setPixmap(qcopter.PixmapButtonOff);
        ui->label_R15->setPixmap(qcopter.PixmapButtonOff);
        cnt++;
        break;
    case 4:
        ui->label_R51->setPixmap(qcopter.PixmapButtonOn);
        ui->label_R52->setPixmap(qcopter.PixmapButtonOn);

        ui->label_R21->setPixmap(qcopter.PixmapButtonOff);
        ui->label_R22->setPixmap(qcopter.PixmapButtonOff);
        ui->label_R23->setPixmap(qcopter.PixmapButtonOff);
        ui->label_R24->setPixmap(qcopter.PixmapButtonOff);
        ui->label_R25->setPixmap(qcopter.PixmapButtonOff);
        cnt++;
        break;
    case 5:
        ui->label_R61->setPixmap(qcopter.PixmapButtonOn);
        ui->label_R62->setPixmap(qcopter.PixmapButtonOn);

        ui->label_R31->setPixmap(qcopter.PixmapButtonOff);
        ui->label_R32->setPixmap(qcopter.PixmapButtonOff);
        ui->label_R33->setPixmap(qcopter.PixmapButtonOff);
        ui->label_R34->setPixmap(qcopter.PixmapButtonOff);
        cnt++;
        break;
    case 6:
        ui->label_R71->setPixmap(qcopter.PixmapButtonOn);

        ui->label_R41->setPixmap(qcopter.PixmapButtonOff);
        ui->label_R42->setPixmap(qcopter.PixmapButtonOff);
        ui->label_R43->setPixmap(qcopter.PixmapButtonOff);
        cnt++;
        break;
    case 7:
        ui->label_R51->setPixmap(qcopter.PixmapButtonOff);
        ui->label_R52->setPixmap(qcopter.PixmapButtonOff);

        ui->label_R61->setPixmap(qcopter.PixmapButtonOff);
        ui->label_R62->setPixmap(qcopter.PixmapButtonOff);
        cnt++;
        break;
    default:
        ui->label_R71->setPixmap(qcopter.PixmapButtonOff);
        cnt = 0;
        disconnect( qcopterButtonTimer, SIGNAL(timeout()), this, SLOT(AnimationButtonRight()));
        break;
    }
}

void Quadcopter_MainWindow::GeologicalPosition( int value )
{
    if(qcopter.lockPanel == true)
    {
        return;
    }

    qcopter.jsonObjCommand["Direction"] = value;
    qcopter.jsonDocCommand.setObject(qcopter.jsonObjCommand);

    //qDebug() << qcopter.jsonDocCommand;
    //qDebug() << "Compass Degree" << value;

    qcopterConsole->mqttSendMsg(qcopter.jsonDocCommand.toJson());

    qcopter.lockPanel = true;
}

void Quadcopter_MainWindow::Throttle(int value)
{
    if(qcopter.lockPanel == true)
    {
        return;
    }

    ui->lcdNumber_ThrottleValue->display(value);

    qcopter.jsonObjCommand["Height"] = value;
    qcopter.jsonDocCommand.setObject(qcopter.jsonObjCommand);

    //qDebug() << qcopter.jsonDocCommand;
    //qDebug() << "Height" << value << "cm";

    qcopterConsole->mqttSendMsg(qcopter.jsonDocCommand.toJson());

    qcopter.lockPanel = true;
}

void Quadcopter_MainWindow::DroneSelectNext()
{
    //unsubscribe the current topic
    //and increase the topic value
    //subscribe to the new topic value
    qDebug() << "Next Camera has been pressed";
}

void Quadcopter_MainWindow::DroneSelectPrevious()
{
    //unsubscribe the current topic
    //and decrease the topic value
    //subscribe to the new topic value
    qDebug() << "Previous Camera has been pressed";
}

void Quadcopter_MainWindow::ButtonCameraShutter()
{
    //Save a png image from the main screen.
    qDebug() << "Shutter Camera has been pressed";
}

void Quadcopter_MainWindow::QuadcopterParamInit()
{
    qcopter.jsonObjStatus.insert("Temperatuer", 0);
    qcopter.jsonObjStatus.insert("Humedity" , 0);
    qcopter.jsonObjStatus.insert("Battery" , 0);
    qcopter.jsonObjStatus.insert("Speed" , 0);
    qcopter.jsonObjStatus.insert("Displacement" , 0);
    qcopter.jsonObjStatus.insert("GeologicalPosition" , 0);
    qcopter.jsonObjStatus.insert("Height", 0);

    qcopter.jsonDocStatus.setObject(qcopter.jsonObjStatus);

    qcopter.jsonObjCommand.insert("Forward",0);
    qcopter.jsonObjCommand.insert("Reverse",0);
    qcopter.jsonObjCommand.insert("Left",0);
    qcopter.jsonObjCommand.insert("Right",0);
    qcopter.jsonObjCommand.insert("Direction",0);
    qcopter.jsonObjCommand.insert("Height",0);

    qcopter.jsonDocCommand.setObject(qcopter.jsonObjCommand);

    qDebug() << qcopter.jsonDocStatus;
    qDebug() << qcopter.jsonDocCommand;

    QuadcopterParamUpdate( qcopter.jsonObjStatus );
}

void Quadcopter_MainWindow::QuadcopterParamUpdate(QJsonObject inputObj)
{
    if(inputObj.contains("Temperature"))
    {
        qcopter.jsonObjStatus["Temperature"] = inputObj["Temperature"];
    }
    if(inputObj.contains("Humedity"))
    {
        qcopter.jsonObjStatus["Humedity"] = inputObj["Humedity"];
    }
    if(inputObj.contains("Speed"))
    {
        qcopter.jsonObjStatus["Speed"] = inputObj["Speed"];
    }
    if(inputObj.contains("Displacement"))
    {
        qcopter.jsonObjStatus["Displacement"] = inputObj["Displacement"];
    }
    if(inputObj.contains("Height"))
    {
        qcopter.jsonObjStatus["Height"] = inputObj["Height"];
    }
    if(inputObj.contains("GeologicalPosition"))
    {
        qcopter.jsonObjStatus["GeologicalPosition"] = inputObj["GeologicalPosition"];
    }
    if(inputObj.contains("Battery"))
    {
        qcopter.jsonObjStatus["Battery"] = inputObj["Battery"];
    }

    qcopter.jsonDocStatus.setObject(qcopter.jsonObjStatus);

    ui->lcdNumber_Temperature->display(qcopter.jsonObjStatus.value("Temperature").toInt());
    ui->lcdNumber_Humedity->display(qcopter.jsonObjStatus.value("Humedity").toInt());
    ui->lcdNumber_Battery->display(qcopter.jsonObjStatus.value("Battery").toInt());
    ui->lcdNumber_Speed->display(qcopter.jsonObjStatus.value("Speed").toInt());
    ui->lcdNumber_Displacement->display(qcopter.jsonObjStatus.value("Displacement").toInt());
    ui->lcdNumber_Height->display(qcopter.jsonObjStatus.value("Height").toInt());
    ui->dial_GeologicalPosition->setValue(qcopter.jsonObjStatus.value("GeologicalPosition").toInt());
}

void Quadcopter_MainWindow::ClockInit()
{
    qcopter.clockFont.setPixelSize(32);
    ui->label_Time->setFont(qcopter.clockFont);
    ui->label_Time->setAlignment(Qt::AlignCenter);
    qcopter.time = QDateTime::currentDateTime();
    ui->label_Time->setText(qcopter.time.toString("HH:mm:ss"));
}

void Quadcopter_MainWindow::ClockUpdate()
{
    qcopter.time = QDateTime::currentDateTime();
    ui->label_Time->setText(qcopter.time.toString("HH:mm:ss"));

    qcopter.lockPanel = false;
}

void Quadcopter_MainWindow::ConnectFunctions()
{
    connect(ui->pushButton_ConnectServer, SIGNAL(clicked(bool)), this, SLOT(MQTTConsole()));

    connect(ui->pushButton_MoveForward, SIGNAL(pressed()), this, SLOT(ButtonForward()));
    connect(ui->pushButton_MoveReverse, SIGNAL(pressed()), this, SLOT(ButtonReverse()));
    connect(ui->pushButton_MoveLeft, SIGNAL(pressed()), this, SLOT(ButtonLeft()));
    connect(ui->pushButton_MoveRight, SIGNAL(pressed()), this, SLOT(ButtonRight()));
    connect(ui->verticalSlider_Throttle, SIGNAL(valueChanged(int)), this, SLOT(Throttle(int)));
    connect(ui->dial_GeologicalPosition, SIGNAL(valueChanged(int)), this, SLOT(GeologicalPosition(int)));
    connect(ui->pushButton_DroneSelectNext, SIGNAL(clicked(bool)), this, SLOT(DroneSelectNext()));
    connect(ui->pushButton_DroneSelectPrevious, SIGNAL(clicked(bool)), this, SLOT(DroneSelectPrevious()));
    connect(ui->pushButton_DroneCameraSnapshot, SIGNAL(clicked(bool)), this, SLOT(ButtonCameraShutter()));
    connect(qcopterGeneralTimer, SIGNAL(timeout()), this, SLOT(ClockUpdate()));

    connect(qcopterConsole, SIGNAL(QCopter_NewMessage(QMqttMessage)), this, SLOT(MQTTReceivedMsg(QMqttMessage)));
}

void Quadcopter_MainWindow::NoisyTVGifControl(bool cmd, uint8_t screenNumber)
{

    switch (screenNumber)
    {
    case 1:
        if(cmd)
        {
            ui->graphicsView_DroneCameraView->setVisible(false);

            ui->label_DroneCameraView->setVisible(true);
            lostConnectionGif->start();
        }
        else
        {
            ui->graphicsView_DroneCameraView->setVisible(true);

            ui->label_DroneCameraView->setVisible(false);
            lostConnectionGif->stop();
        }
        break;
    case 2:
        if(cmd)
        {
            ui->graphicsView_Camera0->setVisible(false);

            ui->label_Camera1_2->setVisible(true);
            //ui->label_MainScreen->raise();
            lostConnectionGif->start();
        }
        else
        {
            ui->graphicsView_Camera0->setVisible(true);

            ui->label_Camera1_2->setVisible(false);
            lostConnectionGif->stop();
        }
        break;
    case 3:
        if(cmd)
        {
            ui->graphicsView_Camera1->setVisible(false);

            ui->label_Camera2_2->setVisible(true);
            //ui->label_MainScreen->raise();
            lostConnectionGif->start();
        }
        else
        {
            ui->graphicsView_Camera1->setVisible(true);

            ui->label_Camera2_2->setVisible(false);
            lostConnectionGif->stop();
        }
        break;
    case 4:
        if(cmd)
        {
            ui->graphicsView_Camera2->setVisible(false);

            ui->label_Camera3_2->setVisible(true);
            //ui->label_MainScreen->raise();
            lostConnectionGif->start();
        }
        else
        {
            ui->graphicsView_Camera2->setVisible(true);

            ui->label_Camera3_2->setVisible(false);
            lostConnectionGif->stop();
        }
        break;
    case 5:
        if(cmd)
        {
            ui->graphicsView_Camera3->setVisible(false);

            ui->label_Camera4_2->setVisible(true);
            //ui->label_MainScreen->raise();
            lostConnectionGif->start();
        }
        else
        {
            ui->graphicsView_Camera3->setVisible(true);

            ui->label_Camera4_2->setVisible(false);
            lostConnectionGif->stop();
        }
        break;
    case 6:
        if(cmd)
        {
            ui->graphicsView_Camera4->setVisible(false);

            ui->label_Camera5_2->setVisible(true);
            //ui->label_MainScreen->raise();
            lostConnectionGif->start();
        }
        else
        {
            ui->graphicsView_Camera4->setVisible(true);

            ui->label_Camera5_2->setVisible(false);
            lostConnectionGif->stop();
        }
        break;
    default:
        break;
    }
}

