#include <string>
#include "cs.h"
#include "Utils.h"

using namespace std;

int CStation::Cplus = 0;

int CStation::GetCid ()
{
    return CsIndx;
}

int CStation::up_csid() 
{
    return CsIndx = ++Cplus;
}

int CStation::GetPshops ()
{
    return WorkshopsNum;
}

int CStation::GetWorks ()
{
    return WorkingNum;
}

string CStation::GetCname ()
{
    return name;
}

void CStation::SetCsid(int i)
{
    CsIndx = i;
}

void CStation::SetWorks(int a) 
{
    WorkingNum = a;
}

istream& operator >> (istream& is, CStation& cs)
{
    cs.up_csid();
    cout << "\nЗадайте название компрессорной станции:" << endl;
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    getline(cin, cs.name);
    cout << "Задайте количество цехов компрессорной станции:" << endl;
    GetValue(cs.WorkshopsNum);
    cout << "Какое количество цехов находится в работе?" << endl;
    while (((cin >> cs.WorkingNum).fail()) || (cin.peek() != '\n') || (cs.WorkingNum > cs.WorkshopsNum) || (cs.WorkingNum <0))
    {
        if (cs.WorkingNum > cs.WorkshopsNum)
        {
            cout << "Количество работающих цехов не может быть больше, чем общее количество цехов" << endl;
            cin.clear();
            cin.ignore(INT_MAX,'\n');
        }
        else
        {
            cin.clear();
            cin.ignore(INT_MAX,'\n');
        }
    }
    cout << "Какова эффективность данной КС по стобалльной шкале?" << endl;
    cs.efficiency = GetLimValue(0,100);
    return is;
}

ostream& operator << (ostream& os, CStation& cs)
{
    os << endl << cs.CsIndx << ") Название компрессорной станции: " << cs.name
    << "\n   Количество цехов компрессорной станции: " << cs.WorkshopsNum
    << "\n   Количество работающих цехов компрессорной станции: " << cs.WorkingNum
    << "\n   Эффективность компрессорной станции (от 1 до 100): " <<  cs.efficiency << endl << endl;
    return os;
}

ofstream& operator << (ofstream& file, CStation& cs)
{
    file << cs.CsIndx << endl << cs.name << endl << cs.WorkshopsNum << endl << cs.WorkingNum << endl << cs.efficiency << endl;    
    return file;
}

ifstream& operator >> (ifstream& file, CStation& cs)
{
    file >> cs.CsIndx;
    file.ignore();
    getline(file, cs.name);
    file >> cs.WorkshopsNum >> cs.WorkingNum >> cs.efficiency;  
    return file; 
}
