#include <qapplication.h>
#include <iostream>
#include <time.h>
#include "../.ui/trainer.h"

using namespace std;

void *trainer_app_thread(void *none)
{
	int argc = 0;
	char *argv[1] ;
	char temp[]= {"prog"};
	argv[0]=temp;
		
	
	try
	{
		cout<<"a"<<endl;
	QApplication app(argc,argv);
		cout<<"b"<<endl;
	Trainer GloveTrainer;
		cout<<"c"<<endl;
	app.setMainWidget( &GloveTrainer );
		cout<<"d"<<endl;
	GloveTrainer.show();
		cout<<"e"<<endl;
	app.exec();
	}
	catch(...)
	{
	cout<<"exception"<<endl;
	}
	return 0;
}


