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


#include "misc.h"
#include "world.h"

#define PI 3.14159265358

int main(int argc, char *argv[]) {
    World wd;
    
    Vessel* shuttle = wd.createVessel("Shuttle", "SpaceShuttleOrbiter.3ds");
    shuttle->defPosition(vec3());
    shuttle->defVitesse(vec3());
    shuttle->defAttitude(osg::Quat());
    shuttle->defOmega(vec3());
    
    //Planet* earth = wd.createPlanet("Terre", "Earth");
    
    wd.setUpViewer();
    
    double prevSimTime = 0.0f;
    
    std::cout << "Entering loop" << std::endl;
    
    while( !wd.getViewer().done() ) {
        const double currSimTime = wd.getViewer().getFrameStamp()->getSimulationTime();
        double elapsed( currSimTime - prevSimTime );
//        if( wd.getViewer().getFrameStamp()->getFrameNumber() < 3 )
//            elapsed = 1./60.;
        
        wd.update(elapsed);
        
        shuttle->addForce(vec3(0.,0.,9.81*104915.915));
        
        prevSimTime = currSimTime;
        wd.getViewer().frame();
    }
    
//    
    
    return 0;
}

