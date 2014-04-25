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


//http://eoimages.gsfc.nasa.gov/ve/2432/cloud_combined_2048.jpg
//http://static.die.net/earth/mercator/1600.jpg
//http://www.parstimes.com/MODIS/cloud_combined.jpg

#include "planet.h"

Planet::Planet(osg::ref_ptr<osg::Group>& root, const std::string& disp_name, const std::string& spice_name, const std::string& ground_tex_name, const std::string& cloud_tex_name) {
    
    _nom = disp_name;
    _spice = Spice::Object(spice_name);
    
    // Importation des parametres physiques dans SPICE
    double Req, Rpo;
    _spice.getRadii(&Req, &Rpo);
    
    // OSG part
    osg::Uniform* lightPositionUniform;
    osg::Uniform* cloudPositionUniform;
    
    _osg_node = new osg::Geode();
    
    _osg_node->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(), 1.0f)));
	
	osg::StateSet *planetStateSet = _osg_node->getOrCreateStateSet();
	planetStateSet->ref();
	
	osg::Program *programObject = new osg::Program();
	osg::Shader *vertexObject = new osg::Shader(osg::Shader::VERTEX);
	osg::Shader *fragmentObject = new osg::Shader(osg::Shader::FRAGMENT);
	programObject->addShader(fragmentObject);
	programObject->addShader(vertexObject);
	
	vertexObject->loadShaderSourceFromFile(GetApplicationResourcesPath() + "planet.vert");
	fragmentObject->loadShaderSourceFromFile(GetApplicationResourcesPath() + "planet.frag");
	
	planetStateSet->setAttributeAndModes(programObject, osg::StateAttribute::ON);
	
	
	// TEXTURES
	
	// EARTH
    if (isURL(ground_tex_name))
        std::cout << "Téléchargement de " + ground_tex_name;
	osg::Image *image = osgDB::readImageFile(ground_tex_name);
	if (isURL(ground_tex_name))
        std::cout << "    Terminé" << std::endl;
    
    if (!image) {
		std::cout << "Couldn't load texture " << ground_tex_name << std::endl;
	}
	osg::Texture2D *texture = new osg::Texture2D;
	texture->setDataVariance(osg::Object::DYNAMIC);
	texture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR_MIPMAP_LINEAR);
	texture->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);
	texture->setWrap(osg::Texture::WRAP_S, osg::Texture::REPEAT);
	texture->setWrap(osg::Texture::WRAP_T, osg::Texture::CLAMP);
	texture->setImage(image);
	
	planetStateSet->setTextureAttributeAndModes(
                                                // use texture unit 0
                                                0, texture, osg::StateAttribute::ON
                                                );
	
	// use texture unit 0
	planetStateSet->addUniform(new osg::Uniform("planet_map", 0));
	
	
	// CLOUDS
	if (isURL(cloud_tex_name))
        std::cout << "Téléchargement de " + cloud_tex_name;
	osg::Image *image_clouds = osgDB::readImageFile(cloud_tex_name);
	if (isURL(cloud_tex_name))
        std::cout << "    Terminé" << std::endl;
	
    if (!image_clouds) {
		std::cout << "Couldn't load texture " << cloud_tex_name << std::endl;
	}
	osg::Texture2D *texture_clouds = new osg::Texture2D;
	texture_clouds->setDataVariance(osg::Object::DYNAMIC);
	texture_clouds->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR_MIPMAP_LINEAR);
	texture_clouds->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);
	texture_clouds->setWrap(osg::Texture::WRAP_S, osg::Texture::REPEAT);
	texture_clouds->setWrap(osg::Texture::WRAP_T, osg::Texture::CLAMP);
	texture_clouds->setImage(image_clouds);
	
	planetStateSet->setTextureAttributeAndModes(
                                                // use texture unit 1
                                                1, texture_clouds, osg::StateAttribute::ON
                                                );
	
	// use texture unit 0
	planetStateSet->addUniform(new osg::Uniform("planet_map_clouds", 1));
	
	// END TEXTURES
	
	
	lightPositionUniform = new osg::Uniform("light_position", osg::Vec4());
	planetStateSet->addUniform(lightPositionUniform);
	
	cloudPositionUniform = new osg::Uniform("cloud_position", osg::Vec2());
	planetStateSet->addUniform(cloudPositionUniform);
	
	lightPositionUniform->set(osg::Vec4(-1.0, 0.0, 0.0, 0.0));
	cloudPositionUniform->set(osg::Vec2(0.0, 0.0));
    
    root->addChild( _osg_node.get() );
    
    osg::notify( osg::ALWAYS ) << "Planète " << _nom << " crée" << std::endl;
    
}

Planet::~Planet() {
    
}

void Planet::update(double dt) {
    
}





