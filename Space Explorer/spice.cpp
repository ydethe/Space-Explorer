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
    
	Object::Object() : mName("[UNDEF]") {
		
	}
    
    Object::Object(const std::string& name) : mName(name) {
		
	}
	
	Object::~Object() {
	}
    
    void Object::getRadii(double* Req, double* Rpo) {
        SpiceDouble radii[3];
        SpiceInt N;
        
        std::cout << "Appel" << std::endl;
        bodvrd_c(mName.c_str(), "RADII", 3, &N, radii);
        *Req = double(radii[0]*1000.);
        *Rpo = double(radii[2]*1000.);
//        std::cout << N << "," << *Req << "," << *Rpo << std::endl;
    }
    
	vec3 Object::getPosition(double t) const {
        vec3 mPosition;
        
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
		mPosition = vec3(state[0], state[1], state[2]);
		
        return mPosition;
	}
	
	vec3 Object::getVelocity(double t) const {
		vec3 mVelocity;
        
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
		mVelocity =vec3(state[3], state[4], state[5]);
		
        return mVelocity;
	}
	
    osg::Quat Object::getAttitude(double t) const {
        osg::Quat mAttitude;
        osg::Matrixd mat;
        
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
		mat = osg::Matrixd(xform[0][0], xform[0][1], xform[0][2], 0.,
                      xform[1][0], xform[1][1], xform[1][2], 0.,
                      xform[2][0], xform[2][1], xform[2][2], 0.,
                      0.,          0.,          0.,          1.);
		
        mAttitude = mat.getRotate();
        return mAttitude;
	}
	
	vec3 Object::getAngularVelocity(double t) const {
		vec3 mAngularVelocity = vec3(0.,0.,0.);
        
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
		
        for (int k=0; k<3; k++) {
            mAngularVelocity = mAngularVelocity + vec3(-xform[4][k]*xform[5][k], xform[3][k]*xform[5][k], -xform[3][k]*xform[4][k]);
        }
        
        return mAngularVelocity;
	}
	
	void Clear(const std::string& KerFile) {
		unload_c(KerFile.c_str());
	}
}
