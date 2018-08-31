// benchmark test928.cpp : Defines the entry point for the console application.
// NOTE: works, but has bugs with score generation. Also crashes at end of test.
#include "stdafx.h"
#include <iostream>
#include <thread>
#include <math.h>
#include <ctime>
#include <future>
#include <conio.h>
#include <chrono>
#include <mutex>
#include <Windows.h>
using namespace std;
int check = 2;
static mutex m;
double a, b, powcheck, k, d, x, y;// x and y are the squares of a and b.
int loop, r, t,sel;
float percentage = 0.00;// declaring variable to update percentage
double c;
float score[5], totalscore = 0.00, partscore[3] = {0.00,0.00,0.00};
thread tmain[100];
void mainbase(int,int);
void selection()
{
	
		int choose;
		unsigned concurentThreadsSupported = thread::hardware_concurrency();
		cout << concurentThreadsSupported << " threads supported" << '\n';
	base:cout << "Type 1 to start benchmarking." << '\n';
		try
		{
		cin >> choose;
		if (cin.fail())
			throw 2;
		if (choose != 1)
		{
			throw "Invalid number. \n";
		}
	}
	catch (char* msg)
	{
		cout << msg << '\n';
		goto base;
	}
	catch (int x)
	{
		cout << "Invalid entry entered. Program cannot continue and will close. \n";
		_getch();
		exit(1);
	}
}
void main2()
{
	for (int time = 0; time < 3; time++)
	{
		for (loop = 1; loop <= 5; loop++)
		{
			for (t = 1; t <= 5; t++)
			{
				tmain[(time * 25) + ((t - 1) + 5 * (loop - 1))] = thread(mainbase,t,time);
				lock_guard <mutex> g(m);
				cout << "Thread ID:- " << tmain[(time + 1)*((t - 1) + 5 * (loop - 1))].get_id() << '\n';
				if (time == 0)
					this_thread::sleep_for(1s);
				else if (time == 1)
					this_thread::sleep_for(2s);
			}
		}
		// get score for relevant part
	}
	_getch();
}
void mainbase(int p, int sel)
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
			x = a * a;
			y = b * b;
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
	partscore[sel] += score[p - 1];
	totalscore = totalscore + (1 / 15 * (score[p - 1]));
	percentage += 1.33;
	lock_guard <mutex> g(m);
	cout << ceil(percentage) << " % complete!" << '\n';
	cout << "Time taken for that stage:- " << timetake[p - 1] << '\n';
	cout << "Points obtained in that stage:- " << score[p - 1] * 5 << '\n';
}
int main()
{
	try
	{
		selection();
		main2();
		cout << '\n' << '\n';
		// /5 is not intentional; program gives output 5 times greater for some reason
		cout << "Score in Part A:" << partscore[0]/5 << '\n';
		cout << "Score in Part B:" << partscore[1]/5 << '\n';
		cout << "Score in Part C:" << partscore[2]/5 << '\n';
		// gives 0 for some reason
		cout << "Your system has scored a total of " << totalscore << " points!" << '\n';
		cout << '\n';
			// kill all threads
			tmain->detach();
			delete tmain;
			// crashes with heap corruption message
			_getch();
			delete[] tmain;
		}
		catch (exception e)
		{
			cout << "ERROR detected";
			exit(1);
		}
}
