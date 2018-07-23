#ifndef __neomeiro__TitleScene__
#define __neomeiro__TitleScene__

#include "cocos2d.h"
#include "Cource.h"
#include "ImovileAd.h"


class TitleScene: public cocos2d::Layer {
protected:
	TitleScene();
	virtual ~TitleScene();
	bool init() override;

public:

	cocos2d::Size winSize;
	Vec2 ctPt;

	static cocos2d::Scene* createScene();CREATE_FUNC(TitleScene)
	;
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode,
			cocos2d::Event * event);
	void onEnterTransitionDidFinish() override;

	void openRankPark();
	void sendRankParkScore(int value);
	void tweet();

	CC_SYNTHESIZE_RETAIN(cocos2d::MenuItemImage*,_musicOnBtn,MusicOnBtn);
	CC_SYNTHESIZE_RETAIN(cocos2d::MenuItemImage*,_musicOffBtn,MusicOffBtn);
//	CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*,_title1,Title1);
	CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*,_title2,Title2);
//	CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*,_title3,Title3);
	CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*,_background,BackGround);
	CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*,_background2,BackGround2);
	CC_SYNTHESIZE_RETAIN(Node*,_baseNode,BaseNode);//スクロール用ノードすべてをこれに張り付け


	CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*,_ball,Ball);
	CC_SYNTHESIZE_RETAIN(cocos2d::MenuItemImage*,_tweetp,Tweetp);
	CC_SYNTHESIZE_RETAIN(cocos2d::MenuItemImage*,_startp,Startp);
	CC_SYNTHESIZE_RETAIN(cocos2d::MenuItemImage*,_rankingp,Rankingp);
	CC_SYNTHESIZE_RETAIN(cocos2d::MenuItemImage*,_howTop,HowTop);
	CC_SYNTHESIZE_RETAIN(cocos2d::MenuItemImage*,_yubip,Yubip);
	CC_SYNTHESIZE_RETAIN(cocos2d::MenuItemImage*,_sumahop,Sumahop);
	CC_SYNTHESIZE_RETAIN(cocos2d::Menu*,_menu1,Menu1);
	CC_SYNTHESIZE_RETAIN(cocos2d::Menu*,_menu2,Menu2);
	CC_SYNTHESIZE_RETAIN(cocos2d::Menu*,_menu3,Menu3);
	CC_SYNTHESIZE_RETAIN(cocos2d::Menu*,_menu4,Menu4);
	CC_SYNTHESIZE_RETAIN(cocos2d::Menu*,_menu5,Menu5);
	CC_SYNTHESIZE_RETAIN(cocos2d::Menu*,_menu6,Menu6);
	CC_SYNTHESIZE_RETAIN(cocos2d::Menu*,_menu7,Menu7);
	CC_SYNTHESIZE_RETAIN(ImovileAd*,_ad,AD);
	CC_SYNTHESIZE_RETAIN(cocos2d::Label*,_ttlPoint,TtlPoint);

};

#endif // __HELLOWORLD_SCENE_H__
