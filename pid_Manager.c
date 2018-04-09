#include<assert.h>

#include<stdio.h>

#include<pthread.h>

#include<time.h>



#define MIN_PID 100

#define MAX_PID 1000



pthread_mutex_t _mutexLock;



struct process
{

	int _pid,_isAllocated;

}

_array[MAX_PID-MIN_PID];



int allocate_map() 
{

	int i=MIN_PID;

	while(i<=MAX_PID)
        {

		_array[i-MIN_PID]._pid=i;

		_array[i-MIN_PID]._isAllocated=0;

		i++;

	}

	return 1;

}



int allocate_pid() 
{

	int i=0;

	while(i<MAX_PID)
        {

		if (_array[i]._isAllocated==0) 
                {

			pthread_mutex_lock(&_mutexLock);

			_array[i]._isAllocated=1;

			pthread_mutex_unlock(&_mutexLock);

			return _array[i]._pid;

		}
		i++;

	}

	return -1;

}



void release_pid(int _pid) 
{

	int i=0;

	while(i<MAX_PID) 
        {

		if(_array[i]._pid==_pid) 
                {

			int _res=pthread_mutex_lock(&_mutexLock);

			assert(_res==0);

			_array[i]._isAllocated=0;

			_res=pthread_mutex_unlock(&_mutexLock);

			break;

		}

		i++;

	}

}
void* processFunc(void *_args) 
{

	int _pid=allocate_pid();

	printf("New process created : %d\n",_pid);

	int _time=(rand()+20)%(40+1);

	sleep(_time);

	release_pid(_pid);

	printf("Process destroyed : %d\n",_pid);

}



void createProcess() 
{

	int i=0;

	pthread_t _arrayPid[15];

	if(pthread_mutex_init(&_mutexLock,NULL)!=0)

		printf("Mutex init.");

	while(i<15) 
        {

		pthread_create(&_arrayPid[i],NULL,processFunc,NULL);

		sleep(1);

		i++;

	}

	
	i=0;

	while(i<15) 
        {

		pthread_join(_arrayPid[i],NULL);

		i++;

	}

}


