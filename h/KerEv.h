/*
 * KerEv.h
 *
 *  Created on: Apr 29, 2020
 *      Author: OS1
 */

#ifndef KEREV_H_
#define KEREV_H_

#include"PCB.h"

typedef unsigned char IVTNo;

class KernelEv {
public:
	KernelEv(IVTNo intnum);
	virtual ~KernelEv();

	void wait();
	void signal();

private:

	int myBoss;
	PCB* myBossPCB;

	int val;
	int blocked;
	int ivtn;


};

#endif /* KEREV_H_ */
