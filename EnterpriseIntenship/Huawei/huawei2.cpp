//
// Created by 12638 on 2021/4/7.
//
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
// dp[i] 当前位置的时长
//dp[0][0] = a[0][0]
// 递归 dp[i][j ] = dp[i-1][j] + a[i][j], dp[]
//return dp[row][col] 首先都初始化为-1
//把可能的值都记下来,然后排序选择最接近的.

int main(){
    vector<vector<vector<int>>> dp ;

    int mat[15][15] = { 0 };
    int t,row,col;
    cin >>  row>> col >> t;  //cin遇到空格就中断

    for(int i = 0 ; i < row ; i ++) {
        for (int j = 0 ; j < col ; j ++){
            cin >> mat[i][j];
        }
    }
    dp.resize(row);//r行
    for (int k = 0; k < row; ++k){
        dp[k].resize(col);//每行为c列
    }
    dp[0][0].emplace_back( mat[0][0]);
    for(int i = 1 ; i < row ; i ++) {
        dp[i][0].emplace_back(dp[i-1][0][0] +mat[i][0]); // 往下只有一种路
    }
    for(int i = 1 ; i < col ; i ++) {
        dp[0][i].emplace_back( dp[0][i-1][0] + mat[0][i])  ; // 往右只有一种路
    }
    for(int i = 1 ; i < row ; i ++) {
        for (int j = 1 ; j < col ; j ++){
            for (int k = 0 ; k < dp[i][j-1].size() ; k++) {
                if (dp[i][j - 1][k] + mat[i][j] <= t) {
                    dp[i][j].emplace_back( dp[i][j - 1][k] + mat[i][j]);// 往右
                }
            }
            for (int k = 0 ; k < dp[i - 1][j].size() ; k++) {
                if (dp[i - 1][j][k] + mat[i][j] <= t) {
                    dp[i][j].emplace_back( dp[i - 1][j][k] + mat[i][j]);//往下
                }
            }
        }
    }
    sort( dp[row-1][col-1].begin(),dp[row-1][col-1].end());
    for(int i = 0 ; i < dp[row-1][col-1].size() ;i++ ) {
        if (dp[row - 1][col - 1][i] < t && dp[row - 1][col - 1][i] > 0 )
            i++;
        else {
            if (i > 0)
                cout << dp[row - 1][col - 1][i - 1];//上一个是最接近的. 这个是大一些的.
            else
                cout << -1;
        }
    }
    return 0;
}

////
//// Created by 12638 on 2021/4/7.
////
//#include <iostream>
//#include <vector>
//#include <string>
//#include <algorithm>
//using namespace std;
//// dp[i] 当前位置的时长
////dp[0][0] = a[0][0]
//// 递归 dp[i][j ] = dp[i-1][j] + a[i][j], dp[]
////return dp[row][col] 首先都初始化为-1
//
//int main(){
//    int dp[15][15] = {0};
//    int mat[15][15] = { 0 };
//    int t,row,col;
//    cin >>  row>> col >> t;  //cin遇到空格就中断
//    for(int i = 0 ; i < row ; i ++) {
//        for (int j = 0 ; j < col ; j ++){
//            cin >> mat[i][j];
//        }
//    }
//    dp[0][0] = mat[0][0];
//    for(int i = 1 ; i < row ; i ++) {
//        dp[i][0] = dp[i-1][0] +mat[i][0] ; // 往下只有一种路
//    }
//    for(int i = 1 ; i < col ; i ++) {
//        dp[0][i] =  dp[0][i-1] + mat[0][i] ; // 往右只有一种路
//    }
//    for(int i = 1 ; i < row ; i ++) {
//        for (int j = 1 ; j < col ; j ++){
//            if(dp[i][j-1] + mat[i][j] < t){
//                dp[i][j] = dp[i][j-1] + mat[i][j];// 往右
//            }
//            if(dp[i-1][j] + mat[i][j] < t ){
//                dp[i][j] = min(dp[i][j] ,dp[i-1][j] + mat[i][j]);//往下
//            }
//        }
//    }
//    if(dp[row-1][col-1] < t)
//        cout << dp[row-1][col-1];
//    else
//        cout << -1;
//    return 0;
//}

//int S[100010];
//int Find(int x){
//    if(S[x] <= -1)  //����Ǹ��Ǿͷ���
//        return x;
//    return S[x] = Find(S[x]);
//}
////
////  �����������Ǿͺϲ��� sizeС�����ӵ�size��ġ�
//void Union(int x1,int x2){
//    int root1,root2;
//    root1 = Find(x1);  //���ҵ��ڵ�ĸ�
//    root2 = Find(x2);
//    if( root1 == root2 )
//        return ;   //root isn't equal then we merge them
//    if(S[root1] < S[root2]){
//        S[root1]  += S[root2];
//        //	cout  << S[root1] << S[root2] ;
//        S[root2] = root1;
//        //	cout  << root1 ;
//    }
//    else{
//        S[root2]  += S[root1];
//        //	cout  << S[root1] << S[root2] ;
//        S[root1] = root2;
//    }
//}
//int main(){
//    int n;
//    cin >> n;
//    cin.get();
//    for(int i = 0; i < n ;i++){
//        S[i] = -1 ;   // һ��ʼ��size����1 ��û�и���
//    }
//    vector<string> st(n);
//    vector<string> want(n);
//    for (int i = 0 ; i < n ; i ++){
//        getline(cin, st[i], ' ');//遇到空格停止，读取第一个字符串串
//        getline(cin, want[i], '\n');//遇到换行停止，此时读取了第二个字符串
//    }
//    //cout << st[0] << want[0] << endl;
//    for (int i = 0 ; i < n ; i ++){
//        string  tmp = st[i];
//        int pos = 0;
//        int min = 0 , max = n-1 ;// binarysearch
//        int mid =  max + ((max-min)>>1);
//        for( ; min <=  max ; j ++){
//            if(st[mid] == want[i]){
//                pos = mid;
//                break;
//            }
//        }
//        Union(i,pos);
//    }
//    int max = 0 ;
//    for (int i = 0 ; i < n ; i ++){
//        if(S[i] <= -1 ){
//            max ++;
//        }
//    }
//    cout << max;
//    return 0;
//}
