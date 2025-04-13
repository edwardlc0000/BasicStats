#pragma once

#ifndef BASIC_STATS_HPP
#define BASIC_STATS_HPP

#include <vector>
#include <utility>
#include <algorithm>
#include <random>
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
		std::vector<T> sorted_data = data;
		std::sort(sorted_data.begin(), sorted_data.end());
		size_t n = sorted_data.size();
		if (n % 2 == 0)
			return (sorted_data[n / 2 - 1] + sorted_data[n / 2]) / 2.0;
		else
			return sorted_data[n / 2];
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
		std::vector<T> sorted_data = data;
		std::sort(sorted_data.begin(), sorted_data.end());
		size_t n = sorted_data.size();
		if (n % 2 == 0)
			return median(std::vector<T>(sorted_data.begin(), sorted_data.begin() + n / 2));
		else
			return median(std::vector<T>(sorted_data.begin(), sorted_data.begin() + n / 2 + 1));
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
		std::vector<T> sorted_data = data;
		std::sort(sorted_data.begin(), sorted_data.end());
		size_t n = sorted_data.size();
		return median(std::vector<T>(sorted_data.begin() + n / 2, sorted_data.end()));
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
	 * @brief Calculate the percentile of a vector of numbers using linear interpolation.
	 * 
	 * @tparam T The type of the elements in the vector.
	 * @param data The vector of numbers.
	 * @param p The percentile to calculate (0-100).
	 * @return The value at the specified percentile.
	 */
	template<typename T>
	double percentile(const std::vector<T>& data, double p)
	{
		if (data.empty()) return 0.0;
		if (p < 0 || p > 100) throw std::out_of_range("Percentile must be between 0 and 100.");
		std::vector<T> sorted_data = data;
		std::sort(sorted_data.begin(), sorted_data.end());
		double rank = (p / 100) * (sorted_data.size() - 1);
		size_t lower = static_cast<size_t>(std::floor(rank));
		size_t upper = static_cast<size_t>(std::ceil(rank));
		double weight = rank - lower;
		if (upper >= sorted_data.size()) return sorted_data[lower];
		return sorted_data[lower] + weight * (sorted_data[upper] - sorted_data[lower]);
	}

	/**
	 * @brief Filter a vector of numbers based on a predicate function.
	 * 
	 * @tparam T The type of the elements in the vector.
	 * @param data The vector of numbers.
	 * @return A new vector containing the elements that satisfy the predicate.
	 */
	template<typename T, typename Function>
	std::vector<T> filter(const std::vector<T>& data, Function predicate)
	{
		static_assert(std::is_invocable_r_v<bool, Function, T>, "Predicate must be a callable that returns bool.");
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
	template<typename T, typename Function>
	std::vector<T> filter(const std::vector<T>& data, const std::vector<T>& criteria_data, Function predicate)
	{
		static_assert(std::is_invocable_r_v<bool, Function, T>, "Predicate must be a callable that returns bool.");
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

	/**
	 * @brief Resample a vector of numbers with replacement.
	 *
	 * @tparam T The type of the elements in the vector.
	 * @param data The vector of numbers.
	 * @param seed The seed for random number generation (default: random_device).
	 * @return A new vector containing the resampled elements.
	 */
	template<typename T>
	std::vector<T> resample(const std::vector<T>& data, unsigned int seed = std::random_device{}())
	{
		if (data.empty()) return {};
		std::vector<T> result;
		result.reserve(data.size());
		std::mt19937 gen(seed);
		std::uniform_int_distribution<size_t> dist(0, data.size() - 1);
		for (size_t i = 0; i < data.size(); i++)
		{
			size_t index = dist(gen);
			result.push_back(data[index]);
		}
		return result;
	}

	/**
	 * @brief Calculate the confidence interval of a statistic using bootstrap resampling.
	 * 
	 * @tparam T The type of the elements in the vector.
	 * @param data The vector of numbers.
	 * @param func The function to apply to the resampled data.
	 * @param confidence_level The confidence level (0-100).
	 * @param nmax The number of bootstrap samples to generate.
	 * @return A pair containing the lower and upper bounds of the confidence interval.
	 */
	template<typename T, typename Function>
	std::pair<double, double> confidence_interval(const std::vector<T>& data, Function func, double confidence_level, unsigned int nmax = 1024)
	{
		static_assert(std::is_invocable_r_v<double, Function, const std::vector<T>&>, "Function must return double and accept a vector of T.");
		if (data.empty()) return { 0.0, 0.0 };
		if (confidence_level <= 0 || confidence_level >= 100) throw std::out_of_range("Confidence level must be between 0 and 1.");
		std::vector<T> result_vector;
		for (unsigned int i = 0; i < nmax; ++i)
		{
			std::vector<T> resamepled_data = resample(data);
			double result = func(resampled_data);
			result_vector.push_back(result);
		}
		double min = percentile(result_vector, (100 - confidence_level) / 2);
		double max = percentile(result_vector, 100 - (100 - confidence_level) / 2);
		return { min, max };
	}

	/**
	 * @brief Calculate the confidence interval of the difference between two statistics using bootstrap resampling.
	 * 
	 * @tparam T The type of the elements in the vector.
	 * @param data1 The first vector of numbers.
	 * @param data2 The second vector of numbers.
	 * @param func The function to apply to the resampled data.
	 * @param confidence_level The confidence level (0-100).
	 * @param nmax The number of bootstrap samples to generate.
	 * @return A pair containing the lower and upper bounds of the confidence interval.
	 */
	template<typename T, typename Function>
	std::pair<double, double> confidence_interval(const std::vector<T>& data1, const std::vector<T>& data2, Function func, double confidence_level, unsigned int nmax = 1024)
	{
		static_assert(std::is_invocable_r_v<double, Function, const std::vector<T>&>, "Function must return double and accept a vector of T.");
		if (data1.empty() || data2.empty()) return { 0.0, 0.0 };
		if (confidence_level <= 0 || confidence_level >= 100) throw std::out_of_range("Confidence level must be between 0 and 1.");
		std::vector<T> result_vector;
		for (unsigned int i = 0; i < nmax; ++i)
		{
			std::vector<T> resampled_data1 = resample(data1);
			std::vector<T> resampled_data2 = resample(data2);
			double result1 = func(resampled_data1);
			double result2 = func(resampled_data2);
			double result = result1 - result2;
			result_vector.push_back(result);
		}
		double min = percentile(result_vector, (100 - confidence_level) / 2);
		double max = percentile(result_vector, 100 - (100 - confidence_level) / 2);
		return { min, max };
	}

}

#endif // !BASIC_STATS_HPP

