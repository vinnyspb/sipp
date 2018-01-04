#include <gtest/gtest.h>

#include <sipp/sipp.hpp>

using namespace sipp::literals;

class DistanceTestFixture : public ::testing::Test {

};

TEST_F(DistanceTestFixture, TestConversionMetersToKm)
{
    sipp::Kilometers kilometers(2.0_m);
    ASSERT_FLOAT_EQ(kilometers.count(), 0.002);
}

TEST_F(DistanceTestFixture, TestConversionMetersToFeet)
{
    sipp::Feet feet(100.0_m);
    ASSERT_FLOAT_EQ(feet.count(), 328.084);
}

TEST_F(DistanceTestFixture, TestConversionKmToNM)
{
    sipp::NauticalMiles NM = 123.5_km;
    ASSERT_FLOAT_EQ(NM.count(), 66.684665);
}

TEST_F(DistanceTestFixture, TestExplicitConversionWithPrecisionLoss)
{
    sipp::Distance<int> meters(1150);
    auto km = sipp::distance_cast<sipp::Distance<int, std::ratio<1000, 1>>>(meters);
    ASSERT_EQ(1, km.count());
}

TEST_F(DistanceTestFixture, TestMultiplyDistanceWithInteger)
{
    auto d = 100.0_km;
    auto d1 = 5 * d;
    auto d2 = d * 5;
    ASSERT_FLOAT_EQ(d1.count(), 500.0);
    ASSERT_FLOAT_EQ(d2.count(), 500.0);
}

TEST_F(DistanceTestFixture, TestMultiplyDistanceWithFloat)
{
    auto d = 100.0_km;
    auto d1 = 1.5 * d;
    auto d2 = d * 1.5;
    ASSERT_FLOAT_EQ(d1.count(), 150.0);
    ASSERT_FLOAT_EQ(d2.count(), 150.0);
}

TEST_F(DistanceTestFixture, TestDivideDistanceByFloat)
{
    auto d = 100.0_km;
    auto d1 = d / 2.0;
    ASSERT_FLOAT_EQ(d1.count(), 50.0);
}

TEST_F(DistanceTestFixture, TestSumDistances)
{
    auto d1 = 100.0_km;
    auto d2 = 20.0_m;

    auto sum1 = sipp::distance_cast<sipp::Meters>(d1 + d2);
    auto sum2 = sipp::distance_cast<sipp::Meters>(d2 + d1);
    ASSERT_FLOAT_EQ(sum1.count(), 100020.0);
    ASSERT_FLOAT_EQ(sum2.count(), 100020.0);
}

TEST_F(DistanceTestFixture, TestSumDistancesUnary)
{
    auto d1 = 100.0_km;
    d1 += 20.0_m;

    auto sum = sipp::distance_cast<sipp::Meters>(d1);
    ASSERT_FLOAT_EQ(sum.count(), 100020.0);
}

TEST_F(DistanceTestFixture, TestSubtractDistances)
{
    auto d1 = 100.0_km;
    auto d2 = 20.0_m;

    auto sum = sipp::distance_cast<sipp::Meters>(d1 - d2);
    ASSERT_FLOAT_EQ(sum.count(), 99980.0);
}

TEST_F(DistanceTestFixture, TestSubtractDistancesUnary)
{
    auto d1 = 100.0_km;
    d1 -= 20.0_m;

    auto sum = sipp::distance_cast<sipp::Meters>(d1);
    ASSERT_FLOAT_EQ(sum.count(), 99980.0);
}

TEST_F(DistanceTestFixture, TestMultiplyWithScalarUnary)
{
    auto d1 = 100.0_km;
    d1 *= 5;

    auto sum = sipp::distance_cast<sipp::Meters>(d1);
    ASSERT_FLOAT_EQ(sum.count(), 500000.0);
}

TEST_F(DistanceTestFixture, TestDivideByScalarUnary)
{
    auto d1 = 100.0_km;
    d1 /= 5;

    auto sum = sipp::distance_cast<sipp::Meters>(d1);
    ASSERT_FLOAT_EQ(sum.count(), 20000.0);
}

TEST_F(DistanceTestFixture, TestOperatorLess)
{
    auto d1 = 100.0_km;
    auto d2 = 100001.0_m;

    ASSERT_LT(d1, d2);
}

TEST_F(DistanceTestFixture, TestOperatorLessEqual)
{
    auto d1 = 100.0_km;
    auto d2 = 100001.0_m;

    ASSERT_LE(d1, d2);
}

TEST_F(DistanceTestFixture, TestOperatorGreater)
{
    auto d1 = 100.0_km;
    auto d2 = 100001.0_m;

    ASSERT_GT(d2, d1);
}

TEST_F(DistanceTestFixture, TestOperatorGreaterEqual)
{
    auto d1 = 100.0_km;
    auto d2 = 100001.0_m;

    ASSERT_GE(d2, d1);
}

TEST_F(DistanceTestFixture, TestOperatorEquality)
{
    auto d1 = 100.0_km;
    auto d2 = 100000.0_m;

    ASSERT_GE(d2, d1);
    ASSERT_GE(d1, d2);
    ASSERT_LE(d1, d2);
    ASSERT_LE(d2, d1);
    ASSERT_EQ(d1, d2);
}

TEST_F(DistanceTestFixture, TestAbs)
{
    auto altitude1 = -1000_ft;
    auto altitude2 = 1000_ft;

    ASSERT_EQ(altitude1.abs(), 1000_ft);
    ASSERT_EQ(altitude2.abs(), 1000_ft);
}
