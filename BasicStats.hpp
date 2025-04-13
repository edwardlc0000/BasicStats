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
	double median(std::vector<T>& data)
	{
		if (data.empty()) return 0.0;
		std::sort(data.begin(), data.end());
		size_t n = data.size();
		if (n % 2 == 0)
			return (data[n / 2 - 1] + data[n / 2]) / 2.0;
		else
			return data[n / 2];
	}
}

#endif // !BASIC_STATS_HPP

