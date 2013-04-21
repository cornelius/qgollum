#include <QtGui>

#include "gollumview.h"

int main(int argv, char **args)
{
  QApplication app(argv, args);

  GollumView *view = new GollumView;

  QPushButton *quitButton = new QPushButton("&Quit");

  QObject::connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));

  QVBoxLayout *layout = new QVBoxLayout;
  layout->setMargin( 0 );
  layout->addWidget(view);
  layout->addWidget(quitButton);

  view->start( QDir::currentPath() );
  
  QWidget window;
  window.setLayout(layout);

  window.show();

  return app.exec();
}
