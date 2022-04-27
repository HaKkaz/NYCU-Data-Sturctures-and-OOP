#include <iostream>
using namespace std;

// Enter your code here

struct node{
    int val;
    node *lc , *rc;
    node(int _val):val(_val){lc = rc = nullptr;}

    void insert(int _val){
        if(_val <= val){
            if(lc == nullptr){
                lc = new node(_val);
            }
            else{
                lc->insert(_val);
            }
        }
        else{
            if(rc == nullptr){
                rc = new node(_val);
            }
            else{
                rc->insert(_val);
            }
        }
    }
}*root;

void dfs(node *cur , int type){
    if(type == 0) cout << cur->val << '\n';
    if(cur->lc) dfs(cur->lc , type);
    if(type == 1) cout << cur->val << '\n';
    if(cur->rc) dfs(cur->rc , type);
    if(type == 2) cout << cur->val << '\n'; 
}

int main() {
    // Enter your code here. Read input from STDIN. Print output to STDOUT 
    int n; 
    for(int i = 0 ; cin >> n ; i++){
        if(i == 0) root = new node(n);
        else root->insert(n);
    }
    cout << "PreOrder" << endl;
    dfs(root , 0);
    cout << "InOrder" << endl;
    dfs(root , 1);
    cout << "PostOrder" << endl;
    dfs(root , 2);
  
    return 0;
}