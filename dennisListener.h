#include<Ogre.h>
#include<iostream>
#include<OIS/OIS.h>

using namespace Ogre;


#ifndef DENNISLISTENER_H_INCLUDED
#define DENNISLISTENER_H_INCLUDED

class DennisListener:public FrameListener
{
public:
   DennisListener(RenderWindow *win, Camera *cam, bool bufferedMouse, bool bufferedKey);

   ~DennisListener();

   virtual void moveCamera();
   virtual void rotateCamera();
   virtual void windowResized(RenderWindow* rw);

   virtual bool frameStarted(const FrameEvent &evt);

protected:
   RenderWindow *mWindow;
   Camera *mCamera;

   bool mBufferedMouse, mBufferedKey;
   OIS::Keyboard *mKeyboard;
   OIS::Mouse *mMouse;
   OIS::InputManager *mInputManager;

   void initializeInputSystem();

   Vector3 transVector;
   Real mRotateSpeed, mMoveSpeed;


};


#endif // DENNISLISTENER_H_INCLUDED
