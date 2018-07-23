#include "PrmScene.h"
#include "TitleScene.h"
#include "IMobileCocos2dxModule.h"
#include "ParticleSystemPool.h"
#include "MainScene.h"
#include "MainScene_Debug.h"
#include "MeiroMeder.h"
#include "TestScene.h"
#include "SizeSetBtnControler.h"
#include "cmath"

USING_NS_CC;

//重力ベクトル
const Vec2 GRAVITY_ACCERATION = Vec2(0, -10);
const Vec2 NONGRAVITY = Vec2(0, 0);

PrmScene::PrmScene() :
		_mMeder(NULL), _backGround(NULL), _backGround2(NULL), _stageLabel(NULL), _level(1), _nomove1(
		NULL), _nomove2(NULL), _nomove3(
		NULL), _touchListener(NULL), _selectStage(NULL), _ad(NULL), _prmBtn(NULL), _menuPrm(NULL), _fstTch(
		NULL), _startp(NULL), _startM(NULL), _meiroSizeSp(NULL), _kabeKazuSp(NULL), _kabePrmSp(NULL), _prmWaku(
		NULL), _meiroSizeBtn(NULL), _meiroSizeXBtn(NULL), _meiroSizeYBtn(NULL), _meiroSizeCBtn(
		NULL), _sizeSetBtnControler(NULL), _ban1(NULL), _ban2(NULL), _ban3(NULL), _ban4(NULL), _ban5(NULL), _susumi1btn1(
		NULL), _zizoku1btn1(NULL), _syototu1btn1(NULL), _seisei1btn1(NULL), _henkabtn1(NULL), _susumi2btn1(
		NULL), _zizoku2btn1(NULL), _syototu2btn1(NULL), _seisei2btn1(NULL), _susumi1btn2(NULL), _zizoku1btn2(
		NULL), _syototu1btn2(NULL), _seisei1btn2(NULL), _henkabtn2(NULL), _susumi2btn2(NULL), _zizoku2btn2(
		NULL), _syototu2btn2(NULL), _seisei2btn2(NULL), _susumi1btn3(NULL), _zizoku1btn3(NULL), _syototu1btn3(
		NULL), _seisei1btn3(NULL), _henkabtn3(NULL), _susumi2btn3(NULL), _zizoku2btn3(NULL), _syototu2btn3(
		NULL), _seisei2btn3(NULL), _susumi1btn4(NULL), _zizoku1btn4(NULL), _syototu1btn4(NULL), _seisei1btn4(
		NULL), _henkabtn4(NULL), _susumi2btn4(NULL), _zizoku2btn4(NULL), _syototu2btn4(NULL), _seisei2btn4(
		NULL), _susumi1btn5(NULL), _zizoku1btn5(NULL), _syototu1btn5(NULL), _seisei1btn5(NULL), _henkabtn5(
		NULL), _susumi2btn5(NULL), _zizoku2btn5(NULL), _syototu2btn5(NULL), _seisei2btn5(NULL) {
}

PrmScene::~PrmScene() {
	CC_SAFE_RELEASE_NULL(_menuPrm);
	CC_SAFE_RELEASE_NULL(_prmBtn);
	CC_SAFE_RELEASE_NULL(_mMeder);
	CC_SAFE_RELEASE_NULL(_backGround);
	CC_SAFE_RELEASE_NULL(_backGround2);
	CC_SAFE_RELEASE_NULL(_stageLabel);
	//CC_SAFE_RELEASE_NULL(_world);
	CC_SAFE_RELEASE_NULL(_nomove1);
	CC_SAFE_RELEASE_NULL(_nomove2);
	CC_SAFE_RELEASE_NULL(_nomove3);
	CC_SAFE_RELEASE_NULL(_touchListener);
	CC_SAFE_RELEASE_NULL(_selectStage);
	CC_SAFE_RELEASE_NULL(_startp);
	CC_SAFE_RELEASE_NULL(_startM);

	CC_SAFE_RELEASE_NULL(_ad);

	CC_SAFE_RELEASE_NULL(_fstTch);

	CC_SAFE_RELEASE_NULL(_meiroSizeSp);
	CC_SAFE_RELEASE_NULL(_kabeKazuSp);
	CC_SAFE_RELEASE_NULL(_kabePrmSp);
	CC_SAFE_RELEASE_NULL(_prmWaku);

	CC_SAFE_RELEASE_NULL(_meiroSizeBtn);

	CC_SAFE_RELEASE_NULL(_meiroSizeXBtn);
	CC_SAFE_RELEASE_NULL(_meiroSizeYBtn);
	CC_SAFE_RELEASE_NULL(_meiroSizeCBtn);
	CC_SAFE_RELEASE_NULL(_sizeSetBtnControler);

	CC_SAFE_RELEASE_NULL(_ban1);
	CC_SAFE_RELEASE_NULL(_ban2);
	CC_SAFE_RELEASE_NULL(_ban3);
	CC_SAFE_RELEASE_NULL(_ban4);
	CC_SAFE_RELEASE_NULL(_ban5);
	CC_SAFE_RELEASE_NULL(_susumi1btn1);
	CC_SAFE_RELEASE_NULL(_zizoku1btn1);
	CC_SAFE_RELEASE_NULL(_syototu1btn1);
	CC_SAFE_RELEASE_NULL(_seisei1btn1);
	CC_SAFE_RELEASE_NULL(_henkabtn1);
	CC_SAFE_RELEASE_NULL(_susumi2btn1);
	CC_SAFE_RELEASE_NULL(_zizoku2btn1);
	CC_SAFE_RELEASE_NULL(_syototu2btn1);
	CC_SAFE_RELEASE_NULL(_seisei2btn1);
	CC_SAFE_RELEASE_NULL(_susumi1btn2);
	CC_SAFE_RELEASE_NULL(_zizoku1btn2);
	CC_SAFE_RELEASE_NULL(_syototu1btn2);
	CC_SAFE_RELEASE_NULL(_seisei1btn2);
	CC_SAFE_RELEASE_NULL(_henkabtn2);
	CC_SAFE_RELEASE_NULL(_susumi2btn2);
	CC_SAFE_RELEASE_NULL(_zizoku2btn2);
	CC_SAFE_RELEASE_NULL(_syototu2btn2);
	CC_SAFE_RELEASE_NULL(_seisei2btn2);
	CC_SAFE_RELEASE_NULL(_susumi1btn3);
	CC_SAFE_RELEASE_NULL(_zizoku1btn3);
	CC_SAFE_RELEASE_NULL(_syototu1btn3);
	CC_SAFE_RELEASE_NULL(_seisei1btn3);
	CC_SAFE_RELEASE_NULL(_henkabtn3);
	CC_SAFE_RELEASE_NULL(_susumi2btn3);
	CC_SAFE_RELEASE_NULL(_zizoku2btn3);
	CC_SAFE_RELEASE_NULL(_syototu2btn3);
	CC_SAFE_RELEASE_NULL(_seisei2btn3);
	CC_SAFE_RELEASE_NULL(_susumi1btn4);
	CC_SAFE_RELEASE_NULL(_zizoku1btn4);
	CC_SAFE_RELEASE_NULL(_syototu1btn4);
	CC_SAFE_RELEASE_NULL(_seisei1btn4);
	CC_SAFE_RELEASE_NULL(_henkabtn4);
	CC_SAFE_RELEASE_NULL(_susumi2btn4);
	CC_SAFE_RELEASE_NULL(_zizoku2btn4);
	CC_SAFE_RELEASE_NULL(_syototu2btn4);
	CC_SAFE_RELEASE_NULL(_seisei2btn4);
	CC_SAFE_RELEASE_NULL(_susumi1btn5);
	CC_SAFE_RELEASE_NULL(_zizoku1btn5);
	CC_SAFE_RELEASE_NULL(_syototu1btn5);
	CC_SAFE_RELEASE_NULL(_seisei1btn5);
	CC_SAFE_RELEASE_NULL(_henkabtn5);
	CC_SAFE_RELEASE_NULL(_susumi2btn5);
	CC_SAFE_RELEASE_NULL(_zizoku2btn5);
	CC_SAFE_RELEASE_NULL(_syototu2btn5);
	CC_SAFE_RELEASE_NULL(_seisei2btn5);

}

Scene* PrmScene::createScene() {
	/*
	 auto scene = Scene::createWithPhysics();

	 //物理エンジン
	 auto world = scene->getPhysicsWorld();

	 //world->setGravity(GRAVITY_ACCERATION);
	 world->setGravity(Vec2::ZERO);
	 //#if COCOS2D_DEBUG >0

	 //world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	 //#endif

	 world->setSpeed(6.0);

	 // 'layer' is an autorelease object
	 auto layer = PrmScene::create();

	 // add layer as a child to scene
	 scene->addChild(layer);

	 // return the scene
	 return scene;

	 */

	auto scene = Scene::create();

	auto layer = PrmScene::create();

	scene->addChild(layer);

	// return the scene
	return scene;

}

// on "init" you need to initialize your instance
bool PrmScene::init() {

	if (!Layer::init()) {
		return false;
	}
	//this->setScale(0.5f);
//毎回のアップデート

	auto udf = UserDefault::getInstance();

	auto director = Director::getInstance();
	winSize.setSize(director->getWinSize().width, director->getWinSize().height);

	this->ctPt.set(winSize.width / 2, winSize.height / 2);

	this->setnoMove1(ParallaxNode::create());
	this->addChild(_nomove1);
	this->setnoMove2(ParallaxNode::create());
	this->addChild(_nomove2, 6);
	this->setnoMove3(ParallaxNode::create());
	this->addChild(_nomove3, 1);

	this->setBackGround(Sprite::create("back4.png"));
	_backGround->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2));
	this->addChild(_backGround, 5);

	this->setSelectStage(Sprite::create("prmseltitle.png"));
	this->_selectStage->setPosition(ctPt.x, winSize.height - 100);
	this->addChild(_selectStage, 6);

	this->setBackGround2(Sprite::create("back5.png"));
	_backGround2->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2));
	this->addChild(_backGround2);

	this->setLevel(udf->getIntegerForKey("LEVEL", 7));

	//スライダーコントローラーセット
	this->setSizeSetBtnControler(SizeSetBtnControler::create());
	this->addChild(this->_sizeSetBtnControler);
	this->addChild(this->_sizeSetBtnControler->getSlider(), 11);
	const char *str0 = "PrmScene::init()_0";
	log("%s", str0);

	this->_touchSpritepool.pushBack(this->getSizeSetBtnControler()->getSlider());

	const char *str2 = "PrmScene::init()_2";
	log("%s", str2);

//迷路の項目テキストをセット

	this->setMeiroSizeSp(Sprite::create("meirosize.png"));
	this->_meiroSizeSp->setAnchorPoint(Vec2(0, 0.5));
	this->_meiroSizeSp->setPosition(30, winSize.height - 270);
	this->addChild(_meiroSizeSp, 1);

	this->setKabeKazuSp(Sprite::create("seiseikazu.png"));
	this->_kabeKazuSp->setAnchorPoint(Vec2(0, 0.5));
	this->_kabeKazuSp->setPosition(30, winSize.height - 340);
	this->addChild(_kabeKazuSp, 1);

	this->setKabePrmSp(Sprite::create("meiroprm.png"));
	this->_kabePrmSp->setAnchorPoint(Vec2(0, 0.5));
	this->_kabePrmSp->setPosition(30, winSize.height - 410);
	this->addChild(_kabePrmSp, 1);

	this->setPrmWaku(Sprite::create("selprmwaku3.png"));
	this->_prmWaku->setPosition(_kabePrmSp->getPosition() + Vec2(50, -90));
	_prmWaku->setAnchorPoint(Vec2(0, 1));
	_prmWaku->setVisible(true);
	_prmWaku->setScale(1);
	this->addChild(_prmWaku, 1);

//サイズセットボタンをセット

	this->setMeiroSizeXBtn(SizeSetBtn::create("meirosize_waku.png"));
	this->_meiroSizeXBtn->setPosition(
			_meiroSizeSp->getContentSize().width + _meiroSizeSp->getPosition().x -80,
			_meiroSizeSp->getPosition().y);
	this->addChild(_meiroSizeXBtn, 10);
	this->getSizeSetBtnControler()->AddSizeSetController(_meiroSizeXBtn);
	this->_meiroSizeXBtn->SetAtai(udf->getIntegerForKey("COURCE_X", 16));
	this->_meiroSizeXBtn->SetNamaeListenner("Xの大きさ", "10", "200", 10, 200);
//
////	_sizeSetBtnpool.pushBack(_meiroSizeXBtn);
//
//	const char *str3 = "PrmScene::init()_3";
//	log("%s", str3);

	this->setMeiroSizeYBtn(SizeSetBtn::create("meirosize_waku.png"));
	this->_meiroSizeYBtn->setPosition(
			_meiroSizeSp->getContentSize().width + _meiroSizeSp->getPosition().x +55,
			_meiroSizeSp->getPosition().y);
	this->addChild(_meiroSizeYBtn, 10);
	this->getSizeSetBtnControler()->AddSizeSetController(_meiroSizeYBtn);
	this->_meiroSizeYBtn->SetAtai(udf->getIntegerForKey("COURCE_Y", 20));
	this->_meiroSizeYBtn->SetNamaeListenner("Yの大きさ", "10", "200", 10, 200);

//	_sizeSetBtnpool.pushBack(_meiroSizeYBtn);

	this->setMeiroSizeCBtn(SizeSetBtn::create("meirosize_waku.png"));
	this->_meiroSizeCBtn->setPosition(_kabeKazuSp->getContentSize().width + _kabeKazuSp->getPosition().x + 60,
			_kabeKazuSp->getPosition().y);
	this->addChild(_meiroSizeCBtn, 10);
	this->getSizeSetBtnControler()->AddSizeSetController(_meiroSizeCBtn);
	this->_meiroSizeCBtn->SetAtai(udf->getIntegerForKey("MADER_CNT", 2));
	this->_meiroSizeCBtn->SetNamaeListenner("生成壁の数", "1", "5", 1, 5);

//番号をセット

	int w_ = 80;
	int h_ = -60;
	Vec2 fstPt_;
	fstPt_.set(_kabePrmSp->getPosition() + Vec2(280, -50));

	int x_ = 0;
	int y_ = 0;

	//番号①をセット
//	this->setBan1(Sprite::create("bango1.png"));
//	this->_ban1->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
//	this->addChild(_ban1, 10);
//	y_++;
//
//	this->setSusumi1btn1(SizeSetBtn::create("meirosize_waku.png"));
//	this->_susumi1btn1->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
//	this->addChild(_susumi1btn1, 10);
//	this->getSizeSetBtnControler()->AddSizeSetController(_susumi1btn1);
//	this->_susumi1btn1->SetAtai(this->ChgFrom_2_100(udf->getIntegerForKey("TYOKU_1", 3)));
//	this->_susumi1btn1->SetNamaeListenner("生成壁①の進み方1", "ジグザク", "真っ直ぐ", 1, 5);
//	y_++;
//
//	this->setZizoku1btn1(SizeSetBtn::create("meirosize_waku.png"));
//	this->_zizoku1btn1->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
//	this->addChild(_zizoku1btn1, 10);
//	this->getSizeSetBtnControler()->AddSizeSetController(_zizoku1btn1);
//	this->_zizoku1btn1->SetAtai(this->ChgFrom_2_100(udf->getIntegerForKey("ZIZOKU_1", 3)));
//	this->_zizoku1btn1->SetNamaeListenner("生成壁①の持続性1", "短い", "長い", 1, 5);
//	y_++;
//
//	this->setSyototu1btn1(SizeSetBtn::create("meirosize_waku.png"));
//	this->_syototu1btn1->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
//	this->addChild(_syototu1btn1, 10);
//	this->getSizeSetBtnControler()->AddSizeSetController(_syototu1btn1);
//	this->_syototu1btn1->SetAtai(this->ChgFrom_1_100(udf->getIntegerForKey("KABE_1", 3)));
//	this->_syototu1btn1->SetNamaeListenner("生成壁①の壁衝突時1", "終了", "壁に沿う", 1, 5);
//	y_++;
//
//	this->setSeisei1btn1(SizeSetBtn::create("meirosize_waku.png"));
//	this->_seisei1btn1->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
//	this->addChild(_seisei1btn1, 10);
//	this->getSizeSetBtnControler()->AddSizeSetController(_seisei1btn1);
//	this->_seisei1btn1->SetAtai(this->ChgFrom_1_100(udf->getIntegerForKey("EDA_1", 3)));
//	this->_seisei1btn1->SetNamaeListenner("生成壁①の次の生成1", "外周壁", "内壁", 1, 5);
//	y_++;
//
//	this->setHenkabtn1(SizeSetBtn::create("meirosize_waku.png"));
//	this->_henkabtn1->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
//	this->addChild(_henkabtn1, 10);
//	this->getSizeSetBtnControler()->AddSizeSetController(_henkabtn1);
//	this->_henkabtn1->SetAtai(this->ChgFrom_1_100(udf->getIntegerForKey("SYOKI_1", 3)));
//	this->_henkabtn1->SetNamaeListenner("生成壁①の変化時期", "最初", "最後", 1, 5);
//	y_++;
//
//	this->setSusumi2btn1(SizeSetBtn::create("meirosize_waku.png"));
//	this->_susumi2btn1->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
//	this->addChild(_susumi2btn1, 10);
//	this->getSizeSetBtnControler()->AddSizeSetController(_susumi2btn1);
//	this->_susumi2btn1->SetAtai(this->ChgFrom_2_100(udf->getIntegerForKey("TYOKU2_1", 3)));
//	this->_susumi2btn1->SetNamaeListenner("生成壁①の進み方2", "ジグザク", "真っ直ぐ", 1, 5);
//	y_++;
//
//	this->setZizoku2btn1(SizeSetBtn::create("meirosize_waku.png"));
//	this->_zizoku2btn1->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
//	this->addChild(_zizoku2btn1, 10);
//	this->getSizeSetBtnControler()->AddSizeSetController(_zizoku2btn1);
//	this->_zizoku2btn1->SetAtai(this->ChgFrom_2_100(udf->getIntegerForKey("ZIZOKU2_1", 3)));
//	this->_zizoku2btn1->SetNamaeListenner("生成壁①の持続性2", "短い", "長い", 1, 5);
//	y_++;
//
//	this->setSyototu2btn1(SizeSetBtn::create("meirosize_waku.png"));
//	this->_syototu2btn1->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
//	this->addChild(_syototu2btn1, 10);
//	this->getSizeSetBtnControler()->AddSizeSetController(_syototu2btn1);
//	this->_syototu2btn1->SetAtai(this->ChgFrom_1_100(udf->getIntegerForKey("KABE2_1", 3)));
//	this->_syototu2btn1->SetNamaeListenner("生成壁①の壁衝突時2", "終了", "壁に沿う", 1, 5);
//	y_++;
//
//	this->setSeisei2btn1(SizeSetBtn::create("meirosize_waku.png"));
//	this->_seisei2btn1->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
//	this->addChild(_seisei2btn1, 10);
//	this->getSizeSetBtnControler()->AddSizeSetController(_seisei2btn1);
//	this->_seisei2btn1->SetAtai(this->ChgFrom_1_100(udf->getIntegerForKey("EDA2_1", 3)));
//	this->_seisei2btn1->SetNamaeListenner("生成壁①の次の生成2", "外周壁", "内壁", 1, 5);
//	y_ = 0;
//	x_++;

//番号①をセット
	this->setBan1(Sprite::create("bango1.png"));
	this->_ban1->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
	this->addChild(_ban1, 10);
	_ban1->setTag(1);
	y_++;

	this->setSusumi1btn1(SizeSetBtn::create("meirosize_waku.png"));
	this->_susumi1btn1->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
	this->addChild(_susumi1btn1, 10);
	this->getSizeSetBtnControler()->AddSizeSetController(_susumi1btn1);
	this->_susumi1btn1->SetAtai(this->ChgFrom_2_100(udf->getIntegerForKey("TYOKU_1", 3)));
	this->_susumi1btn1->SetNamaeListenner("生成壁①の進み方1", "ジグザク", "真っ直ぐ", 1, 5);
	_susumi1btn1->setTag(1);
	y_++;

	this->setZizoku1btn1(SizeSetBtn::create("meirosize_waku.png"));
	this->_zizoku1btn1->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
	this->addChild(_zizoku1btn1, 10);
	this->getSizeSetBtnControler()->AddSizeSetController(_zizoku1btn1);
	this->_zizoku1btn1->SetAtai(this->ChgFrom_2_100(udf->getIntegerForKey("ZIZOKU_1", 3)));
	this->_zizoku1btn1->SetNamaeListenner("生成壁①の持続性1", "短い", "長い", 1, 5);
	_zizoku1btn1->setTag(1);
	y_++;

	this->setSyototu1btn1(SizeSetBtn::create("meirosize_waku.png"));
	this->_syototu1btn1->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
	this->addChild(_syototu1btn1, 10);
	this->getSizeSetBtnControler()->AddSizeSetController(_syototu1btn1);
	this->_syototu1btn1->SetAtai(this->ChgFrom_1_100(udf->getIntegerForKey("KABE_1", 3)));
	this->_syototu1btn1->SetNamaeListenner("生成壁①の壁衝突時1", "終了", "壁に沿う", 1, 5);
	_syototu1btn1->setTag(1);
	y_++;

	this->setSeisei1btn1(SizeSetBtn::create("meirosize_waku.png"));
	this->_seisei1btn1->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
	this->addChild(_seisei1btn1, 10);
	this->getSizeSetBtnControler()->AddSizeSetController(_seisei1btn1);
	this->_seisei1btn1->SetAtai(this->ChgFrom_1_100(udf->getIntegerForKey("EDA_1", 3)));
	this->_seisei1btn1->SetNamaeListenner("生成壁①の次の生成1", "外周壁", "内壁", 1, 5);
	_seisei1btn1->setTag(1);
	y_++;

	this->setHenkabtn1(SizeSetBtn::create("meirosize_waku.png"));
	this->_henkabtn1->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
	this->addChild(_henkabtn1, 10);
	this->getSizeSetBtnControler()->AddSizeSetController(_henkabtn1);
	this->_henkabtn1->SetAtai(this->ChgFrom_1_100(udf->getIntegerForKey("SYOKI_1", 3)));
	this->_henkabtn1->SetNamaeListenner("生成壁①の変化時期", "最初", "最後", 1, 5);
	_henkabtn1->setTag(1);
	y_++;

	this->setSusumi2btn1(SizeSetBtn::create("meirosize_waku.png"));
	this->_susumi2btn1->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
	this->addChild(_susumi2btn1, 10);
	this->getSizeSetBtnControler()->AddSizeSetController(_susumi2btn1);
	this->_susumi2btn1->SetAtai(this->ChgFrom_2_100(udf->getIntegerForKey("TYOKU2_1", 3)));
	this->_susumi2btn1->SetNamaeListenner("生成壁①の進み方2", "ジグザク", "真っ直ぐ", 1, 5);
	_susumi2btn1->setTag(1);

	y_++;

	this->setZizoku2btn1(SizeSetBtn::create("meirosize_waku.png"));
	this->_zizoku2btn1->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
	this->addChild(_zizoku2btn1, 10);
	this->getSizeSetBtnControler()->AddSizeSetController(_zizoku2btn1);
	this->_zizoku2btn1->SetAtai(this->ChgFrom_2_100(udf->getIntegerForKey("ZIZOKU2_1", 3)));
	this->_zizoku2btn1->SetNamaeListenner("生成壁①の持続性2", "短い", "長い", 1, 5);
	_zizoku2btn1->setTag(1);
	y_++;

	this->setSyototu2btn1(SizeSetBtn::create("meirosize_waku.png"));
	this->_syototu2btn1->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
	this->addChild(_syototu2btn1, 10);
	this->getSizeSetBtnControler()->AddSizeSetController(_syototu2btn1);
	this->_syototu2btn1->SetAtai(this->ChgFrom_1_100(udf->getIntegerForKey("KABE2_1", 3)));
	this->_syototu2btn1->SetNamaeListenner("生成壁①の壁衝突時2", "終了", "壁に沿う", 1, 5);
	_syototu2btn1->setTag(1);
	y_++;

	this->setSeisei2btn1(SizeSetBtn::create("meirosize_waku.png"));
	this->_seisei2btn1->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
	this->addChild(_seisei2btn1, 10);
	this->getSizeSetBtnControler()->AddSizeSetController(_seisei2btn1);
	this->_seisei2btn1->SetAtai(this->ChgFrom_1_100(udf->getIntegerForKey("EDA2_1", 3)));
	this->_seisei2btn1->SetNamaeListenner("生成壁①の次の生成2", "外周壁", "内壁", 1, 5);
	_seisei2btn1->setTag(1);
	y_ = 0;
	x_++;
	//番号②をセット
	this->setBan2(Sprite::create("bango2.png"));
	this->_ban2->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
	this->addChild(_ban2, 10);
	y_++;

	this->setSusumi1btn2(SizeSetBtn::create("meirosize_waku.png"));
	this->_susumi1btn2->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
	this->addChild(_susumi1btn2, 10);
	this->getSizeSetBtnControler()->AddSizeSetController(_susumi1btn2);
	this->_susumi1btn2->SetAtai(this->ChgFrom_2_100(udf->getIntegerForKey("TYOKU_2", 3)));
	this->_susumi1btn2->SetNamaeListenner("生成壁②の進み方1", "ジグザク", "真っ直ぐ", 1, 5);
	y_++;

	this->setZizoku1btn2(SizeSetBtn::create("meirosize_waku.png"));
	this->_zizoku1btn2->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
	this->addChild(_zizoku1btn2, 10);
	this->getSizeSetBtnControler()->AddSizeSetController(_zizoku1btn2);
	this->_zizoku1btn2->SetAtai(this->ChgFrom_2_100(udf->getIntegerForKey("ZIZOKU_2", 3)));
	this->_zizoku1btn2->SetNamaeListenner("生成壁②の持続性1", "短い", "長い", 1, 5);
	y_++;

	this->setSyototu1btn2(SizeSetBtn::create("meirosize_waku.png"));
	this->_syototu1btn2->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
	this->addChild(_syototu1btn2, 10);
	this->getSizeSetBtnControler()->AddSizeSetController(_syototu1btn2);
	this->_syototu1btn2->SetAtai(this->ChgFrom_1_100(udf->getIntegerForKey("KABE_2", 3)));
	this->_syototu1btn2->SetNamaeListenner("生成壁②の壁衝突時1", "終了", "壁に沿う", 1, 5);
	y_++;

	this->setSeisei1btn2(SizeSetBtn::create("meirosize_waku.png"));
	this->_seisei1btn2->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
	this->addChild(_seisei1btn2, 10);
	this->getSizeSetBtnControler()->AddSizeSetController(_seisei1btn2);
	this->_seisei1btn2->SetAtai(this->ChgFrom_1_100(udf->getIntegerForKey("EDA_2", 3)));
	this->_seisei1btn2->SetNamaeListenner("生成壁②の次の生成1", "外周壁", "内壁", 1, 5);
	y_++;

	this->setHenkabtn2(SizeSetBtn::create("meirosize_waku.png"));
	this->_henkabtn2->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
	this->addChild(_henkabtn2, 10);
	this->getSizeSetBtnControler()->AddSizeSetController(_henkabtn2);
	this->_henkabtn2->SetAtai(this->ChgFrom_1_100(udf->getIntegerForKey("SYOKI_2", 3)));
	this->_henkabtn2->SetNamaeListenner("生成壁②の変化時期", "最初", "最後", 1, 5);
	y_++;

	this->setSusumi2btn2(SizeSetBtn::create("meirosize_waku.png"));
	this->_susumi2btn2->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
	this->addChild(_susumi2btn2, 10);
	this->getSizeSetBtnControler()->AddSizeSetController(_susumi2btn2);
	this->_susumi2btn2->SetAtai(this->ChgFrom_2_100(udf->getIntegerForKey("TYOKU2_2", 3)));
	this->_susumi2btn2->SetNamaeListenner("生成壁②の進み方2", "ジグザク", "真っ直ぐ", 1, 5);
	y_++;

	this->setZizoku2btn2(SizeSetBtn::create("meirosize_waku.png"));
	this->_zizoku2btn2->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
	this->addChild(_zizoku2btn2, 10);
	this->getSizeSetBtnControler()->AddSizeSetController(_zizoku2btn2);
	this->_zizoku2btn2->SetAtai(this->ChgFrom_2_100(udf->getIntegerForKey("ZIZOKU2_2", 3)));
	this->_zizoku2btn2->SetNamaeListenner("生成壁②の持続性2", "短い", "長い", 1, 5);
	y_++;

	this->setSyototu2btn2(SizeSetBtn::create("meirosize_waku.png"));
	this->_syototu2btn2->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
	this->addChild(_syototu2btn2, 10);
	this->getSizeSetBtnControler()->AddSizeSetController(_syototu2btn2);
	this->_syototu2btn2->SetAtai(this->ChgFrom_1_100(udf->getIntegerForKey("KABE2_2", 3)));
	this->_syototu2btn2->SetNamaeListenner("生成壁②の壁衝突時2", "終了", "壁に沿う", 1, 5);
	y_++;

	this->setSeisei2btn2(SizeSetBtn::create("meirosize_waku.png"));
	this->_seisei2btn2->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
	this->addChild(_seisei2btn2, 10);
	this->getSizeSetBtnControler()->AddSizeSetController(_seisei2btn2);
	this->_seisei2btn2->SetAtai(this->ChgFrom_1_100(udf->getIntegerForKey("EDA2_2", 3)));
	this->_seisei2btn2->SetNamaeListenner("生成壁②の次の生成2", "外周壁", "内壁", 1, 5);
	y_ = 0;
	x_++;
	//番号③をセット
	this->setBan3(Sprite::create("bango3.png"));
	this->_ban3->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
	this->addChild(_ban3, 10);
	y_++;

	this->setSusumi1btn3(SizeSetBtn::create("meirosize_waku.png"));
	this->_susumi1btn3->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
	this->addChild(_susumi1btn3, 10);
	this->getSizeSetBtnControler()->AddSizeSetController(_susumi1btn3);
	this->_susumi1btn3->SetAtai(this->ChgFrom_2_100(udf->getIntegerForKey("TYOKU_3", 3)));
	this->_susumi1btn3->SetNamaeListenner("生成壁③の進み方1", "ジグザク", "真っ直ぐ", 1, 5);
	y_++;

	this->setZizoku1btn3(SizeSetBtn::create("meirosize_waku.png"));
	this->_zizoku1btn3->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
	this->addChild(_zizoku1btn3, 10);
	this->getSizeSetBtnControler()->AddSizeSetController(_zizoku1btn3);
	this->_zizoku1btn3->SetAtai(this->ChgFrom_2_100(udf->getIntegerForKey("ZIZOKU_3", 3)));
	this->_zizoku1btn3->SetNamaeListenner("生成壁③の持続性1", "短い", "長い", 1, 5);
	y_++;

	this->setSyototu1btn3(SizeSetBtn::create("meirosize_waku.png"));
	this->_syototu1btn3->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
	this->addChild(_syototu1btn3, 10);
	this->getSizeSetBtnControler()->AddSizeSetController(_syototu1btn3);
	this->_syototu1btn3->SetAtai(this->ChgFrom_1_100(udf->getIntegerForKey("KABE_3", 3)));
	this->_syototu1btn3->SetNamaeListenner("生成壁③の壁衝突時1", "終了", "壁に沿う", 1, 5);
	y_++;

	this->setSeisei1btn3(SizeSetBtn::create("meirosize_waku.png"));
	this->_seisei1btn3->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
	this->addChild(_seisei1btn3, 10);
	this->getSizeSetBtnControler()->AddSizeSetController(_seisei1btn3);
	this->_seisei1btn3->SetAtai(this->ChgFrom_1_100(udf->getIntegerForKey("EDA_3", 3)));
	this->_seisei1btn3->SetNamaeListenner("生成壁③の次の生成1", "外周壁", "内壁", 1, 5);
	y_++;

	this->setHenkabtn3(SizeSetBtn::create("meirosize_waku.png"));
	this->_henkabtn3->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
	this->addChild(_henkabtn3, 10);
	this->getSizeSetBtnControler()->AddSizeSetController(_henkabtn3);
	this->_henkabtn3->SetAtai(this->ChgFrom_1_100(udf->getIntegerForKey("SYOKI_3", 3)));
	this->_henkabtn3->SetNamaeListenner("生成壁③の変化時期", "最初", "最後", 1, 5);
	y_++;

	this->setSusumi2btn3(SizeSetBtn::create("meirosize_waku.png"));
	this->_susumi2btn3->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
	this->addChild(_susumi2btn3, 10);
	this->getSizeSetBtnControler()->AddSizeSetController(_susumi2btn3);
	this->_susumi2btn3->SetAtai(this->ChgFrom_2_100(udf->getIntegerForKey("TYOKU2_3", 3)));
	this->_susumi2btn3->SetNamaeListenner("生成壁③の進み方2", "ジグザク", "真っ直ぐ", 1, 5);
	y_++;

	this->setZizoku2btn3(SizeSetBtn::create("meirosize_waku.png"));
	this->_zizoku2btn3->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
	this->addChild(_zizoku2btn3, 10);
	this->getSizeSetBtnControler()->AddSizeSetController(_zizoku2btn3);
	this->_zizoku2btn3->SetAtai(this->ChgFrom_2_100(udf->getIntegerForKey("ZIZOKU2_3", 3)));
	this->_zizoku2btn3->SetNamaeListenner("生成壁③の持続性2", "短い", "長い", 1, 5);
	y_++;

	this->setSyototu2btn3(SizeSetBtn::create("meirosize_waku.png"));
	this->_syototu2btn3->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
	this->addChild(_syototu2btn3, 10);
	this->getSizeSetBtnControler()->AddSizeSetController(_syototu2btn3);
	this->_syototu2btn3->SetAtai(this->ChgFrom_1_100(udf->getIntegerForKey("KABE2_3", 3)));
	this->_syototu2btn3->SetNamaeListenner("生成壁③の壁衝突時2", "終了", "壁に沿う", 1, 5);
	y_++;

	this->setSeisei2btn3(SizeSetBtn::create("meirosize_waku.png"));
	this->_seisei2btn3->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
	this->addChild(_seisei2btn3, 10);
	this->getSizeSetBtnControler()->AddSizeSetController(_seisei2btn3);
	this->_seisei2btn3->SetAtai(this->ChgFrom_1_100(udf->getIntegerForKey("EDA2_3", 3)));
	this->_seisei2btn3->SetNamaeListenner("生成壁③の次の生成2", "外周壁", "内壁", 1, 5);
	y_ = 0;
	x_++;
	//番号④をセット
	this->setBan4(Sprite::create("bango4.png"));
	this->_ban4->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
	this->addChild(_ban4, 10);
	y_++;

	this->setSusumi1btn4(SizeSetBtn::create("meirosize_waku.png"));
	this->_susumi1btn4->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
	this->addChild(_susumi1btn4, 10);
	this->getSizeSetBtnControler()->AddSizeSetController(_susumi1btn4);
	this->_susumi1btn4->SetAtai(this->ChgFrom_2_100(udf->getIntegerForKey("TYOKU_4", 3)));
	this->_susumi1btn4->SetNamaeListenner("生成壁④の進み方1", "ジグザク", "真っ直ぐ", 1, 5);
	y_++;

	this->setZizoku1btn4(SizeSetBtn::create("meirosize_waku.png"));
	this->_zizoku1btn4->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
	this->addChild(_zizoku1btn4, 10);
	this->getSizeSetBtnControler()->AddSizeSetController(_zizoku1btn4);
	this->_zizoku1btn4->SetAtai(this->ChgFrom_2_100(udf->getIntegerForKey("ZIZOKU_4", 3)));
	this->_zizoku1btn4->SetNamaeListenner("生成壁④の持続性1", "短い", "長い", 1, 5);
	y_++;

	this->setSyototu1btn4(SizeSetBtn::create("meirosize_waku.png"));
	this->_syototu1btn4->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
	this->addChild(_syototu1btn4, 10);
	this->getSizeSetBtnControler()->AddSizeSetController(_syototu1btn4);
	this->_syototu1btn4->SetAtai(this->ChgFrom_1_100(udf->getIntegerForKey("KABE_4", 3)));
	this->_syototu1btn4->SetNamaeListenner("生成壁④の壁衝突時1", "終了", "壁に沿う", 1, 5);
	y_++;

	this->setSeisei1btn4(SizeSetBtn::create("meirosize_waku.png"));
	this->_seisei1btn4->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
	this->addChild(_seisei1btn4, 10);
	this->getSizeSetBtnControler()->AddSizeSetController(_seisei1btn4);
	this->_seisei1btn4->SetAtai(this->ChgFrom_1_100(udf->getIntegerForKey("EDA_4", 3)));
	this->_seisei1btn4->SetNamaeListenner("生成壁④の次の生成1", "外周壁", "内壁", 1, 5);
	y_++;

	this->setHenkabtn4(SizeSetBtn::create("meirosize_waku.png"));
	this->_henkabtn4->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
	this->addChild(_henkabtn4, 10);
	this->getSizeSetBtnControler()->AddSizeSetController(_henkabtn4);
	this->_henkabtn4->SetAtai(this->ChgFrom_1_100(udf->getIntegerForKey("SYOKI_4", 3)));
	this->_henkabtn4->SetNamaeListenner("生成壁④の変化時期", "最初", "最後", 1, 5);
	y_++;

	this->setSusumi2btn4(SizeSetBtn::create("meirosize_waku.png"));
	this->_susumi2btn4->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
	this->addChild(_susumi2btn4, 10);
	this->getSizeSetBtnControler()->AddSizeSetController(_susumi2btn4);
	this->_susumi2btn4->SetAtai(this->ChgFrom_2_100(udf->getIntegerForKey("TYOKU2_4", 3)));
	this->_susumi2btn4->SetNamaeListenner("生成壁④の進み方2", "ジグザク", "真っ直ぐ", 1, 5);
	y_++;

	this->setZizoku2btn4(SizeSetBtn::create("meirosize_waku.png"));
	this->_zizoku2btn4->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
	this->addChild(_zizoku2btn4, 10);
	this->getSizeSetBtnControler()->AddSizeSetController(_zizoku2btn4);
	this->_zizoku2btn4->SetAtai(this->ChgFrom_2_100(udf->getIntegerForKey("ZIZOKU2_4", 3)));
	this->_zizoku2btn4->SetNamaeListenner("生成壁④の持続性2", "短い", "長い", 1, 5);
	y_++;

	this->setSyototu2btn4(SizeSetBtn::create("meirosize_waku.png"));
	this->_syototu2btn4->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
	this->addChild(_syototu2btn4, 10);
	this->getSizeSetBtnControler()->AddSizeSetController(_syototu2btn4);
	this->_syototu2btn4->SetAtai(this->ChgFrom_1_100(udf->getIntegerForKey("KABE2_4", 3)));
	this->_syototu2btn4->SetNamaeListenner("生成壁④の壁衝突時2", "終了", "壁に沿う", 1, 5);
	y_++;

	this->setSeisei2btn4(SizeSetBtn::create("meirosize_waku.png"));
	this->_seisei2btn4->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
	this->addChild(_seisei2btn4, 10);
	this->getSizeSetBtnControler()->AddSizeSetController(_seisei2btn4);
	this->_seisei2btn4->SetAtai(this->ChgFrom_1_100(udf->getIntegerForKey("EDA2_4", 3)));
	this->_seisei2btn4->SetNamaeListenner("生成壁④の次の生成2", "外周壁", "内壁", 1, 5);
	y_ = 0;
	x_++;
	//番号⑤をセット
	this->setBan5(Sprite::create("bango5.png"));
	this->_ban5->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
	this->addChild(_ban5, 10);
	y_++;

	this->setSusumi1btn5(SizeSetBtn::create("meirosize_waku.png"));
	this->_susumi1btn5->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
	this->addChild(_susumi1btn5, 10);
	this->getSizeSetBtnControler()->AddSizeSetController(_susumi1btn5);
	this->_susumi1btn5->SetAtai(this->ChgFrom_2_100(udf->getIntegerForKey("TYOKU_5", 3)));
	this->_susumi1btn5->SetNamaeListenner("生成壁⑤の進み方1", "ジグザク", "真っ直ぐ", 1, 5);
	y_++;

	this->setZizoku1btn5(SizeSetBtn::create("meirosize_waku.png"));
	this->_zizoku1btn5->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
	this->addChild(_zizoku1btn5, 10);
	this->getSizeSetBtnControler()->AddSizeSetController(_zizoku1btn5);
	this->_zizoku1btn5->SetAtai(this->ChgFrom_2_100(udf->getIntegerForKey("ZIZOKU_5", 3)));
	this->_zizoku1btn5->SetNamaeListenner("生成壁⑤の持続性1", "短い", "長い", 1, 5);
	y_++;

	this->setSyototu1btn5(SizeSetBtn::create("meirosize_waku.png"));
	this->_syototu1btn5->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
	this->addChild(_syototu1btn5, 10);
	this->getSizeSetBtnControler()->AddSizeSetController(_syototu1btn5);
	this->_syototu1btn5->SetAtai(this->ChgFrom_1_100(udf->getIntegerForKey("KABE_5", 3)));
	this->_syototu1btn5->SetNamaeListenner("生成壁⑤の壁衝突時1", "終了", "壁に沿う", 1, 5);
	y_++;

	this->setSeisei1btn5(SizeSetBtn::create("meirosize_waku.png"));
	this->_seisei1btn5->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
	this->addChild(_seisei1btn5, 10);
	this->getSizeSetBtnControler()->AddSizeSetController(_seisei1btn5);
	this->_seisei1btn5->SetAtai(this->ChgFrom_1_100(udf->getIntegerForKey("EDA_5", 3)));
	this->_seisei1btn5->SetNamaeListenner("生成壁⑤の次の生成1", "外周壁", "内壁", 1, 5);
	y_++;

	this->setHenkabtn5(SizeSetBtn::create("meirosize_waku.png"));
	this->_henkabtn5->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
	this->addChild(_henkabtn5, 10);
	this->getSizeSetBtnControler()->AddSizeSetController(_henkabtn5);
	this->_henkabtn5->SetAtai(this->ChgFrom_1_100(udf->getIntegerForKey("SYOKI_5", 3)));
	this->_henkabtn5->SetNamaeListenner("生成壁⑤の変化時期", "最初", "最後", 1, 5);
	y_++;

	this->setSusumi2btn5(SizeSetBtn::create("meirosize_waku.png"));
	this->_susumi2btn5->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
	this->addChild(_susumi2btn5, 10);
	this->getSizeSetBtnControler()->AddSizeSetController(_susumi2btn5);
	this->_susumi2btn5->SetAtai(this->ChgFrom_2_100(udf->getIntegerForKey("TYOKU2_5", 3)));
	this->_susumi2btn5->SetNamaeListenner("生成壁⑤の進み方2", "ジグザク", "真っ直ぐ", 1, 5);
	y_++;

	this->setZizoku2btn5(SizeSetBtn::create("meirosize_waku.png"));
	this->_zizoku2btn5->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
	this->addChild(_zizoku2btn5, 10);
	this->getSizeSetBtnControler()->AddSizeSetController(_zizoku2btn5);
	this->_zizoku2btn5->SetAtai(this->ChgFrom_2_100(udf->getIntegerForKey("ZIZOKU2_5", 3)));
	this->_zizoku2btn5->SetNamaeListenner("生成壁⑤の持続性2", "短い", "長い", 1, 5);
	y_++;

	this->setSyototu2btn5(SizeSetBtn::create("meirosize_waku.png"));
	this->_syototu2btn5->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
	this->addChild(_syototu2btn5, 10);
	this->getSizeSetBtnControler()->AddSizeSetController(_syototu2btn5);
	this->_syototu2btn5->SetAtai(this->ChgFrom_1_100(udf->getIntegerForKey("KABE2_5", 3)));
	this->_syototu2btn5->SetNamaeListenner("生成壁⑤の壁衝突時2", "終了", "壁に沿う", 1, 5);
	y_++;

	this->setSeisei2btn5(SizeSetBtn::create("meirosize_waku.png"));
	this->_seisei2btn5->setPosition(fstPt_ + Vec2(w_ * x_, h_ * y_));
	this->addChild(_seisei2btn5, 10);
	this->getSizeSetBtnControler()->AddSizeSetController(_seisei2btn5);
	this->_seisei2btn5->SetAtai(this->ChgFrom_1_100(udf->getIntegerForKey("EDA2_5", 3)));
	this->_seisei2btn5->SetNamaeListenner("生成壁⑤の次の生成2", "外周壁", "内壁", 1, 5);
	y_ = 0;
	x_++;

	_ban1->setTag(1);
	_susumi1btn1->setTag(1);
	_zizoku1btn1->setTag(1);
	_syototu1btn1->setTag(1);
	_seisei1btn1->setTag(1);
	_henkabtn1->setTag(1);
	_susumi2btn1->setTag(1);
	_zizoku2btn1->setTag(1);
	_syototu2btn1->setTag(1);
	_seisei2btn1->setTag(1);

	_ban2->setTag(2);
	_susumi1btn2->setTag(2);
	_zizoku1btn2->setTag(2);
	_syototu1btn2->setTag(2);
	_seisei1btn2->setTag(2);
	_henkabtn2->setTag(2);
	_susumi2btn2->setTag(2);
	_zizoku2btn2->setTag(2);
	_syototu2btn2->setTag(2);
	_seisei2btn2->setTag(2);

	_ban3->setTag(3);
	_susumi1btn3->setTag(3);
	_zizoku1btn3->setTag(3);
	_syototu1btn3->setTag(3);
	_seisei1btn3->setTag(3);
	_henkabtn3->setTag(3);
	_susumi2btn3->setTag(3);
	_zizoku2btn3->setTag(3);
	_syototu2btn3->setTag(3);
	_seisei2btn3->setTag(3);

	_ban4->setTag(4);
	_susumi1btn4->setTag(4);
	_zizoku1btn4->setTag(4);
	_syototu1btn4->setTag(4);
	_seisei1btn4->setTag(4);
	_henkabtn4->setTag(4);
	_susumi2btn4->setTag(4);
	_zizoku2btn4->setTag(4);
	_syototu2btn4->setTag(4);
	_seisei2btn4->setTag(4);

	_ban5->setTag(5);
	_susumi1btn5->setTag(5);
	_zizoku1btn5->setTag(5);
	_syototu1btn5->setTag(5);
	_seisei1btn5->setTag(5);
	_henkabtn5->setTag(5);
	_susumi2btn5->setTag(5);
	_zizoku2btn5->setTag(5);
	_syototu2btn5->setTag(5);
	_seisei2btn5->setTag(5);

	this->ShowPrmK(this->getMeiroSizeCBtn()->Value);

//	_sizeSetBtnpool.pushBack(_meiroSizeCBtn);

//	_meiroSizeBtn->getSlider()->setPosition(_meiroSizeBtn->getPosition() + Vec2(0, -100));
//	this->addChild(_meiroSizeBtn->getSlider(), 10);

//スタートボタンをセット

	this->setStartp(MenuItemImage::create("start_btn.png", "start_btn_p.png", [this](Ref* ref) {
		auto udf = UserDefault::getInstance();
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("kati.mp3");

		UserDefault::getInstance()->setIntegerForKey("LEVEL", 7);
		this->SetPrm();
		auto scene=MainScene::createScene();
		auto transition=TransitionCrossFade::create(0.5f,scene);
		Director::getInstance()->replaceScene(transition);

	}));

	auto fadeout = EaseSineIn::create(FadeOut::create(0.5));
	auto rep = RepeatForever::create(Sequence::create(fadeout, fadeout->reverse(), nullptr));
	this->getStartp()->runAction(rep);
	this->setStartM(Menu::create(this->_startp, NULL));
	this->getStartM()->setPosition(this->ctPt.x, 100);
	this->addChild(this->getStartM(), 5);

	this->setMMeder(MeiroMeder::create());

//	this->_baseNode->addChild(_sel2->getMenu(),1);
	//広告表示

	this->setAD(ImovileAd::create());
	_ad->AdShow(false, false, false, false, false, false);

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyReleased = CC_CALLBACK_2(PrmScene::onKeyReleased, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

//	this->setPrmBtn(MenuItemImage::create("tumami.png", "tumami.png", [this](Ref* ref) {
//		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("kati.mp3");
//		auto scene = TestScene::createScene();
//		auto transition = TransitionCrossFade::create(0.5, scene);
//		Director::getInstance()->replaceScene(transition);
//
//	}));
//
//	this->setMenuPrm(Menu::create(this->_prmBtn, NULL));
//	_menuPrm->setPosition(Vec2(50, 50));
//	this->addChild(this->_menuPrm, 10);

	this->SetTouchListener();
//	this->GetPrm(0);
	return true;

}
int PrmScene::ChgFrom_2_100(int x) {
	if (x == 2) {
		return 1;
	} else if (x > 2 && x <= 33) {
		return 2;
	} else if (x > 33 && x <= 66) {
		return 3;
	} else if (x > 66 && x <= 99) {
		return 4;
	} else {
		return 5;
	}
}
int PrmScene::ChgTo_2_100To(int x) {

	switch (x) {
	case 1: {
		return 2;
		break;
	}
	case 2: {
		return 25;
		break;
	}
	case 3: {
		return 50;
		break;
	}
	case 4: {
		return 75;
		break;
	}
	case 5: {
		return 100;
		break;
	}
	default: {
		return 50;
		break;
	}
	}

}
int PrmScene::ChgFrom_1_100(int x) {
	if (x == 1) {
		return 1;
	} else if (x > 2 && x <= 33) {
		return 2;
	} else if (x > 33 && x <= 66) {
		return 3;
	} else if (x > 66 && x <= 99) {
		return 4;
	} else {
		return 5;
	}
}
int PrmScene::ChgTo_1_100To(int x) {

	switch (x) {
	case 1: {
		return 1;
		break;
	}
	case 2: {
		return 25;
		break;
	}
	case 3: {
		return 50;
		break;
	}
	case 4: {
		return 75;
		break;
	}
	case 5: {
		return 100;
		break;
	}
	default: {
		return 50;
		break;
	}
	}

}

void PrmScene::ShowPrmK(int x) {
	//x番目まで表示

	Node* nd;

	for (Node* nd : this->getChildren()) {

		if (nd->getTag() > x) {
			nd->setVisible(false);
		} else {
			nd->setVisible(true);
		}

	}

}

void PrmScene::SetTouchListener() {

	this->setTouchListenner(EventListenerTouchOneByOne::create());
	_touchListener->onTouchBegan = [this](Touch* touch,Event* event) {

		//最初のタッチのみ
			const char *str0 = " PrmScene::SetTouchListener()_onTouchBegan";
			log("%s", str0);
			//	this->_slider->setPosition(touch->getLocation());
			this->ShowPrmK(this->getMeiroSizeCBtn()->Value);
//			for (Slider* tchsp:this->_touchSpritepool) {
//				const char *str1 = " PrmScene::SetTouchListener()_for (Slider* tchsp:this->_touchSpritepool)";
//				log("%s", str1);
//				tchsp->SelectTumami(touch->getLocation());
////				tchsp->SelectMinusBtn(touch->getLocation());
////				tchsp->SelectPlusBtn(touch->getLocation());
//			}

			for (SizeSetBtn* ssbtn:this->_sizeSetBtnpool) {

//				if(ssbtn->touchID!=ssbtn->getSlider()->touchID){
//					ssbtn->tchFlg=false;
//					ssbtn->getWakuBtn()->setOpacity(0);
//				}

			}

			this->getSizeSetBtnControler()->TouchOnSel(touch->getLocation());

			this->_point1.set(touch->getLocation());
			this->_point2.set(touch->getLocation());

			return true;

		};

	_touchListener->onTouchMoved = [this](Touch* touch,Event* event) {
		//this->setPosition(this->getPosition()+touch->getDelta());
		// this->_point1.set(this->_point2);
			this->_point2.set(touch->getLocation());

			if(this->getSizeSetBtnControler()->getSelectBtn()==this->getMeiroSizeCBtn()) {
				this->ShowPrmK(this->getMeiroSizeCBtn()->Value);
			}

//			for (Slider* tchsp:this->_touchSpritepool) {
//
//				tchsp->SlideMove(touch->getLocation());
//
//			}

			this->getSizeSetBtnControler()->SwaipSel(touch->getLocation());
		};
	_touchListener->onTouchEnded = [this](Touch* touch,Event* event) {

//		const char *str4 = "touch4";
//		log("%s", str4);
			this->_point1.set(Vec2::ZERO);
			this->_point2.set(Vec2::ZERO);
			if(this->getSizeSetBtnControler()->getSelectBtn()==this->getMeiroSizeCBtn()) {
				this->ShowPrmK(this->getMeiroSizeCBtn()->Value);
			}
//			for (Slider* tchsp:this->_touchSpritepool) {
//
//				tchsp->TchOff();
//
//			}
			this->getSizeSetBtnControler()->TouchOffSel(touch->getLocation());
		};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_touchListener,
			this);

}
void PrmScene::update(float dt) {

	//各ゲームステートで分岐する。

	if (this->onUpDateListener) {
		onUpDateListener(this, dt);
	}

}

void PrmScene::SetPrm() {

	auto udf = UserDefault::getInstance();
	udf->setIntegerForKey("MADER_CNT", _meiroSizeCBtn->Value);
	udf->setIntegerForKey("COURCE_X", _meiroSizeXBtn->Value);
	udf->setIntegerForKey("COURCE_Y", _meiroSizeYBtn->Value);

//	udf->setIntegerForKey("TYOKU_1", this->_susumi1btn1->Value);
//	udf->setIntegerForKey("ZIZOKU_1", this->_zizoku1btn1->Value);
//	udf->setIntegerForKey("KABE_1", this->_syototu1btn1->Value);
//	udf->setIntegerForKey("EDA_1", this->_seisei1btn1 > Value);
//	udf->setIntegerForKey("SYOKI_1", this->_henkabtn1->Value);
//	udf->setIntegerForKey("TYOKU2_1", this->_susumi2btn1->Value);
//	udf->setIntegerForKey("ZIZOKU2_1", this->_zizoku2btn1->Value);
//	udf->setIntegerForKey("KABE2_1", this->_syototu2btn1->Value);
//	udf->setIntegerForKey("EDA2_1", this->_seisei2btn1->Value);

//	udf->setIntegerForKey("TYOKU_1", this->ChgTo_2_100To(this->_susumi1btn1->Value));
//	udf->setIntegerForKey("ZIZOKU_1", this->ChgTo_2_100To(this->_zizoku1btn1->Value));
//	udf->setIntegerForKey("KABE_1", this->ChgTo_1_100To(this->_syototu1btn1->Value));
//	udf->setIntegerForKey("EDA_1", this->ChgTo_1_100To(this->_seisei1btn1 > Value));
//	udf->setIntegerForKey("SYOKI_1", this->ChgTo_1_100To(this->_henkabtn1->Value));
//	udf->setIntegerForKey("TYOKU2_1", this->ChgTo_2_100To(this->_susumi2btn1->Value));
//	udf->setIntegerForKey("ZIZOKU2_1", this->ChgTo_2_100To(this->_zizoku2btn1->Value));
//	udf->setIntegerForKey("KABE2_1", this->ChgTo_1_100To(this->_syototu2btn1->Value));
//	udf->setIntegerForKey("EDA2_1", this->ChgTo_1_100To(this->_seisei2btn1->Value));

	udf->setIntegerForKey("TYOKU_1", this->ChgTo_2_100To(this->_susumi1btn1->Value));
	udf->setIntegerForKey("ZIZOKU_1", this->ChgTo_2_100To(this->_zizoku1btn1->Value));
	udf->setIntegerForKey("KABE_1", this->ChgTo_1_100To(this->_syototu1btn1->Value));
	udf->setIntegerForKey("EDA_1", this->ChgTo_1_100To(this->_seisei1btn1->Value));
	udf->setIntegerForKey("SYOKI_1", this->ChgTo_1_100To(this->_henkabtn1->Value));
	udf->setIntegerForKey("TYOKU2_1", this->ChgTo_2_100To(this->_susumi2btn1->Value));
	udf->setIntegerForKey("ZIZOKU2_1", this->ChgTo_2_100To(this->_zizoku2btn1->Value));
	udf->setIntegerForKey("KABE2_1", this->ChgTo_1_100To(this->_syototu2btn1->Value));
	udf->setIntegerForKey("EDA2_1", this->ChgTo_1_100To(this->_seisei2btn1->Value));

	udf->setIntegerForKey("TYOKU_2", this->ChgTo_2_100To(this->_susumi1btn2->Value));
	udf->setIntegerForKey("ZIZOKU_2", this->ChgTo_2_100To(this->_zizoku1btn2->Value));
	udf->setIntegerForKey("KABE_2", this->ChgTo_1_100To(this->_syototu1btn2->Value));
	udf->setIntegerForKey("EDA_2", this->ChgTo_1_100To(this->_seisei1btn1->Value));
	udf->setIntegerForKey("SYOKI_2", this->ChgTo_1_100To(this->_henkabtn2->Value));
	udf->setIntegerForKey("TYOKU2_2", this->ChgTo_2_100To(this->_susumi2btn2->Value));
	udf->setIntegerForKey("ZIZOKU2_2", this->ChgTo_2_100To(this->_zizoku2btn2->Value));
	udf->setIntegerForKey("KABE2_2", this->ChgTo_1_100To(this->_syototu2btn2->Value));
	udf->setIntegerForKey("EDA2_2", this->ChgTo_1_100To(this->_seisei2btn2->Value));

	udf->setIntegerForKey("TYOKU_3", this->ChgTo_2_100To(this->_susumi1btn3->Value));
	udf->setIntegerForKey("ZIZOKU_3", this->ChgTo_2_100To(this->_zizoku1btn3->Value));
	udf->setIntegerForKey("KABE_3", this->ChgTo_1_100To(this->_syototu1btn3->Value));
	udf->setIntegerForKey("EDA_3", this->ChgTo_1_100To(this->_seisei1btn1->Value));
	udf->setIntegerForKey("SYOKI_3", this->ChgTo_1_100To(this->_henkabtn3->Value));
	udf->setIntegerForKey("TYOKU2_3", this->ChgTo_2_100To(this->_susumi2btn3->Value));
	udf->setIntegerForKey("ZIZOKU2_3", this->ChgTo_2_100To(this->_zizoku2btn3->Value));
	udf->setIntegerForKey("KABE2_3", this->ChgTo_1_100To(this->_syototu2btn3->Value));
	udf->setIntegerForKey("EDA2_3", this->ChgTo_1_100To(this->_seisei2btn3->Value));

	udf->setIntegerForKey("TYOKU_4", this->ChgTo_2_100To(this->_susumi1btn4->Value));
	udf->setIntegerForKey("ZIZOKU_4", this->ChgTo_2_100To(this->_zizoku1btn4->Value));
	udf->setIntegerForKey("KABE_4", this->ChgTo_1_100To(this->_syototu1btn4->Value));
	udf->setIntegerForKey("EDA_4", this->ChgTo_1_100To(this->_seisei1btn1->Value));
	udf->setIntegerForKey("SYOKI_4", this->ChgTo_1_100To(this->_henkabtn4->Value));
	udf->setIntegerForKey("TYOKU2_4", this->ChgTo_2_100To(this->_susumi2btn4->Value));
	udf->setIntegerForKey("ZIZOKU2_4", this->ChgTo_2_100To(this->_zizoku2btn4->Value));
	udf->setIntegerForKey("KABE2_4", this->ChgTo_1_100To(this->_syototu2btn4->Value));
	udf->setIntegerForKey("EDA2_4", this->ChgTo_1_100To(this->_seisei2btn4->Value));

	udf->setIntegerForKey("TYOKU_5", this->ChgTo_2_100To(this->_susumi1btn5->Value));
	udf->setIntegerForKey("ZIZOKU_5", this->ChgTo_2_100To(this->_zizoku1btn5->Value));
	udf->setIntegerForKey("KABE_5", this->ChgTo_1_100To(this->_syototu1btn5->Value));
	udf->setIntegerForKey("EDA_5", this->ChgTo_1_100To(this->_seisei1btn1->Value));
	udf->setIntegerForKey("SYOKI_5", this->ChgTo_1_100To(this->_henkabtn5->Value));
	udf->setIntegerForKey("TYOKU2_5", this->ChgTo_2_100To(this->_susumi2btn5->Value));
	udf->setIntegerForKey("ZIZOKU2_5", this->ChgTo_2_100To(this->_zizoku2btn5->Value));
	udf->setIntegerForKey("KABE2_5", this->ChgTo_1_100To(this->_syototu2btn5->Value));
	udf->setIntegerForKey("EDA2_5", this->ChgTo_1_100To(this->_seisei2btn5->Value));

}
void PrmScene::SetPrm(int index_) {

	auto udf = UserDefault::getInstance();
//	udf->setIntegerForKey("MADER_CNT", this->_slider->Value_);
//	udf->setIntegerForKey("COURCE_X", this->_slider11->Value_);
//	udf->setIntegerForKey("COURCE_Y", this->_slider12->Value_);
//	this->index = index_;
//
//	switch (this->index) {
//
//	case 0: {
//		udf->setIntegerForKey("TYOKU_0", this->_slider2->Value_);
//		udf->setIntegerForKey("EDA_0", this->_slider3->Value_);
//		udf->setIntegerForKey("ZIZOKU_0", this->_slider4->Value_);
//		udf->setIntegerForKey("KABE_0", this->_slider5->Value_);
//		udf->setIntegerForKey("SYOKI_0", this->_slider6->Value_);
//		udf->setIntegerForKey("TYOKU2_0", this->_slider7->Value_);
//		udf->setIntegerForKey("EDA2_0", this->_slider8->Value_);
//		udf->setIntegerForKey("ZIZOKU2_0", this->_slider9->Value_);
//		udf->setIntegerForKey("KABE2_0", this->_slider10->Value_);
//		break;
//	}
//	case 1: {
//		udf->setIntegerForKey("TYOKU_1", this->_slider2->Value_);
//		udf->setIntegerForKey("EDA_1", this->_slider3->Value_);
//		udf->setIntegerForKey("ZIZOKU_1", this->_slider4->Value_);
//		udf->setIntegerForKey("KABE_1", this->_slider5->Value_);
//		udf->setIntegerForKey("SYOKI_1", this->_slider6->Value_);
//		udf->setIntegerForKey("TYOKU2_1", this->_slider7->Value_);
//		udf->setIntegerForKey("EDA2_1", this->_slider8->Value_);
//		udf->setIntegerForKey("ZIZOKU2_1", this->_slider9->Value_);
//		udf->setIntegerForKey("KABE2_1", this->_slider10->Value_);
//		break;
//	}
//	case 2: {
//		udf->setIntegerForKey("TYOKU_2", this->_slider2->Value_);
//		udf->setIntegerForKey("EDA_2", this->_slider3->Value_);
//		udf->setIntegerForKey("ZIZOKU_2", this->_slider4->Value_);
//		udf->setIntegerForKey("KABE_2", this->_slider5->Value_);
//		udf->setIntegerForKey("SYOKI_2", this->_slider6->Value_);
//		udf->setIntegerForKey("TYOKU2_2", this->_slider7->Value_);
//		udf->setIntegerForKey("EDA2_2", this->_slider8->Value_);
//		udf->setIntegerForKey("ZIZOKU2_2", this->_slider9->Value_);
//		udf->setIntegerForKey("KABE2_2", this->_slider10->Value_);
//		break;
//	}
//	case 3: {
//		udf->setIntegerForKey("TYOKU_3", this->_slider2->Value_);
//		udf->setIntegerForKey("EDA_3", this->_slider3->Value_);
//		udf->setIntegerForKey("ZIZOKU_3", this->_slider4->Value_);
//		udf->setIntegerForKey("KABE_3", this->_slider5->Value_);
//		udf->setIntegerForKey("SYOKI_3", this->_slider6->Value_);
//		udf->setIntegerForKey("TYOKU2_3", this->_slider7->Value_);
//		udf->setIntegerForKey("EDA2_3", this->_slider8->Value_);
//		udf->setIntegerForKey("ZIZOKU2_3", this->_slider9->Value_);
//		udf->setIntegerForKey("KABE2_3", this->_slider10->Value_);
//		break;
//	}
//	case 4: {
//		udf->setIntegerForKey("TYOKU_4", this->_slider2->Value_);
//		udf->setIntegerForKey("EDA_4", this->_slider3->Value_);
//		udf->setIntegerForKey("ZIZOKU_4", this->_slider4->Value_);
//		udf->setIntegerForKey("KABE_4", this->_slider5->Value_);
//		udf->setIntegerForKey("SYOKI_4", this->_slider6->Value_);
//		udf->setIntegerForKey("TYOKU2_4", this->_slider7->Value_);
//		udf->setIntegerForKey("EDA2_4", this->_slider8->Value_);
//		udf->setIntegerForKey("ZIZOKU2_4", this->_slider9->Value_);
//		udf->setIntegerForKey("KABE2_4", this->_slider10->Value_);
//		break;
//	}
//	case 5: {
//		udf->setIntegerForKey("TYOKU_5", this->_slider2->Value_);
//		udf->setIntegerForKey("EDA_5", this->_slider3->Value_);
//		udf->setIntegerForKey("ZIZOKU_5", this->_slider4->Value_);
//		udf->setIntegerForKey("KABE_5", this->_slider5->Value_);
//		udf->setIntegerForKey("SYOKI_5", this->_slider6->Value_);
//		udf->setIntegerForKey("TYOKU2_5", this->_slider7->Value_);
//		udf->setIntegerForKey("EDA2_5", this->_slider8->Value_);
//		udf->setIntegerForKey("ZIZOKU2_5", this->_slider9->Value_);
//		udf->setIntegerForKey("KABE2_5", this->_slider10->Value_);
//		break;
//	}
//	case 6: {
//		udf->setIntegerForKey("TYOKU_6", this->_slider2->Value_);
//		udf->setIntegerForKey("EDA_6", this->_slider3->Value_);
//		udf->setIntegerForKey("ZIZOKU_6", this->_slider4->Value_);
//		udf->setIntegerForKey("KABE_6", this->_slider5->Value_);
//		udf->setIntegerForKey("SYOKI_6", this->_slider6->Value_);
//		udf->setIntegerForKey("TYOKU2_6", this->_slider7->Value_);
//		udf->setIntegerForKey("EDA2_6", this->_slider8->Value_);
//		udf->setIntegerForKey("ZIZOKU2_6", this->_slider9->Value_);
//		udf->setIntegerForKey("KABE2_6", this->_slider10->Value_);
//		break;
//	}
//	case 7: {
//		udf->setIntegerForKey("TYOKU_7", this->_slider2->Value_);
//		udf->setIntegerForKey("EDA_7", this->_slider3->Value_);
//		udf->setIntegerForKey("ZIZOKU_7", this->_slider4->Value_);
//		udf->setIntegerForKey("KABE_7", this->_slider5->Value_);
//		udf->setIntegerForKey("SYOKI_7", this->_slider6->Value_);
//		udf->setIntegerForKey("TYOKU2_7", this->_slider7->Value_);
//		udf->setIntegerForKey("EDA2_7", this->_slider8->Value_);
//		udf->setIntegerForKey("ZIZOKU2_7", this->_slider9->Value_);
//		udf->setIntegerForKey("KABE2_7", this->_slider10->Value_);
//		break;
//	}
//	case 8: {
//		udf->setIntegerForKey("TYOKU_8", this->_slider2->Value_);
//		udf->setIntegerForKey("EDA_8", this->_slider3->Value_);
//		udf->setIntegerForKey("ZIZOKU_8", this->_slider4->Value_);
//		udf->setIntegerForKey("KABE_8", this->_slider5->Value_);
//		udf->setIntegerForKey("SYOKI_8", this->_slider6->Value_);
//		udf->setIntegerForKey("TYOKU2_8", this->_slider7->Value_);
//		udf->setIntegerForKey("EDA2_8", this->_slider8->Value_);
//		udf->setIntegerForKey("ZIZOKU2_8", this->_slider9->Value_);
//		udf->setIntegerForKey("KABE2_8", this->_slider10->Value_);
//		break;
//	}
//	case 9: {
//		udf->setIntegerForKey("TYOKU_9", this->_slider2->Value_);
//		udf->setIntegerForKey("EDA_9", this->_slider3->Value_);
//		udf->setIntegerForKey("ZIZOKU_9", this->_slider4->Value_);
//		udf->setIntegerForKey("KABE_9", this->_slider5->Value_);
//		udf->setIntegerForKey("SYOKI_9", this->_slider6->Value_);
//		udf->setIntegerForKey("TYOKU2_9", this->_slider7->Value_);
//		udf->setIntegerForKey("EDA2_9", this->_slider8->Value_);
//		udf->setIntegerForKey("ZIZOKU2_9", this->_slider9->Value_);
//		udf->setIntegerForKey("KABE2_9", this->_slider10->Value_);
//		break;
//	}
//	case 10: {
//		udf->setIntegerForKey("TYOKU_10", this->_slider2->Value_);
//		udf->setIntegerForKey("EDA_10", this->_slider3->Value_);
//		udf->setIntegerForKey("ZIZOKU_10", this->_slider4->Value_);
//		udf->setIntegerForKey("KABE_10", this->_slider5->Value_);
//		udf->setIntegerForKey("SYOKI_10", this->_slider6->Value_);
//		udf->setIntegerForKey("TYOKU2_10", this->_slider7->Value_);
//		udf->setIntegerForKey("EDA2_10", this->_slider8->Value_);
//		udf->setIntegerForKey("ZIZOKU2_10", this->_slider9->Value_);
//		udf->setIntegerForKey("KABE2_10", this->_slider10->Value_);
//		break;
//	}
//	case 11: {
//		udf->setIntegerForKey("TYOKU_11", this->_slider2->Value_);
//		udf->setIntegerForKey("EDA_11", this->_slider3->Value_);
//		udf->setIntegerForKey("ZIZOKU_11", this->_slider4->Value_);
//		udf->setIntegerForKey("KABE_11", this->_slider5->Value_);
//		udf->setIntegerForKey("SYOKI_11", this->_slider6->Value_);
//		udf->setIntegerForKey("TYOKU2_11", this->_slider7->Value_);
//		udf->setIntegerForKey("EDA2_11", this->_slider8->Value_);
//		udf->setIntegerForKey("ZIZOKU2_11", this->_slider9->Value_);
//		udf->setIntegerForKey("KABE2_11", this->_slider10->Value_);
//		break;
//	}
//
//	}

}

void PrmScene::GetPrm(int index_) {

	auto udf = UserDefault::getInstance();
//	this->_slider->SlideMove(udf->getIntegerForKey("MADER_CNT", 5));
//	this->_slider11->SlideMove(udf->getIntegerForKey("COURCE_X", 5));
//	this->_slider12->SlideMove(udf->getIntegerForKey("COURCE_Y", 5));
//
//	this->index = index_;
//
//	switch (this->index) {
//
//	case 0: {
//		this->_slider2->SlideMove(udf->getIntegerForKey("TYOKU_0", 5));
//		this->_slider3->SlideMove(udf->getIntegerForKey("EDA_0", 5));
//		this->_slider4->SlideMove(udf->getIntegerForKey("ZIZOKU_0", 5));
//		this->_slider5->SlideMove(udf->getIntegerForKey("KABE_0", 5));
//		this->_slider6->SlideMove(udf->getIntegerForKey("SYOKI_0", 5));
//		this->_slider7->SlideMove(udf->getIntegerForKey("TYOKU2_0", 5));
//		this->_slider8->SlideMove(udf->getIntegerForKey("EDA2_0", 5));
//		this->_slider9->SlideMove(udf->getIntegerForKey("ZIZOKU2_0", 5));
//		this->_slider10->SlideMove(udf->getIntegerForKey("KABE2_0", 5));
//		break;
//	}
//	case 1: {
//		this->_slider2->SlideMove(udf->getIntegerForKey("TYOKU_1", 5));
//		this->_slider3->SlideMove(udf->getIntegerForKey("EDA_1", 5));
//		this->_slider4->SlideMove(udf->getIntegerForKey("ZIZOKU_1", 5));
//		this->_slider5->SlideMove(udf->getIntegerForKey("KABE_1", 5));
//		this->_slider6->SlideMove(udf->getIntegerForKey("SYOKI_1", 5));
//		this->_slider7->SlideMove(udf->getIntegerForKey("TYOKU2_1", 5));
//		this->_slider8->SlideMove(udf->getIntegerForKey("EDA2_1", 5));
//		this->_slider9->SlideMove(udf->getIntegerForKey("ZIZOKU2_1", 5));
//		this->_slider10->SlideMove(udf->getIntegerForKey("KABE2_1", 5));
//		break;
//	}
//	case 2: {
//		this->_slider2->SlideMove(udf->getIntegerForKey("TYOKU_2", 5));
//		this->_slider3->SlideMove(udf->getIntegerForKey("EDA_2", 5));
//		this->_slider4->SlideMove(udf->getIntegerForKey("ZIZOKU_2", 5));
//		this->_slider5->SlideMove(udf->getIntegerForKey("KABE_2", 5));
//		this->_slider6->SlideMove(udf->getIntegerForKey("SYOKI_2", 5));
//		this->_slider7->SlideMove(udf->getIntegerForKey("TYOKU2_2", 5));
//		this->_slider8->SlideMove(udf->getIntegerForKey("EDA2_2", 5));
//		this->_slider9->SlideMove(udf->getIntegerForKey("ZIZOKU2_2", 5));
//		this->_slider10->SlideMove(udf->getIntegerForKey("KABE2_2", 5));
//		break;
//	}
//	case 3: {
//		this->_slider2->SlideMove(udf->getIntegerForKey("TYOKU_3", 5));
//		this->_slider3->SlideMove(udf->getIntegerForKey("EDA_3", 5));
//		this->_slider4->SlideMove(udf->getIntegerForKey("ZIZOKU_3", 5));
//		this->_slider5->SlideMove(udf->getIntegerForKey("KABE_3", 5));
//		this->_slider6->SlideMove(udf->getIntegerForKey("SYOKI_3", 5));
//		this->_slider7->SlideMove(udf->getIntegerForKey("TYOKU2_3", 5));
//		this->_slider8->SlideMove(udf->getIntegerForKey("EDA2_3", 5));
//		this->_slider9->SlideMove(udf->getIntegerForKey("ZIZOKU2_3", 5));
//		this->_slider10->SlideMove(udf->getIntegerForKey("KABE2_3", 5));
//		break;
//	}
//	case 4: {
//		this->_slider2->SlideMove(udf->getIntegerForKey("TYOKU_4", 5));
//		this->_slider3->SlideMove(udf->getIntegerForKey("EDA_4", 5));
//		this->_slider4->SlideMove(udf->getIntegerForKey("ZIZOKU_4", 5));
//		this->_slider5->SlideMove(udf->getIntegerForKey("KABE_4", 5));
//		this->_slider6->SlideMove(udf->getIntegerForKey("SYOKI_4", 5));
//		this->_slider7->SlideMove(udf->getIntegerForKey("TYOKU2_4", 5));
//		this->_slider8->SlideMove(udf->getIntegerForKey("EDA2_4", 5));
//		this->_slider9->SlideMove(udf->getIntegerForKey("ZIZOKU2_4", 5));
//		this->_slider10->SlideMove(udf->getIntegerForKey("KABE2_4", 5));
//		break;
//	}
//	case 5: {
//		this->_slider2->SlideMove(udf->getIntegerForKey("TYOKU_5", 5));
//		this->_slider3->SlideMove(udf->getIntegerForKey("EDA_5", 5));
//		this->_slider4->SlideMove(udf->getIntegerForKey("ZIZOKU_5", 5));
//		this->_slider5->SlideMove(udf->getIntegerForKey("KABE_5", 5));
//		this->_slider6->SlideMove(udf->getIntegerForKey("SYOKI_5", 5));
//		this->_slider7->SlideMove(udf->getIntegerForKey("TYOKU2_5", 5));
//		this->_slider8->SlideMove(udf->getIntegerForKey("EDA2_5", 5));
//		this->_slider9->SlideMove(udf->getIntegerForKey("ZIZOKU2_5", 5));
//		this->_slider10->SlideMove(udf->getIntegerForKey("KABE2_5", 5));
//		break;
//	}
//	case 6: {
//		this->_slider2->SlideMove(udf->getIntegerForKey("TYOKU_6", 5));
//		this->_slider3->SlideMove(udf->getIntegerForKey("EDA_6", 5));
//		this->_slider4->SlideMove(udf->getIntegerForKey("ZIZOKU_6", 5));
//		this->_slider5->SlideMove(udf->getIntegerForKey("KABE_6", 5));
//		this->_slider6->SlideMove(udf->getIntegerForKey("SYOKI_6", 5));
//		this->_slider7->SlideMove(udf->getIntegerForKey("TYOKU2_6", 5));
//		this->_slider8->SlideMove(udf->getIntegerForKey("EDA2_6", 5));
//		this->_slider9->SlideMove(udf->getIntegerForKey("ZIZOKU2_6", 5));
//		this->_slider10->SlideMove(udf->getIntegerForKey("KABE2_6", 5));
//		break;
//	}
//	case 7: {
//		this->_slider2->SlideMove(udf->getIntegerForKey("TYOKU_7", 5));
//		this->_slider3->SlideMove(udf->getIntegerForKey("EDA_7", 5));
//		this->_slider4->SlideMove(udf->getIntegerForKey("ZIZOKU_7", 5));
//		this->_slider5->SlideMove(udf->getIntegerForKey("KABE_7", 5));
//		this->_slider6->SlideMove(udf->getIntegerForKey("SYOKI_7", 5));
//		this->_slider7->SlideMove(udf->getIntegerForKey("TYOKU2_7", 5));
//		this->_slider8->SlideMove(udf->getIntegerForKey("EDA2_7", 5));
//		this->_slider9->SlideMove(udf->getIntegerForKey("ZIZOKU2_7", 5));
//		this->_slider10->SlideMove(udf->getIntegerForKey("KABE2_7", 5));
//		break;
//	}
//	case 8: {
//		this->_slider2->SlideMove(udf->getIntegerForKey("TYOKU_8", 5));
//		this->_slider3->SlideMove(udf->getIntegerForKey("EDA_8", 5));
//		this->_slider4->SlideMove(udf->getIntegerForKey("ZIZOKU_8", 5));
//		this->_slider5->SlideMove(udf->getIntegerForKey("KABE_8", 5));
//		this->_slider6->SlideMove(udf->getIntegerForKey("SYOKI_8", 5));
//		this->_slider7->SlideMove(udf->getIntegerForKey("TYOKU2_8", 5));
//		this->_slider8->SlideMove(udf->getIntegerForKey("EDA2_8", 5));
//		this->_slider9->SlideMove(udf->getIntegerForKey("ZIZOKU2_8", 5));
//		this->_slider10->SlideMove(udf->getIntegerForKey("KABE2_8", 5));
//		break;
//	}
//	case 9: {
//		this->_slider2->SlideMove(udf->getIntegerForKey("TYOKU_9", 5));
//		this->_slider3->SlideMove(udf->getIntegerForKey("EDA_9", 5));
//		this->_slider4->SlideMove(udf->getIntegerForKey("ZIZOKU_9", 5));
//		this->_slider5->SlideMove(udf->getIntegerForKey("KABE_9", 5));
//		this->_slider6->SlideMove(udf->getIntegerForKey("SYOKI_9", 5));
//		this->_slider7->SlideMove(udf->getIntegerForKey("TYOKU2_9", 5));
//		this->_slider8->SlideMove(udf->getIntegerForKey("EDA2_9", 5));
//		this->_slider9->SlideMove(udf->getIntegerForKey("ZIZOKU2_9", 5));
//		this->_slider10->SlideMove(udf->getIntegerForKey("KABE2_9", 5));
//		break;
//	}
//	case 10: {
//		this->_slider2->SlideMove(udf->getIntegerForKey("TYOKU_10", 5));
//		this->_slider3->SlideMove(udf->getIntegerForKey("EDA_10", 5));
//		this->_slider4->SlideMove(udf->getIntegerForKey("ZIZOKU_10", 5));
//		this->_slider5->SlideMove(udf->getIntegerForKey("KABE_10", 5));
//		this->_slider6->SlideMove(udf->getIntegerForKey("SYOKI_10", 5));
//		this->_slider7->SlideMove(udf->getIntegerForKey("TYOKU2_10", 5));
//		this->_slider8->SlideMove(udf->getIntegerForKey("EDA2_10", 5));
//		this->_slider9->SlideMove(udf->getIntegerForKey("ZIZOKU2_10", 5));
//		this->_slider10->SlideMove(udf->getIntegerForKey("KABE2_10", 5));
//		break;
//	}
//	case 11: {
//		this->_slider2->SlideMove(udf->getIntegerForKey("TYOKU_11", 5));
//		this->_slider3->SlideMove(udf->getIntegerForKey("EDA_11", 5));
//		this->_slider4->SlideMove(udf->getIntegerForKey("ZIZOKU_11", 5));
//		this->_slider5->SlideMove(udf->getIntegerForKey("KABE_11", 5));
//		this->_slider6->SlideMove(udf->getIntegerForKey("SYOKI_11", 5));
//		this->_slider7->SlideMove(udf->getIntegerForKey("TYOKU2_11", 5));
//		this->_slider8->SlideMove(udf->getIntegerForKey("EDA2_11", 5));
//		this->_slider9->SlideMove(udf->getIntegerForKey("ZIZOKU2_11", 5));
//		this->_slider10->SlideMove(udf->getIntegerForKey("KABE2_11", 5));
//		break;
//	}
//
//	}

}

void PrmScene::setUpdateAction(std::function<void(PrmScene*, float)> action) {

	this->unscheduleUpdate();
	this->onUpDateListener = action;
	this->scheduleUpdate();

}

void PrmScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {

		auto scene = TitleScene::createScene();
		auto transition = TransitionCrossFade::create(0.5, scene);
		Director::getInstance()->replaceScene(transition);
	}
}

void PrmScene::onEnterTransitionDidFinish() {

	if (UserDefault::getInstance()->getBoolForKey("bgmkey", true)) {
		//	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(
		//			"bgm.mp3", true);
	}

}

