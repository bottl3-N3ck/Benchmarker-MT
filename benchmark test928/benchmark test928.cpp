// benchmark test928.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <math.h>
#include <ctime>
#include <future>
using namespace std;
int check = 2;
double a, b, powcheck, k, d, x, y;// x and y are the squares of a and b.
int loop , r , t;
int percentage = 0;// declaring variable to update percentage
double c;
float score[5], totalscore = 0;
thread tmain[25];
// This program prints all the Pythagorean triplets from 1 to k , which the user will enter.
void selection()
{
	int choose;
	unsigned concurentThreadsSupported = thread::hardware_concurrency();
	cout << concurentThreadsSupported << " threads supported" << '\n';
	cout << "Type 1 to start benchmarking." << '\n';
	base:cin >> choose;
	if (choose != 1)
	{
		cout << "Invalid number. Type 1 to start benchmarking" << '\n';
		goto base;
	}
}
void mainbase(int p)
{
	long count;
	double timetake[5];
	// check is meant to find out if we should also include an explaination as to why a triplet is indeed a Pythagorean one.
	// D will represent C for greatest pythagorean triplet purposes.
	// k is the number which the user will enter. This value limits the value of a and b through which the program can search.

	clock_t begin = clock();
	a = 1;
	b = 1;
	c = 1;
	d = 1;
	count = 0;// a and b are the base/height.
	if (p == 1)
		k = 100;
	else if (p == 2)
		k = 250;
	else if (p == 3)
		k = 500;
	else if (p == 4)
		k = 1000;
	else if (p == 5)
		k = 1500;
	while (b <= k)
	{
		while (a <= k)
		{
			x = a*a;
			y = b*b;
			c = x + y;
			powcheck = b;	// b as starting point. Meant to speed up execution
			while (powcheck <= ceil(1.42*k)) // Max value of c with relation to a and b is c = root2 of a , b
			{
				if (c == pow(powcheck, 2))
				{
					if (c >= d)
						d = c;
					++count;
					powcheck = 2 * k + 1;
				}
				else
					++powcheck;
			}
			++a;
		}
		a = 1;
		++b;
	}
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	timetake[p - 1] = elapsed_secs;
	float r;
	if (p == 1)
		r = 0.003;
	if (p == 2)
		r = 0.035;
	if (p == 3)
		r = 0.273;
	if (p == 4)
		r = 2.225;
	if (p == 5)
		r = 7.536;
	score[p - 1] = 200 * (r / timetake[p - 1]);
	totalscore = totalscore + (0.2*(score[p - 1]));
	cout << 20 * (loop-1)+4*p << " % complete!" << '\n';
	cout << "Time taken for that stage:- " << timetake[p - 1] << '\n';
	cout << "Points obtained in that stage:- " << score[p - 1]*5 << '\n';
}
int main()
{
	selection();
	for (loop = 1; loop <= 5; loop++)
	{
		for (t = 1; t <= 5; t++)
		{
			tmain[(t-1)+5*(loop-1)] = thread(mainbase, t);
			cout << "Thread ID:- " << tmain[t - 1].get_id() << '\n';
		}
	}
	cout << "Your system has scored a total of " << totalscore << " points!" << '\n';
	system("pause");
	cout << '\n';
}
