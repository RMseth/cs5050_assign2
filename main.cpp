#include <iostream>
#include <vector>
#include <string>

//// pre-initialize vector
//void setup( std::vector<std::vector<std::vector<bool>>>& cache ){
//    cache.resize(3); // resize the top level vector to 3 tall (we only have 3 piles)
//
//    for(int i = 0; i < 3; ++i){
//        for(int j = 0; j < 3; ++j){
//            for(int k=0; k < 3; ++k){
//                cache[i][j][k] = ((i==0 && j==0) || (i==0 && k==0) || (k == 0 && j==0)) ? true : false;
//            }
//        }
//    }
//}

// simple recursive function
bool winRecursive(int a, int b, int c){
    if(a==0 && b==0 &&  c==0) return false;

    for(int i = 0; i < a; ++i ){
        return (!winRecursive(a - i, b, c));
    }

    for(int j = 0; j < b; ++j ){
        return (!winRecursive(a, b - j, c));
    }

    for(int k = 0; k < c; ++k ){
        return (!winRecursive(a, b, c - k));
    }
}

// recursion with a memoizing algo.
bool winRecursiveWithMemoizing(int a, int b, int c, std::vector<std::vector<std::vector<bool>>>& cache){

    // need to figure out my base cases here
    for(int i = 0; i < a; ++i){
        for(int j = 0; j < b; ++j){
            for(int k = 0; k < c; ++k){
                if(a == 0 && b == 0 && c == 0) cache[a][b][c] = false;
//                if(winRecursiveWithMemoizing( a - i, b, c, cache ) == cache[i][j][k]) return cache[i][j][k];
//                if(winRecursiveWithMemoizing( a, b - j, c, cache ) == cache[i][j][k]) return cache[i][j][k];
//                if(winRecursiveWithMemoizing( a, b, c - k, cache ) == cache[i][j][k]) return cache[i][j][k];

                for(int i = 0; i < a; ++i ){
                    return (!winRecursiveWithMemoizing(a - i, b, c, cache));
                }

                for(int j = 0; j < b; ++j ){
                    return (!winRecursiveWithMemoizing(a, b - j, c, cache));
                }

                for(int k = 0; k < c; ++k ){
                    return (!winRecursiveWithMemoizing(a, b, c - k, cache));
                }
            }
        }
    }
}

// Dynamic function
bool winDynamic(int a, int b, int c){

}

int main() {

    // declarations
    int num1, num2, num3;
    std::vector<std::vector<std::vector<bool>>> cache;

    srand(time(NULL));
    // setup 3 random numbers between 1 and 1000
    num1 = rand() % 10 + 1;
    num2 = rand() % 10 + 1;
    num3 = rand() % 10 + 1;
    std::cout << "num1: " << num1 << " num2: " << num2 << " num3: " << num3 << std::endl;

    // call recursive function
//    winRecursive(num1, num2, num3);

    // reset the random numbers
    num1 = rand() % 100 + 1;
    num2 = rand() % 100 + 1;
    num3 = rand() % 100 + 1;

    std::cout << "num1: " << num1 << " num2: " << num2 << " num3: " << num3 << std::endl;
//    setup(cache);

    // call memoizing
    winRecursiveWithMemoizing(num1, num2, num3, cache);

    std::cout << "cache contents " << std::endl;
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            for(int k=0; k < 3; ++k){
                std::string value = cache[i][j][k]? "true" : " false";
                std::cout << value << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    std::cout << "\nend of cache contents " << std::endl;

    return 0;
}