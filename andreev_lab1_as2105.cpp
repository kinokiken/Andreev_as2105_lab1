#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "Utils.h"
#include "process.h"
#include "cs.h"
#include "pipe.h"

using namespace std;

void create_graph(All& c);

int main()
{
    setlocale(LC_ALL, "rus"); 

    Pipes P;
    CStation CS;
    All A;
    All::System S;

    while (true)
    {
        switch(A.Menu())
        {
        case 1:{
            cin >> P;
            A.pm.insert({P.GetPid(), P});
            break;}
        case  2:{
            cin >> CS;
            A.csm.insert({CS.GetCid(), CS});
            break;}
        case 3:{
            A.ShowPipeParameters (A.pm);
            A.ShowCsParameters (A.csm);
            break;}
        case 4:
            A.PipeEdit(A.pm, A.graph);
            break;
        case 5:
            A.CsEdit(A.csm, A.graph);
            break;
        case 6:
            A.SaveParameters (A.pm, A.csm);
            break;
        case 7:
            A.LoadParameters (A.pm, A.csm, A.graph);
            P.Pplus = A.pm.size();
            CS.Cplus = A.csm.size();
            S.max_ids = A.graph.size()+1;
            break;
        case 8:
            A.PipeFilter(A.pm);
            break;
        case 9:
            A.CsFilter(A.csm);
            break;
        case 10:
            A.PBatchEdit(A.pm);
            break;
        case 11:
            A.CsBatchEdit(A.csm);
            break;
        case 12: {
            create_graph(A);
            break;
        }
        case 0:
            return 0;
            break;
        default:
            cout << "Выберите опцию из предложенных" << endl;
            break;
        }
    }
}

void create_graph(All& c) 
{
    if (c.graph.size() != 0) 
    {
        cout << "Связи: " << endl;
        for (auto& [i, j] : c.graph)
            cout << i << ") " << j.id_ent << " " << j.id_ex << " " << j.id_pip << endl;
    }
    cout << "\nЧто сделать: 1. Присоединить 2. Отсоединить 3. Топологическая сортировка\n" << endl;
    int chose = GetLimValue(1, 3);
    if (chose == 1) 
    {
        if ((c.csm.size() < 2) or (c.pm.size() < 1))
            cout << "Недостаточно объектов для создания сети\n" << endl;
        else
            cin >> c;
    }
    else if (chose == 3)
    {
        c.fill_graphl(c.graph);
        c.sort();
    }
    else
    {
        if (c.graph.size() != 0) {
            cout << "Введите номер КС на входе: " << endl;
            int ent = GetLimValue(0, CStation::Cplus);
            cout << "Введите номер КС на выходе: " << endl;
            int ext = GetLimValue(0, CStation::Cplus);
            if (ent == ext) 
            {
                cout << "Выберите другую КС!: ";
                ext = GetLimValue(0, CStation::Cplus);
            }
            auto a = c.graph.cbegin();
            while (a != c.graph.cend()) {
                if (((*a).second.id_ent == ent) and ((*a).second.id_ex == ext)) {
                    c.graph.erase(a);
                    break;
                }
                a++;
            }
        }
    }
    cout << endl;
    for (auto& [i, j] : c.graph)
        cout << i << ") " << j.id_ent << " " << j.id_ex << " " << j.id_pip << endl;
}