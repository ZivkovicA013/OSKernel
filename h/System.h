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

class System {
	//valjalo bi da bude unikat
public:
	System();
	virtual ~System();

	void init();
	void restore();
	void MakeMainThread();
	void MakeThreadList();

    static PCBList * List;


private:

	pInterrupt oldTimmerIntr;

};

#endif /* SYSTEM_H_ */
