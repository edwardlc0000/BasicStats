#pragma once

#ifndef BASIC_STATS_HPP
#define BASIC_STATS_HPP

#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>

namespace BasicStats
{
	/**
	 * @brief Calculate the sum of a vector of numbers.
	 * 
	 * @tparam T The type of the elements in the vector.
	 * @param data The vector of numbers.
	 * @return The sum of the elements in the vector.
	 */
	template<typename T>
	double sum(const std::vector<T>& data)
	{
		return std::accumulate(data.begin(), data.end(), 0.0);
	}

	/**
	 * @brief Calculate the arithmetic mean (average) of a vector of numbers.
	 * 
	 * @tparam T the type of the elements in the vector.
	 * @param data The vector of numbers.
	 * @return The arithmetic mean of the elements in the vector.
	 */
	template<typename T>
	double mean(const std::vector<T>& data)
	{
		if (data.empty()) return 0.0;
		return sum(data) / data.size();
	}

	/**
	 * @brief Calculate the geometric mean of a vector of numbers.
	 * 
	 * @tparam T The type of the elements in the vector.
	 * @param data The vector of numbers.
	 * @return The geometric mean of the elements in the vector.
	 */
	template<typename T>
	double geo_mean(const std::vector<T>& data)
	{
		if (data.empty()) return 0.0;
		double product = std::accumulate(data.begin(), data.end(), 1.0, std::multiplies<double>());
		return std::pow(product, 1.0 / data.size());
	}

	/**
	 * @brief Calculate the median of a vector of numbers.
	 *
	 * @tparam T The type of the elements in the vector.
	 * @param data The vector of numbers.
	 * @return The median of the elements in the vector.
	 */
	template<typename T>
	double median(const std::vector<T>& data)
	{
		if (data.empty()) return 0.0;
		std::sort(data.begin(), data.end());
		size_t n = data.size();
		if (n % 2 == 0)
			return (data[n / 2 - 1] + data[n / 2]) / 2.0;
		else
			return data[n / 2];
	}

	/**
	 * @brief Calculate the variance of a vector of numbers.
	 * 
	 * @tparam T The type of the elements in the vector.
	 * @param data The vector of numbers.
	 * @return The variance of the elements in the vector.
	 */
	template<typename T>
	double variance(const std::vector<T>& data)
	{
		if (data.empty()) return 0.0;
		double mean_value = mean(data);
		double sum_squared_diff = std::accumulate(data.begin(), data.end(), 0.0,
			[mean_value](double acc, T value) {
				return acc + (value - mean_value) * (value - mean_value);
			});
		return sum_squared_diff / data.size();
	}

	/**
	 * @brief Calculate the standard deviation of a vector of numbers.
	 *
	 * @tparam T The type of the elements in the vector.
	 * @param data The vector of numbers.
	 * @return The standard deviation of the elements in the vector.
	 */
	template<typename T>
	double stdev(const std::vector<T>& data)
	{
		return std::sqrt(variance(data));
	}

	/**
	 * @brief Calculate the coefficient of variation of a vector of numbers.
	 *
	 * @tparam T The type of the elements in the vector.
	 * @param data The vector of numbers.
	 * @return The coefficient of variation of the elements in the vector.
	 */
	template<typename T>
	double coeff_of_variation(const std::vector<T>& data)
	{
		if (data.empty()) return 0.0;
		return stdev(data) / mean(data);
	}

	/**
	 * @brief Calculate the range of a vector of numbers.
	 * 
	 * @tparam T The type of the elements in the vector.
	 * @param data The vector of numbers.
	 * @return The range of the elements in the vector.
	 */
	template<typename T>
	double range(const std::vector<T>& data)
	{
		if (data.empty()) return 0.0;
		auto [min, max] = std::minmax_element(data.begin(), data.end());
		return *max - *min;
	}

}

#endif // !BASIC_STATS_HPP

