#include <iostream>
#include <vector>
#include <cmath>


using namespace std;
// Enter your code here.

const int MAXN = 1e6;
int heap[MAXN];
int heap_size;

void insert(int val){
    int cur = heap_size;
    heap[++heap_size] = val;
    while((cur>>1) && heap[cur>>1] > heap[cur]){
        swap(heap[(cur>>1)] , heap[cur]);
        cur >>= 1;
    }
}

int pop(){
    int ret = heap[1];
    swap(heap[1] , heap[heap_size]);
    heap_size--;
    int cur = 1;
    while(true){
        int a = cur * 2 <= heap_size ? heap[cur * 2] : 2e9;
        int b = cur * 2 + 1 <= heap_size ? heap[cur * 2 + 1] : 2e9;
        if(a == b  && a == 2e9) break;
        else if( a <= b && a <= heap[cur]) swap(heap[cur * 2] , heap[cur]) , cur = cur * 2;
        else if( b <= heap[cur]) swap(heap[cur * 2 + 1] , heap[cur]) , cur = cur * 2 + 1;
        else break;
    }
    return ret;
}

int main() {
    // Enter your code here. Read input from STDIN. Print output to STDOUT 
    int n; 
    while(cin >> n ,  n){
        int ans = 0;
        heap_size = 0;
        for(int i=0 ; i<n ; ++i){
            int x; cin >> x;
            insert(x);
        }
        // return 0;
        while(heap_size > 1){
            int a = pop();
            int b = pop();
            insert(a+b);
            ans += a + b;
        }
        cout << ans << '\n';
    }
    return 0;
}