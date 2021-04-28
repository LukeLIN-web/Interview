//
// Created by 12638 on 2021/4/18.
//
//
//#include <iostream>
//#include <map>
//#include <string>
//#include <vector>
//using namespace std;
//int main() {
//    //map 放开始和末尾位置
//    int N;
//    cin >>N;
//    int x, flag;
//    string y ;
//    map<string,pair<int,int>> m1;
//    vector<int> vt;
//    for (int i = 0; i < N; i++) {
//        cin >> flag;
//        if(flag == 1){
//            cin >> x ;
//            cin >> y;
//            auto it = m1.find(y);
//            if(it != m1.end()) {
//                vt.insert(vt.begin() + it->second.second +1, x);
//                int j = it->second.first;
//                int k = it->second.second;
//                m1[y] = make_pair(j,k+1);
//                // 如果存在那就插入到最后
//                for(auto it2 : m1){
//                    if(it2.first != it->first && it2.second.first > it->second.first) {
//                        int m = it2.second.first;
//                        int n = it2.second.second;
//                        m1[it2.first] = make_pair(m+1,n+1);
//                    }
//                }
//            }
//            else{
//                vt.emplace_back(x);
//                m1[y] = make_pair(vt.size()-1,vt.size() -1) ;
//            }
//            cout << vt[0] <<"debug 1flag  " ;
//            for (int i = 1; i < vt.size(); i++){
//                cout << " " << vt[i] ;
//            }
//            cout <<endl;
//        }
//        else{
//            string y1,y2;
//            cin >> y1;
//            cin >>y2;
//            int it1begin = m1.find(y1)->second.first;
//            int it1end =  m1.find(y1)->second.second;
//            int it2begin = m1.find(y2)->second.first;
//            int it2end =  m1.find(y2)->second.second;
//            while ( it2end >= it2begin && it1end >= it1begin ){
//                swap(vt[it2end], vt[it1end]);
//                it2end--;
//                it1end--;
//            }
//            while(it1end >= it1begin){
//                int tmp = vt[it1end];
//                vt.insert(vt.begin() + it2begin, tmp);// it2begin前插入
//                vt.erase(vt.begin() + it1end);
//                it1end -- ;
//            }
//            while(it2end >= it2begin){
//                int tmp = vt[it2end];
//                vt.insert(vt.begin() + it1begin, tmp);// it2begin前插入
//                vt.erase(vt.begin() + it2end);
//                it2end -- ;
//            }
//            // 调换位置完成
//            cout << vt[0] <<"debug 2flag  " ;
//            for (int i = 1; i < vt.size(); i++){
//                cout << " " << vt[i] ;
//            }
//            cout << endl;
//        }
//    }
//    cout << vt[0];
//    for (int i = 1; i < vt.size(); i++){
//        cout << " " << vt[i] ;
//    }
//    return 0;
//}


// 2 ti
//int main() {
//    int n , m , k ;
//    cin >> n >> m >> k ;
//    int x, y ;
//    vector<pair<int,int>> am;
//    vector<pair<int,int>> bm;
//    int sum = 0 ;
//    for (int i = 0 ; i < n;  i++){
//        cin >> x >> y ;
//        if(y>=k){
//            sum += x*y;
//        }
//    }
//    cout << sum ;
//    int sum2  = 0 ;
//    for (int i = 0 ; i < m;  i++){
//        cin >> x >> y ;
//        if(y>=k){
//            sum2 += x*y;
//        }
//    }
//    cout << " " << sum2 << endl;
//    if(sum > sum2)
//        cout << "A";
//    else
//        cout << "B";
//    return 0;
//}
