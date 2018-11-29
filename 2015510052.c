#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <semaphore.h>
#include <stdint.h>

void *studentCustomer(void *arg);
void *taxiDriver(void *arg);

// Mutex will be used for critical region problems.
sem_t mutex;
sem_t taxiDriverSemaphore;
sem_t studentCustomerSemaphore;

pthread_t studentCustomerThread;
pthread_t taxiDriver1;
pthread_t taxiDriver2;
pthread_t taxiDriver3;
pthread_t taxiDriver4;
pthread_t taxiDriver5;
pthread_t taxiDriver6;
pthread_t taxiDriver7;
pthread_t taxiDriver8;
pthread_t taxiDriver9;
pthread_t taxiDriver10;

extern int numberOfStudentCustomer;
extern int numberOfTaxiDriver;
extern int totalGeneratedStudentCustomer;
extern int numberOfCarriedStudent;
extern int numberOfEmptySpaceInTaxi;
extern int semValue;

int numberOfStudentCustomer = 0;
int numberOfTaxiDriver = 10;
int totalGeneratedStudentCustomer = 0;
int numberOfCarriedStudent = 0;
int numberOfEmptySpaceInTaxi = 4;
int semValue = 0;

// Check loop
pthread_t endLoop;
char *endChar;

void *killIt(void *arg)
{

	while (1)
	{
		scanf("%s", endChar);
	}
	pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{

	endChar = malloc(sizeof(char *));
	int error = 0;

	sem_init(&mutex, 0, 1);
	sem_init(&taxiDriverSemaphore, 0, 0);
	sem_init(&studentCustomerSemaphore, 0, 0);
	error = pthread_create(&taxiDriver1, NULL, &taxiDriver, (void *)1); /* Create taxidriver 1 */
	if (error != 0)
	{

		printf("Thread creation error: [%s]", strerror(error));
	}
	// printf("TaxiDriver1 created.\n");
	error = pthread_create(&taxiDriver2, NULL, &taxiDriver, (void *)2); /* Create taxidriver 2 */
	if (error != 0)
	{

		printf("Thread creation error: [%s]", strerror(error));
	}
	// printf("TaxiDriver2 created.\n");
	error = pthread_create(&taxiDriver3, NULL, &taxiDriver, (void *)3); /* Create taxidriver 3 */
	if (error != 0)
	{

		printf("Thread creation error: [%s]", strerror(error));
	}
	// printf("TaxiDriver3 created/.\n");
	error = pthread_create(&taxiDriver4, NULL, &taxiDriver, (void *)4); /* Create taxidriver 4 */
	if (error != 0)
	{

		printf("Thread creation error: [%s]", strerror(error));
	}
	// printf("TaxiDriver4 created.\n");
	error = pthread_create(&taxiDriver5, NULL, &taxiDriver, (void *)5); /* Create taxidriver 5 */
	if (error != 0)
	{

		printf("Thread creation error: [%s]", strerror(error));
	}
	// printf("TaxiDriver5 created.\n");
	error = pthread_create(&taxiDriver6, NULL, &taxiDriver, (void *)6); /* Create taxidriver 6 */
	if (error != 0)
	{

		printf("Thread creation error: [%s]", strerror(error));
	}
	// printf("TaxiDriver6 created.\n");
	error = pthread_create(&taxiDriver7, NULL, &taxiDriver, (void *)7); /* Create taxidriver 7 */
	if (error != 0)
	{

		printf("Thread creation error: [%s]", strerror(error));
	}
	// printf("TaxiDriver7 created.\n");
	error = pthread_create(&taxiDriver8, NULL, &taxiDriver, (void *)8); /* Create taxidriver 8 */
	if (error != 0)
	{

		printf("Thread creation error: [%s]", strerror(error));
	}
	// printf("TaxiDriver8 created.\n");
	error = pthread_create(&taxiDriver9, NULL, &taxiDriver, (void *)9); /* Create taxidriver 9 */
	if (error != 0)
	{

		printf("Thread creation error: [%s]", strerror(error));
	}
	// printf("TaxiDriver9 created.\n");
	error = pthread_create(&taxiDriver10, NULL, &taxiDriver, (void *)10); /* Create taxidriver 10 */
	if (error != 0)
	{

		printf("Thread creation error: [%s]", strerror(error));
	}
	// printf("TaxiDriver10 created.\n");
	error = pthread_create(&endLoop, NULL, &killIt, (void *)endChar); /* Another thread for killing process */
	if (error != 0)
	{

		printf("Thread creation error: [%s]", strerror(error));
	}

	sleep(3);

	int random = 0;
	while (totalGeneratedStudentCustomer < 100)
	{

		srand(time(NULL));
		random = rand() % 15;

		if (random % 5 == 0 || random % 7 == 0)
		{ /* Randomly creating customer student. */

			error = pthread_create(&studentCustomerThread, NULL, &studentCustomer, (void *)(5 + 1));

			if (error != 0)
			{

				printf("Thread creation error: [%s]", strerror(error));
			}
		}
		sleep(1);
	}

	sem_destroy(&mutex);
	sem_destroy(&taxiDriverSemaphore);
	sem_destroy(&studentCustomerSemaphore);
}
void *studentCustomer(void *arg)
{

	// printf("Customer student has been created\n");

	sem_wait(&mutex);		   /* For mutex, lock the critical section. */
	numberOfStudentCustomer++; /* Number of customer in queue. */
	totalGeneratedStudentCustomer++;
	printf("Total Generated Number Of Customer Student: %d\n", totalGeneratedStudentCustomer);
	sem_post(&mutex);

	if (numberOfStudentCustomer == 1) {
		// Wake up taxiDriver by enter the first student.
		sem_post(&taxiDriverSemaphore);
	}
	else {
		// Not enter the first student. Wait until full the taxi.
		while (numberOfStudentCustomer != 4)
		;
	}

	pthread_exit(NULL);
}
void *taxiDriver(void *arg)
{

	int sleepTime = 0;

	while (numberOfCarriedStudent < 100)
	{
		printf("Returned Taxi ID: %ld \n",(intptr_t)arg);
		sem_wait(&taxiDriverSemaphore);
		// sem_getvalue(&taxiDriverSemaphore, &semValue);
		// printf("Semaphore value: %d\n",semValue);


		while (numberOfStudentCustomer < 4 && numberOfStudentCustomer != 0) 
		{
			printf("Heyyyyy need %d to go!! Taxi ID: %ld \n", 4-numberOfStudentCustomer,(intptr_t)arg);
			sleep(1);

		}
		if(numberOfStudentCustomer == 4)
		{
			sem_wait(&mutex);
			numberOfStudentCustomer =0;
			numberOfCarriedStudent += 4;
			sem_post(&mutex);
			// sem_post(&taxiDriverSemaphore);


			printf("Carried 4 students!!!!!!!!!!\n");
			sleep(1);


			// Time for carry students.
			srand(time(NULL));
			sleepTime = rand() % 35;
			sleep(sleepTime);
		}

	}
	pthread_exit(NULL);
}
