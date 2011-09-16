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


#ifndef Space_Explorer_planet_h
#define Space_Explorer_planet_h

#include <string>
#include <osg/Shape>
#include <osg/ShapeDrawable>
#include <osg/Geode>
//#include <osg/Texture2D>
//
#include "misc.h"
#include "spice.h"

class Planet {
private:
    std::string _nom;
    Spice::Object _spice;
    osg::ref_ptr<osg::MatrixTransform> _osg_node;
    
public:
    Planet(osg::ref_ptr<osg::Group>& root, const std::string& nom, const std::string& nom_spice);
    ~Planet();
    
    void update(double dt);
    
};

#endif
