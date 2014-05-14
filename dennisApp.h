#include<Ogre.h>

#include "dennisListener.h"
#include<iostream>

using namespace Ogre;

#ifndef DENNISAPP_H_INCLUDED
#define DENNISAPP_H_INCLUDED

class DennisApp
{
public:
    DennisApp();

    DennisApp(String myTitleBar);

    DennisApp(bool showWindowConfigRender);

    DennisApp(String myTitleBar, bool showWindowConfigRender);

    ~DennisApp();

    void go();


protected:
  Root *mRoot;
  SceneManager *mSceneMgr;
  RenderWindow *mWindow;
  Camera *mCamera;
  DennisListener *mFrameListener;

  bool showRenderConfig;
  std::string titleBar;

  //funções de inicialização usadas no metodo go().
  virtual void createRoot();
  virtual void defineResources();
  virtual void setupRenderSystem();
  virtual void initialiaseResourcesGroup();
  virtual void createRenderWindow();
  virtual void chooseSceneManager();
  virtual void createCamera();
  virtual void createScene();
  virtual void createFrameListener();
  virtual void startRenderLoop();
};

#endif // DENNISAPP_H_INCLUDED
