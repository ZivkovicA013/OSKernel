/*
 * System.cpp
 *
 *  Created on: Apr 7, 2020
 *      Author: OS1
 */


#include <dos.h>
#include "System.h"
#include <stdio.h>


#define lock asm cli
#define unlock asm sti




//Potpuna inicijalizacija kernela,promena prekidnih rutina
//Sva neophodna inicijalizacija
//Liste PCB,Niti

PCBList* System::List=0;


System::System() {
	// TODO Auto-generated constructor stub
	this->oldTimmerIntr=0;

}

System::~System() {
	// TODO Auto-generated destructor stub
}


void System::init(){


//postavlja novu prekidnu rutinu
	lock;

	#ifndef BCC_BLOCK_IGNORE
		oldTimmerIntr=getvect(0x08);
		setvect(0x08,PCB::timer);
		setvect(0x60,oldTimmerIntr);
	#endif

	unlock;

}

void System::restore(){
//vraca staru tajmer prekidnu rutinu u predjasnje stanje
	lock
#ifndef BCC_BLOCK_IGNORE
	setvect(0x08,oldTimmerIntr);
#endif
	unlock
}


void System::MakeThreadList(){

	System::List=new PCBList();

}

void System::MakeMainThread(){


	Thread::SetUpMainThread();
	printf("Postavljen main PCB \n");
}


