/* 
 * Text based program to Google Translate service 
 * File: translate.h
 * Author: Tiago Maluta <maluta@unifei.edu.br>
 * License: GPLv3 
 *
*/

#ifndef QLINGUISTEXTENSION_H
#define QLINGUISTEXTENSION_H
 
#include <QString>
#include <QByteArray>
#include <QHttpRequestHeader>
#include <QHttp>
 
class LinguistExtension : public QObject {

  Q_OBJECT 
  
  private:
   QHttp *m_http;
   
  private slots:   
   void _TranslationDone(bool error);
   
  public slots: 
   void Init();
   void Translate(const QString& text, const QString& langTo);

}; 

#endif