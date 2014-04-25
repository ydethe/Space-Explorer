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
#include "vessel.h"

// 221T de pousse dans le vide à 104% du nominal Reglable de 67% à 104%
// 1114kg/s O2 et 210kg/s H2 à 104%
// ISP 453s
// V ejection 4440m/s ds vide et 3560m/s au niveau de la mer
// Rapport de détente tuyère : 69
// Longueur tuyère : 4.24m
// Diamètre sortie : 2.38m
// 


#include "world.h"
#include <osgDB/Archive>
#include <osgDB/ReaderWriter>

int main0(int argc, char *argv[]) {
    std::string archivePath;
    archivePath = GetApplicationResourcesPath() + std::string("XWing.zip");
    
    osg::ref_ptr<osgDB::Archive> archive = osgDB::openArchive(archivePath, osgDB::ReaderWriter::READ);
    osgDB::ReaderWriter::ReaderWriter::ReadResult res = archive->readNode("model.dae");

    osg::ref_ptr<osg::Node> node = res.getNode();
    
    if ( node.valid() )
        std::cout << "OK" << std::endl;
    else
        std::cout << "NOK" << std::endl;
    
    return 0;
}

int main(int argc, char *argv[]) {
    World wd = World();
    
    wd.importConfig("Earth");
    wd.importConfig("XWing");
  
    Vessel* shuttle = wd._vessels[0];
    shuttle->defPosition(vec3(0.,0.,0.));
    shuttle->defVitesse(vec3(0.,0.,0.));
    shuttle->defAttitude(osg::Quat(0.,0.,0., 1.));
    shuttle->defOmega(vec3(1.,0.,0.));
    
    Tank tk = Tank(1131.37, 549.407, 549.407);
    shuttle->setTank(tk);
    shuttle->addEngine(RCS_LIN_X_NEG, vec3(0.,0.,0.), vec3(-4440., 0., 0.), 1114.);
    
    wd.setUpViewer();
    
    double prevSimTime = 0.0f;
    
    while( !wd.getViewer().done() ) {
        const double currSimTime = wd.getViewer().getFrameStamp()->getSimulationTime();
        double dt(currSimTime - prevSimTime);
        
//        if ( currSimTime < 1. )
//            shuttle->setLevel(RCS_LIN_X_NEG, 1.);
//        else
//            shuttle->setLevel(RCS_LIN_X_NEG, 0.);
        
        osg::notify( osg::ALWAYS ) << "------------------------\nt:" << currSimTime << "\tdt:" << dt << std::endl;
        wd.update(dt);
        
        prevSimTime = currSimTime;
    }
    
    return 0;
}



