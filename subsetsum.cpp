#include <bits/stdc++.h>
using namespace std;
#define nl cout<<endl
vector<vector<int>>res;
int a[]={3, 34, 4, 12, 5, 2};

void solve(vector<int>&v,int current_sum,int target,int i){
    if(current_sum==target){
        for (int num : v) {
            std::cout << num << " ";
        }
        res.push_back(v);
        return;
    }
    else if(current_sum>target || i>=6){
       // v.clear();
        return;
    }
    else{
       
        solve(v,current_sum,target,i+1);
         v.push_back(a[i]);
        solve(v,current_sum+a[i],target,i+1);
        v.pop_back();
    }
}

int main()
{
    vector<int>v;

    solve(v,0,9,0);
    
}