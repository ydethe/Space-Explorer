/// \brief Class which handles time. Can use astronomic and "human readable" time.
/// \file clock.h
/// \version 0.1
/// \author Yann de Thé
/// \date September 20th 2011

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


#include "clock.h"

Clock::Clock() {
    this->setToPresent();
}

Clock::~Clock() {
    
}

void Clock::setToPresent() {
    boost::posix_time::ptime now = boost::posix_time::microsec_clock::universal_time();
    boost::posix_time::time_duration td = now - boost::posix_time::ptime(boost::gregorian::date(1970, boost::gregorian::Jan, 1));
    
    _time = double(td.total_microseconds())/1e6;
}

double Clock::update(double dt) {
    _time += dt;
}

double Clock::getMJD() const {
    return 2440587.5 + _time/86400.0;
}

Date Clock::getDate() const {
    Date date;
    double JD = this->getMJD();
    
    int A,a,B,C,D,E;
    double F,Z;
    
    JD += 0.5;
    Z = (int) JD;
    F = JD - Z;
    
    if (Z < 2299161)
        A = (int) Z;
    else {
        a = (int) ((Z - 1867216.25) / 36524.25);
        A = (int) (Z + 1 + a - (int)(a / 4));
    }
    
    B = A + 1524;
    C = (int) ((B - 122.1) / 365.25);
    D = (int) (365.25 * C);
    E = (int) ((B - D) / 30.6001);
    
    /* get the hms */
    date.hours = (int) (F * 24);
    F -= (double)date.hours / 24;
    date.minutes = (int) (F * 1440);
    F -= (double)date.minutes / 1440;
    date.seconds = F * 86400;
    
    /* get the day */
    date.days = B - D - (int)(30.6001 * E);
    
    /* get the month */
    if (E < 14)
        date.months = E - 1;
    else
        date.months = E - 13;
    
    /* get the year */
    if (date.months > 2)
        date.years = C - 4716;
    else
        date.years = C - 4715;
}

double Clock::getTime() const {
    return _time;
}






