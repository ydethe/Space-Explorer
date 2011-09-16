// Copyright (C) 2009  Yann de The
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.


#ifndef UTIL_H_
#define UTIL_H_

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <SpiceUsr.h>
#include <boost/date_time/posix_time/posix_time.hpp>

class BadConversion : public std::runtime_error {
public:
	BadConversion(const std::string& s)
	: std::runtime_error(s)
	{ }
};

template <typename T> std::string stringify(T x) {
	std::ostringstream o;
	if (!(o << x))
		throw BadConversion("stringify");
	return o.str();
}

void getPresentTime(char*);

#endif
