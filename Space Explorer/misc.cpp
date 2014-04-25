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

std::string GetPathFromCFURLRef(CFURLRef urlRef) {
    char buffer[1024];
    std::string path;
    if(CFURLGetFileSystemRepresentation(urlRef, true, (UInt8*)buffer, 1024))
        path = std::string(buffer);
    return path;
}

std::string GetApplicationBundlePath() {
    // Get the main application bundle
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    
    std::string path;
    CFURLRef urlRef = CFBundleCopyBundleURL(mainBundle);
    if(urlRef)
    {
        path = GetPathFromCFURLRef(urlRef);
        CFRelease(urlRef); // docs say we are responsible for releasing CFURLRef
    }
    return path + "/";
    
}

std::string GetApplicationResourcesPath() {
    // Get the main application bundle
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    
    std::string path;
    CFURLRef urlRef = CFBundleCopyResourcesDirectoryURL(mainBundle);
    if(urlRef)
    {
        path = GetPathFromCFURLRef(urlRef);
        CFRelease(urlRef);
    }
    return path + "/";
}

vec3 cross(const vec3& u, const vec3& v) {
    vec3 res;
    
    res[0] = u[1]*v[2] - u[2]*v[1];
    res[1] = u[2]*v[0] - u[0]*v[2];
    res[2] = u[0]*v[1] - u[1]*v[0];
    
    return res;
}

vec3 multMV(const osg::Matrix3& m, const vec3& v) {
    vec3 res;
    
    res[0] = m(0,0)*v[0] + m(0,1)*v[1] + m(0,2)*v[2];
    res[1] = m(1,0)*v[0] + m(1,1)*v[1] + m(1,2)*v[2];
    res[2] = m(2,0)*v[0] + m(2,1)*v[1] + m(2,2)*v[2];
    
    return res;
}

osg::Matrix3 transpose(const osg::Matrix3& m) {
    osg::Matrix3 res;
    
    res(0,0) = m(0,0); res(0,1) = m(0,1); res(0,2) = m(0,2);
    res(1,0) = m(1,0); res(1,1) = m(1,1); res(1,2) = m(1,2);
    res(2,0) = m(2,0); res(2,1) = m(2,1); res(2,2) = m(2,2);
    
    return res;
}

void strip(std::string& str) {

    str.erase(str.begin());
    str.erase(str.end() - 1);
    
}

bool isURL(const std::string& str) {
    return str.substr(0,7) == "http://";
}


