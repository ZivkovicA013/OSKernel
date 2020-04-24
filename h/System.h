/*
 * System.h
 *
 *  Created on: Apr 7, 2020
 *      Author: OS1
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

typedef void interrupt (*pInterrupt)(...);
#include "PCBList.h"
#include "IdleT.h"

class System {
	//valjalo bi da bude unikat

private:

	void SetIntr();
	void MakeMainThread();
	void MakeIdleThread();
	void MakeThreadList();

public:
	System();

	void restore();
    static PCBList * List;


    virtual ~System();

private:

	pInterrupt oldTimmerIntr;

};

#endif /* SYSTEM_H_ */
