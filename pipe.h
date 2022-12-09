#pragma once
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <fstream>

using namespace std;

class Pipes
{
public:
    static int Pplus;

    friend istream& operator >> (istream& is, Pipes& pipe);
    friend ostream& operator << (ostream& os, Pipes& pipe);
    friend ofstream& operator << (ofstream& file, Pipes& pipe);
    friend ifstream& operator >> (ifstream& file, Pipes& pipe);

    int GetPid ();
    float GetDiam();
    int up_pid();
    bool GetRepair();
    void SetRepair(bool a);
    string GetPname();
    void SetPid(int i);
    string RepairMsg(bool repair);

private:
    int PipeIndx = 0;
    float length = 0, diameter = 0;
    string pname = "";
    bool repair = 0;
};