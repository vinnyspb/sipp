#pragma once

namespace sipp {

template<class Rep, class Ratio>
class Distance;

using Meters = Distance<double, std::ratio<1>>;
using Kilometers = Distance<double, std::kilo>;
using Millimeters = Distance<double, std::milli>;
using Micrometers = Distance<double, std::micro>;
using Nanometers = Distance<double, std::nano>;
using Feet = Distance<double, std::ratio<3048, 10000>>;
using NauticalMiles = Distance<double, std::ratio<1852, 1>>;
using StatuteMiles = Distance<double, std::ratio<160934, 100>>;

}
