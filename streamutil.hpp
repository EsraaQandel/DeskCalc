////////////////////////////////////////////////////////////////////////////////
// DeskCalc is based on the calculator described in Bjarne Stroustrup's
//     "The C++ Programming Language"
//
// Copyright (C) 2017  Matthias Stauber
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <limits>
#include <string>
#include <sstream>

////////////////////////////////////////////////////////////////////////////////
namespace mps {
namespace util {
////////////////////////////////////////////////////////////////////////////////

template<typename T>
static inline T get_num(const std::string& prompt)
{   // Gets a number of type T from std::cin, rejecting input which is nothing but a number
    std::cout << prompt;
    std::string input;

    while (!trim(input).size())  // skip empty input lines
        if (!std::getline(std::cin, input))  // EOF or cin.bad()
            throw std::runtime_error("No Input");

    std::istringstream stream{ input };
    T n;
    if (stream >> n)
    {   // test for remaining characters
        char ch;
        if (!(stream >> ch)) return n;
    }
    std::cout << "Format Error.\n";
    return get_num<T>(prompt);
}

////////////////////////////////////////////////////////////////////////////////

template<typename T>
static inline T get_num(const std::string& prompt, T min, T max)
{   // get_num only accepting numbers in range [min;max]
    T n = get_num<T>(prompt);
    while (n < min || n > max)
    {
        std::cerr << "Not in range [" << min << ';' << max << "]\n";
        n = get_num<T>(prompt);
    }
    return n;
}

////////////////////////////////////////////////////////////////////////////////

static inline void keep_window_open()
{
    std::cout << "Press <RETURN> to close this window...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

////////////////////////////////////////////////////////////////////////////////

using getint = get_num<int>;
using get_double = get_num<double>;

////////////////////////////////////////////////////////////////////////////////
}  // namespace util
} // namespace mps
////////////////////////////////////////////////////////////////////////////////
