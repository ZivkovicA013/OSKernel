/*
 * IVTEnt.h
 *
 *  Created on: Apr 30, 2020
 *      Author: OS1
 */

#ifndef IVTENT_H_
#define IVTENT_H_

typedef void interrupt (*ppInterrupt)(...);
typedef unsigned char IVTNo;

#include"KerEv.h"


class IVTEntry {

private:
	KernelEv* kerEvent;
	ppInterrupt oldInterrupt;
	IVTNo number;


public:

	static IVTEntry* IVT[256];

	void SetKernelEvent(KernelEv* event);
	void calloldInterrupt();
	void signal();

	IVTEntry(IVTNo num,ppInterrupt newIntr);
	virtual ~IVTEntry();
};




#endif /* IVTENT_H_ */

