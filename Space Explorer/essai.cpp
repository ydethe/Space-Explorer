/* -*-c++-*- */
/* osgEarth - Dynamic map generation toolkit for OpenSceneGraph
 * Copyright 2008-2010 Pelican Mapping
 * http://osgearth.org
 *
 * osgEarth is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 */
#include <osgEarth/Notify>

#include <osgUtil/Optimizer>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

#include <osg/Material>
#include <osg/Geode>
#include <osg/BlendFunc>
#include <osg/Depth>
#include <osg/Projection>
#include <osg/AutoTransform>
#include <osg/Geometry>
#include <osg/Image>
#include <osg/CullFace>

#include <osgTerrain/TerrainTile>
#include <osgTerrain/GeometryTechnique>

#include <osgDB/WriteFile>

#include <osgText/Text>

#include <osg/Shape>
#include <osg/ShapeDrawable>
#include <osg/Geode>

#include <iostream>

using namespace osg;
using namespace osgDB;
using namespace osgTerrain;

osg::Image* makeRGBA(osg::Image* image) {
    osg::Image* result = new osg::Image;
    result->allocateImage(image->s(), image->t(), image->r(), GL_RGBA, GL_UNSIGNED_BYTE);
    
    if (image->getPixelFormat() == GL_LUMINANCE)
    {
        for (int r = 0; r < image->t(); ++r)
        {
            for (int c = 0; c < image->s(); ++c)
            {
                unsigned char val = *image->data(c, r);
                result->data(c,r)[0] = val;
                result->data(c,r)[1] = val;
                result->data(c,r)[2] = val;
                result->data(c,r)[3] = val;
            }
        }
    }
    
    return result;
}

osg::Node* createClouds(double maxRange)
{
    //Try to read from the WorldWind server
    osg::ref_ptr<osg::Image> image = osgDB::readImageFile("http://eoimages.gsfc.nasa.gov/ve/2432/cloud_combined_2048.jpg");
    if (image.valid())
    {
        OE_NOTICE << "Read clouds from server" << std::endl;
    }
    else
    {
        //Just try to load clouds.jpg from the data directory.
        //Note: You must append the osgearth\data folder to your OSG_FILE_PATH
        //or just copy the clouds.jpg where current osg data is.
        image = osgDB::readImageFile("clouds.jpg");
    }
    
    if (!image.valid())
    {
        OE_NOTICE << "Could not read clouds image " << std::endl;
        return NULL;
    }
    
    //Convert the black and white data to RGBA
    image = makeRGBA(image.get());
    
    // Declare a TexEnv instance, set the mode to 'BLEND'
    osg::TexEnv* blendTexEnv = new osg::TexEnv;
    blendTexEnv->setMode(osg::TexEnv::BLEND);
    
    
}

int main(int argc, char** argv) {
    osg::ArgumentParser arguments(&argc,argv);
    
    // construct the viewer.
    osgViewer::Viewer viewer(arguments);
    
    osg::Group* group = new osg::Group;
    
//    osg::ref_ptr<osg::Node> loadedModel = osgDB::readNodeFiles(arguments);
    osg::ref_ptr<osg::ShapeDrawable> sd = new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(0.0,0.0,0.0), osg::WGS_84_RADIUS_EQUATOR));
    
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable( sd.get() );
    
    if (geode.valid())
    {
        group->addChild(geode.get());
    }
    
    group->addChild(createClouds(osg::WGS_84_RADIUS_EQUATOR * 2.0));
    
    // set the scene to render
    viewer.setSceneData(group);
    
    // run the viewers frame loop
    return viewer.run();
}

