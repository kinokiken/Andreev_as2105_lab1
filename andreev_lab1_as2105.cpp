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

int main()
{
    setlocale(LC_ALL, "rus"); 

    Pipes P;
    CStation CS;
    All A;
    unordered_map<int, Pipes> pm;
    unordered_map<int, CStation> csm;

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
            A.PipeEdit(A.pm);
            break;
        case 5:
            A.CsEdit(A.csm);
            break;
        case 6:
            A.SaveParameters (A.pm, A.csm);
            break;
        case 7:
            A.LoadParameters (A.pm, A.csm);
            P.Pplus = A.pm.size();
            CS.Cplus = A.csm.size();
            break;
        case 8:
            A.PipeFilter(pm);
            break;
        case 9:
            A.CsFilter(csm);
            break;
        case 10:
            A.PBatchEdit(pm);
            break;
        case 11:
            A.CsBatchEdit(csm);
            break;
        case 12: {
            cout << "Что сделать: 1. Присоединить 0. Отсоединить\n" << endl;
            int chose = GetLimValue(0, 1);
            if (chose == 1) 
            {
                if ((A.csm.size() < 2) or (A.pm.size() < 1))
                    cout << "Недостаточно объектов для создания сети\n" << endl;
                else
                    cin >> A;
            }
            else
                if (A.graph.size() != 0)
                    cout << "\nProverim pozhe";
                else
                    cout << "There is no systems!"<<endl;

            for (auto& [i, j] : A.graph)
                cout << i << ") " << j.id_ent << " " << j.id_ex << " " << j.id_pip << endl;

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