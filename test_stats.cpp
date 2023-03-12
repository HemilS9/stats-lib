#include "stats_lib.h"
#include <cassert>

using namespace std;


// ----------------------------------------- Test Function Declarations -----------------------------------------
void test_mean();
void test_sum();
// void test_range();
// void test_median();
// void test_mode();
// void test_IQR();
// void test_stdev();


// --------------------------------------------- Run Tests in Main ---------------------------------------------
int main() {
    cout << "Running all tests" << endl;
    
    test_mean();
    test_sum();

    cout << "All Tests Passed" << endl;
    return 0;
}


// ----------------------------------------- Test Function Implementations -----------------------------------------
void test_mean() {
    vector<double> data = {1, 2, 3, 4, 5};
    StatsLibrary mean_one;
    mean_one.data_init(data.begin(), data.end());
    mean_one.print_data();
    // double result = mean_one.mean();
    // assert(result == 3);
}

void test_sum() {
    vector<double> data = {1, 2, 3, 4, 5};
    StatsLibrary sum_one;
    sum_one.data_init(data.begin(), data.end());
    sum_one.print_data();
    // double result = sum_one.sum();
    // assert(result == 15);
}