/* 
 * Text based program to Google Translate service 
 * File: translate.cpp
 * Author: Tiago Maluta <maluta@unifei.edu.br>
 * License: GPLv3 
 *
 * Compile: # qmake translate.pro
 *          # make 
 * 
 * Run:     # ./translate 
*/
#include <QApplication>
#include <QDebug>

#include "translate.h"

void LinguistExtension::Init()
{
    m_http = new QHttp(this);
    connect(m_http, SIGNAL(done(bool)), this, SLOT(_TranslationDone(bool)));
}

void LinguistExtension::Translate(const QString& text, const QString& langTo) // langTo == "fr", "es", etc.
{

    QString fromLang = "en";
    QString url = QString("/translate_a/t?client=t&sl=" + fromLang + "&tl=" + langTo);

    QHttpRequestHeader header = QHttpRequestHeader("POST", url, 1, 1);
    header.setValue("Host", "www.google.com");
    header.setValue("User-Agent", "Mozilla/5.0");
    header.setValue("Accept-Encoding", "deflate");
    header.setContentLength(text.length());
    header.setValue("Connection", "Close");

    // Text to be translated
    QByteArray ba("text=");
    ba.append(text.toUtf8());

    m_http->setHost("www.google.com");
    m_http->request(header, ba);

}

void LinguistExtension::_TranslationDone(bool error)
{
    QString result0 = QString::fromUtf8(m_http->readAll());

    QRegExp regex("\\{\"trans\":\"(.*)\",\"orig\":", Qt::CaseSensitive, QRegExp::RegExp2);
    regex.setMinimal(true);
    int pos = 0;
    QString result;
    while ((pos = regex.indexIn(result0, pos)) != -1)
    {
    QString t = regex.cap(1);
    result += t;
    pos += regex.matchedLength();
    }

    if (result.startsWith("\""))
    result = result.mid(1);
    if (result.endsWith("\""))
    result.truncate(result.length() - 1);

    qDebug() << result.toAscii();

    exit(1); // TODO: check if it's the correct way...
    
}


int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    if (argc != 3) {
      
	qDebug() << "Usage:";
	qDebug() << "\t" << argv[0] << "[language] \"[text]\" "; 
	qDebug() << "Example:";
	qDebug() << "\t" << argv[0] << "pt_BR \"hot dog\""; 
      
      return -1;

    } else {

	LinguistExtension linguist;
	linguist.Init();
	linguist.Translate(argv[2],argv[1]);

    return app.exec();
    }
}

