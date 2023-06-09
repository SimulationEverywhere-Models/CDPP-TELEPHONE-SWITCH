/*******************************************************************
*
*  DESCRIPTION: Atomic Model Phone
*
*  AUTHOR: M Asif && Khurram Shahzad 
*
*  
*  DATE: 10/10/2003
*
*******************************************************************/

#ifndef __PHONE_H
#define __PHONE_H

#include "atomic.h"     // class Atomic

class Phone : public Atomic
{
public:
	Phone( const string &name = "Phone" );					//Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &in;
	Port &out;
	Time processingTime;
	Time timeLeft;
	int num ; 

};	// class Phone

// ** inline ** // 
inline
string Phone::className() const
{
	return "Phone" ;
}

#endif   //__PHONE_H
