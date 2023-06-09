/*******************************************************************
*
*  DESCRIPTION: Atomic Model Dialing
*
*  AUTHOR: M Asif && Khuuram Shahzad
*
*  DATE: 10/10/2003
*
*******************************************************************/

/** include files **/
#include "dialing.h"      // class Dialing
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: Dialing
* Description: 
********************************************************************/

Dialing::Dialing( const string &name )
: Atomic( name )
, num( addInputPort( "num" ) )
, callee_pickup( addInputPort( "callee_pickup" ) )
, out( addOutputPort( "out" ) )
, connect(addOutputPort( "connect" ) )
, ringingTime( 0, 1, 0, 0 )
, processTime( 0, 0, 1, 0 )
{
	string time( MainSimulator::Instance().getParameter( description(), "ringingTime" ) ) ;
	if( time != "" )
		ringingTime = time ;
}

/*******************************************************************
* Function Name: initFunction
* Description: 
* Precondition: 
********************************************************************/
Model &Dialing::initFunction()
{
	state = 0;
	attended = 0;
	NumHasCame = 0 ; 
	number = 0;

	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &Dialing::externalFunction( const ExternalMessage &msg )
{
	//cout<<"ring time " <<ringingTime<<"\n"  ; 

	if( msg.port() == num )
	{
		cout<<"Dialing: Receive Num to Dial :: "<<msg.value()<<"\n" ;
		state = 1;
		NumHasCame = 1 ; 
		number = (int)msg.value();
		holdIn( active, processTime);
		
	}
	if(msg.port() == callee_pickup){
		if ( NumHasCame == 1 )
		{
			cout<<" Dialing:Callee has pickedUp s\n" ;
			attended = 1; 
			state = 2 ; 
			holdIn( active, processTime );
		}
		else {passivate();}
	}

	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &Dialing::internalFunction( const InternalMessage & )
{
	//cout<<"Internal function  and State: "<<state<<"\n" ;

	if (state == 0){
		state = 1;
		holdIn(active, ringingTime);
	}
	
	else if (state == 3){
		state = 0;
		passivate();
		attended = 0;
		NumHasCame = 0 ; 
	}
	
	else if (state == 1){
		//state = 0;
		//wait for the Callee to for the Call to PickUP
		attended = -1;
		holdIn(active, ringingTime);		
	}	

	else if ( state == 2 ) {
		//Callee and Caller are now connected 
		passivate();
	
	}
		
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &Dialing::outputFunction( const InternalMessage &msg )
{
	//cout<< " Out put funciton and state: "<<state <<" Attende: "<<attended<<"\n" ; 
	if (state == 1)
	{
		if (attended == -1){
			cout<< " Callee is not botherting to Pick phone \n" ; 
			sendOutput( msg.time(), out, NO_PICKUP*number);		
			state = 3 ;
			attended = 0;
		}

		else{
		cout<< " Ring has been sent to the Callee \n" ; 
		sendOutput( msg.time(), out, RINGING*number);
		}
	}
	
	if (state == 2){ 
		cout<< " Callee and Caller are now Connected \n" ; 
		sendOutput( msg.time(), connect, CONNECT);
	}

	return *this ;
}