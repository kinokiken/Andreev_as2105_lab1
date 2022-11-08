#include "pipe.h"
#include "Utils.h"

using namespace std;

int Pipes::Pplus = 0;

int Pipes::GetPid ()
{
    return PipeIndx;
}

int Pipes::up_pid() 
{
    return PipeIndx = ++Pplus;
}

bool Pipes::GetRepair()
{
    return repair;
}

void Pipes::SetRepair(bool a)
{
    repair = a;
}

string Pipes::GetPname()
{
    return pname;
}

void Pipes::SetPid(int i) 
{
    PipeIndx = i;
}

void CinClear()
{
    cout << "Задайте корректное значение:" << endl;
    cin.clear(); //https://overcoder.net/q/37792/%D0%BF%D0%BE%D1%87%D0%B5%D0%BC%D1%83-%D0%BC%D1%8B-%D0%B1%D1%83%D0%B4%D0%B5%D0%BC-%D0%B2%D1%8B%D0%B7%D1%8B%D0%B2%D0%B0%D1%82%D1%8C-cinclear-%D0%B8-cinignore-%D0%BF%D0%BE%D1%81%D0%BB%D0%B5-%D1%87%D1%82%D0%B5%D0%BD%D0%B8%D1%8F-%D0%B2%D0%B2%D0%BE%D0%B4%D0%B0
    cin.ignore(INT_MAX,'\n');    
}

string Pipes::RepairMsg(bool repair)
{
    if (repair == 0)
    {
        return ("Труба находится в ремонте");
    }
    else
    {
        return ("Труба находится в работе");
    }
}

istream& operator >> (istream& is, Pipes& pipe)
{
    pipe.up_pid();
    cout << "\nЗадайте название данной трубы:" << endl;
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    getline(cin, pipe.pname);
    cout << "Задайте длину трубы:" << endl;
    GetValue(pipe.length);
    cout << "Задайте диаметр трубы:" << endl;
    GetValue(pipe.diameter);
    cout << "Находится ли эта труба в ремонте? 0-да, 1-нет" << endl;
    pipe.repair = GetLimValue(0,1);
    cout << "\n Вы успешно задали параметры трубы, возвращаем Вас в меню" << endl << endl;
    return is;
}

ostream& operator << (ostream& os, Pipes& pipe)
{
    os << endl << pipe.PipeIndx << ") Параметры трубы с названием " << pipe.pname << ":" << "\n   Длина трубы: " << pipe.length 
    << "\n   Диаметр трубы: " << pipe.diameter << endl << "   " << pipe.RepairMsg(pipe.repair) << endl;
    return os;
}

ofstream& operator << (ofstream& file, Pipes& pipe)
{
    file << pipe.PipeIndx << endl << pipe.pname << endl << pipe.length << endl << pipe.diameter << endl << pipe.repair << endl;
    return file;
}

ifstream& operator >> (ifstream& file, Pipes& pipe)
{
    file >> pipe.PipeIndx;
    file.ignore();
    getline(file, pipe.pname);
    file >> pipe.length >> pipe.diameter >> pipe.repair;
    return file;
}

