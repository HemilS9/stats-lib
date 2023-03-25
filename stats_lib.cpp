#include "stats_lib.h"

using std::string, std::vector;


// Returns the arithmetic mean of the data
double StatsLibrary::mean() {
    if (data.empty()) {
        throw Invalid_Size_Error();
    }
    if (mean_computed)
        return mean_val;

    double sum_val = StatsLibrary::sum();
    mean_val = sum_val / data.size();
    mean_computed = true;
    return mean_val;
}


// Returns the sum of the data
double StatsLibrary::sum() {
    if (data.empty()) {
        throw Invalid_Size_Error();
    }

    double sum_val = 0;
    for (double val : data) {
        sum_val += val;
    }
    return sum_val;
}


// Returns the range of the data: the difference between the maximum and minimum values
double StatsLibrary::range() {
    if (data.empty()) {
        throw Invalid_Size_Error();
    }

    double max_val = *std::max_element(data.begin(), data.end());
    double min_val = *std::min_element(data.begin(), data.end());
    return max_val - min_val;
}


// Returns the mode, or the most common value in the data. If there are multiple, returns the smallest
double StatsLibrary::mode() {
    if (data.empty()) {
        throw Invalid_Size_Error();
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
        throw Invalid_Size_Error();
    }
    if (median_computed)
        return median_val;

    int middle = sorted_data.size() / 2;
    median_computed = true;
    if (sorted_data.size() % 2 == 0) {
        median_val = (sorted_data[middle] + sorted_data[middle - 1]) / 2;
        return median_val;
    } else {
        median_val = sorted_data[middle];
        return median_val;
    }
}


// Returns the population standard deviation, which is a measure of how spread out the data is
double StatsLibrary::stdev() {
    if (data.empty()) {
        throw Invalid_Size_Error();
    }
    if (stdev_computed)
        return stdev_val;
    if (!mean_computed)
        mean();

    double result = 0;
    for (double val : data) {
        result += (val - mean_val) * (val - mean_val);
    }

    result /= data.size();
    stdev_val = std::sqrt(result);
    stdev_computed = true;
    return stdev_val;
}

// Returns the median of the data, which is more resistant to outliers
// Assumes data is sorted
double StatsLibrary::median(size_t start, size_t end) {
    if (sorted_data.empty()) {
        throw Invalid_Size_Error();
    }

    int middle = (end + start) / 2;
    if ((end - start) % 2 == 0) {
        return (sorted_data[middle] + sorted_data[middle - 1]) / 2;
    } else {
        return sorted_data[middle];
    }
}

// Returns the Interquartile Range (IQR) of the data
double StatsLibrary::IQR() {
    if (data.size() < 4) {
        throw std::invalid_argument("IQR requires at least 4 data points");
    }
    
    std::pair<double, double> quartile_vals = quartiles();
    return quartile_vals.second - quartile_vals.first;
}

std::pair<double, double> StatsLibrary::quartiles() {
    if (sorted_data.size() < 4) {
        throw std::invalid_argument("IQR requires at least 4 data points");
    }

    double Q3, Q1 = median(0, sorted_data.size() / 2);
    if (sorted_data.size() % 2 == 0) {
        Q3 = median(sorted_data.size() / 2, sorted_data.size());
    }
    else {
        Q3 = median((sorted_data.size() / 2) + 1, sorted_data.size());
    }

    return {Q1, Q3};
}


// Prints the 5 Number Summary of the data to the provided output stream
void StatsLibrary::print_summary(std::ostream& os) {
    if (data.size() < 4) {
        throw std::invalid_argument("5 Number Summary requires at least 4 data points");
    }

    if (!median_computed) 
        median();

    double min_val = sorted_data[0];
    double max_val = sorted_data.back();

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
    if (!mean_computed)
        mean();
    if (!stdev_computed)
        stdev();

    std::vector<double> result;
    if (policy == OutlierPolicy::SD) {
        if (data.empty()) {
            throw Invalid_Size_Error();
        }
        double threshold = stdev_val * 3;
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
    if (!stdev_computed) 
        stdev();
    if (!mean_computed)
        mean();
    
    double margin = stdev_val / std::sqrt(data.size());

    double lower = -1, upper = -1;
    double mult;
    switch(conf_level) {
        case ConfidenceLevel::PCT_90: 
            mult = 1.645;
            break;
        case ConfidenceLevel::PCT_95:
            mult = 1.96;
            break;
        case ConfidenceLevel::PCT_99:
            mult = 2.576;
            break;
        default:
            throw std::invalid_argument("Invalid confidence level");
    }
    lower = mean_val - (mult * margin);
    upper = mean_val + (mult * margin);
    return {lower, upper};
}

// Returns the z-score: a measure of how many standard deviations away from the mean a data point is
double StatsLibrary::z_score(double mean_value, double stdev_value, double value) {
    return (value - mean_value) / stdev_value;
}
