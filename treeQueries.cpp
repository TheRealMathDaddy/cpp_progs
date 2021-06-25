/* Program takes in a tree with N vertices and performs Q queries on the tree.
 * 
 * Input:
 * N Q (N = number of nodes and Q = number of queries)
 * w[1] w[2] ... w[N] -- values of the tree nodes
 *
 * Next N-1 lines takes in the edges of the tree:
 * U V (an edge of the tree)
 * 
 * Next Q lines are queries that affect the tree. Queries must be of the form:
 * UPDATE U X (updates value of node U to be X)
 *
 * INCREASING U V A B -- finds the number of increasing sequences between node U and node V
 * where all node values are between A and B (A < B)
 *
 * DECREASING U V A B -- finds the number of decreasing sequences between node U and node V
 * where all node values are between A and B (A < B)
 *
 * NON-INCREASING U V A B -- finds the number of non-increasing sequences between node U and 
 * node V where all node values are between A and B (A < B).
 *
 * NON-DECREASING U V A B -- finds the number of non-decreasing sequences between node U and 
 * node V where all node values are between A and B (A < B).
 *
 *
 * The program does not prompt for the input, you simply enter it in the order given above. Any
 * input entered on the same line should be separated by a space.
 */

#include<iostream>
#include<vector>
#include<string>
using namespace std;


/** Classes and Structures
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
 
struct Node 
{
int label;
int value;
struct Node* neighbor;
int inTree;
};

/** Prototypes
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */

void getInput(int &N, int &Q, vector<struct Node*> &w);
void getTreeEdges(int N, vector<struct Node*> &w);
void add(int u, int v, vector<struct Node*> &w); 
void getQueries(int N, int Q, vector<struct Node*> &w);
void processQuery(char line[], vector<struct Node*> &w, vector<int> &output);
void update(int u, int x, vector<struct Node*> &w);
int findNumIncr(int u, int v, int a, int b, vector<struct Node*> w);
int findNumDecr(int u, int v, int a, int b, vector<struct Node*> w); 
int findNumNonIncr(int u, int v, int a, int b, vector<struct Node*> w);
int findNumNonDecr(int u, int v, int a, int b, vector<struct Node*> w);
void findPath(int u, int v, vector<struct Node*> w, vector<int> &pathUtoV);
void groupBlankCells(vector<int> &pathUtoV);
bool pathContainsVertex(vector<struct Node*> path, int v);
bool pathRangeValid(vector<int> path, int a, int b);
bool pathIs(char ID[], vector<int> pathUtoV, int a, int b);
int binom (int k, int r);

/** Main function
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */

int main () 
{
system("clear");
int N;
int Q;
int k;

vector<struct Node*> w;

getInput(N, Q, w);
getTreeEdges(N, w);

	
getQueries(N, Q, w);



return 0;
}

/**
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */

void getInput(int &N, int &Q, vector<struct Node*> &w)
{
cin >> N;
cin >> Q;

struct Node* n;

int k;

for (k=0; k < N; k++) 
	{
	n = new Node;

	n->label = k+1;
	cin >> n->value;
	n->inTree = 0;
	w.push_back(n);
	}
	
}

/**
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
 
void getTreeEdges(int N, vector<struct Node*> &w)
{
int u;
int v;
int k;

for(k=1; k < N; k++)
	{
	cin >> u;
	cin >> v;
	add(u, v, w);
	
	if (k == 1)
		{
		w.at(u-1) -> inTree = 1;
		w.at(v-1) -> inTree = 1;
		}
	}
}

/**
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
 
void add(int u, int v, vector<struct Node*> &w) 
{
if (w.at(v-1)->inTree)
	{
	w.at(u-1)->neighbor = w.at(v-1);
	w.at(u-1)->inTree = 1;
	}
	
else if (w.at(u-1)->inTree) 
	{
	w.at(v-1)->neighbor = w.at(u-1);
	w.at(v-1)->inTree = 1;
	}
	
else
	w.at(u-1)->neighbor = w.at(v-1);
}

/**
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
 
void getQueries(int N, int Q, vector<struct Node*> &w)
{
int k; //scratch variable
vector<int> output;


char line[101];

for (k=0; k < Q; k++)
	{
	cin.getline(line, 101);
	
	while (strcmp(line, "") == 0)
		cin.getline(line, 101);
		
	processQuery(line, w, output);
	}

cout<<endl;
for(k=0; k < output.size(); k++)
	cout<<output.at(k)<<endl;

}

/**
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */

void processQuery(char line[], vector<struct Node*> &w, vector<int> &output)
{
char query[31];
char* token;
int u;
int v;
int x;
int a;
int b;
int num;


token = strtok(line, " " );
strcpy(query, token);

if (strcmp(query, "UPDATE") == 0)
	{
	token = strtok(NULL, " ");
	u = stoi(token);
	
	token = strtok(NULL, " ");
	x = stoi(token);
	
	update(u, x, w);
	}
	
else 
	{
	token = strtok(NULL, " ");
	u=stoi(token);
	
	
	token = strtok(NULL, " ");
	v = stoi(token);
	
	
	token = strtok(NULL, " ");
	a = stoi(token);
	
	
	token = strtok(NULL, " ");
	b = stoi(token);
	
	
	if (strcmp(query, "INCREASING") == 0)
		{ 
		num = findNumIncr(u, v, a, b, w);
		output.push_back(num);
		}
		
	else if (strcmp(query, "DECREASING") == 0)
		{
		num = findNumDecr(u, v, a, b, w);
		output.push_back(num);
		}
		
	else if (strcmp(query, "NON-INCREASING") == 0)
		{
		num = findNumNonIncr(u, v, a, b, w);
		output.push_back(num);
		}
		
	else if (strcmp(query, "NON-DECREASING") == 0)
		{
		num = findNumNonDecr(u, v, a, b, w);
		output.push_back(num);
		}	
	}
}

/**
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
 
void update(int u, int x, vector<struct Node*> &w)
{
w.at(u-1)->value = x;
}
/**
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
int findNumIncr(int u, int v, int a, int b, vector<struct Node*> w) 
{
int k;
int x;
int y;
int num = 1;
int numIncr = 0;
int pU2VSize;
bool incrPathExists = true;
vector<int> pathUtoV;

findPath(u, v, w, pathUtoV);



groupBlankCells(pathUtoV);
pU2VSize = pathUtoV.size();

if (pathRangeValid(pathUtoV, a, b) && pathIs("INCR", pathUtoV, a, b))
	{
	for(k=0; k < pU2VSize && incrPathExists; k++)
		{
		while (k < pU2VSize && pathUtoV.at(k) >= 0)
			k++;
			
			
		if (k < pU2VSize)
			{
			if (k == 0)
				x = a-1;
				
			else
				x = pathUtoV.at(k-1);
				
			x++;
				
			if (k == pU2VSize - 1)
				y = b+1;
				
			else
				y = pathUtoV.at(k+1);
				
			y--;
				
			numIncr = binom(y-x+1, -1*pathUtoV.at(k)); 
			
			if (numIncr > 0)
				num *= numIncr;
				
			else
				{
				num = 0;
				incrPathExists = false;
				}
				
			}
		}
	}
	
else
	num = 0;

return num;
}

/**
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
 
int findNumDecr(int u, int v, int a, int b, vector<struct Node*> w) 
{
int k;
int x;
int y;
int num = 1;
int numIncr = 0;
int pU2VSize;
bool decrPathExists = true;
vector<int> pathUtoV;

findPath(u, v, w, pathUtoV);

groupBlankCells(pathUtoV);
pU2VSize = pathUtoV.size();

if (pathRangeValid(pathUtoV, a, b) && pathIs("DECR", pathUtoV, a, b))
	{
	for(k=0; k < pU2VSize && decrPathExists; k++)
		{
		while (k < pU2VSize && pathUtoV.at(k) >= 0)
			k++;
			
		if (k < pU2VSize)
			{
			if (k == 0)
				x = b+1;
				
			else
				x = pathUtoV.at(k-1);
				
			x--;
				
			if (k == pU2VSize - 1)
				y = a-1;
				
			else
				y = pathUtoV.at(k+1);
				
			y++;
					
			numIncr = binom(x-y+1, -1*pathUtoV.at(k)); 
		
			if (numIncr > 0)
				num *= numIncr;
				
			else
				{
				num = 0;
				decrPathExists = false;
				}
				
			}
		}
	
	}
	
else
	num = 0;
	
return num;
}

/**
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
 
int findNumNonIncr(int u, int v, int a, int b, vector<struct Node*> w) 
{
int k;
int pU2VSize;
int num = 0;
int numIntsAtoB = b-a + 1;
int numSlots = 0;
vector<int> pathUtoV;

findPath(u, v, w, pathUtoV);

groupBlankCells(pathUtoV);
pU2VSize = pathUtoV.size();


if (pathRangeValid(pathUtoV, a, b))
	{
	if (numIntsAtoB > 0)
		{
		for(k=0; k < pU2VSize; k++)
			{
			if (pathUtoV.at(k) < 0)
				numSlots += (-1*pathUtoV.at(k));
			}
			
		for(k=1; k < numSlots; k++)
			{
			numIntsAtoB *= numIntsAtoB;
			}
			
		num += numIntsAtoB;
		
		num -= findNumIncr(u, v, a, b, w);
		}
	}
	
return num;
}

/**
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
 
int findNumNonDecr(int u, int v, int a, int b, vector<struct Node*> w) 
{
int k;
int pU2VSize;
int num = 0;
int numIntsAtoB = b-a + 1;
int numSlots = 0;
vector<int> pathUtoV;

findPath(u, v, w, pathUtoV);

groupBlankCells(pathUtoV);
pU2VSize = pathUtoV.size();


if (pathRangeValid(pathUtoV, a, b))
	{
	if (numIntsAtoB > 0)
		{		
		for(k=0; k < pU2VSize; k++)
			{
			if (pathUtoV.at(k) < 0)
				numSlots += (-1*pathUtoV.at(k));
			}
			
		for(k=1; k < numSlots; k++)
			numIntsAtoB *= numIntsAtoB;

			
		num += numIntsAtoB;
		
		num -= findNumDecr(u, v, a, b, w);
		}
	}
	
return num;
}

/**
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */

void findPath(int u, int v, vector<struct Node*> w, vector<int> &pathUtoV)
{
vector<struct Node*> pathUtoRoot;
vector<struct Node*> pathVtoRoot;

struct Node* curr_node;

int posn;
int size;
int temp;
bool nearestRootFound = false;

int m;
int n;


curr_node = w.at(u-1);

while (curr_node != NULL)
	{
	pathUtoRoot.push_back(curr_node);
	curr_node = curr_node->neighbor;
	}
	
curr_node = w.at(v-1);

while (curr_node != NULL)
	{
	pathVtoRoot.push_back(curr_node);
	curr_node = curr_node->neighbor;
	}

if (pathContainsVertex(pathUtoRoot, v))
	{
	posn = 0;
	curr_node = pathUtoRoot.at(posn);
	
	while(curr_node -> label != v)
		{
		pathUtoV.push_back(curr_node->value);
		posn++;
		curr_node = pathUtoRoot.at(posn);
		}
		
	pathUtoV.push_back(curr_node->value);
	}
	
else if (pathContainsVertex(pathVtoRoot, u))
	{
	posn = 0;
	curr_node = pathVtoRoot.at(posn);
	
	while (curr_node -> label != u)
		{
		pathUtoV.push_back(curr_node -> value);
		posn++;
		curr_node = pathVtoRoot.at(posn);
		}
		
	pathUtoV.push_back(curr_node->value);
	
	size = pathUtoV.size();
	
	for (posn = 0; posn < size / 2; posn++)
		{
		temp = pathUtoV.at(posn);
		pathUtoV.at(posn) = pathUtoV.at(size - 1 - posn);
		pathUtoV.at(size - 1 - posn) = temp;
		}
	
	}
	
else
	{
	while (pathUtoRoot.size() > 1 && pathVtoRoot.size() > 1 && !nearestRootFound)
		{
		if (pathUtoRoot.at(pathUtoRoot.size() - 1) -> label == pathVtoRoot.at(pathVtoRoot.size() - 1) -> label &&
			pathUtoRoot.at(pathUtoRoot.size() - 2) -> label != pathVtoRoot.at(pathVtoRoot.size() - 2) -> label)
				nearestRootFound = true;
				
		if (!nearestRootFound)
			{
			pathUtoRoot.pop_back();
			pathVtoRoot.pop_back();
			}		
		}
		
	pathVtoRoot.pop_back();
	
	while (!pathVtoRoot.empty())
		{
		pathUtoRoot.push_back(pathVtoRoot.back());
		pathVtoRoot.pop_back();
		}
	
	for(m=0; m < pathUtoRoot.size(); m++)
		{
		pathUtoV.push_back(pathUtoRoot.at(m) -> value);
		}
	
	}
}

/**
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
 
void groupBlankCells(vector<int> &pathUtoV)
{
int k;
int l;

k=0;

while (k < pathUtoV.size())
	{
	while (k < pathUtoV.size() && pathUtoV.at(k) != -1)
		k++;
	
	while (k+1 < pathUtoV.size() && pathUtoV.at(k+1) == -1)
		{
		pathUtoV.at(k) += pathUtoV.at(k+1);
		pathUtoV.erase(pathUtoV.begin() + (k+1), pathUtoV.begin() + (k+2));
		}
		
	k++;
	}
}

/**
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
 
bool pathContainsVertex(vector<struct Node*> path, int v)
{
bool vFound = false;
int posn = 0;
int length = path.size();
struct Node* curr_node = path.at(posn);

while (!vFound && posn < length)
	{
	if (curr_node -> label == v)
		vFound = true;
		
	else 
		{
		posn++;
		
		if (posn < length)
			curr_node = path.at(posn);
			
		}
	}
	
return vFound;
}

/**
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
 
bool pathRangeValid(vector<int> path, int a, int b)
{
bool rangeValid = true;

int k = 0;
int curr = path.at(k);

while (k < path.size() && rangeValid)
	{
	if (path.at(k) > -1 && (path.at(k) < a || path.at(k) > b))
		rangeValid = false;
		
	k++;
	}

return rangeValid;
}

/**
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
 
bool pathIs(char ID[], vector<int> pathUtoV, int a, int b)
{
bool pathIsID = true;
int j;
int k;
int pU2VSize = pathUtoV.size();

if (strcmp(ID, "INCR") == 0)
	{
	for(j=0; j < pU2VSize && pathIsID; j++)
		{
		while (j < pU2VSize && pathIsID && pathUtoV.at(j) < 0)
			j++;
			
		for(k=j+1; k < pU2VSize && pathIsID; k++)
			{
			while (k < pU2VSize && pathIsID && pathUtoV.at(k) < 0)
				k++;
				
			if (k < pU2VSize && pathUtoV.at(j) >= pathUtoV.at(k))
				pathIsID = false; 
				
			}
		j = k;
		}
	}

else if (strcmp(ID, "DECR") == 0)
	{
	for(j=0; j < pU2VSize && pathIsID; j++)
		{
		while (j < pU2VSize && pathIsID && pathUtoV.at(j) < 0)
			j++;
			
		for(k=j+1; k < pU2VSize && pathIsID; k++)
			{
			while (k < pU2VSize && pathIsID && pathUtoV.at(k) < 0)
				k++;
				
			if (k < pU2VSize && pathUtoV.at(k) >= pathUtoV.at(j))
				pathIsID = false; 
				
			}
		j = k;
		}
	}	

return pathIsID;
}

/**
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
 
 int binom (int k, int r)
 {
 int ret = 0; //return value
 
 if (k >= r && r == 0)
	ret = 1;
	
 else if (k >= r && r > 0)
 	ret = binom(k-1, r) + binom(k-1, r-1);
 	
 else if (k < r || r < 0)
 	ret = 0;
 	
 return ret;
 }





