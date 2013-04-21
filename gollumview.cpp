/*
    Copyright (c) 2013 Cornelius Schumacher <schumacher@kde.org>
*/

#include "gollumview.h"

#include <QWebView>

GollumView::GollumView()
  : m_hasError( false )
{
  QBoxLayout *topLayout = new QVBoxLayout( this );

  m_view = new QWebView;
  topLayout->addWidget( m_view );

  m_process = new QProcess( this );
  m_process->setProcessChannelMode(QProcess::MergedChannels);
  connect( m_process, SIGNAL( readyReadStandardOutput() ),
           SLOT( readOutput() ) );
  connect( m_process, SIGNAL( finished( int, QProcess::ExitStatus ) ),
           SLOT( showHome() ) );
}

GollumView::~GollumView()
{
  m_process->terminate();
}

void GollumView::start( const QString &path )
{
  m_process->setWorkingDirectory( path );

  qDebug() << m_process->workingDirectory();

  m_process->start( "gollum" );
}

void GollumView::readOutput()
{
  QTextStream ts( m_process );
  QString line;
  QRegExp reStarted( "has taken the stage on (\\d*) " );
  QRegExp reInvalidRepo( "Grit::InvalidGitRepositoryError - (.*):" );
  
  do {
    line = ts.readLine();
//   qDebug() << "LINE:" << line;
    if ( m_hasError ) continue;

    if ( line.contains( reStarted ) ) {
      int port = reStarted.cap( 1 ).toInt();
      qDebug() << "STAGE" << port;
      showHome();
    }
    if ( line.contains( reInvalidRepo ) ) {
      m_hasError = true;
      QString repo = reInvalidRepo.cap( 1 );
      qDebug() << "INVALID REPO" << repo;
      showInvalidRepo( repo );
    }
  } while ( !line.isNull() );
}

void GollumView::showHome()
{
  m_view->load(QUrl("http://localhost:4567"));
}

void GollumView::showInvalidRepo( const QString &repo )
{
  QMessageBox::critical( this, "Invalid Repositoriy",
    QString("Unable to find a valid repository at '%1'.").arg( repo ) );
  QApplication::exit( 1 );
}
