#include "dialog.h"
#include "ui_dialog.h"
#include <QFileDialog>
#include <QAudioDeviceInfo>


Dialog::Dialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Dialog)
{
  ui->setupUi(this);
  myPlot = new QwtPlot();
  ui->frame_3->layout()->addWidget(myPlot);
  curve= new QwtPlotCurve("packets");
  curve->attach(myPlot);
  curve->setStyle(QwtPlotCurve::Sticks);
  myPlot->show();
}

Dialog::~Dialog()
{
  delete ui;
}

void Dialog::on_pushButton_clicked()
{


  file.setFileName (ui->lineEdit->text ());
  file.open (QIODevice::ReadOnly);
  QAudioDeviceInfo ainfo=QAudioDeviceInfo::defaultOutputDevice ();

  ui->textBrowser->setText (ainfo.supportedCodecs ().join ("\n"));
  // Set up the format, eg.
  fmt.setSampleRate(44100);
  fmt.setChannelCount(2);
  fmt.setSampleSize(16);
  fmt.setCodec("audio/pcm");
  fmt.setByteOrder(QAudioFormat::LittleEndian);
  fmt.setSampleType(QAudioFormat::UnSignedInt);
  aoutput=new QAudioOutput(fmt,this);
  aoutput->start (&file);
}

void Dialog::on_toolButton_clicked()
{
  QString str=QFileDialog::getOpenFileName ();
  ui->lineEdit->setText (str);
}

void Dialog::on_pushButton_2_clicked()
{
//    fmt.setSampleRate(11025);
//    fmt.setChannelCount(1);
//    fmt.setSampleSize(16);


    fmt.setSampleRate(44100);
    fmt.setChannelCount(2);
    fmt.setSampleSize(16);

    fmt.setCodec("audio/pcm");
    fmt.setByteOrder(QAudioFormat::LittleEndian);
    fmt.setSampleType(QAudioFormat::UnSignedInt);

  rawgen.fmt=fmt;
  rawgen.open (QIODevice::ReadOnly);

  QAudioDeviceInfo ainfo=QAudioDeviceInfo::defaultOutputDevice ();
  // Set up the format,
  if(!ainfo.isFormatSupported(fmt))
      qDebug() << "Format not supported...";
  else
      qDebug() << "supported...";
  aoutput=new QAudioOutput(fmt,this);
//  aoutput->setBufferSize(2048);
  aoutput->start (&rawgen);
}
