/*
 * Program that finds the most expensive flight among all of the cheapest flights between a 
 * distinct pair of cities. 
 *
 * Input: (No prompts for input. User will enter input in order given below. Input on same
 *	       will be separated by a space).
 * 
 * c f (c = number of cities, f = number of flights)
 * 
 * Next f lines will take in the source city (x), destination city (y), and price of each flight (p).
 * x y p
 *
 */
#include<iostream>

using namespace std;

struct Node
	{
	int inP;
	int predecessor;
	int w;
	};
	
int checkP(struct Node cities[], int c);
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
int main ()
{
int c; // number of cities, 2<=c<=230
int f; // number of flights, 1<=f<=23665
int k; //scratch variable
int j;

int x; //first city
int y; //second city
int p; //price of flight

int s;// source city for Dijkstra's Algorithm
int m; //minimum vertex not in P
int mostExpensiveFlight;

system("clear");
cout<<"Enter the number of cities and number of flights in that order: "; 
cin>> c;
cin>> f;

int flights[c][c]; //array of flights between the cities
int cheapest_flight[c][c];
struct Node cities[c]; //array used to find cheapest flights between city S to all other cities


for (k=0; k < c; k++)
	{
	for (j=0; j < c; j++)
		{
		flights[k][j] = 0;
		cheapest_flight[k][j] = 0;
		}
	}

for (k=0; k < f; k++)	
	{
	cout<<"Enter the cities and price of each flight: ";
	cin>>x;
	cin>>y;
	cin>>p;
	
		
	flights[x-1][y-1] = p;
	flights[y-1][x-1] = p;
	}
	
for (s = 0; s < c; s++) //Use Dijkstra's Algorithm to find cheapest flight from s to all other cities
	{
	for (k=0; k < c; k++)
		{
		if (k == s)
			{
			cities[k].w = 0;
			cities[k].predecessor = -1;
			cities[k].inP = 1;
			}
			
		else
			{
			cities[k].w = flights[s][k];
			cities[k].predecessor = s;
			cities[k].inP = 0;
			}
		}
		
	while (!checkP(cities, c))//step 3 of Dijkstra's Algorithm
		{
		m = -1;
		for (k=0; k < c && cities[k].inP; k++) // find the first vertex not in P
			;
			
		m = k; 
		
		for (k=m+1; k < c; k++) //find city node not in P with smallest distance 
			{
			if (!cities[k].inP && cities[k].w) //if the current city node is not at infinity distance 
				{
				if (!cities[m].w)// if city[m] has distance infinity
					m = k;
					
				else if (cities[k].w < cities[m].w)
					m = k;
					
				}
			}
			
		cities[m].inP = 1; 
		
		for(k=0; k < c; k++) //for each vertex k, not in P, and adjacent to m
			{                //replace k's weight with min of k.weight and m.weight + w(m,k)
			if (!cities[k].inP && flights[m][k])
				{
				if (cities[m].w && flights[m][k])
					{
					if (!cities[k].w)
						{
						cities[k].w = cities[m].w + flights[m][k];
						cities[k].predecessor = m;
						}
						
					else if (cities[m].w + flights[m][k] < cities[k].w)
						{
						cities[k].w = cities[m].w + flights[m][k];
						cities[k].predecessor = m;
						}
						
					}
				}	
		
			}
		
		}//step 3 of Dijkstra's Algorithm
	
	for (k=s; k < c; k++)
		{
		cheapest_flight[s][k] = cities[k].w;
		cheapest_flight[k][s] = cities[k].w;
		}
	}

mostExpensiveFlight = 0;
for (k=0; k < c; k++)
	{
	for (j=k+1; j < c; j++)
		{
		if (cheapest_flight[k][j] > mostExpensiveFlight)
			mostExpensiveFlight = cheapest_flight[k][j];
		}
	}
	
cout<<"The most expensive flight that can be purchased is $"<<mostExpensiveFlight<<endl<<endl;

return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
int checkP(struct Node cities[], int c)
{
int p_complete = 1;
int k;

for(k=0; k < c && p_complete; k++)	
	{
	if (!cities[k].inP)
		p_complete = 0;
	}
	
return p_complete;
}