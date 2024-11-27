#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "tads/HeapMuebles.cpp"
using namespace std;

int main()
{
    int n; cin>>n;
    int* hash = new int[n+1];
    HeapMuebles heap = HeapMuebles(n);

    for(int i = 0 ; i <= n; i++){
        hash[i] = -1;
    }
    for(int _ = 0;  _  < n; _++){
        int id, precio; cin>>id>>precio;
        if(hash[id] == -1 || hash[id] > precio){
            hash[id] = precio;
        }
    }
    for(int id =  1; id <=n; id++){
        if(hash[id] != -1){
            heap.insertar(id,hash[id]);
        }
    }

    int k; cin>>k;
    while(k--){
        cout<<heap.top()<<'\n';
        heap.pop();
    }
    return 0;
}