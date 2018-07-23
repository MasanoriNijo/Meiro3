#ifndef __neomeiro__SelTag__
#define __neomeiro__SelTag__

#include "cocos2d.h"
#include "MeiroMeder.h"
#include "MainScene.h"
USING_NS_CC;

class SelTag: public cocos2d::Sprite {
protected:
	SelTag();
	virtual ~SelTag();
	bool init() override;

private:
public:

	Size wakuSize;
	Vec2 ctPt;

	int Level_ = 1; //現在選択のレベル

	void SetLevel(int i);

	bool Lock_; //ステージが解放されているかどうか

	void SetLock(bool lok_); //ロックするしない。

	void SetMemoText(std::string txt_);
	void SetLockText(std::string txt_);
	bool SelectTag(Vec2 pt_); //タッチしているかチェック

	Vec2 _point1;
	Vec2 _point2;
	bool touchFlg_; //タッチしたかどうか？
	void TouchOn(Vec2 pt);
	void Swaip(Vec2 pt1, Vec2 pt2);
	void TouchOff();


	enum class SelState {
		LOCK,UNLOCK
	};
	;CC_SYNTHESIZE(SelState,_selState,SelState)
	;


	cocos2d::Size frameSize;
	void update(float dt) override;

	CREATE_FUNC(SelTag)
	;CC_SYNTHESIZE_RETAIN(Sprite*, _lvlLabel,LvlLabel)
	;CC_SYNTHESIZE_RETAIN(Sprite*, _kagi,Kagi)
	;CC_SYNTHESIZE_RETAIN(Sprite*, _selWaku,SelWaku)//セレクト時の色のついた枠
	;CC_SYNTHESIZE_RETAIN(cocos2d::Label*,_selMemo,SelMemo)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Label*,_lokMemo,LokMemo)
	;CC_SYNTHESIZE_RETAIN(MenuItemImage*, _selBtn,SelBtn)
	;CC_SYNTHESIZE_RETAIN(Menu*, _menu,Menu)
	;CC_SYNTHESIZE_RETAIN(MeiroMeder*, _mMeder,MMeder)

};
#endif // __HELLOWORLD_SCENE_H__
