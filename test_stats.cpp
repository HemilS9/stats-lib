#include "stats_lib.h"
#include <cassert>
#include <sstream>
#include <iomanip>

using namespace std;

void ASSERT_EQUAL(string called_from, double a, double b) {
    const double epsilon = 0.001;
    if (abs(a - b) > epsilon) {
        cout << "Test failed in: " << called_from << endl;
        cout << "Expected: " << b << " but got: " << a << endl;
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
void test_z_score();
void test_summary();
void test_outliers();
void test_conf_interval();


// --------------------------------------------- Run Tests in Main ---------------------------------------------
int main() {
    cout << setprecision(3) << fixed;
    cout << "Running all tests" << endl;
    
    test_mean();
    test_sum();
    test_range();
    test_median();
    test_mode();
    test_IQR();
    test_stdev();
    test_z_score();
    test_summary();
    test_outliers();
    test_conf_interval();

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
    ASSERT_EQUAL("median", result, 2.3);

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

void test_z_score() {
    vector<double> data = {1, 2, 3, 4, 5};
    StatsLibrary z_score_one;
    z_score_one.data_init(data.begin(), data.end());
    double result = z_score_one.z_score(3, 2, 5);
    ASSERT_EQUAL("z_score", result, 1);

    StatsLibrary z_score_two;
    result = z_score_two.z_score(5, 10, 5);
    ASSERT_EQUAL("z_score", result, 0);
}

void test_summary() {
    vector<double> data = {5, 7.7, 2.8, -3, 12.5, 3.8, 9.6, 2};
    StatsLibrary summary_one;
    summary_one.data_init(data.begin(), data.end());
    ostringstream result;
    result << setprecision(2) << fixed;
    summary_one.print_summary(result);

    ostringstream correct;
    correct << "Min: -3.00\n";
    correct << "Q1: 2.40\n";
    correct << "Median: 4.40\n";
    correct << "Q3: 8.65\n";
    correct << "Max: 12.50\n";
    assert(result.str() == correct.str());
}

void test_outliers() {
    vector<double> data = {-2, 12.5, 5.8, 99.1, 13, 8};
    StatsLibrary outliers_one;
    outliers_one.data_init(data.begin(), data.end());
    vector<double> result = outliers_one.find_outliers(OutlierPolicy::IQR);
    ASSERT_EQUAL("outliers", result[0], 99.1);

    data = {5, 7, 2.6, 9.8, 11, -121, -2};
    StatsLibrary outliers_two;
    outliers_two.data_init(data.begin(), data.end());
    result = outliers_two.find_outliers(OutlierPolicy::IQR);
    ASSERT_EQUAL("outliers", result[0], -121);
    result = outliers_two.find_outliers(OutlierPolicy::SD);
    ASSERT_EQUAL("outliers", result.size(), 0);

    data = {1, 2, 3, 4, 5};
    StatsLibrary outliers_three;
    outliers_three.data_init(data.begin(), data.end());
    result = outliers_three.find_outliers(OutlierPolicy::SD);
    ASSERT_EQUAL("outliers", result.size(), 0);
}

void test_conf_interval() {
    vector<double> data = {11.8, 18.5, 15.6, 21.2, 19.4, 16, 15};
    StatsLibrary conf_interval;
    conf_interval.data_init(data.begin(), data.end());

    pair<double, double> res_90 = conf_interval.confidence_interval(ConfidenceLevel::PCT_90);
    ASSERT_EQUAL("conf_interval", res_90.first, 14.976);
    ASSERT_EQUAL("conf_interval", res_90.second, 18.596);

    pair<double, double> res_95 = conf_interval.confidence_interval(ConfidenceLevel::PCT_95);
    ASSERT_EQUAL("conf_interval", res_95.first, 14.629);
    ASSERT_EQUAL("conf_interval", res_95.second, 18.942);

    pair<double, double> res_99 = conf_interval.confidence_interval(ConfidenceLevel::PCT_99);
    ASSERT_EQUAL("conf_interval", res_99.first, 13.951);
    ASSERT_EQUAL("conf_interval", res_99.second, 19.62);
}