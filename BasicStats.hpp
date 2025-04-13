#pragma once

#ifndef BASIC_STATS_HPP
#define BASIC_STATS_HPP

#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cmath>
#include <stdexcept>

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
	 * @brief Calculate the first quartile (Q1) of a vector of numbers.
	 * 
	 * @tparam T The type of the elements in the vector.
	 * @param data The vector of numbers.
	 * @return The first quartile of the elements in the vector.
	 */
	template<typename T>
	double first_quartile(const std::vector<T>& data)
	{
		if (data.empty()) return 0.0;
		std::sort(data.begin(), data.end());
		size_t n = data.size();
		if (n % 2 == 0)
			return median(std::vector<T>(data.begin(), data.begin() + n / 2));
		else
			return median(std::vector<T>(data.begin(), data.begin() + n / 2 + 1));
	}

	/**
	 * @brief Calculate the third quartile (Q3) of a vector of numbers.
	 *
	 * @tparam T The type of the elements in the vector.
	 * @param data The vector of numbers.
	 * @return The third quartile of the elements in the vector.
	 */
	template<typename T>
	double third_quartile(const std::vector<T>& data)
	{
		if (data.empty()) return 0.0;
		std::sort(data.begin(), data.end());
		size_t n = data.size();
		if (n % 2 == 0)
			return median(std::vector<T>(data.begin() + n / 2, data.end()));
		else
			return median(std::vector<T>(data.begin() + n / 2 + 1, data.end()));
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

	/**
	 * @brief Calculate the interquartile range (IQR) of a vector of numbers.
	 *
	 * @tparam T The type of the elements in the vector.
	 * @param data The vector of numbers.
	 * @return The interquartile range of the elements in the vector.
	 */
	template<typename T>
	double iqr(const std::vector<T>& data)
	{
		if (data.empty()) return 0.0;
		return third_quartile(data) - first_quartile(data);
	}

	/**
	 * @brief Filter a vector of numbers based on a predicate function.
	 * 
	 * @tparam T The type of the elements in the vector.
	 * @param data The vector of numbers.
	 * @return A new vector containing the elements that satisfy the predicate.
	 */
	template<typename T>
	std::vector<T> filter(const std::vector<T>& data, std::function<bool(T)> predicate)
	{
		std::vector<T> result;
		std::copy_if(data.begin(), data.end(), std::back_inserter(result), predicate);
		return result;
	}

	/**
	 * @brief Filter a vector of numbers based on a predicate function and a criteria vector.
	 *
	 * @tparam T The type of the elements in the vector.
	 * @param criteria_data The vector of criteria numbers.
	 * @param data The vector of numbers.
	 * @return A new vector containing the elements that satisfy the predicate.
	 */
	template<typename T>
	std::vector<T> filter(const std::vector<T>& criteria_data, const std::vector<T>& data, std::function<bool(T)> predicate)
	{
		if (criteria_data.size() != data.size())
		{
			throw std::invalid_argument("Criteria and data vectors must be of the same size.");
		}

		std::vector<T> result;
		for (size_t i = 0; i < criteria_data.size(); i++)
		{
			if (predicate(criteria_data[i]))
			{
				result.push_back(data[i]);
			}
		}
		return result;
	}

}

#endif // !BASIC_STATS_HPP

