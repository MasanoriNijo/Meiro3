#ifndef __gamebase__GameScene__
#define __gamebase__GameScene__

#include "cocos2d.h"
#include "ImovileAd.h"
class GameScene: public cocos2d::Layer {
protected:
	GameScene();
	virtual ~GameScene();
	bool init() override;

public:
	Vec2 ctPt;
	cocos2d::Size winSize;
	static cocos2d::Scene*  createScene();
	CREATE_FUNC(GameScene)
	;
CC_SYNTHESIZE_RETAIN(ImovileAd*,_ad,AD);//広告の表示操作する。
};

#endif // __HELLOWORLD_SCENE_H__
