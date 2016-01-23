#include <iostream>
#include <map>
#include <array>

// simple recursive function
bool winRecursive(int a, int b, int c){
    bool val1 = false, val2 = false, val3 = false;

//    std::cout << "num1: " << a << " num2: " << b << " num3: " << c << std::endl;
    if( a==0 && b==0 && c==0 ) return false; // if all piles are 0 then we have lost
    if( a==0 && b==0 || a==0 && c==0 || b==0 && c==0) return true; // if any of the other 2 piles are zero then we have won

    for(int i = 1; i < a+1; ++i ){
        val1 = (!winRecursive(a - i, b, c));
    }

    for(int j = 1; j < b+1; ++j ){
        val2 = (!winRecursive(a, b - j, c));
    }

    for(int k = 1; k < c+1; ++k ){
        val3 = (!winRecursive(a, b, c - k));
    }

    return (val1 && val2 && val3);
}

// recursion with a memoizing algo.
bool winRecursiveWithMemoizing(int a, int b, int c, std::map<bool,std::map<bool,std::map<bool,bool>>>& cache){

    std::map<bool,std::map<bool,std::map<bool,bool>>>::iterator cacheIter = cache.find(cache[a][b][c]);
    if(cacheIter != cache.end()) return cache[a][b][c];

    if( a==0 && b==0 && c==0 ) return false;  // if all piles are 0 then we have lost
    if( a==0 && b==0 || a==0 && c==0 || b==0 && c==0) return true; // if any of the other 2 piles are zero then we have won

    for (int i = 1; i < a+1; ++i) {
        if(a-i < 0 ) break;
        cache[a-i][b][c] = !winRecursiveWithMemoizing(a - i, b, c, cache);
    }

    for (int j = 1; j < b+1; ++j) {
        if(b-j < 0 ) break;
        cache[a][b-j][c] = !winRecursiveWithMemoizing(a, b - j, c, cache);
    }

    for (int k = 1; k < c+1; ++k) {
        if(c-k < 0 ) break;
        cache[a][b][c-k] = !winRecursiveWithMemoizing(a, b, c - k, cache);
    }

    return cache[a][b][c];
}

// Dynamic function
bool winDynamic(int a, int b, int c){
    int cache[a+1][b+1][c+1];

    for(int i = 0; i < a; ++i){
        for(int j = 0; j < b; ++j){
            for(int k = 0; k < c; ++k){
                if( i==0 && j==0 && k==0 ) break;
                if( i==0 && j==0 || i==0 && k==0 || j==0 && k==0) break; // if any of the other 2 piles are zero then we have won

                for(int l = 1; l < a+1; ++l ){
                    if(i-l < 0 ) break;
                    cache[i][j][k] = cache[i - l][j][k];
                }

                for(int m = 1; m < b+1; ++m ){
                    if(j-m < 0 ) break;
                    cache[i][j][k] = cache[i][j - m][k];
                }

                for(int n = 1; n < c+1; ++n ){
                    if(k-n < 0 ) break;
                    cache[i][j][k] = cache[i][j][k - n];
                }
            }
        }
    }

    return cache[a][b][c];
}

int main() {
    // declarations
    int num1, num2, num3;
    std::map<bool,std::map<bool,std::map<bool,bool>>> cache;

    srand(time(NULL));
    // setup 3 random numbers between 1 and 1000
    num1 = rand() % 10 + 1;
    num2 = rand() % 10 + 1;
    num3 = rand() % 10 + 1;
    std::cout << "pile numbers:\n\t\tnum1: " << num1 << " num2: " << num2 << " num3: " << num3 << std::endl;

    // call recursive function
    std::cout << "**** recursive algo ****" << std::endl;
    if(winRecursive(num1, num2, num3)){
        std::cout << "You win\n\n" << std::endl;
    } else {
        std::cout << "You lost\n\n" << std::endl;
    }

    // reset the random numbers
    num1 = rand() % 100 + 1;
    num2 = rand() % 100 + 1;
    num3 = rand() % 100 + 1;

    std::cout << "pile numbers:\n\t\tnum1: " << num1 << " num2: " << num2 << " num3: " << num3 << std::endl;

    // call memoizing
    std::cout << "**** memoizing ****" << std::endl;
    if(winRecursiveWithMemoizing(num1, num2, num3, cache)){
        std::cout << "You win\n\n" << std::endl;
    } else {
        std::cout << "You lost\n\n" << std::endl;
    }

    // call DP
    std::cout << "**** DP ****" << std::endl;
    if(winDynamic(num1, num2, num3)){
        std::cout << "You win" << std::endl;
    } else {
        std::cout << "You lost\n\n" << std::endl;
    }

    return 0;
}