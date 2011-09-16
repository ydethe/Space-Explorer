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



#ifndef Space_Explorer_world_h
#define Space_Explorer_world_h

#include <vector>

#include <osgGA/TrackballManipulator>
#include <osgViewer/Viewer>

#include "planet.h"
#include "vessel.h"

class World {
public:
    std::vector<Planet*> _planets;
    std::vector<Vessel*> _vessels;
    osg::ref_ptr<osg::Group> _root_node;
    osgViewer::Viewer _viewer;
    
public:
    World();
    ~World();
    
    Planet* createPlanet(const std::string& nom, const std::string& nom_spice);
    Vessel* createVessel(const std::string& nom, const std::string& model_filename);
    
    void setUpViewer();
    osgViewer::Viewer& getViewer();
    
    bool update(double dt);
    
};

#endif



