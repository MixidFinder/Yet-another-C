#include "data_stat.h"

double max(double *data, int n) {
    double max_v = *data;
    for (int i = 0; i < n; i++) {
        if (max_v < data[i]) {
            max_v = data[i];
        }
    }

    return max_v;
}

double min(double *data, int n) {
    double min_v = *data;
    for (int i = 0; i < n; i++) {
        if (min_v > data[i]) {
            min_v = data[i];
        }
    }

    return min_v;
}

double mean(double *data, int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += data[i];
    }
    return sum / n;
}

double variance(double *data, int n) {
    double mean_value = mean(data, n);
    double sum = 0.0;

    for (int i = 0; i < n; i++) {
        sum += (data[i] - mean_value) * (data[i] - mean_value);
    }

    return sum / n;
}