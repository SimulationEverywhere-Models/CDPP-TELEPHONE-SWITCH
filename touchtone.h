/*******************************************************************
*
*  DESCRIPTION: Atomic Model TouchTone
*
*  AUTHOR: khurram Shahzad && M Asif
*
*
*  DATE: 10/10/2003
*
*******************************************************************/

#ifndef __TOUCHTONE_H
#define __TOUCHTONE_H

#define IDLE 0
#define TONE_IN 1
#define KEY_1 2
#define KEY_2 3
#define KEY_3 4

#include "atomic.h"     // class Atomic

class TouchTone : public Atomic
{
public:
	TouchTone( const string &name = "TouchTone" );					//Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &key ; //&touch tone key pressed;
	const Port &tone; //if dial tone is there
	Port &out; 	  //output num to dirloopup
	
	int state ;
	int number;
	Time processingTime;
	Time timeLeft;

};	// class TouchTone

// ** inline ** // 
inline
string TouchTone::className() const
{
	return "TouchTone" ;
}

#endif   //__TOUCHTONE_H
