#include "System.h"
#include "PCB.h"
#include "Thread.h"
#include "UThreadA.h"
#include "UThreadB.h"
#include "Semap.h"
#include "KerSem.h"
#include <stdio.h>


extern int userMain(int argc, char** argv);

int main(int argc,char** argv){

	System* sys=new System();

	lock;
	printf("USER MAIN STARTS \n");
	unlock;
	int i,j,k;


	int x=userMain(argc,argv);


    lock;
	printf("USER MAIN ENDS! \n");
	unlock;


	for ( i = 0; i <15; i++) {
		lock;
		printf("U main sam \n");
		unlock;
		for (j = 0; j< 10000; ++j)
			for ( k = 0; k < 30000; ++k);
	}



	lock;
	printf("System END! \n");
	unlock;

	sys->restore();

}
