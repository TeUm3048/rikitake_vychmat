
#ifndef MAIN_CALCULATE_DIFF_SUM_HH
#define MAIN_CALCULATE_DIFF_SUM_HH

#include <iterator>
#include <boost/circular_buffer.hpp>
#include <numeric>

/**
 * Calculates the last backward difference of a sequence of values.
 *
 * This function takes a range of values specified by the iterators `begin` and `end`,
 * and calculates the last backward difference of the sequence. The last backward difference
 * is defined as the difference between each element and its preceding element, until only
 * one element remains.
 *
 * @param begin An iterator pointing to the beginning of the range.
 * @param end An iterator pointing to the end of the range.
 * @return The last backward difference of the sequence.
 */
template<typename Iterator>
inline
auto last_backward_difference(Iterator begin,
                              Iterator end) -> typename std::iterator_traits<Iterator>::value_type {
    using ValueType = typename std::iterator_traits<Iterator>::value_type;
    std::vector<ValueType> arr(begin, end);

    while (arr.size() > 1) {
        std::vector<ValueType> new_arr;
        for (auto it = arr.begin() + 1; it != arr.end(); ++it) {
            ValueType diff = *it - *(it - 1);
            new_arr.push_back(diff);
        }
        arr = new_arr;
    }
    return arr[0];
}

#endif // MAIN_CALCULATE_DIFF_SUM_HH
