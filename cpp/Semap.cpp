/*
 * Semap.cpp
 *
 *  Created on: Apr 25, 2020
 *      Author: OS1
 */

#include "Semap.h"
#include "System.h"
#include <stdio.h>

Semaphore::Semaphore(int init) {
	// TODO Auto-generated constructor stub
	this->myImpl=new KernelSem(init);
	System::Sem_List->AddNode(this);


}

int Semaphore::wait(Time maxTimeToWait) {
	this->myImpl->wait(maxTimeToWait);
	return 0;
}

int Semaphore::signal(int n) {
	this->myImpl->signal(n);
	return 0;
}

int Semaphore::val() const {
	return this->myImpl->val();
}
KernelSem* Semaphore::GetMyImpl(){
	return this->myImpl;
}

Semaphore::~Semaphore() {
	// TODO Auto-generated destructor stub
	//delete this->myImpl;
}

