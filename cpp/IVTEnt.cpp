/*
 * IVTEnt.cpp
 *
 *  Created on: Apr 30, 2020
 *      Author: OS1
 */

#include "IVTEnt.h"
#include <dos.h>
#include <stdio.h>


IVTEntry* IVTEntry::IVT[256];
IVTEntry::IVTEntry(IVTNo num,ppInterrupt newIntr) {
	asm cli;
	this->number=num;
	this->kerEvent=0;

#ifndef BCC_BLOCK_IGNORE
	oldInterrupt=getvect(num);
	setvect(num,newIntr);
#endif

	IVT[num]=this;

	asm sti;
}

void IVTEntry::SetKernelEvent(KernelEv* event) {
	this->kerEvent=event;
}

void IVTEntry::calloldInterrupt() {
	this->oldInterrupt();
}

void IVTEntry::signal() {
	if(this->kerEvent==0)
		return;

	this->kerEvent->signal();
}

IVTEntry::~IVTEntry() {

	IVT[number]=0;

#ifndef BCC_BLOCK_IGNORE
	setvect(number,oldInterrupt);

#endif
}


