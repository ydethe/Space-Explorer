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

World::World() : _root_node(new osg::Group()), _viewer(osgViewer::Viewer()) {
    Spice::Init(GetApplicationBundlePath() + "../Config/Spice/KernelsToLoad.ker");
}

World::~World() {
    std::vector<Planet*>::iterator itP;
    std::vector<Vessel*>::iterator itV;
    
    for (itP = _planets.begin(); itP != _planets.end(); itP++)
        delete (*itP);
    
    for (itV = _vessels.begin(); itV != _vessels.end(); itV++)
        delete (*itV);
    
    Spice::Clear(GetApplicationBundlePath() + "../Config/Spice/KernelsToLoad.ker");
}

void World::importConfig(const std::string& folder_name) {
    std::string conf_path = GetApplicationBundlePath() + "../Config/" + folder_name + "/config.cfg";
    std::ifstream fichier(conf_path.c_str());
    
    std::string spice_name, ground_tex_name, cloud_tex_name, disp_name, model_filename;
    std::string ligne, nom, param, empty;
    
    disp_name = spice_name = ground_tex_name = cloud_tex_name = model_filename = "";
    
    bool is_vessel = false;
    
    fichier >> nom >> param;
    //fichier >> nom >> empty >> param;
    if ( param.size() >= 4 ) {
        strip(param);
        if (nom == "type") {
            if (param == "Vessel")
                is_vessel = true;
        }
    }
    
    do {
        //fichier >> nom >> empty >> param;
        fichier >> nom >> param;

        if ( param.size() >= 4 ) {
            strip(param);
            if (nom == "disp_name")
                disp_name = param;
            if (nom == "spice_name")
                spice_name = param;
            if (nom == "model")
                model_filename = GetApplicationBundlePath() + "../Meshes/" + folder_name + "/" + param;
            if (nom == "main_tex_name") {
                if (isURL(param))
                    ground_tex_name = param;
                else
                    ground_tex_name = GetApplicationBundlePath() + "../Textures/" + folder_name + "/" + param;
            }
            if (nom == "clouds_tex_name") {
                if (isURL(param))
                    cloud_tex_name  = param;
                else
                    cloud_tex_name  = GetApplicationBundlePath() + "../Textures/" + folder_name + "/" + param;
            }
        }
        nom = "";
    } while( getline(fichier, ligne) );     //Tant qu'on n'est pas a la fin, on lit
    fichier.close();
    
    if (is_vessel) {
        std::cout << "Création du vaisseau " << disp_name << std::endl;
        this->createVessel(disp_name, model_filename);
    } else {
        std::cout << "Création de la planète " << disp_name << std::endl;
        this->createPlanet(disp_name, spice_name, ground_tex_name, cloud_tex_name);
    }
}

Planet* World::createPlanet(const std::string& disp_name, const std::string& spice_name, const std::string& ground_tex_name, const std::string& cloud_tex_name) {
    Planet* planet = new Planet(_root_node, disp_name, spice_name, ground_tex_name, cloud_tex_name);
    _planets.push_back(planet);
    return planet;
}

Vessel* World::createVessel(const std::string& name, const std::string& model_filename) {
    Vessel* vessel = new Vessel(_root_node, name, model_filename);
    _vessels.push_back(vessel);
    return vessel;
}

void World::setUpViewer() {
    _viewer.setUpViewInWindow( 150.0f, 150.0f, 1024.0f, 768.0f );
    _viewer.setSceneData( _root_node.get() );
    
    _camera = _viewer.getCamera();
//    _camera->setProjectionMatrixAsPerspective( 70.0f, 1024.0f/768.0f, 1.0f, 10000.0f );
//    _camera->setViewMatrixAsLookAt(vec3( 1000.0f, 0.0f, -1000.0f ), vec3( 0.0f, 0.0f, 0.0f ), vec3( 0.0f, 0.0f, -1.0f ) );
    
    _viewer.setCameraManipulator(new osgGA::TrackballManipulator);
    
    _viewer.realize();
}

osgViewer::Viewer& World::getViewer() {
    return _viewer;
}


void World::update(double dt) {
    std::vector<Planet*>::iterator itP;
    std::vector<Vessel*>::iterator itV;
    
    for (itP = _planets.begin(); itP != _planets.end(); itP++)
        (*itP)->update(dt);
    
    for (itV = _vessels.begin(); itV != _vessels.end(); itV++)
        (*itV)->update(dt);
    
    _clk.update(dt);
    
    _viewer.frame();
}





