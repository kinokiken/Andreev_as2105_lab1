#pragma once
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <fstream>

using namespace std;

class CStation 
{
public:
    static int Cplus;

    friend istream& operator >> (istream& is, CStation& cs);
    friend ostream& operator << (ostream& os, CStation& cs);
    friend ofstream& operator << (ofstream& file, CStation& cs);
    friend ifstream& operator >> (ifstream& file, CStation& cs);

    int GetCid ();
    int up_csid();
    int GetPshops ();
    int GetWorks ();
    string GetCname ();
    void SetCsid(int i);
    void SetWorks(int a);

private:     
    int CsIndx = 0, WorkshopsNum = 0, efficiency = 0, WorkingNum = 0;
    string name = "";
};