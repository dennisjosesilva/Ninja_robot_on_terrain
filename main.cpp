#include <Ogre.h>

#include "dennisApp.h"
#include "demoListener.h"

#include <CEGUI/CEGUISystem.h>
#include <CEGUI/CEGUISchemeManager.h>
#include <OgreCEGUIRenderer.h>

//#include <ExampleApplication.h>

using namespace Ogre;


class SampleApp : public DennisApp
{
public:
    // Basic constructor
    SampleApp()
    {}

    ~SampleApp()
    {

    }

protected:
    CEGUI::OgreCEGUIRenderer *mRenderer;
    CEGUI::System *mSystem;

    void chooseSceneManager()
    {
        mSceneMgr = mRoot->createSceneManager(ST_EXTERIOR_CLOSE,"TerrainSceneManager");
    }

    void createScene(void)
    {
       mRenderer = new CEGUI::OgreCEGUIRenderer(mWindow, Ogre::RENDER_QUEUE_OVERLAY, false, 3000, mSceneMgr);
       mSystem = new CEGUI::System(mRenderer);

       CEGUI::SchemeManager::getSingleton().loadScheme((CEGUI::utf8*)"TaharezLookSkin.scheme");
       CEGUI::MouseCursor::getSingleton().setImage("TaharezLook", "MouseArrow");

       mSceneMgr->setWorldGeometry("terrain.cfg");

       mCamera->setPosition(500,250,900);
       mCamera->pitch(Degree(-45));
       mCamera->yaw(Degree(-45));
    }

    void createFrameListener()
    {
       mFrameListener = new DemoListener(mWindow, mCamera, mSceneMgr);
       mRoot->addFrameListener(mFrameListener);
    }
};

// ----------------------------------------------------------------------------
// Main function, just boots the application object
// ----------------------------------------------------------------------------
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
int main(int argc, char **argv)
#endif
{
    // Create application object
    SampleApp app;

    try
    {
        app.go();
    }
    catch( Exception& e )
    {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
        MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else

        std::cerr << "An exception has occured: " << e.getFullDescription();
#endif
    }

    return 0;
}
