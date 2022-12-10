#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include "pipe.h"
#include "cs.h"
using namespace std;

class All
{
public:
	unordered_map <int, Pipes> pm;
	unordered_map <int, CStation> csm;

	int check_exist(int x);

	int check_graph(int x);

	int check_p(int x);

	bool check_used(int x, int y);

	bool check_i(int x);

	int edge(float x);

	void topologicalSortUtil(int V, unordered_map<int, bool>& visited, stack<int>& SortedV);

	void topologicalSort();

    int Menu();

    void SaveParameters (unordered_map <int, Pipes>& pm, unordered_map <int, CStation>& csm);

    void LoadParameters (unordered_map <int, Pipes>& pm, unordered_map <int, CStation>& csm);

    void ShowCsParameters (unordered_map <int, CStation>& csm);

    void CsEdit (unordered_map <int, CStation>& csm);

    void EditWorkshops(int id, unordered_map <int, CStation>& csm);

    unordered_set <int> CsFilter (unordered_map <int, CStation>& csm);

    void CsBatchEdit (unordered_map <int, CStation>& csm);

    void PipeEdit(unordered_map <int, Pipes>& pm);

    void ShowPipeParameters (unordered_map <int, Pipes>& pm);

    unordered_set <int> PipeFilter (unordered_map <int, Pipes>& pm);

    void PBatchEdit (unordered_map <int, Pipes>& pm);

	struct System {
		static int max_ids;
		int id;
		System() {
			id = max_ids++;
		}
		int id_ent;
		int id_ex;
		int id_pip;
	};
	unordered_map <int, System> graph;

    unordered_map <int, list<System>> Graph_l;

    void sort();

	void fill_graphl(unordered_map<int, System>& sys);

	friend istream& operator >> (istream& in, All& gts);

	friend ostream& operator<<(ostream& out, unordered_set<int> s);
};