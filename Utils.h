#pragma once
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include "pipe.h"
#include "cs.h"
using namespace std;

template <typename T>
int IdCheck(unordered_map<int, T> umap)
{
    int id;
    while (((cin >> id).fail()) || (cin.peek() != '\n') || (id <= 0) || (!umap.contains(id)))
    {
        cout << "Такого объекта нет, введите другой индекс" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    return id;
}

template <typename T>
void GetValue(T& a)
{
    while (((cin >> a).fail()) || (cin.peek() != '\n') || (a <=0))
    {
        cout << "Введите корректное значение" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }    
}

template <typename T>
T GetLimValue(T min, T max) 
{
	T value;
	while (((cin >> value).fail()) || (cin.peek() != '\n') || (value < min) || (value > max))
    {
        cout << "Введите корректное значение" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
	}
    return value;
}

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