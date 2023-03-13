#include "stats_lib.h"
#include <cassert>

using namespace std;

void ASSERT_EQUAL(string called_from, double a, double b) {
    const double epsilon = 0.0001;
    if (abs(a - b) > epsilon) {
        cout << "Test failed in: " << called_from << endl;
        assert(false);
    }
    return;
}

// ----------------------------------------- Test Function Declarations -----------------------------------------
void test_mean();
void test_sum();
void test_range();
void test_median();
void test_mode();
void test_IQR();
void test_stdev();
// void test_z_score();
// void test_summary();
// void test_outliers();
// void test_conf_interval();


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
    double result = mean_one.mean();
    ASSERT_EQUAL("mean", result, 3);

    data = {25, 44, 7, 82, 65, 38, 39};
    StatsLibrary mean_two;
    mean_two.data_init(data.begin(), data.end());
    result = mean_two.mean();
    ASSERT_EQUAL("mean", result, 42.85714);
}

void test_sum() {
    vector<double> data = {1, 2, 3, 4, 5};
    StatsLibrary sum_one;
    sum_one.data_init(data.begin(), data.end());
    double result = sum_one.sum();
    ASSERT_EQUAL("sum", result, 15);

    data = {33.9, 27.2, 7, 12, 48.88, 32.3};
    StatsLibrary sum_two;
    sum_two.data_init(data.begin(), data.end());
    result = sum_two.sum();
    ASSERT_EQUAL("sum", result, 161.28);
}

void test_range() {
    vector<double> data = {100};
    StatsLibrary range_one;
    range_one.data_init(data.begin(), data.end());
    double result = range_one.range();
    ASSERT_EQUAL("range", result, 0);

    data = {-555, 902, 42, 12, 44.44, 901.1};
    StatsLibrary range_two;
    range_two.data_init(data.begin(), data.end());
    result = range_two.range();
    ASSERT_EQUAL("range", result, 1457);
}

void test_median() {
    vector<double> data = {1, 2, 4, -1, -1, 4, 2.6, 11.3};
    StatsLibrary median_one;
    median_one.data_init(data.begin(), data.end());
    double result = median_one.median();
    ASSERT_EQUAL("median", result, 2.6);

    data = {6.5, 3.9, 2, 12, 4.5};
    StatsLibrary median_two;
    median_two.data_init(data.begin(), data.end());
    result = median_two.median();
    ASSERT_EQUAL("median", result, 4.5);
}

void test_mode() {
    vector<double> data = {0, 9, -12, 44, 55, 9, 9, 11, 11, -12};
    StatsLibrary mode_one;
    mode_one.data_init(data.begin(), data.end());
    double result = mode_one.mode();
    ASSERT_EQUAL("mode", result, 9);

    data = {121, 4, 4, 0, 0, 7, 3, 4, 5.5};
    StatsLibrary mode_two;
    mode_two.data_init(data.begin(), data.end());
    result = mode_two.mode();
    ASSERT_EQUAL("mode", result, 4);
}

void test_IQR() {
    vector<double> data = {-2, 6, 11.7, -21, 2.9};
    StatsLibrary IQR_one;
    IQR_one.data_init(data.begin(), data.end());
    double result = IQR_one.IQR();
    ASSERT_EQUAL("IQR", result, 20.35);

    data = {55, 12, -42, 11, 0, 5.5};
    StatsLibrary IQR_two;
    IQR_two.data_init(data.begin(), data.end());
    result = IQR_two.IQR();
    ASSERT_EQUAL("IQR", result, 12);
}

void test_stdev() {
    vector<double> data = {11.9, -22, 0.5, 13, 16, 17};
    StatsLibrary stdev_one;
    stdev_one.data_init(data.begin(), data.end());
    double result = stdev_one.stdev();
    ASSERT_EQUAL("stdev", result, 13.6567);

    data = {98, 15, 45.8, -2.2};
    StatsLibrary stdev_two;
    stdev_two.data_init(data.begin(), data.end());
    result = stdev_two.stdev();
    ASSERT_EQUAL("stdev", result, 38.0808);
}