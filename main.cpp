#include <iostream>
#include <vector>

// pre-initialize vector
void setup( std::vector<std::vector<std::vector<bool>>>& cache ){
    cache.resize(3); // resize the top level vector to 3 tall (we only have 3 piles)

    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            for(int k=0; k < 3; ++k){
                cache[i][j][k] = ((i==0 && j==0) || (i==0 && k==0) || (k == 0 && j==0)) ? true : false;
            }
        }
    }
}

// simple recursive function
bool winRecursive(int a, int b, int c){
  if((a==0 && b==0) || (a==0 && c==0) || (b==0 && c==0)){
    return true;
  }
    for(int i = 1; i < a+1; ++i ){
        return (!winRecursive(i-1, b, c));
    }

    for(int j = 1; j < b+1; ++j ){
        return (!winRecursive(a, j-1, c));
    }

    for(int k = 1; k < c+1; ++k ){
        return (!winRecursive(a, b, k-1));
    }
}

// recursion with a memoizing algo.
bool winRecursiveWithMemoizing(int a, int b, int c, std::vector<std::vector<std::vector<bool>>>& cache){

    // need to figure out my base cases here

    for(int i = 0; i < a; ++i ){
        return (!winRecursiveWithMemoizing(i-1, b, c, cache));
    }

    for(int j = 0; j < b; ++j ){
        return (!winRecursiveWithMemoizing(a, j-1, c, cache));
    }

    for(int k = 0; k < c; ++k ){
        return (!winRecursiveWithMemoizing(a, b, k-1, cache));
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
    num1 = rand() % 100 + 1;
    num2 = rand() % 100 + 1;
    num3 = rand() % 100 + 1;

    setup(cache);

    std::cout << "num1:" << num1 << " num2:" << num2 << " num3:" << num3 << std::endl;
    // call recursive function
    winRecursive(num1, num2, num3);
    winRecursiveWithMemoizing(num1, num2, num3, cache);


    return 0;
}