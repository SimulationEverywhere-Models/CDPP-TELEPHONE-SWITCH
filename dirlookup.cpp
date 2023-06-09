/*******************************************************************
*
*  DESCRIPTION: Atomic Model Directory Lookup

*
*  AUTHOR: Amir Barylko & Jorge Beyoglonian 
*
*  EMAIL: mailto://amir@dc.uba.ar
*         mailto://jbeyoglo@dc.uba.ar
*
*  DATE: 27/6/1998
*
*******************************************************************/

/** include files **/
#include "dirlookup.h"      // class DirLookup
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: DirLookup
* Description: 
********************************************************************/
DirLookup::DirLookup( const string &name )
: Atomic( name )
, num( addInputPort( "num" ) )
, tone( addInputPort( "tone" ) )
, dc( addInputPort( "dc" ) )
, dialing_in( addInputPort( "dialing_in" ) )
, line_in( addInputPort( "line_in" ) )
, out_to_dial( addOutputPort( "out_to_dial" ) )
, error_out( addOutputPort( "error_out" ) )
, give_line( addOutputPort( "give_line" ) )
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
Model &DirLookup::initFunction()
{
	cout<<"init Function"<<endl;
	phoneList[100] = 0;
	phoneList[101] = 0;
	phoneList[102] = 0;
	phoneList[103] = 0;
	phoneList[104] = 0;
	phoneList[105] = 0;
	phoneList[106] = 0;
	phoneList[107] = 0;
	phoneList[108] = 0;
	phoneList[109] = 0;
	
	output = 0;
	disconnect = false;
	state = IDLE_STATE ;
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &DirLookup::externalFunction( const ExternalMessage &msg )
{
	cout << "DirLookup:External event comes here :: "<< msg.value()<<endl;
	if( msg.port() == num && state == IDLE_STATE)//check number to be dialed, if its valid and not busy already
	{
		int key = (int) msg.value() ;
		itn = phoneList.find(key);
		if(itn != phoneList.end() ){
			cout << "DirLookup:Valid Phone Number ::"<< key << endl; 
			if((*itn).second == 0 ){
				output = VALID;
				//(*itn).second = 1; //change it, don't make it busy at this time
				number = key;
			}
			else {
				output = BUSY;
				cout << "		But Phone Number is Busy."<<endl;
			}
		}
		else {
			cout <<"DirLookup:Invalid phone Number::"<<key <<endl;
			output = INVALID;
		}
		state = BUSY_STATE;
		holdIn( active, processingTime);
	}

	if (msg.port() == tone && state == IDLE_STATE)//make line of caller who pick up phone
	{
		
		int caller = (int)msg.value();
		cout <<"DirLookup:Getting tone of caller , making his line busy::"<<caller <<endl;
		phoneList[caller] = 2;
		state = BUSY_STATE;
		holdIn( active, processingTime);
	}
	if (msg.port() == dialing_in && state == IDLE_STATE)//make line of callee busy
	{
		int callee = (int)msg.value();
		if(callee > 0){ //positive number for ringing
			cout <<"DirLookup:Getting dialing in from dialing module , making his line busy::"<<callee <<endl;
			phoneList[callee] = 1;
			
		}
		else if(callee <0){ // negative number for ring aborted
			callee = callee * -1;
			cout <<"DirLookup:Getting dialing in from dialing module , ring aborted, making his line free::"<<callee <<endl;
			phoneList[callee] = 0;
			disconnect = true;
		}
		state = BUSY_STATE;
		holdIn( active, processingTime);
	}
	if (msg.port() == dc && state == IDLE_STATE)//free line of party who hang up
	{
		int caller = (int)msg.value();
		cout <<"DirLookup:Getting dc of initiator , making his line free::"<<caller <<endl;
		phoneList[caller] = 0;
		if(phoneList[caller] == 2)
			disconnect = true;
		state = BUSY_STATE;
		holdIn( active, processingTime);
	}
	if (msg.port() == line_in && state == WAITING_STATE)	//free line of callee
	{
		cout <<"DirLookup:Getting response of line controller ::"<< msg.value()<<endl;
		if(msg.value() == 1 ){
			output = number ;
		}
		else 
			output = LINE_NOT_FREE ;
		//state = BUSY_STATE;
		holdIn( active, processingTime);
	}
	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &DirLookup::internalFunction( const InternalMessage & )
{
	//cout<<"In internal fucntion :: Status is ::" <<state<<endl;
	//cout<<"In internal fucntion :: output is :: "<<output<<endl;
	if(output == 1){
		state = WAITING_STATE;
		holdIn(active,processingTime);
	}
	else{
		output = 0;
		state = IDLE_STATE;
		passivate();
	}
	
	
	disconnect = false;
	
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &DirLookup::outputFunction( const InternalMessage &msg )
{
	//cout<<"In output fucntion :: Status is :: "<<state<<endl;
	//+"(Busy=-1,Invalid #=-2,line not free=-3)"
	cout<<"In output fucntion :: output is ::" <<output<<endl;
	if(state == WAITING_STATE && output > 0)
		sendOutput( msg.time(), out_to_dial, output) ;
	else if(output < 0)
		sendOutput( msg.time(), error_out, output) ;
	else if (output ==1 || disconnect)
		sendOutput( msg.time(), give_line, output) ;
	return *this ;
}
