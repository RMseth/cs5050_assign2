#include <iostream>
#include <vector>
#include <string>

// simple recursive function
bool winRecursive(int a, int b, int c){
    bool val1 = false, val2 = false, val3 = false;

    std::cout << "num1: " << a << " num2: " << b << " num3: " << c << std::endl;
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
bool winRecursiveWithMemoizing(int a, int b, int c){
    std::vector<std::vector<std::vector<bool>>> cache;
    std::cout << "num1: " << a << " num2: " << b << " num3: " << c << std::endl;

    if( a==0 && b==0 && c==0 ) return false;  // if all piles are 0 then we have lost
    if( a==0 && b==0) return true; // if any of the other 2 piles are zero then we have won
    if( a==0 && c==0) return true;
    if( b==0 && c==0) return true;

    for (int i = 1; i < a+1; ++i) {
        if(!winRecursiveWithMemoizing(a - i, b, c)){
            cache[a-i][b][c] = winRecursiveWithMemoizing(a - i, b, c);
        }
    }

    for (int j = 1; j < b+1; ++j) {
        if(!winRecursiveWithMemoizing(a, b - j, c)){
            cache[a][b - j][c] = winRecursiveWithMemoizing(a, b - j, c);
        }
    }

    for (int k = 1; k < c+1; ++k) {
        if(!winRecursiveWithMemoizing(a, b, c - k)){
            cache[a][b][c - k] = winRecursiveWithMemoizing(a, b, c - k);
        }
    }

    return cache[a][b][c];
}

// Dynamic function
bool winDynamic(int a, int b, int c){
    std::vector<std::vector<std::vector<bool>>> cache;

    std::cout << "num1: " << a << " num2: " << b << " num3: " << c << std::endl;

    for(int i = 0; i < a; ++i){
        for(int j = 0; j < b; ++j){
            for(int k = 0; k < c; ++k){
                if(i == 0 && j == 0 && k == 0) break;

                for(int i = 0; i < a+1; ++i ){
                    cache[i][j][k] = cache[a - i][b][c];
                }

                for(int j = 0; j < b+1; ++j ){
                    cache[i][j][k] = cache[a][b - j][c];
                }

                for(int k = 0; k < c+1; ++k ){
                    cache[i][j][k] = cache[a][b][c - k];
                }
            }
        }
    }

    return cache[a][b][c];
}

int main() {

    // declarations
    int num1, num2, num3;

    srand(time(NULL));
    // setup 3 random numbers between 1 and 1000
    num1 = rand() % 10 + 1;
    num2 = rand() % 10 + 1;
    num3 = rand() % 10 + 1;
    std::cout << "num1: " << num1 << " num2: " << num2 << " num3: " << num3 << std::endl;

    // call recursive function
    if(winRecursive(num1, num2, num3)){
        std::cout << "You win" << std::endl;
    }

    // reset the random numbers
    num1 = rand() % 100 + 1;
    num2 = rand() % 100 + 1;
    num3 = rand() % 100 + 1;

    std::cout << "num1: " << num1 << " num2: " << num2 << " num3: " << num3 << std::endl;

    // call memoizing
//    if(winRecursiveWithMemoizing(num1, num2, num3)){
//        std::cout << "You win" << std::endl;
//    }

    // call DP
//    if(winDynamic(num1, num2, num3)){
//        std::cout << "You win" << std::endl;
//    }
    return 0;
}