/* 
 * A wonderful number is defined as a natural number (> 1) where the sum of the prime factors
 * is equal to the sum of the exponents of those same factors. 
 *
 * Program finds all wonderful numbers that are less than some cap (denoted cap). 
 * 
 * Program out puts the number of wonderful numbers and then lists all of them. 
 */

#include<iostream>
#include<cmath>
#include<vector>

using namespace std;

void getPrimeNumbers(vector<int> &primes, int cap);
bool prime(int num, vector<int> primes);
bool wonderful(int num, vector<int> primes);
void getWonderfulNumCap(int &cap);


int main ()
{
vector<int> primes; 
vector<int> wonderful_nums;
int k;
int cap; 
int numWonderfulNums;

getWonderfulNumCap(cap);
getPrimeNumbers(primes, cap);


for (k=2; k < cap; k++)
	{
	if (wonderful(k, primes))
		wonderful_nums.push_back(k);
	}
	
numWonderfulNums = wonderful_nums.size();
	
cout<<"There are exactly " << numWonderfulNums << " wonderful numbers < " << cap<<"."<<endl;

for(k=0; k < numWonderfulNums; k++)
	cout<<wonderful_nums.at(k)<<endl;

}

void getPrimeNumbers(vector<int> &primes, int cap)
{
int k;

for(k=2; k < cap; k++)
	{
	if (prime(k, primes))
		primes.push_back(k);
	}
}

bool prime(int num, vector<int> primes)
{
int k;
int numPrimes = primes.size();
bool r = true;

for (k=0; k < numPrimes && r; k++)
	{
	if (num % primes.at(k) == 0)
		r = false;
	}


	
return r;
}

bool wonderful(int num, vector<int> primes)
{
bool wonderful = false;
vector<int> factorization;
vector<int> exponents;
int sumExps = 0;
int sumPrimeFactors = 0;
int k;
int count = 0;
int numPrimes = primes.size();

while (num > 1)
	{
	for(k=0; k < numPrimes && num > 1; k++)
		{
		if (num % primes.at(k) == 0)
			{
			factorization.push_back(primes.at(k));
			exponents.push_back(0);
			
			while (num % primes.at(k) == 0)
				{
				num /= primes.at(k);
				exponents.at(count)++;
				}
				
			count++;
			}
		}
	}
	

while (!factorization.empty())
	{
	sumPrimeFactors += factorization.back();
	factorization.pop_back();
	}
	
while(!exponents.empty())
	{
	sumExps += exponents.back();
	exponents.pop_back();
	}
		
		
	if (sumPrimeFactors == sumExps)
		wonderful = true;
				
return wonderful;
}

void getWonderfulNumCap(int &cap)
{
cout<<"Enter the exclusive upper bound for wonderful numbers for which you are looking: ";
cin>>cap;

while (cap < 3)
	{
	cout<<"The exclusive upper bound must be at least 3. Enter a valid upper bound: ";
	cin>> cap;
	}
}