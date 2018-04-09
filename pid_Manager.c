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

