// class Solution:
//     def romanToInt(self, s: str) -> int:
//         dict = { "I":1, "V":5,"X":10,"L":50,"C":100,"D":500,"M":1000,"IV":4,"IX":9,"XC":90,"XL":40, "CM":900, "CD":400}
//         res = 0
//         n = len(s)
//         i = 0
//         while i < n:
//             if i +1 < n:
//                 tmp = s[i] + s[i+1]
//                 i +=1 
//                 print(tmp)
//                 if tmp not in dict:
//                     print(tmp)
//                     i -=1
//                     tmp = s[i]
//             else:
//                 tmp =  s[i]
//             res += dict[tmp]
//             i +=1
//         return res
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