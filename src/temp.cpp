#include "System.h"
#include "PCB.h"
#include "Thread.h"
#include "UThreadA.h"
#include "UThreadB.h"
#include <stdio.h>


class TestThread : public Thread
{
private:
	TestThread *t;

public:

	TestThread(TestThread *thread): Thread(), t(thread){}
	~TestThread()
	{
		this->waitToComplete();
	}
protected:

	void run();

};

void TestThread::run()
{
	t->waitToComplete();
}



int main(){

	System* sistem=new System();
	lock;
	printf("USER MAIN STARTS \n");
	unlock;
	//USER MAIN/////////////////////////////////////////////////

	int i,j,k;
	TestThread *t1,*t2;
	t1 = new TestThread(t2);
	t2 = new TestThread(t1);
	t1->start();
	t2->start();

	delete t1;
	delete t2;

	//END USER MAIN////////////////////////////////////////////

	lock;
	printf("USER MAIN ENDS! \n");
	unlock;


	for ( i = 0; i <20; i++) {
		lock;
		printf("U main sam \n");
		unlock;
		for (j = 0; j< 10000; ++j)
			for ( k = 0; k < 30000; ++k);
	}



	lock
	printf("System END! \n");
	unlock

	sistem->restore();

}
