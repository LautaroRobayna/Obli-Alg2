
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

int min(int a, int b) {
    return a < b ? a : b;
}

bool esPrimo(int num) {
            if(num <= 1) {
                return false;
            } else {
                for (int i = 2; i < num/2; i++)
                {
                    if(num%i==0) {
                        return false;
                    }
                }
                return true;
            }
        }

int primoSup(int num){
            while(!esPrimo(++num));
            return num;
            // 302782: Pedro Chialanza
        }