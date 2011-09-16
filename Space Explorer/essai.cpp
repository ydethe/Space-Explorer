#include <osg/Shape>
#include <osg/ShapeDrawable>
#include <osg/Geode>
#include <osgViewer/Viewer>
#include <osgUtil/Optimizer>
#include <iostream>
#include <osgwTools/Shapes.h>

int main0(int argc, char *argv[]) {
    std::cout << "Creation root..." << std::endl;
    osg::ref_ptr<osg::Group> root = new osg::Group();
    if (!root.valid())
        std::cerr << "root invalide" << std::endl;
    
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable( osgwTools::makeGeodesicSphere() );

    std::cout << "geode dans root..." << std::endl;
    root->addChild( geode.get() );
    
    osgUtil::Optimizer optimizer;
    std::cout << "Optimisation root..." << std::endl;
    optimizer.optimize(root.get());
    
    std::cout << "Creation viewer..." << std::endl;
    osgViewer::Viewer viewer;
    std::cout << "root dans viewer..." << std::endl;
    viewer.setSceneData( root.get() );
    
    std::cout << "realisation viewer..." << std::endl;
    viewer.realize();

    int i=0;
    while (!viewer.done())
        i += 1;
        std::cout << "viewer frame #" << i << std::endl;
        viewer.frame();
    
    return 0;
}

