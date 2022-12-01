#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#define ropeSize 86
#define maxSize 21
#define minSize 9

char *rope;
int currentPosition;
int threadTime;
long timeSleep;
void *toTheStart(void *arg);
void *toTheEnd(void *arg);
pthread_mutex_t buffer_mutex;
pthread_t threadToTheStart;
pthread_t threadToTheEnd;



void __initRope__(){

    for (int i = 0; i < ropeSize; i++){
        rope[i] = '_';
    }
    rope[ropeSize-1] = '\0';
    rope[41] = 'F';
    rope[42] = 'D';
    rope[43] = 'D';       
    currentPosition = 41;

}

//Create the left team
void *toTheStart (void *arg){
    while(1){
        if(currentPosition > 0){
            pthread_mutex_lock(&buffer_mutex);
            rope[currentPosition - 1 ] = 'F';
            rope[currentPosition] = 'D';
            rope[currentPosition + 1] = 'D';
            rope[currentPosition + 2] = '_';
            currentPosition--;
            pthread_mutex_unlock(&buffer_mutex);
            usleep(timeSleep);
        }

    }

}
 
//Create the right team
void *toTheEnd (void *arg){
    while(1){
        if((currentPosition + 2) < 84){
            pthread_mutex_lock(&buffer_mutex);
            rope[currentPosition] = '_';
            rope[currentPosition + 1] = 'F';
            rope[currentPosition + 2] = 'D';
            rope[currentPosition + 3] = 'D';
            currentPosition++;
            pthread_mutex_unlock(&buffer_mutex);
            usleep(timeSleep);

        }

    }

}


int main(){

    //Create the rope
    rope = (char *) malloc(ropeSize * sizeof(char));
    __initRope__(rope);

    //Create a random numbers of threads and sleep time
    int q1, q2;
    srand48(time(0));
    q1 = (int) (drand48()*(maxSize - minSize + 1)) + minSize;
    q2 = (int) (drand48()*(maxSize - minSize + 1)) + minSize;
    timeSleep = (long) (drand48() * 201910638/67.0);

    //Create the threads
    pthread_mutex_init(&buffer_mutex, NULL);
    for(int i = 0; i < q1; i++) {
		pthread_create(&(threadToTheStart), NULL, toTheStart, NULL);
	}
    for(int i = 0; i < q2; i++) {
		pthread_create(&(threadToTheEnd), NULL, toTheEnd, NULL);
	}

    //Thread main
    while(1){

        printf("%d threads to the start e %d to the end \n",q1,q2);
        printf("%s\n", rope);
        system("clear");
        if((currentPosition + 2) >= 84){
            printf("To The End Wins\n");
            break;
        }else if(currentPosition <= 0){
            printf("To The Start Wins\n");
            break;
        }
        usleep(2);

    }
    printf("\n%d threads to the start e %d to the end\n",q1,q2);
    printf("\n%s\n", rope);









}




