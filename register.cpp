/*******************************************************************
*
*  DESCRIPTION: Simulator::registerNewAtomics()
*
*  AUTHOR: Amir Barylko & Jorge Beyoglonian 
*
*  EMAIL: mailto://amir@dc.uba.ar
*         mailto://jbeyoglo@dc.uba.ar
*
*  DATE: 27/6/1998
*
*******************************************************************/

#include "modeladm.h" 
#include "mainsimu.h"
#include "queue.h"      // class Queue

#include "phone.h"      // class Queue
#include "touchtone.h"      // class Queue
#include "dialing.h"      // class Queue
#include "linecont.h"      // class Queue
#include "dirlookup.h"      // class Queue

#include "generat.h"    // class Generator
#include "cpu.h"        // class CPU
#include "transduc.h"   // class Transducer
#include "trafico.h"    // class Trafico


void MainSimulator::registerNewAtomics()
{
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Queue>() , "Queue" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Generator>() , "Generator" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<CPU>() , "CPU" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Transducer>() , "Transducer" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Trafico>() , "Trafico" ) ;
	
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Phone>() , "Phone" ) ;
SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<TouchTone>() , "TouchTone" ) ;
SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<DirLookup>() , "DirLookup" ) ;
SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<LineCont>() , "LineCont" ) ;
SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Dialing>() , "Dialing" ) ;
}
