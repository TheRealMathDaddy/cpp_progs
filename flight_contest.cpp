#include<iostream>
#include<algorithm>
#include<climits>
using namespace std;

struct Flight
	{
	bool inP; //flight already processed in Dijkstra's Algorithm
	int predecessor; //predecessor of flight node
	int d; //distance from source node
	};
	
	
void getInput(int &c, int &f);
void getFlights(int* direct_flight_prices, int c, int f);
void getAllCheapFlights(int* cheapest_flight_prices, int* direct_flight_prices, int c, int f);
bool pFull(struct Flight cheapFlights[], int c); 
int  putMinFlightInP(struct Flight cheapFlights[], int c);
void updateDistances(struct Flight cheapFlights[], int c, int minPosn, int* direct_flight_prices);
int getFPGLB(int* cheapest_flight_prices, int c);

int main()
{
int c; //number of cities
int f; // number of flights
int flightPriceGLB; //greatest lower bound of flight prices

getInput(c, f);

int direct_flight_prices[c][c]; // prices of all direct flights
int cheapest_flight_prices[c][c]; //prices of cheapest flight paths between any 2 cities

getFlights((int*) direct_flight_prices, c, f);


getAllCheapFlights((int*) cheapest_flight_prices, (int*) direct_flight_prices, c, f);

flightPriceGLB = getFPGLB((int*) cheapest_flight_prices, c);

cout<<endl<<flightPriceGLB<<endl;
return 0;
}

/*
 * Functions
 */
 
 void getInput(int &c, int &f)
 {
 cin>>c;
 cin>>f;
 }
 
 void getFlights(int* direct_flight_prices, int c, int f)
 {
 int c1; //first city
 int c2; //second city
 int p;  //flight price
 int k;
 
 for(c1=0; c1 < c; c1++) //init all direct flight prices to -1 (no flight available)
 	{
 	for(c2=0; c2 < c; c2++)
 		*(direct_flight_prices + c1*c + c2) = -1;
 	}
 	
 for(k=0; k < f; k++)
 	{
 	cin>>c1;
 	cin>>c2;
 	
 	cin>> *(direct_flight_prices + (c1-1)*c + (c2-1));
 	
 	*(direct_flight_prices + (c2-1)*c + (c1-1)) = *(direct_flight_prices + (c1-1)*c + (c2-1));
 	}
 }
 
 void getAllCheapFlights(int* cheapest_flight_prices, int* direct_flight_prices, int c, int f)
 {
 struct Flight cheapFlights[c]; //cheapest flight from source city to destination city
 int s; //source city
 int d; //destination city
 int k; //scratch variable
 int minPosn;
 
for(s=0; s < c; s++)
	{
	for(d=0; d < c; d++)
		{
		if (s == d) //initialize source city
			{
			cheapFlights[d].inP = true;
			cheapFlights[d].predecessor = -1;
			cheapFlights[d].d = 0;
			}
			
		else //initialize destination cities
			{
			cheapFlights[d].inP = false;
			cheapFlights[d].predecessor = s;
			cheapFlights[d].d = *(direct_flight_prices + s*c + d);
			}
		}
	
		
	while(!pFull(cheapFlights, c)) //while there are destination cities that have not 
								   // been processed
		{
		minPosn = putMinFlightInP(cheapFlights, c);
			
		updateDistances(cheapFlights, c, minPosn, (int*) direct_flight_prices);
		}	
	
	for(d=0; d < c; d++)
		{
		*(cheapest_flight_prices + s*c + d) = cheapFlights[d].d;
		*(cheapest_flight_prices + d*c + s) = cheapFlights[d].d;
		}
	}
 
 }
 
 bool pFull(struct Flight cheapFlights[], int c) //check to see if there
 												 //is a dest. city that hasn't been processed
 {
 int k;
 bool pfull = true;
 
 for(k=0; k < c && pfull; k++)
 	pfull = cheapFlights[k].inP;

 return pfull;
 }
 
 int putMinFlightInP(struct Flight cheapFlights[], int c)
 {
 int k;
 int minPosn;
 int minFlightDistance = -1;
 
 for(k=0; k < c; k++)
 	{
 	/*
 	if(cheapFlights[k].d < minFlightDistance && !cheapFlights[k].inP)
 		{
 		minFlightDistance = cheapFlights[k].d;
 		minPosn = k;
 		}
 	*/
 	
 	if (cheapFlights[k].d != -1 && !cheapFlights[k].inP)
 		{
 		if (minFlightDistance == -1)
 			{
			minFlightDistance = cheapFlights[k].d;
			minPosn = k;
 			}
 			
 		else if (cheapFlights[k].d < minFlightDistance)
 			{
			minFlightDistance = cheapFlights[k].d;
			minPosn = k;	
 			}
 			
 		}
 	
 	}
 	
 cheapFlights[minPosn].inP = true;
 return minPosn;
 }
 
 void updateDistances(struct Flight cheapFlights[], int c, int minPosn, int* direct_flight_prices)
 {
 int k;
 
 for(k=0; k < c; k++)
 	{
 	if(!cheapFlights[k].inP)
 		{
 		if (cheapFlights[minPosn].d != -1 && *(direct_flight_prices + k*c + minPosn) != -1)
 			{
 			if (cheapFlights[k].d == -1)
 				{
  				cheapFlights[k].d = cheapFlights[minPosn].d + *(direct_flight_prices + k*c + minPosn);
 				cheapFlights[k].predecessor = minPosn;
 				}
 				
 			else if ((cheapFlights[k].d > cheapFlights[minPosn].d + *(direct_flight_prices + k*c + minPosn)))
 				{
  				cheapFlights[k].d = cheapFlights[minPosn].d + *(direct_flight_prices + k*c + minPosn);
 				cheapFlights[k].predecessor = minPosn; 				
 				}
 			}
 		}
 	}
 }
 
 int getFPGLB(int* cheapest_flight_prices, int c)
 {
 int fpGLB = -1;
 
 int j;
 int k;
 
 for(k=0; k < c; k++)
 	{
 	for (j=k; j < c; j++)
 		{
 		fpGLB = max(fpGLB, *(cheapest_flight_prices + k*c + j));
 		}
 	}
 	
 return fpGLB;
 }
 
