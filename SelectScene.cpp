#include "SelectScene.h"
#include "TitleScene.h"
#include "IMobileCocos2dxModule.h"
#include "ParticleSystemPool.h"
#include "MainScene.h"
#include "MainScene_Debug.h"
#include "MeiroMeder.h"
#include "TestScene.h"
#include "cmath"

USING_NS_CC;

//重力ベクトル
const Vec2 GRAVITY_ACCERATION = Vec2(0, -10);
const Vec2 NONGRAVITY = Vec2(0, 0);

SelectScene::SelectScene() :
		_mMeder(NULL), _backGround(NULL), _backGround2(NULL), _stageLabel(NULL), _level(1), _nomove1(
		NULL), _nomove2(NULL), _nomove3(
		NULL), _touchListener(NULL), _selectStage(NULL), _stg(NULL), _ad(NULL), _prmBtn(NULL), _menuPrm(NULL), _baseNode(
		NULL), _sel1(NULL), _sel2(NULL), _sel3(
		NULL), _sel4(NULL), _sel5(NULL), _sel6(NULL), _sel7(NULL), _selYaziTop(NULL), _selYaziDown(NULL), _fstTch(
		NULL) {
}

SelectScene::~SelectScene() {
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
	CC_SAFE_RELEASE_NULL(_stg);
	CC_SAFE_RELEASE_NULL(_ad);
	CC_SAFE_RELEASE_NULL(_baseNode);
	CC_SAFE_RELEASE_NULL(_sel1);
	CC_SAFE_RELEASE_NULL(_sel2);
	CC_SAFE_RELEASE_NULL(_sel3);
	CC_SAFE_RELEASE_NULL(_sel4);
	CC_SAFE_RELEASE_NULL(_sel5);
	CC_SAFE_RELEASE_NULL(_sel6);
	CC_SAFE_RELEASE_NULL(_sel7);
	CC_SAFE_RELEASE_NULL(_selYaziTop);
	CC_SAFE_RELEASE_NULL(_selYaziDown);
	CC_SAFE_RELEASE_NULL(_fstTch);
}

Scene* SelectScene::createScene() {
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
	 auto layer = SelectScene::create();

	 // add layer as a child to scene
	 scene->addChild(layer);

	 // return the scene
	 return scene;

	 */

	auto scene = Scene::create();

	auto layer = SelectScene::create();

	scene->addChild(layer);

	// return the scene
	return scene;

}

// on "init" you need to initialize your instance
bool SelectScene::init() {

	if (!Layer::init()) {
		return false;
	}
	//this->setScale(0.5f);
//毎回のアップデート

	auto director = Director::getInstance();
	winSize.setSize(director->getWinSize().width, director->getWinSize().height);

	this->ctPt.set(winSize.width / 2, winSize.height / 2);

	this->setnoMove1(ParallaxNode::create());
	this->addChild(_nomove1);
	this->setnoMove2(ParallaxNode::create());
	this->addChild(_nomove2, 6);
	this->setnoMove3(ParallaxNode::create());
	this->addChild(_nomove3, 1);

	this->setSelYaziTop(Sprite::create("selyazi.png"));
	this->_selYaziTop->setPosition(ctPt.x, winSize.height - 250);

	this->setSelYaziDown(Sprite::create("selyazi.png"));
	this->_selYaziDown->setRotation(180);
	this->_selYaziDown->setPosition(ctPt.x, 250);

	this->setBackGround(Sprite::create("back4.png"));
	_backGround->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2));
	this->addChild(_backGround, 5);

	this->setSelectStage(Sprite::create("selectlevel.png"));
	this->_selectStage->setPosition(ctPt.x, winSize.height - 100);
	this->addChild(_selectStage, 6);

	this->setBackGround2(Sprite::create("back5.png"));
	_backGround2->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2));
	this->addChild(_backGround2);

	this->setBaseNode(Sprite2::create());
	this->_baseNode->setPosition(winSize.width, UserDefault::getInstance()->getIntegerForKey("SELECT_Y", 0));
	auto move_ = EaseSineOut::create(
			MoveTo::create(0.5f, Vec2(0, UserDefault::getInstance()->getIntegerForKey("SELECT_Y", 0))));
	auto func_ = CallFuncN::create([this](Ref* ref) {

		this->scheduleUpdate();
		this->getnoMove3()->addChild(_selYaziTop,1,Vec2::ZERO,_selYaziTop->getPosition());
		this->getnoMove3()->addChild(_selYaziDown,1,Vec2::ZERO,_selYaziDown->getPosition());
		this->SetTouchListener();

	});
	auto seq_ = Sequence::create(move_, func_, NULL);

	this->_baseNode->runAction(seq_);

	auto udf = UserDefault::getInstance();
	this->setLevel(udf->getIntegerForKey("LEVEL", 1));

	//degugselectデバックモードにする場合はtRUE
	udf->setBoolForKey("DEBUG", false);

	//ラベルを表示

	//ステージを表示

	this->setMMeder(MeiroMeder::create());

	this->setSel1(SelTag::create());
	this->_sel1->setPosition(ctPt.x, ctPt.y);
	this->_sel1->SetLevel(1);

	if (this->getMMeder()->GetLevelStatus(1) > -1) {
		this->_sel1->SetMemoText(
				"超簡単!\nまずはここから！\nクリヤ回数：" + StringUtils::toString((int) this->getMMeder()->GetLevelStatus(1)));
	} else {
		this->_sel1->SetMemoText("超簡単!\nまずはここから！");
	}
	this->_sel1->SetLock(this->getMMeder()->GetLevelStatus(1) < 0);
	this->_selTags.pushBack(this->_sel1);
	this->_baseNode->addChild(_sel1, 2);

	this->setSel2(SelTag::create());
	this->_sel2->setPosition(ctPt.x, ctPt.y - 500 * 1);
	this->_sel2->SetLevel(2);
	if (this->getMMeder()->GetLevelStatus(2) > -1) {
		this->_sel2->SetMemoText(
				"普通な感じ\nクリヤすると\nちょっぴり\nうれしい\nクリヤ回数："
						+ StringUtils::toString((int) this->getMMeder()->GetLevelStatus(2)));
	} else {
		this->_sel2->SetMemoText("普通な感じ\nクリヤすると\nちょっぴり\nうれしい");
	}
	this->_sel2->SetLock(this->getMMeder()->GetLevelStatus(2) < 0);
	this->_selTags.pushBack(this->_sel2);
	this->_baseNode->addChild(_sel2, 2);

	this->setSel3(SelTag::create());
	this->_sel3->setPosition(ctPt.x, ctPt.y - 500 * 2);
	this->_sel3->SetLevel(3);
	if (this->getMMeder()->GetLevelStatus(3) > -1) {
		this->_sel3->SetMemoText(
				"まあまあムズい\nクリヤすると\nそれなりに\nうれしい\nクリヤ回数："
						+ StringUtils::toString((int) this->getMMeder()->GetLevelStatus(3)));
	} else {
		this->_sel3->SetMemoText("まあまあムズい\nクリヤすると\nそれなりに\nうれしい");
	}
	this->_sel3->SetLock(this->getMMeder()->GetLevelStatus(3) < 0);
	this->_selTags.pushBack(this->_sel3);
	this->_baseNode->addChild(_sel3, 2);

	this->setSel4(SelTag::create());
	this->_sel4->setPosition(ctPt.x, ctPt.y - 500 * 3);
	this->_sel4->SetLevel(4);
	if (this->getMMeder()->GetLevelStatus(4) > -1) {
		this->_sel4->SetMemoText(
				"少し骨がある\n空き時間に\nどうぞ!\nクリヤ回数："
						+ StringUtils::toString((int) this->getMMeder()->GetLevelStatus(4)));
	} else {
		this->_sel4->SetMemoText("少し骨がある\n空き時間に\nどうぞ!");
	}
	this->_sel4->SetLock(this->getMMeder()->GetLevelStatus(4) < 0);
	this->_selTags.pushBack(this->_sel4);
	this->_baseNode->addChild(_sel4, 2);

	this->setSel5(SelTag::create());
	this->_sel5->setPosition(ctPt.x, ctPt.y - 500 * 4);
	this->_sel5->SetLevel(5);
	if (this->getMMeder()->GetLevelStatus(5) > -1) {
		this->_sel5->SetMemoText(
				"チョイムズ\nじっくり迷路\nを楽しむ時に\nどうぞ!\nクリヤ回数："
						+ StringUtils::toString((int) this->getMMeder()->GetLevelStatus(5)));
	} else {
		this->_sel5->SetMemoText("チョイムズ\nじっくり迷路\nを楽しむ時に\nどうぞ!");
	}
	this->_sel5->SetLock(this->getMMeder()->GetLevelStatus(5) < 0);
	this->_selTags.pushBack(this->_sel5);
	this->_baseNode->addChild(_sel5, 2);

	this->setSel6(SelTag::create());
	this->_sel6->setPosition(ctPt.x, ctPt.y - 500 * 5);
	this->_sel6->SetLevel(6);
	if (this->getMMeder()->GetLevelStatus(6) > -1) {
		this->_sel6->SetMemoText(
				"超ムズレベル\n地図を見ずに\nクリヤで来たら\n天才!?\nクリヤ回数："
						+ StringUtils::toString((int) this->getMMeder()->GetLevelStatus(6)));
	} else {
		this->_sel6->SetMemoText("超ムズレベル\n地図を見ずに\nクリヤで来たら\n天才!?");
	}
	this->_sel6->SetLock(this->getMMeder()->GetLevelStatus(6) < 0);
	this->_selTags.pushBack(this->_sel6);
	this->_baseNode->addChild(_sel6, 2);

	this->setSel7(SelTag::create());
	this->_sel7->setPosition(ctPt.x, ctPt.y - 500 * 6);
	this->_sel7->SetLevel(7);
	if (this->getMMeder()->GetLevelStatus(7) > -1) {
		this->_sel7->SetMemoText(
				"迷路を自由に\n作れるぞ！\nクリヤ回数：" + StringUtils::toString((int) this->getMMeder()->GetLevelStatus(7)));
	} else {
		this->_sel7->SetMemoText(
					"迷路を自由に\n作れるぞ！");
	}
	this->_sel7->SetLock(this->getMMeder()->GetLevelStatus(7) < 0);
	this->_selTags.pushBack(this->_sel7);
	this->_baseNode->addChild(_sel7, 2);

//	this->_baseNode->addChild(_sel2->getMenu(),1);
	//広告表示

	this->setAD(ImovileAd::create());
	_ad->AdShow(false, true, false, false, false, false);

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyReleased = CC_CALLBACK_2(SelectScene::onKeyReleased, this);
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

	return true;

}

void SelectScene::SetTouchListener() {

	const char *str = "SetTouchListener() ";
	log("%s", str);
//タッチイベントをセットする。
	this->setTouchListenner(EventListenerTouchOneByOne::create());
	_touchListener->onTouchBegan = [this](Touch* touch,Event* event) {

		if(_fstTch==NULL ) {

			_point1.set(touch->getLocation());
			_point2.set(touch->getLocation());
			const char *str = "TouchBegan";
			log("%s", str);

			for(SelTag* tg:this->_selTags) {
//				const char *str = "for(SelTag* tg:this->_selTags)";
//				log("%s", str);
			tg->TouchOn(-this->_baseNode->getPosition()+_point1);
			fstSet_=false;
		}

		this->setFstTch(touch);
		tch_=true;
		moveVelo =0;
		return true;

	}

//		Director::getInstance()->getEventDispatcher()->removeEventListener(this->getTouchListenner());
	return false;

};

	_touchListener->onTouchMoved = [this](Touch* touch,Event* event) {

		if(_fstTch==touch) {
			_point2_before.set(_point2);
			_point2.set(touch->getLocation());
			const char *str = "TouchMove1";
			log("%s", str);
			if(_point1.y>200 && _point1.y<winSize.height-200) {

				if((this->_baseNode->getPosition().y+touch->getDelta().y)<moveDownY) {
					this->_baseNode->setPosition(0,moveDownY);
					this->_selYaziDown->setVisible(false);
					this->_selYaziTop->setVisible(true);
				} else if((this->_baseNode->getPosition().y+touch->getDelta().y)>moveTopY) {
					this->_baseNode->setPosition(0,moveTopY);
					this->_selYaziDown->setVisible(true);
					this->_selYaziTop->setVisible(false);
				} else {
					this->_baseNode->setPosition(0,this->_baseNode->getPosition().y+touch->getDelta().y);
					this->_selYaziDown->setVisible(true);
					this->_selYaziTop->setVisible(true);
				}

			}
			for(SelTag* tg:this->_selTags) {

				tg->Swaip(-this->_baseNode->getPosition()+_point1,-this->_baseNode->getPosition()+_point2);

			}

		}
	};

	_touchListener->onTouchEnded = [this](Touch* touch,Event* event) {
		if(_fstTch==touch) {
			_fstTch=NULL;
			tch_=false;
			for(SelTag* tg:this->_selTags) {
				const char *str = "tg->TouchOff();";
				log("%s", str);
				tg->TouchOff();

			}

		}

	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_touchListener,
			this);

}
void SelectScene::update(float dt) {

	//各ゲームステートで分岐する。

	for (SelTag* tg : this->_selTags) {

//			if (pn->getPenState() == Pen::PenState::SHOWUP && pn != this->getSelPen()) {
//
//				if (this->getSelPen()) {
//
//					this->getSelPen()->setPenState(Pen::PenState::SHOWOFF);
//					this->getSelPen()->fstFlg = true;
//
//				}
//				const char *str = "PenChoise::update(float dt)";
//				log("%s", str);
//				this->setSelPen(pn);
//				if (this->_gameDeta->GetPenUseSts(this->getSelPen()->getPenType()) == 1) {
//					this->_gameDeta->SetPenUseSts(this->getSelPen()->getPenType(), 2);
//				}
//				this->getPenSel()->setVisible(pn->useFlg);
//			}

	}

	//	枠の慣性の動き
	if (tch_) {
		moveVelo = moveVelo * 0.5 + 0.5 * (_baseNode->getPosition().y - beforePt) / dt;
		beforePt = _baseNode->getPosition().y;
	} else {

		if ((this->_baseNode->getPosition().y) <= moveDownY) {
			this->_baseNode->setPosition(0, moveDownY);
			this->_selYaziDown->setVisible(false);
			this->_selYaziTop->setVisible(true);
			moveVelo = 0;
		} else if ((this->_baseNode->getPosition().y) >= moveTopY) {
			this->_baseNode->setPosition(0, moveTopY);
			this->_selYaziDown->setVisible(true);
			this->_selYaziTop->setVisible(false);
			moveVelo = 0;
		} else {

			this->_selYaziDown->setVisible(true);
			this->_selYaziTop->setVisible(true);

			if (moveVelo > 800) {
				moveVelo -= (1500 * dt);
				this->_baseNode->setPosition(0, this->_baseNode->getPosition().y + moveVelo * dt);
			} else if (moveVelo < -800) {
				moveVelo += (1500 * dt);
				this->_baseNode->setPosition(0, this->_baseNode->getPosition().y + moveVelo * dt);
			} else {

				if (!fstSet_) {
					fstSet_ = true;
//				if (moveVelo >= -300 && moveVelo <= 300) {
					moveVelo = 700;
//				} else if (moveVelo <= -300) {
//					moveVelo *= -1;
//				}
					int a = (int) this->_baseNode->getPosition().y + 250;
					int b = 500;

					Y = a / b;
					Y *= 500;
//					Y = 1000;
					this->_baseNode->setPosition(
							this->_baseNode->ChaseA(Vec2(0, Y), this->_baseNode->getPosition(), moveVelo,
									dt));
				} else {

					this->_baseNode->ChaseA(dt);
				}
			}

		}
	}

	if (this->onUpDateListener) {
		onUpDateListener(this, dt);
	}

}

void SelectScene::setUpdateAction(std::function<void(SelectScene*, float)> action) {

	this->unscheduleUpdate();
	this->onUpDateListener = action;
	this->scheduleUpdate();

}

void SelectScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {

		UserDefault::getInstance()->setIntegerForKey("SELECT_Y", (int) this->getBaseNode()->getPosition().y);

		auto scene = TitleScene::createScene();
		auto transition = TransitionCrossFade::create(0.5, scene);
		Director::getInstance()->replaceScene(transition);
	}
}

void SelectScene::onEnterTransitionDidFinish() {

	if (UserDefault::getInstance()->getBoolForKey("bgmkey", true)) {
		//	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(
		//			"bgm.mp3", true);
	}
	this->addChild(this->_baseNode, 2);
//	this->getnoMove3()->addChild(_selYaziTop,1,Vec2::ZERO,_selYaziTop->getPosition());
//	this->getnoMove3()->addChild(_selYaziDown,1,Vec2::ZERO,_selYaziDown->getPosition());
//	this->SetTouchListener();
//	this->scheduleUpdate();
}

