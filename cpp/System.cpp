/*
 * System.cpp
 *
 *  Created on: Apr 7, 2020
 *      Author: OS1
 */

#include <stdio.h>
#include <dos.h>
#include "System.h"



#define lock asm cli
#define unlock asm sti




//Potpuna inicijalizacija kernela,promena prekidnih rutina
//Sva neophodna inicijalizacija
//Liste PCB,Niti

PCBList* System::List=0;
SEMList* System::Sem_List=new SEMList();


System::System() {
	// TODO Auto-generated constructor stub
	this->oldTimmerIntr=0;

	this->SetIntr();
	this->MakeMainThread();
	this->MakeThreadList();
	this->MakeIdleThread();

}

System::~System() {
	// TODO Auto-generated destructor stub
	lock
	delete this->List;
	unlock
}

void System::SetIntr(){

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

	delete this->Sem_List;
	delete this->List;

}

void System::MakeSemaphoreList(){

	System::Sem_List=new SEMList();
}

void System::MakeThreadList(){

	System::List=new PCBList();

}

void System::MakeMainThread(){

	Thread::SetUpMainThread();
}

void System::MakeIdleThread(){

	new IdleT(4096,1);

}

