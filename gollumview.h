/*
    Copyright (c) 2013 Cornelius Schumacher <schumacher@kde.org>
*/
#ifndef GOLLUMVIEW_H
#define GOLLUMVIEW_H

#include <QtGui>

class QWebView;

class GollumView : public QWidget
{
    Q_OBJECT
  public:
    GollumView();
    ~GollumView();

    void start( const QString &path );
    
  public slots:
    void showHome();
    void showInvalidRepo( const QString &repo );

  protected slots:
    void readOutput();

  private:
    QWebView *m_view;

    QProcess *m_process;

    bool m_hasError;
};

#endif
