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

template <typename T>
ostream& operator<< (ostream& out, unordered_map <int, T>& pm) {
    out << "Доступые id: ";
    for (auto& [i, obj] : pm) {
        out << i << " ";
    }
    out << endl;
    return out;
}