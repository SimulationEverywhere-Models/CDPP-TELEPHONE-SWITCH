/*******************************************************************
*
*  DESCRIPTION: Atomic Model DirLookup
*
*  AUTHOR: M Asif && Khurram
*
*
*  DATE: 10/11/2003
*
*******************************************************************/

#ifndef __DIRLOOKUP_H
#define __DIRLOOKUP_H


#define BUSY -1
#define INVALID -2
#define LINE_NOT_FREE -3
#define VALID 1

#define WAITING_STATE 2
#define BUSY_STATE 1
#define IDLE_STATE 0


#include <map>
#include "atomic.h"     // class Atomic

class DirLookup : public Atomic
{
public:
	DirLookup( const string &name = "DirLookup" );					//Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &num; //number dialed /output of touch tone
	const Port &tone; // caller # to make it busy
	const Port &dc;  // caller/calee who hang up -- to make line free
	const Port &dialing_in; // ring callee and make his line busy
	const Port &line_in; // line avaible or not ?
	
	
	Port &out_to_dial; // number to be dial to dialer 
	Port &error_out; // error of forectory look up
	Port &give_line; // asking line controller to give line
	
	bool disconnect;
	int output ;
	int state ;
	int number;
	Time processingTime;
	
	// map of phone#, int (for caller = 2, calee = 1, free = 0)
	typedef map<int,int> PhoneMap ;
	PhoneMap phoneList ;
	PhoneMap::iterator itn; 
	Time timeLeft;

};	// class DirLookup

// ** inline ** // 
inline
string DirLookup::className() const
{
	return "DirLookup" ;
}

#endif   //__DIRLOOKUP_H
