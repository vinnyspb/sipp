#pragma once

namespace sipp {

template<class Rep, class DistanceType, class Ratio>
class Speed;

using HourRatio = std::ratio<3600, 1>;
using MinuteRatio = std::ratio<60, 1>;
using SecondRatio = std::ratio<1>;

using KmPerHour = Speed<double, Kilometers, HourRatio>;
using MetersPerSecond = Speed<double, Meters, SecondRatio>;
using FeetPerSecond = Speed<double, Feet, SecondRatio>;
using FeetPerMinute = Speed<double, Feet, MinuteRatio>;
using Knots = Speed<double, NauticalMiles, HourRatio>;
using MilesPerHour = Speed<double, StatuteMiles, HourRatio>;

}
