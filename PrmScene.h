#ifndef __neomeiro__PrmScene__
#define __neomeiro__PrmScene__

#include "cocos2d.h"
#include "ParticleSystemPool.h"
#include "MeiroMeder.h"
#include "SelTag.h"
#include "ImovileAd.h"
#include "Slider.h"
#include "SizeSetBtn.h"
#include "SizeSetBtnControler.h"

USING_NS_CC;
class PrmScene: public cocos2d::Layer {
protected:
	PrmScene();
	virtual ~PrmScene();
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
	cocos2d::Vector<Slider*> _touchSpritepool;
	cocos2d::Vector<SizeSetBtn*> _sizeSetBtnpool;
	;CC_SYNTHESIZE_RETAIN(cocos2d::Touch*,_fstTch,FstTch)
	; //wタッチを禁止
	int moveLeftX = 80;
	int moveRightX = -680; //-1100
	int moveTopY = 3000;
	int moveDownY = 0; //-1100

	float moveVelo = 0;
	int beforePt = 0;
	bool tch_ = false;
	bool fstSet_ = false; //タッチ後最初にセットする。
	int Y;

	void SetPrm();
	int index = 0;
	void SetPrm(int index_);
	void GetPrm(int index_);

	;CC_SYNTHESIZE(cocos2d::Vector<SelTag*>,_selTags,SelTags)
	void update(float dt);CREATE_FUNC(PrmScene)
	;CC_SYNTHESIZE_RETAIN(MeiroMeder*, _mMeder, MMeder)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*,_backGround,BackGround)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*,_backGround2,BackGround2)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*,_selectStage,SelectStage)
	;
	;CC_SYNTHESIZE_RETAIN(cocos2d::Label*,_stageLabel,StageLabel)
	;CC_SYNTHESIZE(int,_level,Level)
	;CC_SYNTHESIZE_RETAIN(cocos2d::ParallaxNode *, _nomove1,noMove1)
	;CC_SYNTHESIZE_RETAIN(cocos2d::ParallaxNode *, _nomove2,noMove2)
	;CC_SYNTHESIZE_RETAIN(cocos2d::ParallaxNode *, _nomove3,noMove3)
	;

CC_SYNTHESIZE_RETAIN(cocos2d::MenuItemImage*,_startp,Startp)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Menu*,_startM,StartM)
	;

CC_SYNTHESIZE_RETAIN(SizeSetBtnControler *, _sizeSetBtnControler,SizeSetBtnControler)
	;

	//各値設定

	; //迷路サイズ文字
CC_SYNTHESIZE_RETAIN(SizeSetBtn *, _meiroSizeBtn,MeiroSizeBtn)
	; //迷路サイズ文字ボタン
CC_SYNTHESIZE_RETAIN(SizeSetBtn *, _meiroSizeXBtn,MeiroSizeXBtn)
	; //迷路サイズ文字ボタン
CC_SYNTHESIZE_RETAIN(SizeSetBtn *, _meiroSizeYBtn,MeiroSizeYBtn)
	; //迷路サイズ文字ボタン
CC_SYNTHESIZE_RETAIN(SizeSetBtn *, _meiroSizeCBtn,MeiroSizeCBtn)
	; //迷路サイズ文字ボタン

//表題設定
CC_SYNTHESIZE_RETAIN(Sprite *, _meiroSizeSp,MeiroSizeSp)
	;CC_SYNTHESIZE_RETAIN(Sprite *, _kabeKazuSp,KabeKazuSp)
	; //生成壁数
CC_SYNTHESIZE_RETAIN(Sprite *, _kabePrmSp,KabePrmSp)
	;CC_SYNTHESIZE_RETAIN(Sprite *, _prmWaku,PrmWaku)
	; //パラメータの枠


//	数値変換
	int ChgFrom_2_100(int x);
	int ChgTo_2_100To(int x);
	int ChgFrom_1_100(int x);
	int ChgTo_1_100To(int x);


	void ShowPrmK(int x);//x番目まで表示

	//番号
CC_SYNTHESIZE_RETAIN(Sprite*,_ban1,Ban1)
	;CC_SYNTHESIZE_RETAIN(Sprite*,_ban2,Ban2)
	;CC_SYNTHESIZE_RETAIN(Sprite*,_ban3,Ban3)
	;CC_SYNTHESIZE_RETAIN(Sprite*,_ban4,Ban4)
	;CC_SYNTHESIZE_RETAIN(Sprite*,_ban5,Ban5)


	CC_SYNTHESIZE_RETAIN(SizeSetBtn *, _susumi1btn1,Susumi1btn1);
	 CC_SYNTHESIZE_RETAIN(SizeSetBtn *, _zizoku1btn1,Zizoku1btn1);
	 CC_SYNTHESIZE_RETAIN(SizeSetBtn *, _syototu1btn1,Syototu1btn1);
	 CC_SYNTHESIZE_RETAIN(SizeSetBtn *, _seisei1btn1,Seisei1btn1);
	 CC_SYNTHESIZE_RETAIN(SizeSetBtn *, _henkabtn1,Henkabtn1);
	 CC_SYNTHESIZE_RETAIN(SizeSetBtn *, _susumi2btn1,Susumi2btn1);
	 CC_SYNTHESIZE_RETAIN(SizeSetBtn *, _zizoku2btn1,Zizoku2btn1);
	 CC_SYNTHESIZE_RETAIN(SizeSetBtn *, _syototu2btn1,Syototu2btn1);
	 CC_SYNTHESIZE_RETAIN(SizeSetBtn *, _seisei2btn1,Seisei2btn1);

	CC_SYNTHESIZE_RETAIN(SizeSetBtn *, _susumi1btn2,Susumi1btn2);
	 CC_SYNTHESIZE_RETAIN(SizeSetBtn *, _zizoku1btn2,Zizoku1btn2);
	 CC_SYNTHESIZE_RETAIN(SizeSetBtn *, _syototu1btn2,Syototu1btn2);
	 CC_SYNTHESIZE_RETAIN(SizeSetBtn *, _seisei1btn2,Seisei1btn2);
	 CC_SYNTHESIZE_RETAIN(SizeSetBtn *, _henkabtn2,Henkabtn2);
	 CC_SYNTHESIZE_RETAIN(SizeSetBtn *, _susumi2btn2,Susumi2btn2);
	 CC_SYNTHESIZE_RETAIN(SizeSetBtn *, _zizoku2btn2,Zizoku2btn2);
	 CC_SYNTHESIZE_RETAIN(SizeSetBtn *, _syototu2btn2,Syototu2btn2);
	 CC_SYNTHESIZE_RETAIN(SizeSetBtn *, _seisei2btn2,Seisei2btn2);

	CC_SYNTHESIZE_RETAIN(SizeSetBtn *, _susumi1btn3,Susumi1btn3);
	 CC_SYNTHESIZE_RETAIN(SizeSetBtn *, _zizoku1btn3,Zizoku1btn3);
	 CC_SYNTHESIZE_RETAIN(SizeSetBtn *, _syototu1btn3,Syototu1btn3);
	 CC_SYNTHESIZE_RETAIN(SizeSetBtn *, _seisei1btn3,Seisei1btn3);
	 CC_SYNTHESIZE_RETAIN(SizeSetBtn *, _henkabtn3,Henkabtn3);
	 CC_SYNTHESIZE_RETAIN(SizeSetBtn *, _susumi2btn3,Susumi2btn3);
	 CC_SYNTHESIZE_RETAIN(SizeSetBtn *, _zizoku2btn3,Zizoku2btn3);
	 CC_SYNTHESIZE_RETAIN(SizeSetBtn *, _syototu2btn3,Syototu2btn3);
	 CC_SYNTHESIZE_RETAIN(SizeSetBtn *, _seisei2btn3,Seisei2btn3);

	CC_SYNTHESIZE_RETAIN(SizeSetBtn *, _susumi1btn4,Susumi1btn4);
	 CC_SYNTHESIZE_RETAIN(SizeSetBtn *, _zizoku1btn4,Zizoku1btn4);
	 CC_SYNTHESIZE_RETAIN(SizeSetBtn *, _syototu1btn4,Syototu1btn4);
	 CC_SYNTHESIZE_RETAIN(SizeSetBtn *, _seisei1btn4,Seisei1btn4);
	 CC_SYNTHESIZE_RETAIN(SizeSetBtn *, _henkabtn4,Henkabtn4);
	 CC_SYNTHESIZE_RETAIN(SizeSetBtn *, _susumi2btn4,Susumi2btn4);
	 CC_SYNTHESIZE_RETAIN(SizeSetBtn *, _zizoku2btn4,Zizoku2btn4);
	 CC_SYNTHESIZE_RETAIN(SizeSetBtn *, _syototu2btn4,Syototu2btn4);
	 CC_SYNTHESIZE_RETAIN(SizeSetBtn *, _seisei2btn4,Seisei2btn4);

	CC_SYNTHESIZE_RETAIN(SizeSetBtn *, _susumi1btn5,Susumi1btn5);
	 CC_SYNTHESIZE_RETAIN(SizeSetBtn *, _zizoku1btn5,Zizoku1btn5);
	 CC_SYNTHESIZE_RETAIN(SizeSetBtn *, _syototu1btn5,Syototu1btn5);
	 CC_SYNTHESIZE_RETAIN(SizeSetBtn *, _seisei1btn5,Seisei1btn5);
	 CC_SYNTHESIZE_RETAIN(SizeSetBtn *, _henkabtn5,Henkabtn5);
	 CC_SYNTHESIZE_RETAIN(SizeSetBtn *, _susumi2btn5,Susumi2btn5);
	 CC_SYNTHESIZE_RETAIN(SizeSetBtn *, _zizoku2btn5,Zizoku2btn5);
	 CC_SYNTHESIZE_RETAIN(SizeSetBtn *, _syototu2btn5,Syototu2btn5);
	 CC_SYNTHESIZE_RETAIN(SizeSetBtn *, _seisei2btn5,Seisei2btn5);


	void setUpdateAction(std::function<void(PrmScene*, float dt)> action);
	void onEnterTransitionDidFinish() override;
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event);
	std::function<void(PrmScene*, float)> onUpDateListener;
	std::function<void(PrmScene*)> onsecUpDateListener;CC_SYNTHESIZE_RETAIN(EventListenerTouchOneByOne*, _touchListener,TouchListenner)

	;CC_SYNTHESIZE_RETAIN(ImovileAd*,_ad,AD)
	;

	//debug用
CC_SYNTHESIZE_RETAIN(cocos2d::MenuItemImage*,_prmBtn,PrmBtn)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Menu*,_menuPrm,MenuPrm)
	;

};

#endif // __HELLOWORLD_SCENE_H__
