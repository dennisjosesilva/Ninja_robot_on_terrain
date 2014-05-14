#include<Ogre.h>
#include "dennisListener.h"
#include <OIS\OIS.h>
#include <OgreMath.h>
#include <CEGUI/CEGUISystem.h>
#include <CEGUI/CEGUISchemeManager.h>
#include <OgreCEGUIRenderer.h>

using namespace Ogre;

class DemoListener: public DennisListener, public OIS::MouseListener,
                    public OIS::KeyListener
{
public:

   DemoListener(RenderWindow *win, Camera *cam, SceneManager *sceneMgr);
   ~DemoListener();


   bool mouseMoved(const OIS::MouseEvent &arg);
   bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
   bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

   bool onLeftPressed(const OIS::MouseEvent &arg);
   bool onRightPressed(const OIS::MouseEvent &arg);

   bool keyPressed(const OIS::KeyEvent &arg);
   bool keyReleased(const OIS::KeyEvent &arg);

   bool frameStarted(const FrameEvent &evt);

private:
    bool createNewEntity(const OIS::MouseEvent &arg, const String &entityName);

protected:
    Entity *entity;
    Vector3 destination, direction;
    int entityCount;

    Real moveSpeed;
    SceneNode *entityNode;

    AnimationState *mRobotAnimation;
    RaySceneQuery *mRaySceneQuery;
    SceneManager *mSceneMgr;

    Vector3 transCam;

    bool mRMouseDown, mLMouseDown;
    bool mContinue;
};
