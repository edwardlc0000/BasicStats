#include "BasicStats.hpp"
#include "gtest/gtest.h"
#include <cmath>
#include <stdexcept>

TEST(BasicStatsTests, Sum) {
	EXPECT_DOUBLE_EQ(BasicStats::sum(std::vector<int>{1, 2, 3, 4, 5}), 15.0);
	EXPECT_DOUBLE_EQ(BasicStats::sum(std::vector<double>{1.5, 2.5, 3.5}), 7.5);
	EXPECT_DOUBLE_EQ(BasicStats::sum(std::vector<int>{}), 0.0);
}

TEST(BasicStatsTests, Mean) {
	EXPECT_DOUBLE_EQ(BasicStats::mean(std::vector<int>{1, 2, 3, 4, 5}), 3.0);
	EXPECT_DOUBLE_EQ(BasicStats::mean(std::vector<double>{1.5, 2.5, 3.5}), 2.5);
	EXPECT_DOUBLE_EQ(BasicStats::mean(std::vector<int>{}), 0.0);
}

TEST(BasicStatsTests, GeoMean) {
	EXPECT_DOUBLE_EQ(BasicStats::geo_mean(std::vector<int>{1, 3, 9}), 3.0);
	EXPECT_DOUBLE_EQ(BasicStats::geo_mean(std::vector<double>{1.0, 4.0, 16.0}), 4.0);
	EXPECT_DOUBLE_EQ(BasicStats::geo_mean(std::vector<int>{}), 0.0);
}

TEST(BasicStatsTests, Median) {
	EXPECT_DOUBLE_EQ(BasicStats::median(std::vector<int>{1, 3, 2, 5, 4}), 3.0);
	EXPECT_DOUBLE_EQ(BasicStats::median(std::vector<int>{1, 2, 3, 4}), 2.5);
	EXPECT_DOUBLE_EQ(BasicStats::median(std::vector<int>{}), 0.0);
}

TEST(BasicStatsTests, FirstQuartile) {
	EXPECT_DOUBLE_EQ(BasicStats::first_quartile(std::vector<int>{1, 2, 3, 4, 5, 6}), 2.0);
	EXPECT_DOUBLE_EQ(BasicStats::first_quartile(std::vector<int>{1, 2, 3, 4, 5}), 2.0);
	EXPECT_DOUBLE_EQ(BasicStats::first_quartile(std::vector<int>{}), 0.0);
}

TEST(BasicStatsTests, ThirdQuartile) {
	EXPECT_DOUBLE_EQ(BasicStats::third_quartile(std::vector<int>{1, 2, 3, 4, 5, 6}), 5.0);
	EXPECT_DOUBLE_EQ(BasicStats::third_quartile(std::vector<int>{1, 2, 3, 4, 5}), 4.0);
	EXPECT_DOUBLE_EQ(BasicStats::third_quartile(std::vector<int>{}), 0.0);
}

TEST(BasicStatsTests, Variance) {
	EXPECT_DOUBLE_EQ(BasicStats::variance(std::vector<int>{1, 2, 3, 4, 5}), 2.0);
	EXPECT_DOUBLE_EQ(BasicStats::variance(std::vector<int>{}), 0.0);
}

TEST(BasicStatsTests, Stdev) {
	EXPECT_DOUBLE_EQ(BasicStats::stdev(std::vector<int>{1, 2, 3, 4, 5}), std::sqrt(2.0));
	EXPECT_DOUBLE_EQ(BasicStats::stdev(std::vector<int>{}), 0.0);
}

TEST(BasicStatsTests, CoeffOfVariation) {
	EXPECT_DOUBLE_EQ(BasicStats::coeff_of_variation(std::vector<int>{1, 2, 3, 4, 5}), std::sqrt(2.0) / 3.0);
	EXPECT_DOUBLE_EQ(BasicStats::coeff_of_variation(std::vector<int>{}), 0.0);
}

TEST(BasicStatsTests, Range) {
	EXPECT_DOUBLE_EQ(BasicStats::range(std::vector<int>{1, 2, 3, 4, 5}), 4.0);
	EXPECT_DOUBLE_EQ(BasicStats::range(std::vector<int>{}), 0.0);
}

TEST(BasicStatsTests, IQR) {
	EXPECT_DOUBLE_EQ(BasicStats::iqr(std::vector<int>{1, 2, 3, 4, 5, 6}), 3.0);
	EXPECT_DOUBLE_EQ(BasicStats::iqr(std::vector<int>{1, 2, 3, 4, 5}), 2.0);
	EXPECT_DOUBLE_EQ(BasicStats::iqr(std::vector<int>{}), 0.0);
}

TEST(BasicStatsTests, PercentileInc) {
	EXPECT_DOUBLE_EQ(BasicStats::percentile_inc(std::vector<int>{1, 2, 3, 4, 5}, 50), 3.0);
	EXPECT_DOUBLE_EQ(BasicStats::percentile_inc(std::vector<int>{1, 2, 3, 4, 5}, 25), 2.0);
	EXPECT_NEAR(BasicStats::percentile_inc(std::vector<int>{1, 2, 3, 4, 5}, 75), 4.0, 0.01);
	EXPECT_THROW(BasicStats::percentile_inc(std::vector<int>{1, 2, 3, 4, 5}, -10), std::out_of_range);
	EXPECT_THROW(BasicStats::percentile_inc(std::vector<int>{1, 2, 3, 4, 5}, 110), std::out_of_range);
}

TEST(BasicStatsTests, FilterSinglePredicate) {
	auto result = BasicStats::filter(std::vector<int>{ 1, 2, 3, 4, 5 }, [](int x) { return x > 3; });
	EXPECT_EQ(result, std::vector<int>({ 4, 5 }));
}

TEST(BasicStatsTests, FilterWithCriteria) {
	auto result = BasicStats::filter(std::vector<int>{1, 2, 3, 4, 5}, std::vector<int>{10, 20, 30, 40, 50}, [](int x) { return x > 30; });
	EXPECT_EQ(result, std::vector<int>({ 4, 5 }));
	EXPECT_THROW(BasicStats::filter(std::vector<int>{1, 2}, std::vector<int>{1}, [](int x) { return x > 0; }), std::invalid_argument);
}