//! [starter]

#include <exception>
#include <iostream>

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "OgreCameraMan.h"

using namespace Ogre;
using namespace OgreBites;

class GameMap
	: public ApplicationContext
		, public InputListener {
public:
	GameMap();

	~GameMap() override;

	void setup() override;

	bool keyPressed(const KeyboardEvent &evt) override;

	bool mouseMoved (const MouseMotionEvent &evt) override;

	bool mousePressed (const MouseButtonEvent &evt) override;

	bool mouseReleased (const MouseButtonEvent &evt) override;

private:
	SceneNode *camNode;
	bool movingMouse = false;
};


GameMap::GameMap()
	: ApplicationContext("GameMap") {
}


GameMap::~GameMap()
= default;


void GameMap::setup() {
	// do not forget to call the base first
	ApplicationContext::setup();
	addInputListener(this);

	// get a pointer to the already created root
	Root *root = getRoot();
	SceneManager *scnMgr = root->createSceneManager();

	// register our scene with the RTSS
	RTShader::ShaderGenerator *shadergen = RTShader::ShaderGenerator::getSingletonPtr();
	shadergen->addSceneManager(scnMgr);

	// -- tutorial section start --
	//! [cameracreate]
	camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	Camera *cam = scnMgr->createCamera("myCam");
	//! [cameracreate]

	//! [cameraposition]
	camNode->setPosition(0, 400, 0);
	camNode->lookAt(Vector3(0, 0, 0), Node::TransformSpace::TS_WORLD);
	//! [cameraposition]

	//! [cameralaststep]
	cam->setOrthoWindow(500, 500);
	cam->setNearClipDistance(5);
	camNode->attachObject(cam);
	//! [cameralaststep]

	//! [addviewport]
	Viewport *vp = getRenderWindow()->addViewport(cam);
	//! [addviewport]

	//! [viewportback]
	vp->setBackgroundColour(ColourValue(0, 0, 0));
	//! [viewportback]

	//! [cameraratio]
	//cam->setAspectRatio(Real(vp->getActualWidth()) / Real(vp->getActualHeight()));
	//! [cameraratio]

	//! [lightingsset]
	scnMgr->setAmbientLight(ColourValue(0, 0, 0));
	scnMgr->setShadowTechnique(ShadowTechnique::SHADOWTYPE_STENCIL_ADDITIVE);
	//! [lightingsset]

	//! [plane]
	Plane plane(Vector3::UNIT_Y, 0);
	//! [plane]

	//! [planedefine]
	MeshManager::getSingleton().createPlane(
		"ground", RGN_DEFAULT,
		plane,
		1500, 1500, 20, 20,
		true,
		1, 5, 5,
		Vector3::UNIT_Z);
	//! [planedefine]

	//! [planecreate]
	Entity *groundEntity = scnMgr->createEntity("ground");
	scnMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
	//! [planecreate]

	//! [planenoshadow]
	groundEntity->setCastShadows(false);
	//! [planenoshadow]

	//! [planesetmat]
	groundEntity->setMaterialName("Examples/Rockwall");
	//! [planesetmat]

	//! [directlight]
	Light *directionalLight = scnMgr->createLight("DirectionalLight");
	directionalLight->setType(Light::LT_DIRECTIONAL);
	//! [directlight]

	//! [directlightcolor]
	directionalLight->setDiffuseColour(ColourValue(0, 0, 0));
	directionalLight->setSpecularColour(ColourValue(0, 0, 0));
	//! [directlightcolor]

	//! [directlightdir]
	SceneNode *directionalLightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	directionalLightNode->attachObject(directionalLight);
	directionalLightNode->setDirection(Vector3(0, -1, 1));
	//! [directlightdir]

	//! [pointlight]
	Light *pointLight = scnMgr->createLight("PointLight");
	pointLight->setType(Light::LT_POINT);
	//! [pointlight]

	//! [pointlightcolor]
	pointLight->setDiffuseColour(0.3, 0.3, 0.3);
	pointLight->setSpecularColour(0.3, 0.3, 0.3);
	//! [pointlightcolor]

	//! [pointlightpos]
	SceneNode *pointLightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	pointLightNode->attachObject(pointLight);
	pointLightNode->setPosition(Vector3(0, 150, 250));
	//! [pointlightpos]
	// -- tutorial section end --
}


bool GameMap::keyPressed(const KeyboardEvent& evt) {
	if (evt.keysym.sym == SDLK_ESCAPE) {

	}

	return true;
}

bool GameMap::mouseMoved(const MouseMotionEvent &evt) {
	if(movingMouse) {
		auto movement = Vector3(-evt.xrel, 0, -evt.yrel);
		camNode->setPosition(camNode->getPosition() + movement);
	}

	return InputListener::mouseMoved(evt);
}

bool GameMap::mousePressed(const MouseButtonEvent &evt) {
	movingMouse = true;
	return InputListener::mousePressed(evt);
}

bool GameMap::mouseReleased(const MouseButtonEvent &evt) {
	movingMouse = false;
	return InputListener::mouseReleased(evt);
}

int main() {
	try {
		GameMap app;
		app.initApp();
		app.getRoot()->startRendering();
		app.closeApp();
	}
	catch (const std::exception &e) {
		std::cerr << "Error occurred during execution: " << e.what() << '\n';
		return 1;
	}

	return 0;
}

//! [starter]
