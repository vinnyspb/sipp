#pragma once

#include <type_traits>
#include <ratio>

namespace sipp {

template<class Rep, class Ratio>
class Distance;

template<class ToDistance, class Rep, class Ratio>
constexpr ToDistance distance_cast(const Distance<Rep, Ratio> &distance)
{
    return ToDistance(static_cast<typename ToDistance::rep>(
                          (static_cast<double>(ToDistance::ratio::den)
                              / static_cast<double>(ToDistance::ratio::num))
                              * (static_cast<double>(Ratio::num) / static_cast<double>(Ratio::den))
                              * distance.count()));
}

template<class Rep, class Ratio = std::ratio<1>>
class Distance {
public:
    using rep = Rep;
    using ratio = Ratio;

    constexpr Distance() : m_count(0)
    {}

    template<class Rep2>
    constexpr explicit Distance(const Rep2 &value): m_count(value)
    {}

    template<class Rep2, class Ratio2>
    constexpr Distance(const Distance<Rep2, Ratio2> &other)
    {
        *this = other;
    }

    template<class Rep2, class Ratio2>
    constexpr void operator=(const Distance<Rep2, Ratio2> &other)
    {
        static_assert(std::is_floating_point<Rep>::value
                          && std::is_floating_point<Rep2>::value,
                      "Use sipp::distance_cast<> to perform explicit cast of integer types "
                          "(possible precision loss)");
        *this = distance_cast<Distance<Rep, Ratio>>(other);
    }

    template<class Rep2, class Ratio2>
    constexpr Distance<Rep, Ratio> &operator+=(const Distance<Rep2, Ratio2> &other)
    {
        *this = *this + other;
        return *this;
    }

    template<class Rep2, class Ratio2>
    constexpr Distance<Rep, Ratio> &operator-=(const Distance<Rep2, Ratio2> &other)
    {
        *this = *this - other;
        return *this;
    }

    template<class Rep2>
    constexpr Distance<Rep, Ratio> &operator*=(const Rep2 &multiplier)
    {
        *this = *this * multiplier;
        return *this;
    }

    template<class Rep2>
    constexpr Distance<Rep, Ratio> &operator/=(const Rep2 &divider)
    {
        *this = *this / divider;
        return *this;
    }

    constexpr const Rep &count() const
    { return m_count; }

private:
    Rep m_count;
};

template<class Rep, class Ratio, class Rep2>
constexpr Distance<Rep, Ratio> operator*(const Distance<Rep, Ratio> &distance,
                                         const Rep2 &multiplier)
{
    static_assert(std::is_integral<Rep2>::value ||
                      std::is_floating_point<Rep2>::value,
                  "Allowed to multiply Distance only on integral or floating point types");

    return Distance<Rep, Ratio>(distance.count() * multiplier);
}

template<class Rep, class Ratio, class Rep2>
constexpr Distance<Rep, Ratio> operator*(const Rep2 &multiplier,
                                         const Distance<Rep, Ratio> &distance)
{
    return distance * multiplier;
}

template<class Rep, class Ratio, class Rep2>
constexpr Distance<Rep, Ratio> operator/(const Distance<Rep, Ratio> &distance, const Rep2 &divider)
{
    static_assert(std::is_integral<Rep2>::value ||
                      std::is_floating_point<Rep2>::value,
                  "Allowed to divide Distance only by integral or floating point types");

    return Distance<Rep, Ratio>(distance.count() / divider);
}

template<class Rep1, class Ratio1, class Rep2, class Ratio2>
constexpr Distance<Rep1, Ratio1> operator+(const Distance<Rep1, Ratio1> &distance1,
                                           const Distance<Rep2, Ratio2> &distance2)
{
    const Distance<Rep1, Ratio1> converted_distance2 = distance2;
    return Distance<Rep1, Ratio1>(distance1.count() + converted_distance2.count());
}

template<class Rep1, class Ratio1, class Rep2, class Ratio2>
constexpr Distance<Rep1, Ratio1> operator-(const Distance<Rep1, Ratio1> &distance1,
                                           const Distance<Rep2, Ratio2> &distance2)
{
    const Distance<Rep1, Ratio1> converted_distance2 = distance2;
    return Distance<Rep1, Ratio1>(distance1.count() - converted_distance2.count());
}

using Meters = Distance<double, std::ratio<1>>;
using Kilometers = Distance<double, std::kilo>;
using Millimeters = Distance<double, std::milli>;
using Micrometers = Distance<double, std::micro>;
using Nanometers = Distance<double, std::nano>;
using Feet = Distance<double, std::ratio<3048, 10000>>;
using NauticalMiles = Distance<double, std::ratio<1852, 1>>;
using StatuteMiles = Distance<double, std::ratio<160934, 100>>;

namespace literals {

constexpr Meters operator "" _m(long double value)
{ return Meters(value); }

constexpr Kilometers operator "" _km(long double value)
{ return Kilometers(value); }

constexpr Millimeters operator "" _mm(long double value)
{ return Millimeters(value); }

constexpr Micrometers operator "" _um(long double value)
{ return Micrometers(value); }

constexpr Nanometers operator "" _nm(long double value)
{ return Nanometers(value); }

constexpr Feet operator "" _ft(long double value)
{ return Feet(value); }

constexpr NauticalMiles operator "" _NM(long double value)
{ return NauticalMiles(value); }

constexpr StatuteMiles operator "" _mi(long double value)
{ return StatuteMiles(value); }

}

}
