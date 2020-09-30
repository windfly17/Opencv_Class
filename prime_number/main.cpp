#include <iostream>
using namespace std;
int prime(int n);
int main() {
    prime(10000);
    return 0;
}
int prime(int n){
    int i;
    int a=0;
    bool *prime = new bool[n+1];
    for(i=2;i<n;i++){
        prime[i] = true;
    }
    for(i=2;i<=n;i++){
        if(prime[i]){
            cout<<i<<" ";
            a++;
            for(int j=i+i;j<=n;j+=i){
                prime[j] = false;
            }
        }
    }
    cout<< endl;
    cout<<"There are " <<a <<" prime numbers" <<endl;
    return 0;
}
