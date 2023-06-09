/*******************************************************************
*
*  DESCRIPTION: Atomic Model Phone
*
*  AUTHOR: M Asif && Khuuram Shahzad
*
*  DATE: 10/10/2003
*
*******************************************************************/

/** include files **/
#include "phone.h"      // class Phone
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: Phone
* Description: 
********************************************************************/
Phone::Phone( const string &name )
: Atomic( name )
, in( addInputPort( "in" ) )
, out( addOutputPort( "out" ) )
, processingTime( 0, 0, 10, 0 )
{
	string time( MainSimulator::Instance().getParameter( description(), "processTime" ) ) ;

	if( time != "" )
		processingTime = time ;
}

/*******************************************************************
* Function Name: initFunction
* Description: 
* Precondition: 
********************************************************************/
Model &Phone::initFunction()
{
	num = 0 ; 
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &Phone::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == in )
	{
		num = (int) msg.value(); 
		holdIn( active, processingTime );
	}

	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &Phone::internalFunction( const InternalMessage & )
{
	passivate();
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &Phone::outputFunction( const InternalMessage &msg )
{
	sendOutput( msg.time(), out, num);
	return *this ;
}
