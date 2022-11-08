#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "Utils.cpp"
#include "cs.cpp"
#include "pipe.cpp"

using namespace std;

int main()
{
    setlocale(LC_ALL, "rus"); 

    Pipes P;
    CStation CS;
    unordered_map<int, Pipes> pipes_map;
    unordered_map<int, CStation> cs_map;

    while (true)
    {
        switch(Menu())
        {
        case 1:{
            cin >> P;
            pipes_map.insert({P.GetPid(), P});
            break;}
        case  2:{
            cin >> CS;
            cs_map.insert({CS.GetCid(), CS});
            break;}
        case 3:{
            ShowPipeParameters (pipes_map);
            ShowCsParameters (cs_map);
            break;}
        case 4:
            PipeEdit(pipes_map);
            break;
        case 5:
            CsEdit(cs_map);
            break;
        case 6:
            SaveParameters (pipes_map, cs_map);
            break;
        case 7:
            LoadParameters (pipes_map, cs_map);
            P.Pplus = pipes_map.size();
            CS.Cplus = cs_map.size();
            break;
        case 8:
            PipeFilter(pipes_map);
            break;
        case 9:
            CsFilter(cs_map);
            break;
        case 10:
            PBatchEdit(pipes_map);
            break;
        case 11:
            CsBatchEdit(cs_map);
            break;
        case 0:
            return 0;
            break;
        default:
            cout << "Выберите опцию из предложенных" << endl;
            break;
        }
    }
}
