#include <CEGUI/CEGUISystem.h>
#include <CEGUI/CEGUISchemeManager.h>
#include <OgreCEGUIRenderer.h>

#include "demoListener.h"

using namespace Ogre;

DemoListener::DemoListener(RenderWindow *win, Camera *cam, SceneManager *sceneMgr):
            DennisListener(win, cam, true, true)
{
   destination = direction = Vector3::ZERO;

   entity = NULL;
   entityNode = NULL;

   moveSpeed = 15.0;

   mSceneMgr = sceneMgr;
   mRaySceneQuery = mSceneMgr->createRayQuery(Ray());


   mMouse->setEventCallback(this);
   mKeyboard->setEventCallback(this);

   mLMouseDown = mRMouseDown = false;
   mContinue = true;

   transCam = Vector3::ZERO;

   entityCount = 0;
}


DemoListener::~DemoListener()
{
   //mSceneMgr->destroyQuery(mRaySceneQuery);
}

bool DemoListener::mouseMoved(const OIS::MouseEvent &arg)
{
   CEGUI::System::getSingleton().injectMouseMove(arg.state.X.rel, arg.state.Y.rel);
   return true;
}


bool DemoListener::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
   if(id == OIS::MB_Right)
   {
       onRightPressed(arg);
       mRMouseDown = true;
   }

   if(id == OIS::MB_Left)
   {
       onLeftPressed(arg);
       mLMouseDown = true;
   }

   return true;
}

bool DemoListener::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
   if(id == OIS::MB_Right)
      mRMouseDown = false;
   if(id == OIS::MB_Left)
      mLMouseDown = false;

   return true;
}

bool DemoListener::onRightPressed(const OIS::MouseEvent &arg)
{
    createNewEntity(arg, "ninja");
    entityNode->setScale(0.1f, 0.1f, 0.1f);
    entityNode->yaw(Radian(Math::DegreesToRadians(90)));
    return true;
}

bool DemoListener::onLeftPressed(const OIS::MouseEvent &arg)
{
   createNewEntity(arg, "robot");

   return true;
}

bool DemoListener::createNewEntity(const OIS::MouseEvent &arg, const String &entityName)
{
   CEGUI::Point mousePos = CEGUI::MouseCursor::getSingleton().getPosition();
   Ray mouseRay = mCamera->getCameraToViewportRay(mousePos.d_x/float(arg.state.width),
                                                 mousePos.d_y/float(arg.state.height));

   mRaySceneQuery->setRay(mouseRay);
   RaySceneQueryResult &result = mRaySceneQuery->execute();
   RaySceneQueryResult::iterator itr = result.begin( );

   if (itr != result.end() && itr->worldFragment)
   {
      char name[16];
      sprintf( name, "entityCount%d", entityCount++);
      entity = mSceneMgr->createEntity(name, entityName + ".mesh");
      entityNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(String(name) + "Node", itr->worldFragment->singleIntersection);
      entityNode->attachObject(entity);
      entityNode->setScale(0.5f, 0.5f, 0.5f);
   }
}


bool DemoListener::keyPressed(const OIS::KeyEvent &arg)
{
    const float speed = 0.15;

    switch (arg.key)
    {
        case OIS::KC_ESCAPE:
           mContinue = false;

        case OIS::KC_UP:
           transCam.x = speed;
           break;

        case OIS::KC_DOWN:
           transCam.x = -speed;
           break;

       case OIS::KC_RIGHT:
           transCam.z = speed;
           break;

       case OIS::KC_LEFT:
           transCam.z = -speed;
           break;

    }
}


bool DemoListener::keyReleased(const OIS::KeyEvent &arg)
{
     switch (arg.key)
    {
        case OIS::KC_ESCAPE:
           mContinue = false;

        case OIS::KC_UP:
           transCam.x = 0;
           break;

        case OIS::KC_DOWN:
           transCam.x = 0;
           break;

       case OIS::KC_RIGHT:
           transCam.z = 0;
           break;

       case OIS::KC_LEFT:
           transCam.z = 0;
           break;

    }

    return true;
}

bool DemoListener::frameStarted(const FrameEvent &evt)
{
    if(mMouse)
       mMouse->capture();
    if(mKeyboard)
       mKeyboard->capture();

    mCamera->move(transCam);

    return mContinue;
}
