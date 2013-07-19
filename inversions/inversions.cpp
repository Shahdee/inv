#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int SortAndCalc(vector<int>, int, int, int);
int Merge(vector<int>, int , int , int , int);

int _tmain(int argc, _TCHAR* argv[])
{
	ifstream file;
	
	vector<int> arr;
	vector<int>::iterator it;
	
	int ctr;

	file.open("5.txt");
	if(file.is_open())
	{
		string line;
		while(file.good())
		{
			getline(file, line);
			arr.push_back( atoi(line.c_str()));
		}
		
		ctr = SortAndCalc(arr, arr.size(), 0 , arr.size()-1);

		cout<<"Number of inversions equals to: "<<ctr<<"\n";
		
	}
	return 0;
}



int SortAndCalc(vector<int> arr, int length, int borderfrom, int borderto)
{
	int x=0,y=0,z=0;

	if(length==0)
	{
		return 0;
	}
	else
	{
		if((length%2 == 0) || length==1 || (length/2==1 && length%2==0))
		{
			x = SortAndCalc(arr, length/2, borderfrom, borderfrom + length/2-1);
			y = SortAndCalc(arr, length/2, borderfrom + length/2, borderfrom+length-1);
			z = Merge(arr, borderfrom, borderfrom + length/2-1, borderfrom + length/2, borderfrom+length-1); 
		}
		else
		{
			if(length%2 != 0)
			{
				x = SortAndCalc(arr, length/2, borderfrom, borderfrom + length/2-1);
				y = SortAndCalc(arr, length/2+1, borderfrom + length/2, borderfrom+length-1);
				z = Merge(arr, borderfrom, borderfrom + length/2-1, borderfrom + length/2, borderfrom+length-1);
			}
		}

		return x+y+z;
	}
}


int Merge(vector<int> arr, int firstBegin, int firstEnd, int secondBegin, int secondEnd)
{
	if(firstBegin <= firstEnd && secondBegin <= secondEnd)
	{
		int inv = 0;
		int k=0;
		int l=0;

		int part1L = firstEnd-firstBegin+1;
		int part2L = secondEnd-secondBegin+1;

		vector<int>::iterator first = arr.begin() + firstBegin;
		vector<int>::iterator last = arr.begin() + firstEnd+1;//!

		std::vector<int> part1(first, last);

		first =arr.begin()+secondBegin;
		last = arr.begin()+secondEnd+1; //!

		std::vector<int> part2(first, last);

		for(int i=firstBegin; i<=secondEnd; i++)
		{
			if(k<part1L && l<part2L)
			{
				if(part1[k]<part2[l])
				{
					arr[i] = part1[k];
					k++;
				}
				else
				{
					if(part1[k] == part2[l])
					{
						arr[i] = part1[k];
						k++;
					}
					else
					{
						inv += firstEnd-(firstBegin + k)+1; 
						arr[i] = part2[l];
						l++;
					}
				}
			}
			else
			{
				if(l<part2L)
				{
					arr[i] = part2[l];
					l++;
				}
				else
				{
					if(k<part1L)
					{
						arr[i] = part1[k];
						k++;
					}
				}
			}
		}
		return inv;
	}
	return 0;
}



