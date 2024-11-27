
int hacerPositivo(int i) {
    if (i < 0)
    {
        return i * -1;
    }
    return i;
}

int max(int a, int b) {
    return a > b ? a : b;
}
long long max(long long a, long long b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}
long long  min(long long  a, long long  b) {
    return a < b ? a : b;
}
//PRE: n >= 1

bool esPrimo(int n){
    for(int i = 2; i*i <= n; i++){
        if(n%i==0){
            return false;
        }
    }
    return true;
}

//PRE: n >= 1
int primoSup(int n){
    n++;
    while(!(esPrimo(n))){
        n++;
    }
    return n;
}

