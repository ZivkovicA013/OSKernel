/*
 * SEMList.h
 *
 *  Created on: Apr 25, 2020
 *      Author: OS1
 */

#ifndef SEMLIST_H_
#define SEMLIST_H_

#include"Semap.h"

class SEMList {
private:

	struct SEMNode{

		Semaphore* mySEM;
		SEMNode* next;
		int deleted;//1->yes 0->no
		SEMNode(Semaphore* s):mySEM(s),next(0),deleted(0){};

		~SEMNode(){
		}

	};

	SEMNode* ListHead;
	SEMNode* ListTail;

public:

	SEMList();

	void AddNode(Semaphore* s);
	void PrintAll();

	SEMNode* GetHead();
	int IsEmpty();



	virtual ~SEMList();
};

#endif /* SEMLIST_H_ */
