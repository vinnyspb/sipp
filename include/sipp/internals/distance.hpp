#pragma once

#include <type_traits>
#include <ratio>
#include <cmath>

#include "distance_fwd.hpp"

namespace sipp {

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

    template<class Rep2, class Ratio2>
    constexpr bool operator<(const Distance<Rep2, Ratio2> &other) const
    {
        return m_count < distance_cast<Distance<Rep, Ratio>>(other).m_count;
    }

    template<class Rep2, class Ratio2>
    constexpr bool operator<=(const Distance<Rep2, Ratio2> &other) const
    {
        return m_count <= distance_cast<Distance<Rep, Ratio>>(other).m_count;
    }

    template<class Rep2, class Ratio2>
    constexpr bool operator>(const Distance<Rep2, Ratio2> &other) const
    {
        return !(*this <= other);
    }

    template<class Rep2, class Ratio2>
    constexpr bool operator>=(const Distance<Rep2, Ratio2> &other) const
    {
        return !(*this < other);
    }

    template<class Rep2, class Ratio2>
    constexpr bool operator==(const Distance<Rep2, Ratio2> &other) const
    {
        return m_count == distance_cast<Distance<Rep, Ratio>>(other).m_count;
    }

    constexpr Distance<Rep, Ratio> operator-() const
    {
        return Distance<Rep, Ratio>(-m_count);
    }

    constexpr const Rep &count() const
    { return m_count; }

    constexpr Distance<Rep, Ratio> abs() const
    {
        return Distance<Rep, Ratio>(std::abs(m_count));
    }

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

namespace literals {

constexpr Meters operator "" _m(long double value)
{ return Meters(value); }

constexpr Meters operator "" _m(unsigned long long int value)
{ return Meters(value); }

constexpr Kilometers operator "" _km(long double value)
{ return Kilometers(value); }

constexpr Kilometers operator "" _km(unsigned long long int value)
{ return Kilometers(value); }

constexpr Millimeters operator "" _mm(long double value)
{ return Millimeters(value); }

constexpr Millimeters operator "" _mm(unsigned long long int value)
{ return Millimeters(value); }

constexpr Micrometers operator "" _um(long double value)
{ return Micrometers(value); }

constexpr Micrometers operator "" _um(unsigned long long int value)
{ return Micrometers(value); }

constexpr Nanometers operator "" _nm(long double value)
{ return Nanometers(value); }

constexpr Nanometers operator "" _nm(unsigned long long int value)
{ return Nanometers(value); }

constexpr Feet operator "" _ft(long double value)
{ return Feet(value); }

constexpr Feet operator "" _ft(unsigned long long int value)
{ return Feet(value); }

constexpr NauticalMiles operator "" _NM(long double value)
{ return NauticalMiles(value); }

constexpr NauticalMiles operator "" _NM(unsigned long long int value)
{ return NauticalMiles(value); }

constexpr StatuteMiles operator "" _mi(long double value)
{ return StatuteMiles(value); }

constexpr StatuteMiles operator "" _mi(unsigned long long int value)
{ return StatuteMiles(value); }

}

}
