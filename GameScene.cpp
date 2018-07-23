#include "GameScene.h"
#include "ImovileAd.h"

USING_NS_CC;

Scene* GameScene::createScene() {

	auto scene = Scene::create();

	auto layer = GameScene::create();

	scene->addChild(layer);

	// return the scene
	return scene;
}
GameScene::GameScene() :
		_ad(NULL) {

}

GameScene::~GameScene() {
	CC_SAFE_RELEASE_NULL(_ad);
}

// on "init" you need to initialize your instance
bool GameScene::init() {

	if (!Layer::init()) {
		return false;
	}

	auto director = Director::getInstance();
	winSize = director->getWinSize();
	this->ctPt.set(winSize.width / 2, winSize.height / 2);

	//imovileAdをセットする。
	this->setAD(ImovileAd::create());
	this->getAD()->txtFlg = false;
	this->getAD()->instFlg = false;

	return true;
}

