#include <gtest/gtest.h>

#include <sipp/sipp.hpp>

using namespace sipp::literals;

class SpeedTestFixture : public ::testing::Test {

};

TEST_F(SpeedTestFixture, TestFeetPerMinuteToMetersPerSecond)
{
    sipp::MetersPerSecond meters_per_second(3000.0_ft_min);
    ASSERT_FLOAT_EQ(meters_per_second.count(), 15.24);
}

TEST_F(SpeedTestFixture, TestKnotsToKmh)
{
    sipp::KmPerHour km_per_hour(140.0_kts);
    ASSERT_FLOAT_EQ(km_per_hour.count(), 259.28);
}

TEST_F(SpeedTestFixture, TestKmhToKnots)
{
    sipp::Knots knots(900.0_km_h);
    ASSERT_FLOAT_EQ(knots.count(), 485.961);
}

TEST_F(SpeedTestFixture, TestKmhToMPH)
{
    sipp::MilesPerHour miles_per_hour(900.0_km_h);
    ASSERT_FLOAT_EQ(miles_per_hour.count(), 559.23547);
}

TEST_F(SpeedTestFixture, TestMultiplySpeedWithScalar)
{
    auto spd = 900.0_km_h;
    auto spd1 = 2 * spd;
    auto spd2 = spd * 2.0;

    ASSERT_FLOAT_EQ(spd1.count(), spd2.count());
    ASSERT_FLOAT_EQ(spd1.count(), 1800.0);
}

TEST_F(SpeedTestFixture, TestSumSpeeds)
{
    auto spd1 = 900.0_km_h;
    auto spd2 = 10.0_mph;

    auto sum = sipp::speed_cast<sipp::KmPerHour>(spd1 + spd2);

    ASSERT_FLOAT_EQ(sum.count(), 916.0934);
}

TEST_F(SpeedTestFixture, TestMultiplyWithScalarUnary)
{
    auto spd = 100.0_km_h;
    spd *= 5;

    auto result = sipp::speed_cast<sipp::KmPerHour>(spd);
    ASSERT_FLOAT_EQ(result.count(), 500.0);
}

TEST_F(SpeedTestFixture, TestDivideByScalarUnary)
{
    auto spd = 100.0_km_h;
    spd /= 5;

    auto result = sipp::speed_cast<sipp::KmPerHour>(spd);
    ASSERT_FLOAT_EQ(result.count(), 20.0);
}

TEST_F(SpeedTestFixture, TestOperatorLess)
{
    auto spd1 = 100.0_km_h; // ~27.777778 m/s
    auto spd2 = 27.78_m_s;

    ASSERT_LT(spd1, spd2);
}

TEST_F(SpeedTestFixture, TestOperatorLessEqual)
{
    auto spd1 = 100.0_km_h; // ~27.777778 m/s
    auto spd2 = 27.78_m_s;

    ASSERT_LE(spd1, spd2);
}

TEST_F(SpeedTestFixture, TestOperatorGreater)
{
    auto spd1 = 100.0_km_h; // ~27.777778 m/s
    auto spd2 = 27.78_m_s;

    ASSERT_GT(spd2, spd1);
}

TEST_F(SpeedTestFixture, TestOperatorGreaterEqual)
{
    auto spd1 = 100.0_km_h; // ~27.777778 m/s
    auto spd2 = 27.78_m_s;

    ASSERT_GE(spd2, spd1);
}

TEST_F(SpeedTestFixture, TestOperatorEquality)
{
    auto spd1 = 1_ft_s;
    auto spd2 = 60_ft_min;

    ASSERT_GE(spd2, spd1);
    ASSERT_GE(spd1, spd2);
    ASSERT_LE(spd1, spd2);
    ASSERT_LE(spd2, spd1);
    ASSERT_EQ(spd2, spd1);
}

TEST_F(SpeedTestFixture, TestNegateOperator)
{
    auto spd1 = -60_ft_min;

    ASSERT_LT(spd1, 0_ft_min);
}
