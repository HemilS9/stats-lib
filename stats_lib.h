#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <map>
#include <cmath>

enum class OutlierPolicy : uint8_t {SD, IQR};
enum class ConfidenceLevel : uint8_t {PCT_90, PCT_95, PCT_99};

class StatsLibrary {
    private:
    std::vector<double> data;

    public:
    StatsLibrary() {};

    // template<typename InputIterator>
    // StatsLibrary(InputIterator begin, InputIterator end) {
    //     data_init(begin, end);
    // }

    // Initialize the data vector
    template <typename InputIterator>
    void data_init(InputIterator begin, InputIterator end) {
        std::vector<double> temp(begin, end);
        data = temp;
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

    // Returns the standard deviation, which is a measure of how spread out the data is
    double stdev();

    // Returns the Interquartile Range (IQR) of the data
    double IQR();

    // Returns the z-score: a measure of how many standard deviations away from the mean a data point is
    double z_score(double value);

    // Prints the 5 Number Summary of the data to the provided output stream
    void print_summary(std::ostream& os);

    // Return a list of outliers given the outlier policy
    std::vector<double> find_outliers(OutlierPolicy policy);

    // Prints the confidence interval to the provided output stream, given the confidence level
    std::pair<double, double> confidence_interval(ConfidenceLevel conf_level);

    // // Return nCr : the number of combinations of ways you can choose r values from n items
    // unsigned long int choose(int n, int r);
    // unsigned long int choose_helper(std::vector<vector<int>> &memo, int n, int r);

    // // Return nPr : the number of permutations of ways you can choose r values from n items
    // unsigned long int permute(int n, int r);
    // unsigned long int permute_helper(std::vector<vector<int>> &memo, int n, int r);
};