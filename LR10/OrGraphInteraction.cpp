#include "OrGraphInteraction.h"

OrGraphInteraction::OrGraphInteraction()
{

}

void OrGraphInteraction::printQuit()
{
	cout << endl << endl << "Backspace - возврат в меню";

	int answ = _getch();
	bool press = false;

	while (!press)
	{
		if (answ == 8)
		{
			press = true;
			break;
		}
		else
		{
			answ = _getch();
		}
	}

	system("cls");
}

void OrGraphInteraction::Read_g()
{
	adjacencyM.resize(MAXV, vector<bool>(MAXV));
	ReverseAdjacencyM.resize(MAXV, vector<bool>(MAXV));

	ifstream ifs("data.txt");
	if (ifs.is_open())
	{
		ifs >> verts;
		ifs >> edges;
		while (!ifs.eof())
		{
			int v, u;
			ifs >> v;
			ifs >> u;
			adjacencyM[v][u] = true;
		}
		cout << "Данные успешно считаны";
	}
	else
	{
		cerr << "Ошибка открытия файла";
	}
	ifs.close();
}

void OrGraphInteraction::Print_g()
{
	for (int i = 1; i <= verts; i++)
	{
		cout << i << " вершина: ";
		vector<int> temp;
		for (int j = 1; j <= verts; j++)
		{
			if (adjacencyM[i][j])
			{
				temp.push_back(j);
				cout << j << " ";
			}
		}
		if (temp.empty())
		{
			cout << "<нет исходящих ребер>";
		}
		cout << endl;
	}
}

int OrGraphInteraction::edgeClass(int first, int second, vector<int>& parents, vector<int>& visited, vector<int>& entryTimes)
{
	if (parents[second] == first) return TREE;
	if (visited[second] == 0) return BACK;
	if (visited[second] == 1 && entryTimes[second] > entryTimes[first]) return FORWARD;
	if (visited[second] == 1 && entryTimes[second] < entryTimes[first]) return CROSS;

	throw exception("Невозможно определить тип ребра");
}

void OrGraphInteraction::DFSCompsPred(int curVert, vector<int>& status, stack<int>& st)
{
	status[curVert] = 0;

	for (int i = 1; i <= verts; i++)
	{
		if (adjacencyM[curVert][i] && status[i] == -1)
		{
			DFSCompsPred(i, status, st);
		}
	}

	st.push(curVert);
}

void OrGraphInteraction::DFSComps(vector<int>& comp, vector<int>& status, int curVert)
{
	status[curVert] = 0;
	comp.push_back(curVert);

	for (int i = 1; i <= verts; i++)
	{
		if (ReverseAdjacencyM[curVert][i] && status[i] == -1)
		{
			DFSComps(comp, status, i);
		}
	}
}

void OrGraphInteraction::Reverse_g()
{
	for (int i = 1; i <= verts; i++)
	{
		for (int j = 1; j <= verts; j++)
		{
			if (adjacencyM[i][j])
			{
				ReverseAdjacencyM[j][i] = true;
			}
		}
	}
}

vector<vector<int>> OrGraphInteraction::FindCompsDFS()
{
	vector<vector<int>> result;

	vector<int> visited(verts + 1, -1); // -1 = не посещена    0 = посещена     1 = обработана (не нужно)
	stack<int> st;
	
	for (int i = 1; i <= verts; i++)
	{
		if (visited[i] == -1)
		{
			DFSCompsPred(i, visited, st);
		}
	}

	Reverse_g();

	visited.assign(verts + 1, -1);

	while (!st.empty())
	{
		int curVert = st.top();
		st.pop();

		if (visited[curVert] == -1)
		{
			vector<int> comp;
			DFSComps(comp, visited, curVert);
			result.push_back(comp);
		}
	}

	return result;
}

void OrGraphInteraction::PrintComps(vector<vector<int>>& comps)
{
	for (int i = 0; i < comps.size(); i++)
	{
		cout << i + 1 << " компонента: ";
		for (auto& el : comps[i])
		{
			cout << el << " ";
		}
		if (comps[i].empty())
		{
			cout << "<нет вершин>";
		}
		cout << endl;
	}
}

void OrGraphInteraction::DFSCompsTopSort(int curVert, vector<int>& status, stack<int>& st)
{
	status[curVert] = 0;

	for (int i = 1; i <= verts; i++)
	{
		if (adjacencyM[curVert][i] && status[i] == -1)
		{
			DFSCompsTopSort(i, status, st);
		}
		else if (adjacencyM[curVert][i] && status[i] == 0)
		{
			throw exception("Существует цикл");
		}
	}

	status[curVert] = 1;

	st.push(curVert);
}

vector<int> OrGraphInteraction::topSort()
{
	vector<int> result;

	vector<int> visited(verts + 1, -1); // -1 = не посещена    0 = посещена     1 = обработана
	stack<int> st;

	for (int i = 1; i <= verts; i++)
	{
		if (visited[i] == -1)
		{
			DFSCompsTopSort(i, visited, st);
		}
	}

	while (!st.empty())
	{
		result.push_back(st.top());
		st.pop();
	}

	return result;
}