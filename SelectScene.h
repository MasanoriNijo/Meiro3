#ifndef __neomeiro__SelectScene__
#define __neomeiro__SelectScene__

#include "cocos2d.h"
#include "ParticleSystemPool.h"
#include "MeiroMeder.h"
#include "SelTag.h"
#include "PrmScene.h"
#include "ImovileAd.h"

USING_NS_CC;
class SelectScene: public cocos2d::Layer {
protected:
	SelectScene();
	virtual ~SelectScene();
	bool init() override;
private:

	cocos2d::Size winSize;
	Vec2 ctPt;

public:
	int w = 46;
	int d = 1; //���H�摜�̗]��
	std::vector<int> mIndexs;
	cocos2d::Vec2 _point1;
	cocos2d::Vec2 _point2;
	cocos2d::Vec2 _point2_before;
	static cocos2d::Scene* createScene();

	void SetTouchListener(); //タッチイベントをセットする。

	;CC_SYNTHESIZE_RETAIN(cocos2d::Touch*,_fstTch,FstTch)
	; //wタッチを禁止
	int moveLeftX = 80;
	int moveRightX = -680; //-1100
	int moveTopY = 3000;
	int moveDownY =0; //-1100

	float moveVelo = 0;
	int beforePt = 0;
	bool tch_ = false;
	bool fstSet_=false;//タッチ後最初にセットする。
	int Y;

	;CC_SYNTHESIZE(cocos2d::Vector<SelTag*>,_selTags,SelTags)
	void update(float dt);CREATE_FUNC(SelectScene)
	;CC_SYNTHESIZE_RETAIN(MeiroMeder*, _mMeder, MMeder)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*,_backGround,BackGround)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*,_backGround2,BackGround2)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*,_selectStage,SelectStage)
	;CC_SYNTHESIZE_RETAIN(Sprite2*,_baseNode,BaseNode)
	; //スクロール用ノードすべてをこれに張り付け

	;CC_SYNTHESIZE_RETAIN(cocos2d::Label*,_stageLabel,StageLabel)
	;CC_SYNTHESIZE(int,_level,Level)
	;CC_SYNTHESIZE_RETAIN(cocos2d::ParallaxNode *, _nomove1,noMove1)
	;CC_SYNTHESIZE_RETAIN(cocos2d::ParallaxNode *, _nomove2,noMove2)
	;CC_SYNTHESIZE_RETAIN(cocos2d::ParallaxNode *, _nomove3,noMove3);
	void setUpdateAction(std::function<void(SelectScene*, float dt)> action);
	void onEnterTransitionDidFinish() override;
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event);
	std::function<void(SelectScene*, float)> onUpDateListener;
	std::function<void(SelectScene*)> onsecUpDateListener;CC_SYNTHESIZE_RETAIN(EventListenerTouchOneByOne*, _touchListener,TouchListenner)

	;CC_SYNTHESIZE_RETAIN(SelTag*,_sel1,Sel1)
	;CC_SYNTHESIZE_RETAIN(SelTag*,_sel2,Sel2)
	;CC_SYNTHESIZE_RETAIN(SelTag*,_sel3,Sel3)
	;CC_SYNTHESIZE_RETAIN(SelTag*,_sel4,Sel4)
	;CC_SYNTHESIZE_RETAIN(SelTag*,_sel5,Sel5)
	;CC_SYNTHESIZE_RETAIN(SelTag*,_sel6,Sel6)
	;CC_SYNTHESIZE_RETAIN(SelTag*,_sel7,Sel7)

	;CC_SYNTHESIZE_RETAIN(Sprite*,_selYaziTop,SelYaziTop)
	;CC_SYNTHESIZE_RETAIN(Sprite*,_selYaziDown,SelYaziDown)
	;CC_SYNTHESIZE_RETAIN(Sprite*,_stg,Stg)
	;CC_SYNTHESIZE_RETAIN(ImovileAd*,_ad,AD)
	;

	//debug用
CC_SYNTHESIZE_RETAIN(cocos2d::MenuItemImage*,_prmBtn,PrmBtn)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Menu*,_menuPrm,MenuPrm)
	;

};

#endif // __HELLOWORLD_SCENE_H__
