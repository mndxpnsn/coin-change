//
//  main.cpp
//  CoinChange
//
//  Created by mndx on 08/01/2022.
//

#include <iostream>
#include <vector>

int max_sum = 250;
int max_num = 50;

typedef struct memo_table {
    bool is_set;
    long val;
} m_table;

m_table** table;

void init_memo_table(int max_sum, int max_num) {
    table = new m_table*[max_sum + 1];
    for(int i = 0; i < max_sum + 1; ++i) {
        table[i] = new m_table[max_num + 1];
    }
    
    for(int i = 0; i < max_sum + 1; ++i) {
        for(int j = 0; j < max_num + 1; ++j) {
            table[i][j].is_set = false;
            table[i][j].val = 0;
        }
    }
}

long num_ways(int n, std::vector<long> c, long prev_num, long sum) {
    long size_vec = c.size();
    long res = 0;
    
    if(table[sum][prev_num].is_set) {
        return table[sum][prev_num].val;
    }
    
    for(int i = 0; i < size_vec; ++i) {
        if(c[i] >= prev_num) {
            long sum_loc = sum + c[i];
            if(sum_loc == n) {
                res = res + 1;
            }
            if(sum_loc < n) {
                res = res + num_ways(n, c, c[i], sum_loc);
            }
        }
    }
    
    table[sum][prev_num].is_set = true;
    table[sum][prev_num].val = res;
    
    return res;
}

long get_ways(int n, std::vector<long> c) {
    long res = 0;
    res = num_ways(n, c, 0, 0);
    
    return res;
}

int main(int argc, const char * argv[]) {
    //Declarations
    int n; //Targer integer. 1 <= n <= 250
    std::vector<long> c; //Denominations. values are in 1 <= c[i] <= 50
    
    //Initialization of params
    n = 50;
    c = {3, 2, 1, 4};
    
    //Initialize memo table
    init_memo_table(max_sum, max_num);
    
    //Compute number of ways to give change
    long num_of_ways = get_ways(n, c);
    
    //Print results
    std::cout << "number of ways to give change: " << num_of_ways << std::endl;
    std::cout << "done" << std::endl;
    
    return 0;
}
