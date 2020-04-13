/*
 * PCBNode.h
 *
 *  Created on: Apr 10, 2020
 *      Author: OS1
 */

#ifndef PNODE_H_
#define PNODE_H_

#include "PCB.h"

class PNode {

private:

	PCB* pcb;
	PNode* next;

public:

	PNode(PCB* pcb);

	PNode* GetNext();//Dohvati Sledeci
	void  PrintMe();
	void  SetNext(PNode* node);
	void SetNextNull();
	void SetPCBNull();
	PCB* GetPCB();

	~PNode();
};

#endif /* PNODE_H_ */
