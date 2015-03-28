#include <cstdio>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <cstring>

using namespace std;

vector< vector<int> >adj;

/* $ ./a.out node.json edge.txt no_of_parts*/
int main(int argc, char* argv[])
{	
	FILE * fin = fopen(argv[2], "r");
	if(!fin)
	{
		printf("Could not open edge list file\n");
		return -1;
	}

	int n = 0;
	int m = 0;
	map<int, int> mapping;
	while(!feof(fin))
	{
		int x,y;
		fscanf(fin, "%d %d",&x,&y);

		if(mapping.find(x)==mapping.end())
		{
			mapping[x] = n++;
			adj.push_back(vector<int>());
		}


		if(mapping.find(y)==mapping.end())
		{
			mapping[y] = n++;
			adj.push_back(vector<int>());
		}
		
		adj[mapping[x]].push_back(mapping[y]);
		adj[mapping[y]].push_back(mapping[x]);

		m++;
	}
	fclose(fin);

	/*FILE * fout = fopen(argv[2], "w");
	if(!fout)
	{
		printf("Could not open mapping file\n");
		return -1;
	}

	map<int, int>::iterator it;
	for(it=mapping.begin();it!=mapping.end();++it)
	{
		fprintf(fout, "%d %d\n", it->first, it->second+1);
	}

	fclose(fout);*/


	FILE * fout = fopen("adjacency.txt", "w");
	if(!fout)
	{
		printf("Could not open adjacency file\n");
		return -1;
	}

	fprintf(fout, "%d %d\n", n,m);
	for(int i=0; i<n;i++)
	{
		for(int j=0; j<adj[i].size(); j++)
			fprintf(fout, "%d ",adj[i][j]+1);
		fprintf(fout, "\n");
	}
	fclose(fout);

	// printf("erfnej\n");

	//EXEC
	char *arglist[4];

	arglist[0] = (char *)malloc(100*sizeof(char)); strcpy(arglist[0],"gpmetis");
	arglist[1] = (char *)malloc(100*sizeof(char)); strcpy(arglist[1],"adjacency.txt");
	arglist[2] = (char *)malloc(100*sizeof(char)); strcpy(arglist[2],argv[3]);
	arglist[3] = NULL;
	execvp("gpmetis", arglist);

	





}