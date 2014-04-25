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


#ifndef Space_Explorer_misc_h
#define Space_Explorer_misc_h

#include <CoreFoundation/CoreFoundation.h>

#include <osgDB/ReadFile>
#include <osg/PositionAttitudeTransform>
#include <osg/MatrixTransform>
#include <osgDB/FileUtils>

#include "util.h"

#include <eigen3/Eigen/Eigen>

#define OSGNOTIFYLEVEL DEBUG

std::string GetPathFromCFURLRef(CFURLRef urlRef);

std::string GetApplicationBundlePath();

std::string GetApplicationResourcesPath();

vec3 cross(const vec3& u, const vec3& v);
vec3 multMV(const osg::Matrix3&, const vec3&);
osg::Matrix3 transpose(const osg::Matrix3&);

void strip(std::string&);
bool isURL(const std::string&);


#endif
