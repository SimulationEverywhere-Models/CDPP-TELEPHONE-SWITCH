/*******************************************************************
*
*  DESCRIPTION: Atomic Model Line Controller
*
*  AUTHOR: M Asif && Khurram
*
*
*  DATE: 10/11/2003
*
*******************************************************************/

#ifndef __LINECONT_H
#define __LINECONT_H


#define LINE 1
#define NO_LINE -1

#include "atomic.h"     // class Atomic

class LineCont : public Atomic
{
public:
	LineCont( const string &name = "LineCont" );					//Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &in;
	Port &out;
	int lines ;
	int output ;
	Time processingTime;
	Time timeLeft;

};	// class LineCont

// ** inline ** // 
inline
string LineCont::className() const
{
	return "LineCont" ;
}

#endif   //__LINECONT_H
