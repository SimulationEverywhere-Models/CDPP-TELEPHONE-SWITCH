/*******************************************************************
*
*  DESCRIPTION: Atomic Model Dialing
*
*  AUTHOR: M Asif && Khurram Shahzad 
*
*  
*  DATE: 10/10/2003
*
*******************************************************************/

#ifndef __DIALING_H
#define __DIALING_H

#define DIALING 1
#define RINGING 1
#define NO_PICKUP -1
#define CONNECT 1



#include "atomic.h"     // class Atomic

class Dialing : public Atomic
{
public:
	Dialing( const string &name = "Dialing" );					//Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &num;
	const Port &callee_pickup;
	Port &out;
	Port &connect;

	int state ; 
	int attended;
	int NumHasCame ; 
	int number;
	Time processTime ;
	Time ringingTime;
	Time timeLeft;
	

};	// class Dialing

// ** inline ** // 
inline
string Dialing::className() const
{
	return "Dialing" ;
}

#endif   //__DIALTONE_H
