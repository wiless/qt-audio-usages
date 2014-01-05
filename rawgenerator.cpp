#include "rawgenerator.h"

#include <QString>
#include <QDebug>
#include <qmath.h>

RawGenerator::RawGenerator(QObject *parent) :
  QIODevice(parent)
{


    QIODevice::setOpenMode(QIODevice::ReadOnly);
//     file.setFileName("jhund2.wav");
     file.setFileName("temp.wav");
    if(!file.open(QIODevice::ReadOnly))
        qDebug() << "Unable to open file";


    file.seek(44);
    internal=file.readAll();

//    int Nsamples=16384*4;
//    internal.resize(Nsamples*sizeof(quint16));
//     const double scale=(pow(2,16)-1);
//    for(int k=0;k<Nsamples;k++)
//    {
//        double dvalue=(double)qrand()/RAND_MAX ;
//        quint16 value=dvalue*scale;
////        qDebug() << value;
//        memcpy(internal.data()+k*sizeof(quint16),&value,sizeof(quint16));
//    }

     qDebug() << " File Size " << internal.size();

}

qint64 RawGenerator::readData(char *data, qint64 maxSize)
{
      static qint64 counter;

      qint64 possiblebytes=(internal.size()-counter);
      qDebug() << " Requested " << maxSize << "   Avaialble : " << possiblebytes;

      if(possiblebytes>=maxSize)
      {
          memcpy(data,internal.data()+counter,maxSize);
       counter+=maxSize;
      }
      else
       {

          memcpy(data,internal.data()+counter,possiblebytes);
          counter=0;
          memcpy(data+possiblebytes,internal.data()+counter,maxSize-possiblebytes);
          counter+=maxSize-possiblebytes;
          qDebug() << " You RESET" << maxSize;

      }


     return maxSize;

//      qDebug() << " You will never see this";


//      double fc=100; ///10Hz
//      int period=1.0/fc;
//      double Ts=1.0/fmt.sampleRate ();
//      int mysize=(maxSize<1024)?maxSize:1024;
//      if(counter==0)
//      {

//          qDebug() << " Frequency " << fc;
//          qDebug() << " Ts " << Ts;
//          qDebug() << " fmt.sampleRate() " << fmt.sampleRate();
//          qDebug() << " Audio Duration " << Ts*maxSize;

//      }
      QString str;
      qDebug () << " Current File pos " << file.pos();
      qint64 bytesreadable=file.bytesAvailable();
      qint64 possible=qMin(bytesreadable,maxSize);

      qint64 result= file.read(data,possible);
      qint64 filepos=file.pos();
      if(possible!=maxSize)
      {
          file.seek(0);
          qDebug () << " RESET file postion ----  " << file.pos();
          result+=file.read(data+possible,(maxSize-possible));

      }
//      str=str.sprintf(" Was called for %d To Read bytes %d, but fillsize = %d current Pos %d",counter++,(int)maxSize,result,filepos);
      qDebug () << "Read Bytes " << result << " Requested  " << maxSize << " Lost " << maxSize-result;

          qDebug () << " After Read File pos " << file.pos();
          if(result<maxSize)
          {

//              file.seek(0);
               qDebug () << " RESET file postion ----  " << file.pos();
          }
      return result;
//      for(int k=0;k<mysize;k++)
//        {

//          double t=(Ts*k);

//          double dvalue=0.5*qSin (fc*M_2_PI*t)+0.5;

//          quint8 value=dvalue*255;

////          qDebug () << value;
//          data[k]=value;

//        }

    //  return mysize;
}

qint64 RawGenerator::writeData(const char *data, qint64 len)
{
    return len;
}

bool RawGenerator::seek(qint64 pos)
{
    qDebug() << "Trying to seek this pos : " << pos;
}

qint64 RawGenerator::pos() const
{
     qDebug() << "Trying to Query my pos : ";
     return 0;
}
