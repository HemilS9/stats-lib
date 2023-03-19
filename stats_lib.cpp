#include "stats_lib.h"

using std::string, std::vector;


// // Initialize the data vector
// template<typename InputIterator>
// void StatsLibrary::data_init(InputIterator begin, InputIterator end) {
//     vector<double> temp(begin, end);
//     data = temp;
// }


// Returns the arithmetic mean of the data
double StatsLibrary::mean() {
    if (data.empty()) {
        throw std::invalid_argument("Data must not be empty");
    }

    double ans = StatsLibrary::sum();
    return ans / data.size();
}


// Returns the sum of the data
double StatsLibrary::sum() {
    if (data.empty()) {
        throw std::invalid_argument("Data must not be empty");
    }

    double ans = 0;
    for (double val : data) {
        ans += val;
    }
    return ans;
}


// Returns the range of the data: the difference between the maximum and minimum values
double StatsLibrary::range() {
    if (data.empty()) {
        throw std::invalid_argument("Data must not be empty");
    }

    double max_val = *std::max_element(data.begin(), data.end());
    double min_val = *std::min_element(data.begin(), data.end());
    return max_val - min_val;
}


// Returns the mode, or the most common value in the data. If there are multiple, returns the smallest
double StatsLibrary::mode() {
    if (data.empty()) {
        throw std::invalid_argument("Data must not be empty");
    }

    std::map<double, int> all_freqs;
    for (double val : data) {
        all_freqs[val]++;
    }

    int max_freq = 0;
    double result = *data.begin();
    for (auto [val, freq] : all_freqs) {
        if (freq > max_freq) {
            max_freq = freq;
            result = val;
        }
    }
    return result;
}


// Returns the median of the data, which is more resistant to outliers
double StatsLibrary::median() {
    if (data.empty()) {
        throw std::invalid_argument("Data must not be empty");
    }
    std::sort(data.begin(), data.end());

    int middle = data.size() / 2;
    if (data.size() % 2 == 0) {
        return (data[middle] + data[middle - 1]) / 2;
    } else {
        return data[middle];
    }
}


// Returns the standard deviation, which is a measure of how spread out the data is
double StatsLibrary::stdev() {
    if (data.empty()) {
        throw std::invalid_argument("Data must not be empty");
    }
    double result = 0;
    double mean_val = mean();
    for (double val : data) {
        result += (val - mean_val) * (val - mean_val);
    }
    result /= data.size();
    return std::sqrt(result);
}

// Returns the median of the data, which is more resistant to outliers
// Assumes data is sorted
double StatsLibrary::median(size_t start, size_t end) {
    if (data.empty()) {
        throw std::invalid_argument("Data must not be empty");
    }

    int middle = (end + start) / 2;
    if ((end - start) % 2 == 0) {
        return (data[middle] + data[middle - 1]) / 2;
    } else {
        return data[middle];
    }
}

// Returns the Interquartile Range (IQR) of the data
double StatsLibrary::IQR() {
    if (data.size() < 4) {
        throw std::invalid_argument("IQR requires at least 4 data points");
    }
    std::sort(data.begin(), data.end());

    double Q3, Q1 = median(0, data.size() / 2);
    if (data.size() % 2 == 0) {
        Q3 = median(data.size() / 2, data.size());
    }
    else {
        Q3 = median((data.size() / 2) + 1, data.size());
    }

    return Q3 - Q1;
}

std::pair<double, double> StatsLibrary::quartiles() {
    if (data.size() < 4) {
        throw std::invalid_argument("IQR requires at least 4 data points");
    }
    std::sort(data.begin(), data.end());

    double Q3, Q1 = median(0, data.size() / 2);
    if (data.size() % 2 == 0) {
        Q3 = median(data.size() / 2, data.size());
    }
    else {
        Q3 = median((data.size() / 2) + 1, data.size());
    }

    return {Q1, Q3};
}


// Prints the 5 Number Summary of the data to the provided output stream
void StatsLibrary::print_summary(std::ostream& os) {
    if (data.size() < 4) {
        throw std::invalid_argument("5 Number Summary requires at least 4 data points");
    }

    double median_val = median();
    double min_val = data[0];
    double max_val = data.back();

    std::pair<double, double> q1q3 = quartiles();
    double q1 = q1q3.first;
    double q3 = q1q3.second;

    os << "Min: " << min_val << std::endl;
    os << "Q1: " << q1 << std::endl;
    os << "Median: " << median_val << std::endl;
    os << "Q3: " << q3 << std::endl;
    os << "Max: " << max_val << std::endl;
}


// Return a list of outliers given the outlier policy
std::vector<double> StatsLibrary::find_outliers(OutlierPolicy policy) {
    std::vector<double> result;
    if (policy == OutlierPolicy::SD) {
        if (data.empty()) {
            throw std::invalid_argument("Data must not be empty");
        }
        double mean_val = mean();
        double threshold = stdev() * 3;
        for (double val : data) {
            if (std::abs(val - mean_val) >= threshold) {
                result.push_back(val);
            }
        }
    }
    else if (policy == OutlierPolicy::IQR) {
        if (data.size() < 4) {
            throw std::invalid_argument("IQR requires at least 4 data points");
        }
        std::pair<double, double> q1q3 = quartiles();
        double Q1 = q1q3.first;
        double Q3 = q1q3.second;
        double threshold = IQR() * 1.5;
        for (double val : data) {
            if (val < (Q1 - threshold) || val > (Q3 + threshold)) {
                result.push_back(val);
            }
        }
    }
    else {
        throw std::invalid_argument("Invalid outlier policy");
    }

    return result;
}

// Prints the confidence interval to the provided output stream, given the confidence level
std::pair<double, double> StatsLibrary::confidence_interval(ConfidenceLevel conf_level) {
    double mean_val = mean();
    double stdev_val = stdev();
    double margin = stdev_val / std::sqrt(data.size());

    double lower = -1, upper = -1;
    switch(conf_level) {
        case ConfidenceLevel::PCT_90: 
            lower = mean_val - (1.645 * (margin));
            upper = mean_val + (1.645 * (margin));
            return {lower, upper};
        case ConfidenceLevel::PCT_95:
            lower = mean_val - (1.96 * (margin));
            upper = mean_val + (1.96 * (margin));
            return {lower, upper};
        case ConfidenceLevel::PCT_99:
            lower = mean_val - (2.576 * (margin));
            upper = mean_val + (2.576 * (margin));
            return {lower, upper};
        default:
            throw std::invalid_argument("Invalid confidence level");
    }
}

// Returns the z-score: a measure of how many standard deviations away from the mean a data point is
double StatsLibrary::z_score(double mean_val, double stdev_val, double value) {
    return (value - mean_val) / stdev_val;
}


// // Return nCr : the number of combinations of ways you can choose r values from n items
// unsigned long int StatsLibrary::choose(int n, int r) {
//     if (n < r) {
//         return 0;
//     }
// }

// // https://www.calculatorsoup.com/calculators/discretemathematics/combinations.php
// unsigned long int StatsLibrary::choose_helper(std::vector<vector<int>> &memo, int n, int r) {
//     if (n == r) {
//         return 1;
//     }
//     if (r == 1) {
//         return n;
//     }
// }


// // Return nPr : the number of permutations of ways you can choose r values from n items
// unsigned long int StatsLibrary::permute(int n, int r) {
//     if (n < r) {
//         return 0;
//     }
// }

// // https://www.calculatorsoup.com/calculators/discretemathematics/permutations.php
// unsigned long int StatsLibrary::permute_helper(std::vector<vector<int>> &memo, int n, int r) {
//     if (r == 1) {
//         return n;
//     }
// }
