#include "HelloWorldScene.h"
#include "TitleScene.h"
#include "IMobileCocos2dxModule.h"
USING_NS_CC;

Scene* HelloWorld::createScene() {
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
HelloWorld::HelloWorld() :
		_baseNode(NULL), _startp(NULL), _startM(NULL), _backp(NULL), _backM(NULL), _debugWaku(NULL), _back0(
		NULL), _back1(NULL), _how1(NULL),_rightYazi(NULL), _leftYazi(
		NULL), _menuL(NULL), _menuR(NULL), _howToP(NULL), _menu(NULL), _menu2(NULL), _menu3(NULL), _ad(
		NULL) {
}

HelloWorld::~HelloWorld() {
	CC_SAFE_RELEASE_NULL(_baseNode);
	CC_SAFE_RELEASE_NULL(_startp);
	CC_SAFE_RELEASE_NULL(_startM);
	CC_SAFE_RELEASE_NULL(_backp);
	CC_SAFE_RELEASE_NULL(_backM);
	CC_SAFE_RELEASE_NULL(_debugWaku);
	CC_SAFE_RELEASE_NULL(_back0);
	CC_SAFE_RELEASE_NULL(_back1);
	CC_SAFE_RELEASE_NULL(_how1);

	CC_SAFE_RELEASE_NULL(_rightYazi);
	CC_SAFE_RELEASE_NULL(_leftYazi);
	CC_SAFE_RELEASE_NULL(_menuL);
	CC_SAFE_RELEASE_NULL(_menuR);
	CC_SAFE_RELEASE_NULL(_howToP);
	CC_SAFE_RELEASE_NULL(_menu);
	CC_SAFE_RELEASE_NULL(_menu2);
	CC_SAFE_RELEASE_NULL(_menu3);
	CC_SAFE_RELEASE_NULL(_ad);

}
// on "init" you need to initialize your instance
bool HelloWorld::init() {
	//////////////////////////////
	// 1. super init first
	if (!Layer::init()) {
		return false;
	}

	auto director = Director::getInstance();
	auto oto = CocosDenshion::SimpleAudioEngine::getInstance();
	winSize = director->getWinSize();
	ctPt.set(winSize.width / 2, winSize.height / 2);

	this->setBaseNode(Node::create());
	this->_baseNode->setPosition(winSize.width, 0);
	auto move_ = EaseSineOut::create(MoveTo::create(0.5f, Vec2::ZERO));
	this->_baseNode->runAction(move_);

	this->setBack0(Sprite::create("back4.png"));
	_back0->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2));
	this->addChild(_back0, 5);
	this->setBack1(Sprite::create("back5.png"));
	_back1->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2));
	this->addChild(_back1, 1);

	Sprite * ht = Sprite::create("howto.png");

	ht->setPosition(ctPt.x, winSize.height - 120);
	this->addChild(ht, 6);

	this->setHow1(Sprite::create("how1.png"));
	_how1->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2));
	this->_baseNode->addChild(_how1, 2);



	//スタートボタンをセット

	this->setStartp(MenuItemImage::create("start_btn.png", "start_btn_p.png", [this](Ref* ref) {
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("kati.mp3");

		auto move_ = EaseSineIn::create(MoveTo::create(0.5f, Vec2(-winSize.width, 0)));
		this->_baseNode->runAction(move_);
		auto delay_=DelayTime::create(0.5f);
		auto func_=CallFuncN::create([this](Ref* ref) {
					auto scene=SelectScene::createScene();
					auto transition=TransitionCrossFade::create(0.5f,scene);
					Director::getInstance()->replaceScene(transition);
				});
		auto seq_=Sequence::create(delay_,func_,NULL);
		this->runAction(seq_);

	}));

	auto fadeout = EaseSineIn::create(FadeOut::create(0.5));
	auto rep = RepeatForever::create(Sequence::create(fadeout, fadeout->reverse(), nullptr));
	this->getStartp()->runAction(rep);
	this->setStartM(Menu::create(this->_startp, NULL));
	this->getStartM()->setPosition(this->ctPt.x - 100, 100);
	this->addChild(this->getStartM(), 7);

	this->setBackp(MenuItemImage::create("modoru_btn.png", "modoru_p_btn.png", [this](Ref* ref) {
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("kati.mp3");

		auto move_ = EaseSineIn::create(MoveTo::create(0.5f, Vec2(-winSize.width, 0)));
		this->_baseNode->runAction(move_);
		auto delay_=DelayTime::create(0.5f);
		auto func_=CallFuncN::create([this](Ref* ref) {
					auto scene=TitleScene::createScene();
					auto transition=TransitionCrossFade::create(0.5f,scene);
					Director::getInstance()->replaceScene(transition);
				});
		auto seq_=Sequence::create(delay_,func_,NULL);
		this->runAction(seq_);
	}));

	this->setBackM(Menu::create(this->_backp, NULL));
	_backM->setPosition(this->ctPt.x + 200, 100);
	this->addChild(_backM, 7);

//	this->setLeftYazi(MenuItemImage::create("yazi_l.png", "yazi_lp.png", [this](Ref* ref) {
//		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("kati.mp3");
//
//		this->pageInt--;
//
//		if(this->pageInt<=0) {
//			this->pageInt=4;
//		}
//
//		this->ChangePage(this->pageInt);
//
//	}));
//	this->setMenuL(Menu::create(this->_leftYazi, NULL));
//	_menuL->setPosition(ctPt + Vec2(-170, -260));
////	this->_baseNode->addChild(_menuL, 5);
//
//	this->setRightYazi(MenuItemImage::create("yazi_r.png", "yazi_rp.png", [this](Ref* ref) {
//		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("kati.mp3");
//		this->pageInt++;
//
//		if(this->pageInt>=5) {
//			this->pageInt=1;
//		}
//
//		this->ChangePage(this->pageInt);
//	}));
//
//	this->setMenuR(Menu::create(this->_rightYazi, NULL));
//	_menuR->setPosition(ctPt + Vec2(170, -260));
//
//	this->ChangePage(this->pageInt);
////	this->_baseNode->addChild(_menuR, 5);
//	//imobile add
	this->setAD(ImovileAd::create());
	_ad->AdShow(false, false,false, false, false, false);

	return true;
}

void HelloWorld::ChangePage(int i) {

	switch (i) {

	case 1: {

		this->_how1->setVisible(true);
//		this->_how2->setVisible(false);
//		this->_how3->setVisible(false);
//		this->_how4->setVisible(false);
		break;
	}
	case 2: {

		this->_how1->setVisible(false);
//		this->_how2->setVisible(true);
//		this->_how3->setVisible(false);
//		this->_how4->setVisible(false);
		break;
	}
	case 3: {

		this->_how1->setVisible(false);
//		this->_how2->setVisible(false);
//		this->_how3->setVisible(true);
//		this->_how4->setVisible(false);
		break;
	}
	case 4: {

		this->_how1->setVisible(false);
//		this->_how2->setVisible(false);
//		this->_how3->setVisible(false);
//		this->_how4->setVisible(true);
		break;
	}
	}

}

void HelloWorld::onEnterTransitionDidFinish() {

	this->addChild(this->_baseNode, 2);
//	this->addChild(_title2, 3);
//	this->addChild(_title1, 3);
//	this->addChild(_title3, 3);
}

void HelloWorld::menuCloseCallback(Ref* pSender) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
