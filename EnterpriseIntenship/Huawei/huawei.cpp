//
// Created by 12638 on 2021/4/23.
//
#include<iostream>
#include <string>
using namespace std;
//太麻烦了!! 一个是用map, iv, ix, i, x 加到map中
// map<string,int> m; m.insert('i',1); m.insert('ix',4);看如果it和it+1在map中, 就+4,然后右移2位, 否则就加it对应的值1,右移一位,
// 这样拓展性好. 或者比第二位大, 加进去, 比第二位小,那就减去I

int main(){
    string s ;
    cin >>s;
    char lastnum = 'B';
    int sum = 0 ;
    for(int i = 0 ;i < s.size(); i ++){
        if(s[i] == 'I'){
            sum ++;
        }
        else if(s[i] == 'V'){
            sum = lastnum == 'I' ? sum + 5 - 2 : sum + 5;
        }
        else if(s[i] == 'X'){
            sum = lastnum == 'I' ? sum + 10 - 2 : sum + 10;
        }
        else if(s[i] == 'L'){
            sum = lastnum == 'X' ? sum + 50 - 20 : sum + 50;
        }
        else if(s[i] == 'C'){
            sum = lastnum == 'X' ? sum + 100 - 20 : sum + 100;
        }
        else if(s[i] == 'D'){
            sum = lastnum == 'C' ? sum + 500 - 200 : sum + 500;
        }
        else if(s[i] == 'M'){
            sum = lastnum == 'C' ? sum + 1000 - 200 : sum + 1000;
        }
        lastnum = s[i];
    }
    cout << sum <<endl;
    return 0;
}