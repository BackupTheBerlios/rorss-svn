/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
#include <qapplication.h>
using namespace std;

void Trainer::fileNew()
{
	
}


void Trainer::fileOpen()
{
	
}


void Trainer::fileSave()
{
	
}




void Trainer::fileExit()
{
	
}












void Trainer::init()
{
	cout<<"initializing network"<<endl;
	initialize_network();
	cout<<"creating thread"<<endl;
	GloveUpdateThread = new boost::thread(boost::bind(&Trainer::GloveUpdateThreadFunction,this));
	cout<<"init complete"<<endl;	
}


void Trainer::LeftFinger5Slider_valueChanged( int )
{
	
}


void Trainer::LeftFinger4Slider_valueChanged( int )
{
	
}


void Trainer::LeftFinger3Slider_valueChanged( int )
{
	
}


void Trainer::LeftFinger2Slider_valueChanged( int )
{
	
}


void Trainer::LeftFinger1Slider_valueChanged( int )
{
	
}


void Trainer::RightFinger1Slider_valueChanged( int )
{
	
}


void Trainer::RightFinger2Slider_valueChanged( int )
{
	
}


void Trainer::RightFinger3Slider_valueChanged( int )
{
	
}


void Trainer::RightFinger4Slider_valueChanged( int )
{
	
}


void Trainer::RightFinger5Slider_valueChanged( int )
{
	
}


void Trainer::LeftFinger5Spinner_valueChanged( int )
{
	
}


void Trainer::LeftFinger4Spinner_valueChanged( int )
{
	
}


void Trainer::LeftFinger3Spinner_valueChanged( int )
{
	
}


void Trainer::LeftFinger2Spinner_valueChanged( int )
{
	
}


void Trainer::LeftFinger1Spinner_valueChanged( int )
{
	
}


void Trainer::RightFinger1Spinner_valueChanged( int )
{
	
}


void Trainer::RightFinger2Spinner_valueChanged( int )
{
	
}


void Trainer::RightFinger3Spinner_valueChanged( int )
{
	
}


void Trainer::RightFinger4Spinner_valueChanged( int )
{
	
}


void Trainer::RightFinger5Spinner_valueChanged( int )
{
	
}


void Trainer::LeftPitchSpinner_valueChanged( int )
{
	
}


void Trainer::LeftRollSpinner_valueChanged( int )
{
	
}


void Trainer::RightPitchSpinner_valueChanged( int )
{
	
}


void Trainer::RightRollSpinner_valueChanged( int )
{
	
}


void Trainer::LeftPitchDial_valueChanged( int )
{
	
}


void Trainer::LeftRollDial_valueChanged( int )
{
	
}


void Trainer::RightPitchDial_valueChanged( int )
{
	
}


void Trainer::RightRollDial_valueChanged( int )
{
	
}


void Trainer::UiRadio_clicked()
{
	
}


void Trainer::GloveRadio_clicked()
{
	
}


void Trainer::TrainEvaluateButton_toggled( bool )
{
	
}


void Trainer::TrainEvaluateButton_clicked()
{
	if(EvaluateButton->isOn())
	{
		CategoryUpdate();
	}
	else
	{
		InputUpdate();
		output1[0]=Category1Spin->value()/100;	
		output1[1]=Category2Spin->value()/100;	
		output1[2]=Category3Spin->value()/100;	
		output1[3]=Category4Spin->value()/100;	
		output1[4]=Category5Spin->value()/100;	
		output1[5]=Category6Spin->value()/100;	
		output1[6]=Category7Spin->value()/100;	
		update_network();	
	}
		
}


void Trainer::CounterExamplesCheck_toggled( bool )
{
	
}


void Trainer::ContinuousEvaluationCheck_toggled( bool )
{
	if(EvaluateButton->isOn())
	{
		if(ContinuousEvaluationCheck->isChecked())
		{
			TrainEvaluateButton->setToggleButton(true);
		}
		else
		{
			if(TrainEvaluateButton->isOn())
				TrainEvaluateButton->toggle();
			TrainEvaluateButton->setToggleButton(false);
		}
	}
	
}


void Trainer::TrainButton_clicked()
{
	
}


void Trainer::EvaluateButton_clicked()
{
	
}


void Trainer::Category1Spin_valueChanged( int )
{
	QColor mycolor(0,55+2*Category1Spin->value(),0);
	Category1LED->setPaletteBackgroundColor(mycolor);
}


void Trainer::Category2Spin_valueChanged( int )
{
	QColor mycolor(0,55+2*Category2Spin->value(),0);
	Category2LED->setPaletteBackgroundColor(mycolor);	
}


void Trainer::Category3Spin_valueChanged( int )
{
	QColor mycolor(0,55+2*Category3Spin->value(),0);
	Category3LED->setPaletteBackgroundColor(mycolor);	
}


void Trainer::Category4Spin_valueChanged( int )
{
	QColor mycolor(0,55+2*Category4Spin->value(),0);
	Category4LED->setPaletteBackgroundColor(mycolor);	
}


void Trainer::Category5Spin_valueChanged( int )
{
	QColor mycolor(0,55+2*Category5Spin->value(),0);
	Category5LED->setPaletteBackgroundColor(mycolor);	
}


void Trainer::Category6Spin_valueChanged( int )
{
	QColor mycolor(0,55+2*Category6Spin->value(),0);
	Category6LED->setPaletteBackgroundColor(mycolor);	
}


void Trainer::Category7Spin_valueChanged( int )
{
	QColor mycolor(0,55+2*Category7Spin->value(),0);
	Category7LED->setPaletteBackgroundColor(mycolor);	
}


void Trainer::EvaluateButton_toggled( bool )
{
	if(EvaluateButton->isOn())
	{
		TrainEvaluateButton->setText( "Evaluate" );
		if(ContinuousEvaluationCheck->isChecked())
			TrainEvaluateButton->setToggleButton(true);
		else
			TrainEvaluateButton->setToggleButton(false);
	}
	else
	{
		if(TrainEvaluateButton->isOn())
			TrainEvaluateButton->toggle();
		TrainEvaluateButton->setText( "Train" );
		TrainEvaluateButton->setToggleButton(false);
	}
}


void Trainer::GloveUpdateThreadFunction()
{
	timespec cycle_delay;
	hand_struct Lhand, Rhand;
	cycle_delay.tv_sec = 0;
	cycle_delay.tv_nsec = 2000000;
	while(true)
	{
		if(GloveRadio->isOn())
		{
			Left_Hand.get_hand(Lhand);
			Right_Hand.get_hand(Rhand);
			qApp->lock();
			LeftFinger1Slider->setValue(Lhand.thumb*100);
			LeftFinger2Slider->setValue(Lhand.index*100);
			LeftFinger3Slider->setValue(Lhand.middle*100);
			LeftFinger4Slider->setValue(Lhand.ring*100);
			LeftFinger5Slider->setValue(Lhand.little*100);
			LeftPitchDial->setValue(Lhand.pitch*100);
			LeftRollDial->setValue(Lhand.roll*100);
			RightFinger1Slider->setValue(Rhand.thumb*100);
			RightFinger2Slider->setValue(Rhand.index*100);
			RightFinger3Slider->setValue(Rhand.middle*100);
			RightFinger4Slider->setValue(Rhand.ring*100);
			RightFinger5Slider->setValue(Rhand.little*100);
			RightPitchDial->setValue(Rhand.pitch*100);
			RightRollDial->setValue(Rhand.roll*100);
			qApp->unlock();
		}
		if(EvaluateButton->isOn() && TrainEvaluateButton->isOn())
		{
			CategoryUpdate();
		}
		nanosleep(&cycle_delay,NULL);
	}
}


void Trainer::ClearValuesButton_clicked()
{
Category1Spin->setValue(0);
Category2Spin->setValue(0);
Category3Spin->setValue(0);
Category4Spin->setValue(0);
Category5Spin->setValue(0);
Category6Spin->setValue(0);
Category7Spin->setValue(0);
}


void Trainer::Category1LED_clicked()
{
if(Category1Spin->value()<20)	
	Category1Spin->setValue(50);
else if(Category1Spin->value()<70)
	Category1Spin->setValue(100);
else
	Category1Spin->setValue(0);

}


void Trainer::Category2LED_clicked()
{
if(Category2Spin->value()<20)	
	Category2Spin->setValue(50);
else if(Category2Spin->value()<70)
	Category2Spin->setValue(100);
else
	Category2Spin->setValue(0);
}


void Trainer::Category3LED_clicked()
{
if(Category3Spin->value()<20)	
	Category3Spin->setValue(50);
else if(Category3Spin->value()<70)
	Category3Spin->setValue(100);
else
	Category3Spin->setValue(0);
}


void Trainer::Category4LED_clicked()
{
if(Category4Spin->value()<20)	
	Category4Spin->setValue(50);
else if(Category4Spin->value()<70)
	Category4Spin->setValue(100);
else
	Category4Spin->setValue(0);
}


void Trainer::Category5LED_clicked()
{
if(Category5Spin->value()<20)	
	Category5Spin->setValue(50);
else if(Category5Spin->value()<70)
	Category5Spin->setValue(100);
else
	Category5Spin->setValue(0);
}


void Trainer::Category6LED_clicked()
{
if(Category6Spin->value()<20)	
	Category6Spin->setValue(50);
else if(Category6Spin->value()<70)
	Category6Spin->setValue(100);
else
	Category6Spin->setValue(0);
}


void Trainer::Category7LED_clicked()
{
if(Category7Spin->value()<20)	
	Category7Spin->setValue(50);
else if(Category7Spin->value()<70)
	Category7Spin->setValue(100);
else
	Category7Spin->setValue(0);
}


void Trainer::CategoryUpdate()
{
	InputUpdate();
	evaluate();
	static int index,max;
	static QString categorystring;
	qApp->lock();
	Category1Spin->setValue(output[0]*100);
	Category2Spin->setValue(output[1]*100);
	Category3Spin->setValue(output[2]*100);
	Category4Spin->setValue(output[3]*100);
	Category5Spin->setValue(output[4]*100);
	Category6Spin->setValue(output[5]*100);
	Category7Spin->setValue(output[6]*100);	
	max=Category1Spin->value();
	categorystring=Category1Text->text();
	if(max < Category2Spin->value()) { max=Category2Spin->value() ; categorystring=Category2Text->text();}
	if(max < Category3Spin->value()) { max=Category3Spin->value() ; categorystring=Category3Text->text();}
	if(max < Category4Spin->value()) { max=Category4Spin->value() ; categorystring=Category4Text->text();}
	if(max < Category5Spin->value()) { max=Category5Spin->value() ; categorystring=Category5Text->text();}
	if(max < Category6Spin->value()) { max=Category6Spin->value() ; categorystring=Category6Text->text();}
	if(max < Category7Spin->value()) { max=Category7Spin->value() ; categorystring=Category7Text->text();}
	Category->setText(categorystring);
	qApp->unlock();
}




void Trainer::InputUpdate()
{
			input1[0]=RightFinger1Slider->value()/100;
			input1[1]=RightFinger2Slider->value()/100;
			input1[2]=RightFinger3Slider->value()/100;
			input1[3]=RightFinger4Slider->value()/100;
			input1[4]=RightFinger5Slider->value()/100;
			input1[5]=RightPitchDial->value()/100;
			input1[6]=RightRollDial->value()/100;
			input1[7]=LeftFinger1Slider->value()/100;
			input1[8]=LeftFinger2Slider->value()/100;
			input1[9]=LeftFinger3Slider->value()/100;
			input1[10]=LeftFinger4Slider->value()/100;
			input1[11]=LeftFinger5Slider->value()/100;
			input1[12]=LeftFinger1Slider->value()/100;
			input1[13]=LeftFinger1Slider->value()/100;
}
