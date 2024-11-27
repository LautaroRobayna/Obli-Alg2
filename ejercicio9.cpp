#include <iostream>
#include <string>
#include <limits>
#include <iomanip>

using namespace std;

const int INF = 1e9; // A large positive number

int main() {
    int n; cin >> n;
    int *playersCuality = new int[n+1];
    int *playersPrice = new int[n+1];
    bool *playersForeign = new bool[n+1];

    for(int i = 1; i <= n; i++){
        int cuality = 0;
        for(int j = 0; j < 6; j++){
            int value; cin >> value;
            cuality += value;
        }
        cuality /= 6;
        string ff; cin >> ff;
        int price; cin >> price;
        string foreign; cin >> foreign;
        string confidence; cin >> confidence;

        if(confidence == "Baja"){
            cuality -= 5;
        } else if(confidence == "Alta"){
            cuality += 5;
        }

        if(ff == "Lesionado"){
            cuality = 0;
        } else if(ff == "Mala") {
            cuality -= 5;
        } else if (ff == "Buena") {
            cuality += 5;
        }

        playersCuality[i] = cuality;
        playersPrice[i] = price;
        playersForeign[i] = (foreign == "Si");
    }

    int money, E; cin >> money >> E;

    // Initialize DP table
    int ****dp = new int***[n+1];
    for (int i = 0; i <= n; i++) {
        dp[i] = new int**[12];
        for (int j = 0; j <= 11; j++) {
            dp[i][j] = new int*[money+1];
            for (int g = 0; g <= money; g++) {
                dp[i][j][g] = new int[E+1];
                for (int e = 0; e <= E; e++) {
                    dp[i][j][g][e] = -INF;
                }
            }
        }
    }

    dp[0][0][0][0] = 0;

    // DP computation
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= 11; j++) {
            for (int g = 0; g <= money; g++) {
                for (int e = 0; e <= E; e++) {
                    dp[i][j][g][e] = max(dp[i][j][g][e], dp[i-1][j][g][e]);

                    int newE = e + (playersForeign[i] ? 1 : 0);
                    if (j > 0 && g >= playersPrice[i] && newE <= E) {
                        dp[i][j][g][newE] = max(dp[i][j][g][newE], dp[i-1][j-1][g - playersPrice[i]][e] + playersCuality[i]);
                    }
                }
            }
        }
    }

    // Calculate result
    int maxValuation = -INF;
    for (int g = 0; g <= money; g++) {
        for (int e = 0; e <= E; e++) {
            if (dp[n][11][g][e] > maxValuation) {
                maxValuation = dp[n][11][g][e];
            }
        }
    }

    if (maxValuation < 0) {
        cout << "No es posible seleccionar 11 jugadores dentro del presupuesto y límite de extranjeros." << endl;
    } else {
        cout << maxValuation / 11 << endl;
    }

    return 0;
}
