#pragma once
#include <iostream>
#include <fstream>

#include <Windows.h>
#include <conio.h>
#include <cmath>

#include <vector>
#include <stack>

#define MAXV 1000

using namespace std;

enum classificatons 
{
	TREE = 1,
	BACK = -1,
	FORWARD = 2,
	CROSS = 0
};

class OrGraphInteraction
{
	void DFSCompsPred(int curVert, vector<int>& status, stack<int>& st);
	void DFSComps(vector<int>& comp, vector<int>& status, int curVert);
	void Reverse_g();

	void DFSCompsTopSort(int curVert, vector<int>& status, stack<int>& st);
public:

	vector<vector<bool>> adjacencyM;
	vector<vector<bool>> ReverseAdjacencyM;
	int verts, edges;

	OrGraphInteraction();

	void printQuit();
	void Read_g();
	void Print_g();

	int edgeClass(int first, int second, vector<int>& parents, vector<int>& visited, vector<int>& entryTimes);

	vector<vector<int>> FindCompsDFS();
	void PrintComps(vector<vector<int>>& comps);

	vector<int> topSort();
};