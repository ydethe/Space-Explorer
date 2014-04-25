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
 

#ifndef SPICE_H_
#define SPICE_H_

#include <iostream>
#include <eigen3/Eigen/Eigen>
#include <string>
#include <SpiceUsr.h>
#include <osg/Matrixd>

#include "util.h"

namespace Spice {
    /**
     * \brief Loads an ephemeris file.
     *
     * \param KerFile Path to the ephemeris file to load.
     */
	void Init(const std::string& KerFile);
	
	class Object {
	private:
		std::string mName;
        
	public:
        Object();
		/**
         * \brief Constructor.
         *
         * \param name Name of the CSPICE object (e.g. "Earth").
         */
        Object(const std::string& name);
		~Object();
        /**
         * \brief Returns the position of the body at the given date.
         *
         * \param t MJD date.
         * \return Position in J2000 frame.
         */
		void getRadii(SpiceDouble* Req, SpiceDouble* Rpo);
        vec3 getPosition(double t) const;
		vec3 getVelocity(double t) const;
        osg::Quat getAttitude(double t) const;
		vec3 getAngularVelocity(double t) const;
		
	};
	
	void Clear(const std::string& KerFile);
}

#endif
