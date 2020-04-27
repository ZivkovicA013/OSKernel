/*
 * IdleT.cpp
 *
 *  Created on: Apr 18, 2020
 *      Author: OS1
 */

#include "IdleT.h"
#include <stdio.h>

IdleT::IdleT(StackSize stackSize,Time timeSlice):Thread(stackSize,timeSlice) {

	PCB::idleThread=this->myPCB;

}

IdleT::~IdleT() {
	// TODO Auto-generated destructor stub
}

void IdleT::run(){

	int j,k;

		while(1) {
				lock;
				//printf("IDLE \n");
				unlock;
				for ( k = 0; k<10000; ++k)
							for (j = 0; j <30000; ++j);

			}


}
