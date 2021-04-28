#include<iostream>
using namespace std;
int main(){
    string s ;
    cin >> s;
    char lastnum;
    int sum = 0 ;
    for(int i = 0 ;i < s.size(); i ++){
        if(s[i] == 'I'){
            sum ++;
        }
        else if(s[i] == 'V'){
            if(lastnum == 'I'){
                sum  = sum + 5 -2;
            }
            else{
                sum = sum +5;
            }
        }
        else if(s[i] == 'X'){
            if(lastnum == 'I'){
                sum  = sum + 10 -2;
            }
            else{
                sum = sum +10 ;
            }
        }
        else if(s[i] == 'L'){
            if(lastnum == 'X'){
                sum  = sum + 50 -20;
            }
            else{
                sum = sum +50 ;
            }
        }
        else if(s[i] == 'C'){
            if(lastnum == 'X'){
                sum  = sum + 100 -20;
            }
            else{
                sum = sum +100 ;
            }
        }
        else if(s[i] == 'D'){
            if(lastnum == 'C'){
                sum  = sum + 500 -200;
            }
            else{
                sum = sum +500 ;
            }
        }
        else if(s[i] == 'M'){
            if(lastnum == 'C'){
                sum  = sum + 1000 -200;
            }
            else{
                sum = sum + 1000 ;
            }
        }
    }
    return 0;
}