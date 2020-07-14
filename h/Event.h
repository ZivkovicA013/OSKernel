/*
 * Event.h
 *
 *  Created on: Apr 29, 2020
 *      Author: OS1
 */

#ifndef EVENT_H_
#define EVENT_H_

typedef unsigned char IVTNo;

#include "KerEv.h"
#include "IVTEnt.h"

//Wait moze da pozove samo ona nit koja je napravila taj dogadjaj,ostali pozivi se ignorisu.
//prvo ivt entrt pa kernel event
//prep ent

class Event {
public:

	Event(IVTNo ivtNo);

	void wait();

	virtual ~Event();

protected:

	friend class KernelEv;
	void signal();//can call KernelEv



private:
	KernelEv* myImpl;
};
#define PREPAREENTRY(no, flag)\
void interrupt intr##no(...);\
IVTEntry ivte##no(no, intr##no);\
void interrupt intr##no(...){\
        ivte##no.signal();\
        if (flag) ivte##no.calloldInterrupt();\
}\

#endif /* EVENT_H_ */
