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


#include "planet.h"

Planet::Planet(osg::ref_ptr<osg::Group>& root, const std::string& nom, const std::string& nom_spice) : _nom(nom), _spice(Spice::Object(nom_spice)) {
    
    _osg_node = new osg::MatrixTransform();
    
    osg::Geode* geode = new osg::Geode();
    
    geode->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(0.,0.,0.), 1000.)));

    
//    //Getting the state set of the geode
//	osg::ref_ptr<osg::StateSet> nodess( geode->getOrCreateStateSet() );
//    
//    //loading texture image object
//    osg::ref_ptr<osg::Image> image( osgDB::readImageFile("earth.png") );
//    
//    //Bind the image to a 2D texture object
//	osg::ref_ptr<osg::Texture2D> tex( new osg::Texture2D );
//	tex->setImage( image.get() );
//    
//    //Applying texture on the object
//	//nodess->setMode(GL_CULL_FACE,osg::StateAttribute::OFF);
//	nodess->setTextureAttributeAndModes(0, tex.get(), osg::StateAttribute::ON);
    
    _osg_node->addChild( geode );
    root->addChild( _osg_node.get() );
    root->addChild( geode );
    
    osg::notify( osg::ALWAYS ) << _nom << " crée" << std::endl;
    
}

Planet::~Planet() {
    
}

void Planet::update(double dt) {
    
}





