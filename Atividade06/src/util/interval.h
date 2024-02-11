/**
 * @file interval.h
 * @brief Contains a class representing a closed interval [min, max]
*/
#ifndef INTERVAL_H
#define INTERVAL_H

/**
 * @class interval
 * @brief A class representing a closed interval [min, max]
 * 
 * @param min The minimum value of the interval
 * @param max The maximum value of the interval
*/
class interval {
  public:
    double min, max;

    interval() : min(+infinity), max(-infinity) {} // Default interval is empty

    interval(double _min, double _max) : min(_min), max(_max) {}

    bool contains(double x) const {
        return min <= x && x <= max;
    }

    bool surrounds(double x) const {
        return min < x && x < max ;
    }

    double clamp(double x) const {
        if (x < min) return min;
        if (x > max) return max;
        return x;
    }

    static const interval empty, universe;
};

const static interval empty   (+infinity, -infinity);
const static interval universe(-infinity, +infinity);

#endif