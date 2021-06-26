/*
 * Indian National Olympiad in Informatics 2012 competition.
 *
 * Tutaria is celebrating its independence day by having a contest where its citizens
 * partake in 3 tasks: COBOL competition, pole vault, and doughnut eating contest.
 * 
 * Each citizen must complete the contest in the same order: COBOL, pole vault, doughnut eating.
 * The exact time each citizen needs to complete each task. The pole vault and doughnut eating
 * contest can be completed by participants simultaneously, but as Tutaria has only one
 * computer, only one citizen can complete the COBOL task at a time. 
 * 
 *
 * The program takes in the number of citizens and the times needed by each citizen
 * to complete these tasks. The contest ends when all participants have finished all tasks.
 * 
 * Tutaria wants to minimize the contest time. The objective of the program is to find the 
 * minimum time needed for the contest duration.
 *
 * Input: 
 ** N (number of citizens in Tutaria taking part in the contest)
 ***
 *** Next N Lines takes in times each citizen needs to complete each task 
 *** c p d (c = time for COBOL, p = time for pole vault, d = time for doughnut eating)
 ****
 **** Output:
 **** Minimum time needed for the contest.  
 */
 
 /*
  * Updating localMinTime in function updateMinTime modeled
  * from maheshmeena's code -- submission 48034827
  */
 
 #include<iostream>
 #include<vector>
 #include<algorithm>
 #include<climits>

using namespace std;
 
 
/* 
 * Classes
 */
class Participant
	{
	public: 
		int c; //time to complete COBOL task
		int p; //time to complete pole vault
		int d; //time to complete doughnut eating task
		int total; //time to complete all tasks
		int pdSum; //time to complete non-COBOL tasks
	};
	
/*
 * Function prototypes
 */
 
 void getInput(int &N, vector<Participant> &participants);
 void updateMinTime(vector<Participant> participants, int &minTime);
 bool sortbyPD(Participant l, Participant r);
/*
 * Main function
 */
 
 int main ()
 {
 int N; //number of participants in the contest
 int minTime = INT_MAX; //init minTime
 vector<Participant> participants;
 
 
 getInput(N, participants);
 
 sort(participants.begin(), participants.end(), sortbyPD);
 
 updateMinTime(participants, minTime);
 
 
 cout<<"\n"<<minTime<<"\n";
 
 return 0;
 }

/* 
 * Functions
 */
 
 void getInput(int &N, vector<Participant> &participants)
 {
 int k;
 int m;
 Participant p;
 cin >> N;
for (k=0; k < N; k++)
	{
	cin >> p.c;
	cin >> p.p;
	cin >> p.d;

	p.pdSum = p.p + p.d;
	p.total = p.c + p.pdSum;
	participants.push_back(p);
	}
 }

/* 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 */
  

void updateMinTime(vector<Participant> participants, int &minTime)
{
int localMinTime   = participants.at(0).total;
int size           = participants.size();
int k;
int cobolSum = 0;

for(k=0; k < size; k++)
	{
	localMinTime = max(localMinTime, cobolSum + participants.at(k).total);
	cobolSum += participants.at(k).c;
	}

if (localMinTime < minTime)
	minTime = localMinTime;
	
}

bool sortbyPD(Participant l, Participant r)
{
return l.pdSum > r.pdSum;
}