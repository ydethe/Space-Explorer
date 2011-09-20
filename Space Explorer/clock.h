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


#ifndef Space_Explorer_clock_h
#define Space_Explorer_clock_h

#include "util.h"

typedef struct {
    int years; 		/*!< Years. All values are valid */
    int months;		/*!< Months. Valid values : 1 (January) - 12 (December) */
    int days; 		/*!< Days. Valid values 1 - 28,29,30,31 Depends on month.*/
    int hours; 		/*!< Hours. Valid values 0 - 23. */
    int minutes; 	/*!< Minutes. Valid values 0 - 59. */
    double seconds;	/*!< Seconds. Valid values 0 - 59.99999.... */
} Date;

class Clock {
private:
    double _time; // In seconds since January 1st 2000
    
public:
    Clock();
    ~Clock();
    
    void setToPresent();
    double update(double dt);
    double getMJD() const;
    Date getDate() const;
    double getTime() const;
    
};

#endif
