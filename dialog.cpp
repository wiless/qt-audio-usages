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
  curve->setStyle(QwtPlotCurve::Lines);
  curve->setPen (QColor(Qt::blue));
  myPlot->show();
}

Dialog::~Dialog()
{
  delete ui;
}

void Dialog::on_toolButton_clicked()
{
  QString str=QFileDialog::getOpenFileName ();
  ui->lineEdit->setText (str);
}


void Dialog::on_btnMethod1_clicked()
{
  file.setFileName (ui->lineEdit->text ());
  file.open (QIODevice::ReadOnly);
  QAudioDeviceInfo ainfo=QAudioDeviceInfo::defaultOutputDevice ();

  //  ui->textBrowser->setText (ainfo.supportedCodecs ().join ("\n"));
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

void Dialog::on_btnMethod2_clicked()
{
  fmt.setSampleRate(44100);
  fmt.setChannelCount(2);
  fmt.setSampleSize(16);

  fmt.setCodec("audio/pcm");
  fmt.setByteOrder(QAudioFormat::LittleEndian);
  fmt.setSampleType(QAudioFormat::UnSignedInt);

  rawgen.fmt=fmt;
  rawgen.init (ui->lineEdit->text ());


  QAudioDeviceInfo ainfo=QAudioDeviceInfo::defaultOutputDevice ();
  // Set up the format,
  if(!ainfo.isFormatSupported(fmt))
    qDebug() << "Format not supported...";
  else
    qDebug() << "supported...";
  aoutput=new QAudioOutput(fmt,this);
  //  aoutput->setBufferSize(2048);
  connect(&rawgen,SIGNAL(plotSignal(char*,qint64)),this,SLOT(plotValues(char*,qint64)));
  aoutput->start (&rawgen);
}

void Dialog::plotValues(char *data, qint64 maxsize)
{

  int samples=maxsize/(fmt.sampleSize ()/8);

  QVector <double> xvals(samples);
  QVector <quint16> rawdata(samples);
  QVector <double> yvals(samples);
  memcpy(rawdata.data (),data,maxsize);
  double Ts=1.0/fmt.frequency ();
  for(int k=0;k<samples;k++)
    {
      xvals[k]=k*Ts;
      yvals[k]=(double)((qint16)rawdata[k])/32768;
    }
  curve->setSamples (xvals,yvals);
   myPlot->replot ();
}
