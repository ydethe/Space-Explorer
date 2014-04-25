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

#include <fstream>

#include "planet.h"
#include "vessel.h"
#include "clock.h"

class World {
public:
    std::vector<Planet*> _planets;
    std::vector<Vessel*> _vessels;
    osg::ref_ptr<osg::Group> _root_node;
    osgViewer::Viewer _viewer;
    osg::Camera* _camera;
    Clock _clk;
    
public:
    World();
    ~World();
    
    void importConfig(const std::string& folder_name);
    
    Planet* createPlanet(const std::string& spice_name, const std::string& ground_tex_name, const std::string& cloud_tex_name, const std::string& disp_name);
    Vessel* createVessel(const std::string& name, const std::string& model_filename);
    
    void setUpViewer();
    osgViewer::Viewer& getViewer();
    
    void update(double dt);
    
};

#endif



