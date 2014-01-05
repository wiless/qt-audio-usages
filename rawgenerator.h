#ifndef RAWGENERATOR_H
#define RAWGENERATOR_H

#include <QIODevice>
#include <QtMultimediaKit/QAudioFormat>
#include <QFile>

class RawGenerator : public QIODevice
{
  Q_OBJECT
public:
  QAudioFormat fmt;
  QFile file;
  QByteArray internal;
public:
  explicit RawGenerator(QObject *parent = 0);


  qint64 readData(char* data, qint64 maxSize);
  qint64 writeData(const char *data, qint64 len);
  bool isSequential(){return true;}
  bool seek ( qint64 pos );
  qint64 pos() const;



signals:
  
public slots:
  
};

#endif // RAWGENERATOR_H
