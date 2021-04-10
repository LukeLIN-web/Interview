//
// Created by 12638 on 2021/4/10.
//
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

// 
//总得分30％
//正确性16％
//速度50％
class Solution {
public:
    int findLengthOfShortestSubarray(vector<int>& arr) {
        int N = arr.size();
        if(N == 0 || N == 1){
            return 0;
        }
        int left = 1;
        while(left < N && arr[left] >= arr[left -1]){
            left++;// find left longest nondecreasing sequence
        }
        //[0,left)
        int right = N -1;
        while(right > 0 && arr[right] >= arr[right-1]){
            right--;// find right longest nondecreasing sequence
        }
        // [right,N)
        if(right == 0 || left == N)
            return 0 ;// all nondecreasing
        if(right == N-1 && left == 1){
            if( arr[left-1] <= arr[right]       )
                return N-2;
            else
                return N-1;// 我这里写错了!我微软笔试写成 n了. 而且可能不用去掉n-1, 可能可以去掉中间留下两边.
        }
        int result = N - left ;// slice from left to N
        // find the link point between left sequence and right sequence
        for (int i = 0; i < left; ++i) {
            while(right <= N-1 &&  arr[right] < arr   [i] ){
                right++;
            }
            result =  min(result,right-1 -i );
        }
        return result;
    }
};


int main(){
    vector<int> A = {16,10,0,3,22,1,14,7,1,12,15};
    int w = Solution(A);
    cout <<w ;
    return 0;
}