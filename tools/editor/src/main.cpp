
#include <QtWidgets/QApplication>


#if !defined(NDEBUG) && defined(_MSC_VER)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include "main_window.h"

int main(int argc, char *argv[])
{
#ifdef _CRTDBG_MAP_ALLOC
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
#endif
	
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}
