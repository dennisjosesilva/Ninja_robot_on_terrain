#include "dennisApp.h"

using namespace std;


DennisApp::DennisApp():titleBar("Dennis title default"), showRenderConfig(true)
{
}

DennisApp::DennisApp(String myTitleBar):titleBar(myTitleBar),showRenderConfig(true)
{
}

DennisApp::DennisApp(bool showWindowConfigRender):titleBar("Dennis title default"),
                                           showRenderConfig(showWindowConfigRender)
{
}


DennisApp::DennisApp(String myTitleBar, bool showWindowConfigRender):titleBar(myTitleBar),
                                           showRenderConfig(showWindowConfigRender)
{
}

DennisApp::~DennisApp()
{
    if(mRoot)
       delete mRoot;
    if(mFrameListener)
        delete mFrameListener;
  /*  if(mWindow)
       delete mWindow;
    if(mCamera)
       delete mCamera;
    if(vp)
       delete vp;*/
}


void DennisApp::go()
{
   createRoot();
   defineResources();
   setupRenderSystem();
   createRenderWindow();
   chooseSceneManager();
   createCamera();
   initialiaseResourcesGroup();
   createScene();
   createFrameListener();
   mRoot->startRendering();
}

void DennisApp::createRoot()
{
    mRoot = new Root();
}

void DennisApp::defineResources()
{
    String seciName, typeName, archName;

    ConfigFile cf;
    cf.load("resources.cfg");

    ConfigFile::SectionIterator seci = cf.getSectionIterator();

    while(seci.hasMoreElements())
    {
        seciName = seci.peekNextKey();
        ConfigFile::SettingsMultiMap *settings = seci.getNext();
        ConfigFile::SettingsMultiMap::iterator i;

        for(i = settings->begin(); i != settings->end(); i++)
        {
            typeName = i->first;
            archName = i->second;
            ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, seciName);
        }
    }
}

void DennisApp::setupRenderSystem()
{
    if(showRenderConfig)
       mRoot->showConfigDialog();
    else
       if (!mRoot->restoreConfig() && !mRoot->showConfigDialog())
           throw Exception(52, "User canceled the config dialog!", "Application::setupRenderSystem()");
}

void DennisApp::initialiaseResourcesGroup()
{
   TextureManager::getSingleton().setDefaultNumMipmaps(5);
   ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void DennisApp::chooseSceneManager()
{
    mSceneMgr = mRoot->createSceneManager(ST_GENERIC, "DefaultSceneManager");
}

void DennisApp::createRenderWindow()
{
    mWindow = mRoot->initialise(true, titleBar);
}

void DennisApp::createCamera()
{
    mCamera = mSceneMgr->createCamera("DefaultCamera");
    Viewport *vp = mWindow->addViewport(mCamera);

    // Position it at 500 in Z direction
    mCamera->setPosition(Vector3(0,0,500));
   // Look back along -Z
    mCamera->lookAt(Vector3(0,0,-300));
    mCamera->setNearClipDistance(5);

    mCamera->setAspectRatio(
            Real(vp->getActualWidth()) / Real(vp->getActualHeight()));

}

void DennisApp::createScene()
{
  Entity *ent = mSceneMgr->createEntity("Robot", "robot.mesh");
  mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ent);
}



void DennisApp::createFrameListener()
{
    mFrameListener = new DennisListener(mWindow, mCamera, false, false);
    mRoot->addFrameListener(mFrameListener);
}

void DennisApp::startRenderLoop()
{
    mRoot->startRendering();
}
