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


#include "spice.h"

namespace Spice {
	void Init(const std::string& KerFile) {
		furnsh_c(KerFile.c_str());
	}
    
	Object::Object(const std::string& name) : mName(name) {
		
	}
	
	Object::~Object() {
	}
		
	Eigen::Vector3d Object::getPosition(double t) const {
        Eigen::Vector3d mPosition;
        
		SpiceDouble tdb;
		SpiceDouble state[6];
		SpiceDouble lt;
		SpiceDouble xform[6][6];
		SpiceChar date[30];
		
		// Conversion de l'heure
		getPresentTime(date);
		str2et_c(date, &tdb);
		
		// Calcul pos. & vit.
		spkezr_c(mName.c_str(), tdb, "J2000", "None", "Sun", state, &lt);
		mPosition << state[0], state[1], state[2];
		
        return mPosition;
	}
	
	Eigen::Vector3d Object::getVelocity(double t) const {
		Eigen::Vector3d mVelocity;
        
		SpiceDouble tdb;
		SpiceDouble state[6];
		SpiceDouble lt;
		SpiceDouble xform[6][6];
		SpiceChar date[30];
		
		// Conversion de l'heure
		getPresentTime(date);
		str2et_c(date, &tdb);
		
		// Calcul pos. & vit.
		spkezr_c(mName.c_str(), tdb, "J2000", "None", "Sun", state, &lt);
		mVelocity << state[3], state[4], state[5];
		
        return mVelocity;
	}
	
	Eigen::Matrix3d Object::getAttitude(double t) const {
		Eigen::Matrix3d mAttitude;
        
		SpiceDouble tdb;
		SpiceDouble state[6];
		SpiceDouble lt;
		SpiceDouble xform[6][6];
		SpiceChar date[30];
		
		// Conversion de l'heure
		getPresentTime(date);
		str2et_c(date, &tdb);
		
		// Calcul att. & vit. angulaire
		sxform_c((std::string("IAU_") + mName).c_str(), "J2000", tdb, xform);
		mAttitude << xform[0][0], xform[0][1], xform[0][2], xform[1][0], xform[1][1], xform[1][2], xform[2][0], xform[2][1], xform[2][2];
		
        return mAttitude;
	}
	
	Eigen::Matrix3d Object::getAngularVelocity(double t) const {
		Eigen::Matrix3d mAngularVelocity;
        
		SpiceDouble tdb;
		SpiceDouble state[6];
		SpiceDouble lt;
		SpiceDouble xform[6][6];
		SpiceChar date[30];
		
		// Conversion de l'heure
		getPresentTime(date);
		str2et_c(date, &tdb);
		
		// Calcul att. & vit. angulaire
		sxform_c((std::string("IAU_") + mName).c_str(), "J2000", tdb, xform);
		mAngularVelocity << xform[3][0], xform[3][1], xform[3][2], xform[4][0], xform[4][1], xform[4][2], xform[5][0], xform[5][1], xform[5][2];
        
        return mAngularVelocity;
	}
	
	void Clear(const std::string& KerFile) {
		unload_c(KerFile.c_str());
	}
}
