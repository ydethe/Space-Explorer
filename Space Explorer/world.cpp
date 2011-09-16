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


#include "world.h"

std::vector<Planet*> _planets;
std::vector<Vessel*> _vessels;
osg::ref_ptr<osg::Group> _root_node;

World::World() : _root_node(new osg::Group()) {
    Spice::Init(getResourceFilePaths() + std::string("/KernelsToLoad.ker"));
}

World::~World() {
    std::vector<Planet*>::iterator itP;
    std::vector<Vessel*>::iterator itV;
    
    for (itP = _planets.begin(); itP != _planets.end(); itP++)
        delete (*itP);
    
    for (itV = _vessels.begin(); itV != _vessels.end(); itV++)
        delete (*itV);
    
    Spice::Clear("../../KernelsToLoad.ker");
}

Planet* World::createPlanet(const std::string& nom, const std::string& nom_spice) {
    Planet* planet = new Planet(_root_node, nom, nom_spice);
    _planets.push_back(planet);
    return planet;
}

Vessel* World::createVessel(const std::string& nom, const std::string& model_filename) {
    Vessel* vessel = new Vessel(_root_node, nom, model_filename);
    _vessels.push_back(vessel);
    return vessel;
}

void World::setUpViewer() {
    _viewer.setUpViewInWindow( 150.0f, 150.0f, 1024.0f, 768.0f );
    _viewer.setSceneData( _root_node.get() );
    _viewer.getCamera()->setViewMatrixAsLookAt(osg::Vec3( 1000.0f, 0.0f, -1000.0f ), osg::Vec3( 0.0f, 0.0f, 0.0f ), osg::Vec3( 0.0f, 0.0f, -1.0f ) );
    _viewer.getCamera()->setProjectionMatrixAsPerspective( 70.0f, 1.0f, 1.0f, 10000.0f );
    _viewer.setCameraManipulator(new osgGA::TrackballManipulator);
    
    _viewer.realize();
}

osgViewer::Viewer& World::getViewer() {
    return _viewer;
}


bool World::update(double dt) {
    std::vector<Planet*>::iterator itP;
    std::vector<Vessel*>::iterator itV;
    
    for (itP = _planets.begin(); itP != _planets.end(); itP++)
        (*itP)->update(dt);
    
    for (itV = _vessels.begin(); itV != _vessels.end(); itV++)
        (*itV)->update(dt);
    
}





