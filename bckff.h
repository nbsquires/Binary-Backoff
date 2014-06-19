/*
Author: Natasha Squires
Title: bckff.h
A simply header file that contains structs, and function protocols
*/
struct station{
        int stationID;
        int waitSlot;
        int wait;
        int transmit;
        int sent;
        int sendTime;
};

struct timeSlot{
        int stnID;
        int time;
};

void transmit(struct station *stations, int loop);
int binary(int n);
int power(int base, int exp);
int fibWait(int n);
int fibonacci(int n);
