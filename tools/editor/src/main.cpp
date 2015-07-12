
#include <QApplication>
#include <QStyleFactory>
#include <QDebug>

#if  defined(_MSC_VER)
#include <vld.h>
#endif

#include "main_window.h"

int main(int argc, char *argv[])
{	
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}
