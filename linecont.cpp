/*******************************************************************
*
*  DESCRIPTION: Atomic Model Line Controller
*
*  AUTHOR: M Asif & Khurram
*
*
*  DATE: 16/10/2003
*
*******************************************************************/

/** include files **/
#include "linecont.h"      // class LineCont
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: LineCont
* Description: 
********************************************************************/
LineCont::LineCont( const string &name )
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
* Description: Resetea la lista
* Precondition: El tiempo del proximo evento interno es Infinito
********************************************************************/
Model &LineCont::initFunction()
{
	output = 0;
	lines = 3;
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &LineCont::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == in )
	{
		if (msg.value() == 1) // To get a line 
		{
			cout<<"LineCont: asked for line "<<endl;
			if(lines > 0){ // if line is available 
				cout<<"LineCont: line is available "<<endl;
				output = LINE;
				lines--;
			}
			else{
				cout<<"LineCont: No line available "<<endl;
				output = NO_LINE;
			}
		
		}
		else if(msg.value() == 0) //To make a line free
		{
			cout<<"LineCont: freeing line" <<endl;
			lines++;
		}
		
		holdIn( active, processingTime);
	}



	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &LineCont::internalFunction( const InternalMessage & )
{
	output = 0;
	passivate();
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &LineCont::outputFunction( const InternalMessage &msg )
{
	if(output == 1 || output == -1)
		sendOutput( msg.time(), out, output) ;
	return *this ;
}
