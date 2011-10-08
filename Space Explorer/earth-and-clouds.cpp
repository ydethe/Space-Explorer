#include <osg/ShapeDrawable>
#include <osg/Geometry>
#include <osg/StateSet>
#include <osg/Texture2D>
#include <osgDB/ReadFile> 
#include <osgViewer/Viewer>
#include <osgGA/TrackballManipulator>
#include <iostream>

osg::Uniform *lightPositionUniform;
osg::Uniform *cloudPositionUniform;

static const float LIGHT_SPEED = -0.1;

osg::Node *createEarth() {
	osg::Geode *sphere = new osg::Geode();
	sphere->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(), 1)));
	
	osg::StateSet *sphereStateSet = sphere->getOrCreateStateSet();
	sphereStateSet->ref();
	
	osg::Program *programObject = new osg::Program();
	osg::Shader *vertexObject = new osg::Shader(osg::Shader::VERTEX);
	osg::Shader *fragmentObject = new osg::Shader(osg::Shader::FRAGMENT);
	programObject->addShader(fragmentObject);
	programObject->addShader(vertexObject);
	
	vertexObject->loadShaderSourceFromFile("earth.vert");
	fragmentObject->loadShaderSourceFromFile("earth.frag");
	
	sphereStateSet->setAttributeAndModes(programObject, osg::StateAttribute::ON);
	
	
	// TEXTURES
	
	// EARTH
	osg::Image *image = osgDB::readImageFile("EarthMap_2500x1250.jpg");
	if (!image) {
		std::cout << "Couldn't load texture " << "EarthMap_2500x1250.jpg" << std::endl;
		return NULL;
	}
	osg::Texture2D *texture = new osg::Texture2D;
	texture->setDataVariance(osg::Object::DYNAMIC);
	texture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR_MIPMAP_LINEAR);
	texture->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);
	texture->setWrap(osg::Texture::WRAP_S, osg::Texture::REPEAT);
	texture->setWrap(osg::Texture::WRAP_T, osg::Texture::CLAMP);
	texture->setImage(image);
	
	sphereStateSet->setTextureAttributeAndModes(
		// use texture unit 0
		0, texture, osg::StateAttribute::ON
	);
	
	// use texture unit 0
	sphereStateSet->addUniform(new osg::Uniform("earth_map", 0));
	
	
	// CLOUDS
	osg::Image *image_clouds = osgDB::readImageFile("EarthClouds_2500x1250.jpg");
	if (!image_clouds) {
		std::cout << "Couldn't load texture " << "EarthMap_2500x1250.jpg" << std::endl;
		return NULL;
	}
	osg::Texture2D *texture_clouds = new osg::Texture2D;
	texture_clouds->setDataVariance(osg::Object::DYNAMIC);
	texture_clouds->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR_MIPMAP_LINEAR);
	texture_clouds->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);
	texture_clouds->setWrap(osg::Texture::WRAP_S, osg::Texture::REPEAT);
	texture_clouds->setWrap(osg::Texture::WRAP_T, osg::Texture::CLAMP);
	texture_clouds->setImage(image_clouds);
	
	sphereStateSet->setTextureAttributeAndModes(
		// use texture unit 1
		1, texture_clouds, osg::StateAttribute::ON
	);
	
	// use texture unit 0
	sphereStateSet->addUniform(new osg::Uniform("earth_map_clouds", 1));
	
	// END TEXTURES
	
	
	lightPositionUniform = new osg::Uniform("light_position", osg::Vec4());
	sphereStateSet->addUniform(lightPositionUniform);
	
	cloudPositionUniform = new osg::Uniform("cloud_position", osg::Vec2());
	sphereStateSet->addUniform(cloudPositionUniform);
	
	return sphere;
}

osg::Node *startup() {
	osg::Group *scene = new osg::Group();
	
	scene->addChild(createEarth());
	return scene;
}

void update(double time) {
	lightPositionUniform->set(osg::Vec4(cos(time * LIGHT_SPEED), sin(time * LIGHT_SPEED), 0.0, 0.0));
	cloudPositionUniform->set(osg::Vec2(time/500.0, 0.0));
}

int main_tmp() {
	osg::Node *scene = startup();
	if (!scene) return 1;
	osgViewer::Viewer viewer;
	viewer.setSceneData(scene);
	viewer.setCameraManipulator(new osgGA::TrackballManipulator());
	viewer.realize();
	
	while (!viewer.done()) {
		viewer.frame();
		update(viewer.elapsedTime());
	}
}
