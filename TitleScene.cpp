#include "TitleScene.h"
#include "MainScene.h"
#include "Ball.h"
#include "TestScene.h"
#include "SelectScene.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "IMobileCocos2dxModule.h"
#include "platform/android/jni/JniHelper.h"

// �Ăяo�����\�b�h��������Ă���p�b�P�[�W����java�N���X��
#define  CLASS_NAME "org/cocos2dx/cpp/AppActivity"
#define TWEET "tweet"
#define OPENRNK "openRankPark"
#define SENDSCR "sendRankParkScore"
#define WRITEDETA "writeDeta"
#define READDETA "readDeta"

//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//#include "InterfaceJNI.h"
//#endif

USING_NS_CC;

const char* BGM_KEY = "bgmkey";
//const char* BEST_TIME="besttime";
//const char* AD_VIEW_ID="adViewId";

//MenuItemImage* musicOnBtn;
//MenuItemImage* musicOffBtn;

Scene* TitleScene::createScene() {

	auto scene = Scene::create();

	auto layer = TitleScene::create();

	scene->addChild(layer);

	// return the scene
	return scene;
}
TitleScene::TitleScene() :
		_musicOffBtn(NULL), _musicOnBtn(NULL), _tweetp(NULL), _ball(NULL), _background(
		NULL), _background2(NULL), _menu1(NULL), _menu2(NULL), _menu3(NULL), _menu4(NULL), _menu5(
		NULL), _menu6(NULL), _menu7(NULL), _startp(
		NULL), _rankingp(NULL), _howTop(NULL), _yubip(NULL), _sumahop(NULL), _title2(NULL), _ad(NULL), _ttlPoint(
		NULL), _baseNode(NULL) {

}

TitleScene::~TitleScene() {

	CC_SAFE_RELEASE_NULL(_title2);

	CC_SAFE_RELEASE_NULL(_musicOnBtn);
	CC_SAFE_RELEASE_NULL(_musicOffBtn);
	CC_SAFE_RELEASE_NULL(_tweetp);
	CC_SAFE_RELEASE_NULL(_ball);
	CC_SAFE_RELEASE_NULL(_background);
	CC_SAFE_RELEASE_NULL(_background2);
	CC_SAFE_RELEASE_NULL(_menu1);
	CC_SAFE_RELEASE_NULL(_menu2);
	CC_SAFE_RELEASE_NULL(_menu3);
	CC_SAFE_RELEASE_NULL(_menu4);
	CC_SAFE_RELEASE_NULL(_menu5);
	CC_SAFE_RELEASE_NULL(_menu6);
	CC_SAFE_RELEASE_NULL(_startp);
	CC_SAFE_RELEASE_NULL(_rankingp);
	CC_SAFE_RELEASE_NULL(_yubip);
	CC_SAFE_RELEASE_NULL(_sumahop);
	CC_SAFE_RELEASE_NULL(_ad);
	CC_SAFE_RELEASE_NULL(_ttlPoint);
	CC_SAFE_RELEASE_NULL(_baseNode);
}

// on "init" you need to initialize your instance
bool TitleScene::init() {

	if (!Layer::init()) {
		return false;
	}

	auto oto = CocosDenshion::SimpleAudioEngine::getInstance();
	auto director = Director::getInstance();
	winSize.setSize(director->getWinSize().width, director->getWinSize().height);

	this->ctPt.set(winSize.width / 2, winSize.height / 2);

	this->setBackGround(Sprite::create("back4.png"));
	_background->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2));
	this->addChild(_background, 5);

	this->setBackGround2(Sprite::create("back5.png"));
	_background2->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2));
	this->addChild(_background2, 1);

	this->setBaseNode(Node::create());
	this->_baseNode->setPosition(winSize.width, 0);
	auto move_ = EaseSineOut::create(MoveTo::create(0.5f, Vec2::ZERO));
	this->_baseNode->runAction(move_);

	this->setTitle2(Sprite::create("title4.png"));
	_title2->setPosition(this->ctPt + Vec2(0, 200));
//	_title2->setScale(1.0f);
//	_title2->setOpacity(0);
//	auto fade_ = FadeIn::create(1);
//	_title2->runAction(fade_);

	this->_baseNode->addChild(_title2, 2);

	auto udf = UserDefault::getInstance();
	udf->setIntegerForKey("INDEX", 1);
	udf->setIntegerForKey("STAGECNT", 1);

//	this->setTitle1(Sprite::create("title1.png"));
//	_title1->setPosition(_title2->getPosition() + Vec2(-100, 110));
//
//	_title1->setScale(0);
//
//	auto big1_ = EaseElasticOut::create(ScaleTo::create(1, 0.8f));
//	auto rot1_ = EaseElasticOut::create(RotateTo::create(1, -20));
//	auto seq_ = Spawn::create(big1_, rot1_, NULL);
//
//	_title1->runAction(seq_);

//	this->setTitle3(Sprite::create("title3.png"));
//
//	Vec2 pt1;
//	pt1.set(_title2->getPosition() + Vec2(100, -110));
//	Vec2 pt2(pt1);
//	pt2 += Vec2(400, 0);
//	_title3->setScale(0.8f);
//	_title3->setPosition(pt2);
//
//	auto move2_ = EaseElasticOut::create(MoveTo::create(2, pt1));
//
//	_title3->runAction(move2_);

//this->addChild(_title3, 3);
//start
//	auto udf = UserDefault::getInstance();
//	udf->setIntegerForKey("restTime", 0);
//	udf->setIntegerForKey("nowLvl", 1);
//	udf->setIntegerForKey("dctCnt", 0);
//	udf->setIntegerForKey("mapCnt", 0);
//	udf->setIntegerForKey("spdCnt", 0);
//	udf->setIntegerForKey("bomCnt", 0);
//	udf->setBoolForKey("retryFlg", false);
//	udf->setIntegerForKey("MEIROINDEX", 0);
//	udf->setIntegerForKey("STAGECNT", 0);
//	udf->setIntegerForKey("ADCNT", 0);

	this->setStartp(MenuItemImage::create("start_btn.png", "start_btn_p.png", [this](Ref* ref) {
		auto udf = UserDefault::getInstance();
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("kati.mp3");
		//	if (udf->getBoolForKey("grvFlg",false)) {

			//		udf->setIntegerForKey("MEIROINDEX",0);
			//		udf->setIntegerForKey("STAGECNT",0);
			//		udf->setIntegerForKey("nowLvl",1);
			//		udf->setIntegerForKey("LEVEL",1);

			//		auto scene = MainScene::createScene();
			//		auto transition = TransitionCrossFade::create(0.5, scene);
			//		Director::getInstance()->replaceScene(transition);
			//	} else {

			auto move_ = EaseSineIn::create(MoveTo::create(0.5f, Vec2(-winSize.width, 0)));
			this->_baseNode->runAction(move_);


			auto delay_=DelayTime::create(0.5f);
			auto func_=CallFuncN::create([this](Ref* ref){
						auto scene=SelectScene::createScene();
						auto transition=TransitionCrossFade::create(0.5f,scene);
						Director::getInstance()->replaceScene(transition);
			});
			auto seq_=Sequence::create(delay_,func_,NULL);
			this->runAction(seq_);


//			auto scene=MainScene::createScene();
//			auto transition=TransitionCrossFade::create(0.5,scene);
//			Director::getInstance()->replaceScene(transition);

			//	}
			/*
			 CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("kati.mp3");
			 auto scene=MainScene::createScene();
			 auto transition=TransitionCrossFade::create(0.5,scene);
			 Director::getInstance()->replaceScene(transition);
			 */

		}));

	auto fadeout = EaseSineIn::create(FadeOut::create(0.5));
	auto rep = RepeatForever::create(Sequence::create(fadeout, fadeout->reverse(), nullptr));
	this->getStartp()->runAction(rep);



	this->setHowTop(MenuItemImage::create("howto_btn.png", "howto_btn_p.png", [this](Ref* ref) {
		auto scene=HelloWorld::createScene();
		auto transition=TransitionCrossFade::create(0.5,scene);
		Director::getInstance()->replaceScene(transition);
	}));

	this->setMenu1(Menu::create(_startp, NULL));
	_menu1->setAnchorPoint(Vec2(0.5, 1));
	_menu1->alignItemsVerticallyWithPadding(10);
	_menu1->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2 - 70));
	this->_baseNode->addChild(_menu1, 2);

	this->setMusicOnBtn(
			MenuItemImage::create("music_btn.png", "music_p_btn.png",
					[this](Ref* ref) {
						UserDefault::getInstance()->setBoolForKey(BGM_KEY,!UserDefault::getInstance()->getBoolForKey(BGM_KEY));
						//UserDefault::getInstance()->setBoolForKey("grvFlg",true);
						CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
						this->getMusicOnBtn()->setVisible(false);
						this->getMusicOffBtn()->setVisible(true);
					}));
	this->setMenu2(Menu::create(_musicOnBtn, NULL));
	_menu2->alignItemsHorizontallyWithPadding(20);
	_menu2->setPosition(Vec2(150, 350));
	this->_baseNode->addChild(_menu2);

	this->setMusicOffBtn(
			MenuItemImage::create("music_not_btn.png", "music_not_p_btn.png",
					[this](Ref* ref) {
						UserDefault::getInstance()->setBoolForKey(BGM_KEY,!UserDefault::getInstance()->getBoolForKey(BGM_KEY));
						//UserDefault::getInstance()->setBoolForKey("grvFlg",false);
						//CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(
						//	"bgm.mp3", true);
						this->getMusicOnBtn()->setVisible(true);
						this->getMusicOffBtn()->setVisible(false);
					}));

	this->setMenu3(Menu::create(_musicOffBtn, NULL));
	_menu3->alignItemsHorizontallyWithPadding(20);
	_menu3->setPosition(Vec2(150, 350));
	this->_baseNode->addChild(_menu3);

	if (UserDefault::getInstance()->getBoolForKey(BGM_KEY, true)) {
		_musicOffBtn->setVisible(false);
		_musicOnBtn->setVisible(true);
	} else {
		_musicOffBtn->setVisible(true);
		_musicOnBtn->setVisible(false);
	}

	this->setTweetp(MenuItemImage::create("mail_btn.png", "mail_p_btn.png", [this](Ref* ref) {
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

			this->tweet();
//#endif

		}));

	this->setMenu4(Menu::create(_tweetp, NULL));
	_menu4->alignItemsHorizontallyWithPadding(20);
	_menu4->setPosition(Vec2(winSize.width - 150, 350));
	this->_baseNode->addChild(_menu4);

	//���샂�[�h�̐؂�ւ�


	this->setMenu5(Menu::create(_howTop, NULL));
	_menu5->alignItemsHorizontallyWithPadding(20);
	_menu5->setPosition(Vec2(winSize.width / 2, 350));
	this->_baseNode->addChild(_menu5);

	this->setYubip(MenuItemImage::create("yubibtn.png", "yubibtn_p.png", [this](Ref* ref) {

		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("kati.mp3");
		auto scene = TestScene::createScene();
		auto transition = TransitionCrossFade::create(0.5, scene);
		Director::getInstance()->replaceScene(transition);

	}));

	this->setMenu6(Menu::create(_yubip, NULL));
	_menu6->alignItemsHorizontallyWithPadding(20);
	_menu6->setPosition(Vec2(winSize.width / 2, 100));
	this->addChild(_menu6);

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyReleased = CC_CALLBACK_2(TitleScene::onKeyReleased, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	//広告表示

	this->setAD(ImovileAd::create());
	this->_ad->AdShow(false, true, false, false, false, true);

//	this->AdShow(false,true,false,false,false,true);

	return true;
}

void TitleScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
		Director::sharedDirector()->end();
	}
}
void TitleScene::onEnterTransitionDidFinish() {
	if (UserDefault::getInstance()->getBoolForKey(BGM_KEY, true)) {
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("open.mp3", false);
	}
	this->addChild(this->_baseNode, 2);
//	this->addChild(_title2, 3);
//	this->addChild(_title1, 3);
//	this->addChild(_title3, 3);
}

void TitleScene::openRankPark() {
	JniMethodInfo t;
	// �N���X���ƃ��\�b�h�����w�肵�܂��B
	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, OPENRNK, "()V")) {
		// void�Ȃ̂ŁACallStaticVoidMethod�ŌĂ�
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		// ���
		t.env->DeleteLocalRef(t.classID);
	}
}
void TitleScene::sendRankParkScore(int value) {
	JniMethodInfo t;
	// �N���X���ƃ��\�b�h�����w�肵�܂��B
	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, SENDSCR, "(I)V")) {
		// void�Ȃ̂ŁACallStaticVoidMethod�ŌĂ�
		t.env->CallStaticVoidMethod(t.classID, t.methodID, value);
		// ���
		t.env->DeleteLocalRef(t.classID);
	}
}
void TitleScene::tweet() {
	JniMethodInfo t;
	// �N���X���ƃ��\�b�h�����w�肵�܂��B
	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, TWEET, "(I)V")) {
		// void�Ȃ̂ŁACallStaticVoidMethod�ŌĂ�
		int value = UserDefault::getInstance()->getIntegerForKey("TTLPOINT", 0);
		t.env->CallStaticVoidMethod(t.classID, t.methodID, value);
		// ���
		t.env->DeleteLocalRef(t.classID);
	}

}

