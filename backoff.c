/*
Author: Natasha Squires
Title: backoff.c
A program that simulates the binary exponential backoff algorithm, or the fibonacci 
backoff algorithm
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <sys/time.h>
#include "bckff.h"

int n, numStations;
FILE *fp;

int main(int argc, char *argv[])
{

	if(argc < 3)
	{
		printf("usage: ./binary [no. of stations] ['bin' or 'fib']\n");
		exit(1);	
	}
	
	//fp = fopen("results.dat", "a+");

	numStations = atoi(argv[1]);

	struct station stations[numStations];
	struct timeSlot timeSlots[numStations];

	int i, stationsLeft=numStations, loop=0, ts=0;
	n=1;

	//Array initializing stuff
	for(i=0; i<numStations; i++)
	{
		stations[i].stationID=i+1;
		stations[i].wait = 0;
		stations[i].transmit = 1;
		stations[i].waitSlot = 0;
		stations[i].sent = 0;
	}

	//random generator seeding stuff
	struct timeval start;
	gettimeofday(&start, NULL);
	srand(start.tv_sec*1000000 + start.tv_usec);

	//while there are still stations left to submit a frame
	while(stationsLeft>0)
	{
		transmit(stations,loop); // transmit the stations
		
		//for each station
		for(i=0; i<numStations; i++)
		{
			//if a station is allowed to transmit/retransmit at this time slot
			if(stations[i].waitSlot==loop)
				stations[i].wait=0; //it doesn't have to wait anymore
			else
				stations[i].wait=1; //it still has to wait

			//if a station has been retransmitted, but a collision has been detected
			if(stations[i].transmit==0 && stations[i].wait==0)
			{
				if(strcmp(argv[2], "bin")==0)
					stations[i].waitSlot = binary(n) + (loop+1); //binary backoff
				else if(strcmp(argv[2], "fib")==0)
					stations[i].waitSlot = fibWait(n) + (loop+1); //fibonacci backoff
			}
			//else if a station is allowed to send its frame
			else if(stations[i].transmit==1)
			{
				if(stations[i].sent!=1) //do this stuff only if it hasn't already been sent
				{
					stations[i].sent=1;
					stationsLeft--; //decrement the number of stations left
					//fill in time slot information
					timeSlots[ts].stnID = stations[i].stationID;
					timeSlots[ts].time = stations[i].waitSlot;
					ts++; //increment no. of time slots
				}
			}
		}
		loop++; //increment loop counter (aka current time slot)
	}

	//prints out which station sends at what time slot
	for(i=0; i<numStations; i++)
		printf("station %d sent at time slot %d\n", timeSlots[i].stnID, timeSlots[i].time);

//	fprintf(fp, "%d\n", timeSlots[numStations-1].time);
//	fclose(fp);
	return 0;
}

//transmits the stations
void transmit(struct station *stations, int loop)
{
	int i,j, trnsmt=0, ID;

	//for each station
	for(i=0; i<numStations; i++)
	{
		//if a station is allowed to transmit at the current time slot
		if(stations[i].waitSlot==loop)
		{
			trnsmt++;//increase no. of stations that wish to transmit
			ID = stations[i].stationID;
			//for all other stations
			for(j=i+1; j<numStations; j++)
			{
				//if a collision has been detected
				if(stations[i].waitSlot==stations[j].waitSlot)
				{
					//make it so these stations aren't allowed to send their frames
					stations[i].transmit=0;
					stations[j].transmit=0;
				}
			}
		}
	}

	//if more than one frame wants to transmit at this time slot
	if(trnsmt>1)
		n++; //increase n (for the backoff algorithms)
	//if there's only one frame that wants to transmit at this time slot
	else if(trnsmt==1)
	{
		for(i=0; i<numStations; i++)
		{
			//find the matching station
			if(stations[i].stationID == ID)
				stations[i].transmit=1; //good to go!
		}
	}
}

//the binary exponential backoff algorithm
int binary(int n)
{
	//find the 2^n
        int p = power(2, n);

	//get a random number from in between 0 and 2^n-1
        int sTime = rand() % p;

        return sTime;
}

//Just a way to compute powers since C's function was giving me troubles
int power(int base, int exp)
{
	int p;
	if(exp==0)
		return 1;

	for(p = base; exp > 1; exp--)
		p*=base;

	return p;
}

//the fibonacci backoff algorithm
int fibWait(int n)
{
	//get the nth number for that fibonacci sequence
	int f = fibonacci(n);

	//pick a random number in that interval
	int sTime = rand() % f;

	return sTime;
}

//A function to compute the fibonacci number
int fibonacci(int i)
{
	if(i==0)
		return 0;
	else if(i==1)
		return 1;
	else if(i>1)
		return (fibonacci(i-1)+fibonacci(i-2));
}
