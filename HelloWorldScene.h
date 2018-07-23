#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ImovileAd.h"
#include "SelectScene.h"
#include "TitleScene.h"
USING_NS_CC;
class HelloWorld: public cocos2d::Layer {

protected:
	HelloWorld();
	virtual ~HelloWorld();

public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	void onEnterTransitionDidFinish() override;
	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld)

	void ChangePage(int i);

	int pageInt = 1;
	Size winSize;
	Vec2 ctPt;CC_SYNTHESIZE_RETAIN(Node*,_baseNode,BaseNode)
	; //スクロール用ノードすべてをこれに張り付け
CC_SYNTHESIZE_RETAIN(cocos2d::MenuItemImage*,_startp,Startp)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Menu*,_startM,StartM)
	;CC_SYNTHESIZE_RETAIN(cocos2d::MenuItemImage*,_backp,Backp)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Menu*,_backM,BackM)
	;

	;CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*,_debugWaku,DebugWaku)
	;CC_SYNTHESIZE_RETAIN(Sprite*,_back0,Back0)
	;CC_SYNTHESIZE_RETAIN(Sprite*,_back1,Back1)
	;CC_SYNTHESIZE_RETAIN(Sprite*,_how1,How1)
//	;CC_SYNTHESIZE_RETAIN(Sprite*,_how2,How2)
//	;CC_SYNTHESIZE_RETAIN(Sprite*,_how3,How3)
//	;CC_SYNTHESIZE_RETAIN(Sprite*,_how4,How4)
	;CC_SYNTHESIZE_RETAIN(MenuItemImage*, _rightYazi,RightYazi)
	;CC_SYNTHESIZE_RETAIN(MenuItemImage*, _leftYazi,LeftYazi)
	;CC_SYNTHESIZE_RETAIN(Menu*, _menuL,MenuL)
	;CC_SYNTHESIZE_RETAIN(Menu*, _menuR,MenuR)
	;CC_SYNTHESIZE_RETAIN(MenuItemImage*,_howToP,HowToP)
	;CC_SYNTHESIZE_RETAIN(Menu*,_menu,Menu)
	;CC_SYNTHESIZE_RETAIN(Menu*,_menu2,Menu2)
	;CC_SYNTHESIZE_RETAIN(Menu*,_menu3,Menu3)
	;CC_SYNTHESIZE_RETAIN(ImovileAd*,_ad,AD)
	;

};

#endif // __HELLOWORLD_SCENE_H__
