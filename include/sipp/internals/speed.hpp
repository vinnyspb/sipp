#pragma once

#include "distance.hpp"
#include "speed_fwd.hpp"

namespace sipp {

template<class ToSpeed, class Rep, class DistanceType, class Ratio>
constexpr ToSpeed speed_cast(const Speed<Rep, DistanceType, Ratio> &speed)
{
    const auto converted_distance =
        distance_cast<typename ToSpeed::distance_type>(DistanceType(speed.count())).count();
    const auto converted_period =
        (static_cast<double>(Ratio::num) * static_cast<double>(ToSpeed::ratio::den))
            / (static_cast<double>(Ratio::den) * static_cast<double>(ToSpeed::ratio::num));

    return ToSpeed(static_cast<typename ToSpeed::rep>(converted_distance / converted_period));
}

template<class Rep, class DistanceType, class Ratio = std::ratio<1>>
class Speed {
public:
    using rep = Rep;
    using distance_type = DistanceType;
    using ratio = Ratio;

    constexpr Speed() : m_count(0)
    {}

    template<class Rep2>
    constexpr explicit Speed(const Rep2 &value): m_count(value)
    {}

    template<class Rep2, class DistanceType2, class Ratio2>
    constexpr Speed(const Speed<Rep2, DistanceType2, Ratio2> &other)
    {
        *this = other;
    }

    template<class Rep2, class DistanceType2, class Ratio2>
    constexpr void operator=(const Speed<Rep2, DistanceType2, Ratio2> &other)
    {
        static_assert(std::is_floating_point<Rep>::value
                          && std::is_floating_point<Rep2>::value,
                      "Use sipp::speed_cast<> to perform explicit cast of integer types "
                          "(possible precision loss)");
        *this = speed_cast<Speed<Rep, DistanceType, Ratio>>(other);
    }

    template<class Rep2, class DistanceType2, class Ratio2>
    constexpr Speed<Rep, DistanceType, Ratio> &operator+=(const Speed<Rep2,
                                                                      DistanceType2,
                                                                      Ratio2> &other)
    {
        *this = *this + other;
        return *this;
    }

    template<class Rep2, class DistanceType2, class Ratio2>
    constexpr Speed<Rep, DistanceType, Ratio> &operator-=(const Speed<Rep2,
                                                                      DistanceType2,
                                                                      Ratio2> &other)
    {
        *this = *this - other;
        return *this;
    }

    template<class Rep2>
    constexpr Speed<Rep, DistanceType, Ratio> &operator*=(const Rep2 &multiplier)
    {
        *this = *this * multiplier;
        return *this;
    }

    template<class Rep2>
    constexpr Speed<Rep, DistanceType, Ratio> &operator/=(const Rep2 &divider)
    {
        *this = *this / divider;
        return *this;
    }

    template<class Rep2, class DistanceType2, class Ratio2>
    constexpr bool operator<(const Speed<Rep2,
                                         DistanceType2,
                                         Ratio2> &other) const
    {
        return m_count < speed_cast<Speed<Rep, DistanceType, Ratio>>(other).m_count;
    }

    template<class Rep2, class DistanceType2, class Ratio2>
    constexpr bool operator<=(const Speed<Rep2,
                                          DistanceType2,
                                          Ratio2> &other) const
    {
        return m_count <= speed_cast<Speed<Rep, DistanceType, Ratio>>(other).m_count;
    }

    template<class Rep2, class DistanceType2, class Ratio2>
    constexpr bool operator>(const Speed<Rep2,
                                         DistanceType2,
                                         Ratio2> &other) const
    {
        return !(*this <= other);
    }

    template<class Rep2, class DistanceType2, class Ratio2>
    constexpr bool operator>=(const Speed<Rep2,
                                          DistanceType2,
                                          Ratio2> &other) const
    {
        return !(*this < other);
    }

    template<class Rep2, class DistanceType2, class Ratio2>
    constexpr bool operator==(const Speed<Rep2,
                                          DistanceType2,
                                          Ratio2> &other) const
    {
        return m_count == speed_cast<Speed<Rep, DistanceType, Ratio>>(other).m_count;
    }

    constexpr const Rep &count() const
    { return m_count; }

private:
    Rep m_count;
};

template<class Rep, class DistanceType, class Ratio, class Rep2>
constexpr Speed<Rep, DistanceType, Ratio> operator*(const Speed<Rep, DistanceType, Ratio> &speed,
                                                    const Rep2 &multiplier)
{
    static_assert(std::is_integral<Rep2>::value ||
                      std::is_floating_point<Rep2>::value,
                  "Allowed to multiply Speed only on integral or floating point types");

    return Speed<Rep, DistanceType, Ratio>(speed.count() * multiplier);
}

template<class Rep, class DistanceType, class Ratio, class Rep2>
constexpr Speed<Rep, DistanceType, Ratio> operator*(const Rep2 &multiplier,
                                                    const Speed<Rep, DistanceType, Ratio> &speed)
{
    return speed * multiplier;
}

template<class Rep, class DistanceType, class Ratio, class Rep2>
constexpr Speed<Rep, DistanceType, Ratio> operator/(const Speed<Rep, DistanceType, Ratio> &speed,
                                                    const Rep2 &divider)
{
    static_assert(std::is_integral<Rep2>::value ||
                      std::is_floating_point<Rep2>::value,
                  "Allowed to divide Speed only by integral or floating point types");

    return Speed<Rep, DistanceType, Ratio>(speed.count() / divider);
}

template<class Rep1, class DistanceType1, class Ratio1, class Rep2, class DistanceType2, class Ratio2>
constexpr Speed<Rep1, DistanceType1, Ratio1> operator+(const Speed<Rep1,
                                                                   DistanceType1,
                                                                   Ratio1> &speed1,
                                                       const Speed<Rep2,
                                                                   DistanceType2,
                                                                   Ratio2> &speed2)
{
    const Speed<Rep1, DistanceType1, Ratio1> converted_speed2 = speed2;
    return Speed<Rep1, DistanceType1, Ratio1>(speed1.count() + converted_speed2.count());
}

template<class Rep1, class DistanceType1, class Ratio1, class Rep2, class DistanceType2, class Ratio2>
constexpr Speed<Rep1, DistanceType1, Ratio1> operator-(const Speed<Rep1,
                                                                   DistanceType1,
                                                                   Ratio1> &speed1,
                                                       const Speed<Rep2,
                                                                   DistanceType2,
                                                                   Ratio2> &speed2)
{
    const Speed<Rep1, DistanceType1, Ratio1> converted_speed2 = speed2;
    return Speed<Rep1, DistanceType1, Ratio1>(speed1.count() - converted_speed2.count());
}

namespace literals {

constexpr KmPerHour operator "" _km_h(long double value)
{ return KmPerHour(value); }

constexpr MetersPerSecond operator "" _m_s(long double value)
{ return MetersPerSecond(value); }

constexpr FeetPerSecond operator "" _ft_s(long double value)
{ return FeetPerSecond(value); }

constexpr FeetPerMinute operator "" _ft_min(long double value)
{ return FeetPerMinute(value); }

constexpr Knots operator "" _kts(long double value)
{ return Knots(value); }

constexpr MilesPerHour operator "" _mph(long double value)
{ return MilesPerHour(value); }

}

}
