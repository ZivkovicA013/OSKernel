/*
 * Event.cpp
 *
 *  Created on: Apr 29, 2020
 *      Author: OS1
 */

#include "Event.h"
#include "IVTEnt.h"

Event::Event(IVTNo ivtNo) {
	// TODO Auto-generated constructor stub
	asm cli;
	this->myImpl=new KernelEv(ivtNo);
	IVTEntry::IVT[ivtNo]->SetKernelEvent(this->myImpl);
	asm sti;

}

Event::~Event() {
	asm cli;
	//delete this->myImpl;
	asm sti;
}

void Event::signal() {
	this->myImpl->signal();
}

void Event::wait(){
	this->myImpl->wait();
}
