/*
 * UThreadB.cpp
 *
 *  Created on: Apr 9, 2020
 *      Author: OS1
 */

#include "UThreadB.h"

#include <stdio.h>



#include "UThreadA.h"
#include <stdio.h>

#define lock asm cli

#define unlock asm sti

UThreadB::UThreadB(StackSize stackSize,Time timeSlice):Thread(stackSize,timeSlice) {
	// TODO Auto-generated constructor stub

}

UThreadB::~UThreadB() {
	//this->waitToComplete();
}

void UThreadB::run(){

	int i,j,k;


	for (i =0; i < 10; i++) {
			lock;
			printf("u B %d ID niti je %d \n",i,this->getId());
			unlock;
			for ( k = 0; k<10000; ++k)
						for (j = 0; j <30000; ++j);

		}

}
