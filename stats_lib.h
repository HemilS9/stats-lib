#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <map>
#include <cmath>

class Invalid_Size_Error {};

enum class OutlierPolicy : uint8_t {SD, IQR};
enum class ConfidenceLevel : uint8_t {PCT_90, PCT_95, PCT_99};

class StatsLibrary {
    private:
    std::vector<double> data;
    std::vector<double> sorted_data;
    double mean_val, median_val, stdev_val;
    bool mean_computed = false, median_computed = false, stdev_computed = false;

    public:
    StatsLibrary() {};

    // Initialize the data vector
    template <typename InputIterator>
    void data_init(InputIterator begin, InputIterator end) {
        std::vector<double> temp(begin, end);
        data = temp;
        sorted_data = data;
        std::sort(sorted_data.begin(), sorted_data.end());
    }

    // Returns the arithmetic mean of the data
    double mean();

    // Returns the sum of the data
    double sum();

    // Returns the range of the data: the difference between the maximum and minimum values
    double range();

    // Returns the mode, or the most common value in the data. If there are multiple, returns the smallest
    double mode();

    // Returns the median of the data, which is more resistant to outliers
    double median();
    double median(size_t start, size_t end);

    // Returns the population standard deviation, which is a measure of how spread out the data is
    double stdev();

    // Returns the Interquartile Range (IQR) of the data
    double IQR();
    std::pair<double, double> quartiles();

    // Prints the 5 Number Summary of the data to the provided output stream
    void print_summary(std::ostream& os);

    // Return a list of outliers given the outlier policy
    std::vector<double> find_outliers(OutlierPolicy policy);

    // Prints the confidence interval to the provided output stream, given the confidence level
    std::pair<double, double> confidence_interval(ConfidenceLevel conf_level);

    // Returns the z-score: a measure of how many standard deviations away from the mean a data point is
    double z_score(double mean_val, double stdev_val, double value);
};