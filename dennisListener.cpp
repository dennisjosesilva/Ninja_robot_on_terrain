#include "dennisListener.h"



void DennisListener::windowResized(RenderWindow* rw)
{
   unsigned int width, height, depth;
   int left, top;
   rw->getMetrics(width, height, depth, left, top);

   const OIS::MouseState &ms = mMouse->getMouseState();
   ms.width = width;
   ms.height = height;
}

DennisListener::DennisListener(RenderWindow *win, Camera *cam, bool bufferedMouse, bool bufferedKey)
:mWindow(win), mCamera(cam),mBufferedMouse(bufferedMouse), mBufferedKey(bufferedKey)
{
    initializeInputSystem();

    transVector = Vector3::ZERO;
    mRotateSpeed = 0.15;
    mMoveSpeed = 150;

    windowResized(mWindow);

}



DennisListener::~DennisListener()
{
    mInputManager->destroyInputObject(mKeyboard);
    mInputManager->destroyInputObject(mMouse);
    OIS::InputManager::destroyInputSystem(mInputManager);
}

void DennisListener::initializeInputSystem()
{
   size_t windowHnd = 0;
   std::ostringstream windowHndStr;
   OIS::ParamList pl;

   mWindow->getCustomAttribute("WINDOW", &windowHnd);
   windowHndStr << windowHnd;
   pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
   mInputManager = OIS::InputManager::createInputSystem(pl);

   try
   {
        mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, mBufferedKey));
        mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject(OIS::OISMouse, mBufferedMouse));
   }
   catch (const OIS::Exception &e)
   {
       throw Exception(42, e.eText, "Application::setupInputSystem");
   }
}

void DennisListener::moveCamera()
{

    if(mKeyboard->isKeyDown(OIS::KC_RIGHT) || mKeyboard->isKeyDown(OIS::KC_D))
       transVector.x = mMoveSpeed;

    if(mKeyboard->isKeyDown(OIS::KC_LEFT) || mKeyboard->isKeyDown(OIS::KC_A))
       transVector.x = -mMoveSpeed;

    if(mKeyboard->isKeyDown(OIS::KC_UP) || mKeyboard->isKeyDown(OIS::KC_W))
       transVector.z = -mMoveSpeed;

    if(mKeyboard->isKeyDown(OIS::KC_DOWN) || mKeyboard->isKeyDown(OIS::KC_S))
       transVector.z = mMoveSpeed;

}

void DennisListener::rotateCamera()
{
    mCamera->yaw(Degree(mMouse->getMouseState().X.rel * -mRotateSpeed));
    mCamera->pitch(Degree(mMouse->getMouseState().Y.rel * -mRotateSpeed));

}


bool DennisListener::frameStarted(const FrameEvent &evt)
{

    if(mKeyboard)
       mKeyboard->capture();
    if(mMouse)
       mMouse->capture();

    rotateCamera();
    moveCamera();
    mCamera->moveRelative(transVector * evt.timeSinceLastFrame);
    transVector = Vector3::ZERO;

    if(mKeyboard->isKeyDown(OIS::KC_ESCAPE))
       return false;

    return true;
}
