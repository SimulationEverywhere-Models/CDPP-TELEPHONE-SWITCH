/*******************************************************************
*
*  DESCRIPTION: Atomic Model Touch Tone
*
*  AUTHOR: Khurram Shahzad && M Asif 
*
*  DATE: 10/10/2003
*
*******************************************************************/

/** include files **/
#include "touchtone.h"    // class TouchTone
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: TouchTone
* Description: 
********************************************************************/
TouchTone::TouchTone( const string &name )
: Atomic( name )
, key( addInputPort( "key" ) )
, tone( addInputPort( "tone" ) )
, out( addOutputPort( "out" ) )
, processingTime( 0, 0, 10, 0 )
{
	string time( MainSimulator::Instance().getParameter( description(), "processTime" ) ) ;

	if( time != "" )
		processingTime = time ;
}

/*******************************************************************
* Function Name: initFunction
********************************************************************/
Model &TouchTone::initFunction()
{
	state = IDLE;
	number = 0;
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &TouchTone::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == tone ){
		cout<<"TochTone:tone arrived, now waiting for no dialed from ::"<<msg.value()<<endl;
		state = TONE_IN;
		holdIn( active, processingTime );
	}
	
	if( msg.port() == key && state > IDLE)
	{
		int n = msg.value();
		cout<<"TochTone:key pressed ::"<<n<<endl; 
		state++;
		number = number *10 + n;
		holdIn( active, processingTime );
	}
	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &TouchTone::internalFunction( const InternalMessage & )
{
	if(state == KEY_3){
		number = 0;
		state =IDLE ;
		
	}
	passivate();
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &TouchTone::outputFunction( const InternalMessage &msg )
{
	if(state == KEY_3){
		cout<<"TochTone: sending dialed number on putput now :: "<<number<<endl; 	
		sendOutput( msg.time(), out, number ) ;
	}
	return *this ;
}
