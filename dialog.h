#ifndef DIALOG_H
#define DIALOG_H
#include <QDialog>
#include <QtMultimediaKit/QAudioOutput>
#include <QtMultimediaKit/QAudioFormat>
#include <QFile>
#include <rawgenerator.h>
#include <qwt/qwt_plot.h>
#include <qwt/qwt_plot_curve.h>

namespace Ui {
  class Dialog;
}

class Dialog : public QDialog
{
  Q_OBJECT
private:
  QAudioOutput *aoutput;
  QAudioFormat fmt;
  QFile file;
  RawGenerator rawgen;
  QwtPlot *myPlot;
  QwtPlotCurve *curve;
public:
  explicit Dialog(QWidget *parent = 0);
  ~Dialog();
  
private slots:
  void on_pushButton_clicked();

  void on_toolButton_clicked();

  void on_pushButton_2_clicked();

private:
  Ui::Dialog *ui;
};

#endif // DIALOG_H
