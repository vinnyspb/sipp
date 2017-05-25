[![Linux/macOS Build Status](https://travis-ci.org/vinnyspb/sipp.svg?branch=master)](https://travis-ci.org/vinnyspb/sipp)
[![Windows Build status](https://ci.appveyor.com/api/projects/status/fprd626eq7t7769f/branch/master?svg=true)](https://ci.appveyor.com/project/vinnyspb/sipp/branch/master)
[![codecov](https://codecov.io/gh/vinnyspb/sipp/branch/master/graph/badge.svg)](https://codecov.io/gh/vinnyspb/sipp)

# SI++ library

## Description

Inspired by std::chrono, header-only library providing
compile-time conversions and type-safety between different unit metrics.

Name SI comes from [International System of Units](https://en.wikipedia.org/wiki/International_System_of_Units).

Library provides 2 basic template types: `Distance` and `Speed`.

Think about these as `std::chrono::duration<>` template.
There are typedefs instantiating exact metric units (see below).

## Dependencies

C++14 compatible compiler.

## Distance

### Example

```cpp
#include <sipp/sipp.hpp>

// ...

using namespace sipp::literals;

auto distance_in_km = 100.0_km;
sipp::Feet distance_in_feet = distance_in_km;

std::cout << "Distance in kilometers: " << distance_in_km.count() << std::endl;
std::cout << "Distance in feet: " << distance_in_feet.count() << std::endl;

auto casted = sipp::distance_cast<sipp::Meters>(5 * distance_in_km);
std::cout << "Multiplied kilometers and cast to meters: " << casted.count() << std::endl;

```

### Implemented unit metrics

* `sipp::Meters`, literal `_m`
* `sipp::Kilometers`, literal `_km`
* `sipp::Millimeters`, literal `_mm`
* `sipp::Micrometers`, literal `_um`
* `sipp::Nanometers`, literal `_nm`
* `sipp::Feet`, literal `_ft`
* `sipp::NauticalMiles`, literal `_NM`
* `sipp::StatuteMiles`, literal `_mi`

## Speed

### Example

```cpp
#include <sipp/sipp.hpp>

// ...

using namespace sipp::literals;

auto speed_in_kmh = 100.0_km_h;
sipp::Knots speed_in_knots = speed_in_kmh;

std::cout << "Speed in km/h " << speed_in_kmh.count() << std::endl;
std::cout << "Speed in knots: " << speed_in_knots.count() << std::endl;

auto casted = sipp::speed_cast<sipp::FeetPerMinute>(speed_in_knots + 10_m_s);
std::cout << "100 km/h + 10 m/s casted to feet/min: " << casted.count() << std::endl;

```

### Implemented unit metrics

* `sipp::KmPerHour`, literal `_km_h`
* `sipp::MetersPerSecond`, literal `_m_s`
* `sipp::FeetPerSecond`, literal `_ft_s`
* `sipp::FeetPerMinute`, literal `_ft_min`
* `sipp::Knots`, literal `_kts`
* `sipp::MilesPerHour`, literal `_mph`

## Contribution

There are unit tests, which can be built with cmake.
Requires googletest (which is in git submodule `3rdparty/googletest`).

```bash
$ cd /path/to/sources
$ git submodule update --init --recursive
$ mkdir -p build
$ cd build
$ cmake -DCMAKE_BUILD_TYPE=Debug ../
$ make sipp_tests
$ ./sipp_tests
```
