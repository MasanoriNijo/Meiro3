#include "cocos2d.h"
#include "SelTag.h"
#include "PrmScene.h"
#include "cmath"

USING_NS_CC;

//const int FRAME_COUNT = 1;
/*
 const int ballCatg = 1 << 0;
 const int SelTagCatg = 1 << 1;
 const int courceCatg = 1 << 2;
 const int startCatg = 1 << 3;
 const int goalCatg = 1 << 4;
 */
// on "init" you need to initialize your instance
SelTag::SelTag() :
		_lvlLabel(NULL), _kagi(NULL), _selMemo(NULL), _lokMemo(NULL), _selBtn(NULL), _menu(NULL), _mMeder(
		NULL), _selWaku(NULL) {
}
SelTag::~SelTag() {
	CC_SAFE_RELEASE_NULL(_lvlLabel);
	CC_SAFE_RELEASE_NULL(_kagi);
	CC_SAFE_RELEASE_NULL(_selMemo);
	CC_SAFE_RELEASE_NULL(_lokMemo);
	CC_SAFE_RELEASE_NULL(_selBtn);
	CC_SAFE_RELEASE_NULL(_menu);
	CC_SAFE_RELEASE_NULL(_mMeder);
	CC_SAFE_RELEASE_NULL(_selWaku);

}
bool SelTag::init() {

	if (!Sprite::initWithFile("levelwaku.png")) {
		return false;
	}

	wakuSize.setSize(this->getContentSize().width, this->getContentSize().height);
	ctPt.set(wakuSize.width / 2, wakuSize.height / 2);

	this->setLvlLabel(Sprite::create("levels2.png"));
	frameSize = Size(this->_lvlLabel->getContentSize().width, this->_lvlLabel->getContentSize().height / 7);
	this->getLvlLabel()->setPosition(ctPt.x, 80);
	this->addChild(_lvlLabel, 1);



	TTFConfig ttfConfig3("HGRPP1.TTC", 40, GlyphCollection::DYNAMIC);

	this->setSelMemo(Label::createWithTTF(ttfConfig3, "SELMEMO"));
	_selMemo->setColor(Color3B::WHITE);
	_selMemo->setAnchorPoint(Vec2(0, 1));
	//_atai->setAnchorPoint(Vec2::ZERO);
	_selMemo->setAlignment(TextHAlignment::LEFT);
	_selMemo->setPosition(Vec2(50, 350));
	this->addChild(_selMemo, 2);

	this->setLokMemo(Label::createWithTTF(ttfConfig3, "ロックメモ\nミッションを\nクリヤしてね！"));
	_lokMemo->setColor(Color3B::WHITE);
	_lokMemo->setAnchorPoint(Vec2(0, 1));
	//_atai->setAnchorPoint(Vec2::ZERO);
	_lokMemo->setAlignment(TextHAlignment::LEFT);
	_lokMemo->setPosition(Vec2(50, 350));
	this->addChild(_lokMemo, 2);

//	this->setSelBtn(MenuItemImage::create("levelwaku.png", "levelwaku2.png", [this](Ref* ref) {
//
//		UserDefault::getInstance()->setIntegerForKey("LEVEL", this->Level_);
//		UserDefault::getInstance()->setIntegerForKey("SELECT_Y", (int) this->getParent()->getPosition().y);
//		const char *str0 = "SelTag_Push";
//		log("%s", str0);
//		auto scene=MainScene::createScene();
//		auto transition=TransitionCrossFade::create(0.8f,scene);
//		Director::getInstance()->replaceScene(transition);
//	}));
//	this->setMenu(Menu::create(_selBtn, NULL));
//	this->_menu->setPosition(ctPt);
//	this->addChild(_menu, 1);

	this->setSelWaku(Sprite::create("levelwaku2.png"));
	this->_selWaku->setPosition(ctPt);
	this->_selWaku->setVisible(false);
	this->addChild(this->_selWaku, 1);

	this->setKagi(Sprite::create("lock.png"));
	this->_kagi->setRotation(-45);
	this->_kagi->setPosition(30, wakuSize.height - 30);
	this->addChild(this->_kagi, 1);

	this->SetLock(false);
	this->SetLevel(1);
	return true;
}

void SelTag::SetLevel(int i) {

	if (i > 0 && i < 8) {

		this->getLvlLabel()->setTextureRect(
				Rect(0, frameSize.height * (i - 1), frameSize.width, frameSize.height));
		_lokMemo->setString("レベル" + StringUtils::toString((int) (i - 1)) + "を\n3回クリヤしてね!");

		Level_ = i;
	} else {
		this->getLvlLabel()->setTextureRect(Rect(0, 0, frameSize.width, frameSize.height));
		Level_ = 0;
	}

}

void SelTag::SetLock(bool lok_) {
	//ロックするしない。
	if (lok_) {
//		this->_menu->setVisible(false);
		this->getKagi()->setVisible(true);
		this->setSelState(SelState::LOCK);
		this->getSelMemo()->setVisible(true);
		this->getLokMemo()->setVisible(false);
	} else {
//		this->_menu->setVisible(true);
		this->getKagi()->setVisible(false);
		this->setSelState(SelState::UNLOCK);
		this->getSelMemo()->setVisible(true);
		this->getLokMemo()->setVisible(false);
	}

}

void SelTag::SetMemoText(std::string txt_) {
	this->getSelMemo()->setString("" + txt_);
}
void SelTag::SetLockText(std::string txt_) {
	this->getLokMemo()->setString("" + txt_);
}

bool SelTag::SelectTag(Vec2 pt_) {

	Vec2 ptp;
	ptp.set(pt_);
	Rect rect = this->getBoundingBox();
	//touch->getworldPosition();
	if (rect.containsPoint(ptp)) {
		this->touchFlg_ = true;
	} else {
		this->touchFlg_ = false;
	}

	return touchFlg_;

}
void SelTag::TouchOn(Vec2 pt) {

	this->_point1.set(pt);
	this->_point2.set(pt);
	this->SelectTag(pt);

	const char *str0 = "SelTag::TouchOn";
	log("%s", str0);

	switch (this->getSelState()) {

	case SelState::LOCK: {
		if (this->touchFlg_) {
			this->getLokMemo()->setVisible(true);
			this->getSelMemo()->setVisible(false);
		}
		break;

	}
	case SelState::UNLOCK: {

		if (this->touchFlg_) {
			this->_selWaku->setVisible(true);
		}

		break;

	}
	}

}
void SelTag::Swaip(Vec2 pt1, Vec2 pt2) {

//	const char *str = "Pen::Swaip";
//	log("%s", str);

	this->_point1.set(pt1);
	this->_point2.set(pt2);
	this->SelectTag(pt2);
	switch (this->getSelState()) {

	case SelState::LOCK: {
		if (!this->touchFlg_) {
			this->getLokMemo()->setVisible(false);
			this->getSelMemo()->setVisible(true);
		}
		break;

	}
	case SelState::UNLOCK: {
		if (!this->touchFlg_ || (this->_point1 - this->_point2).length() > 50) {
			this->touchFlg_ = false;
			this->_selWaku->setVisible(false);
		}
		break;

	}

	}

}
void SelTag::TouchOff() {

	this->_point1.set(Vec2::ZERO);
	this->_point2.set(Vec2::ZERO);
	switch (this->getSelState()) {

	case SelState::LOCK: {
		this->getLokMemo()->setVisible(false);
		this->getSelMemo()->setVisible(true);
		break;

	}
	case SelState::UNLOCK: {

		if (this->touchFlg_) {

			UserDefault::getInstance()->setIntegerForKey("LEVEL", this->Level_);
			UserDefault::getInstance()->setIntegerForKey("SELECT_Y",
					(int) this->getParent()->getPosition().y);
			const char *str0 = "SelTag_Push";
			log("%s", str0);

			//ここで分岐
			if (this->Level_ < 7) {
				auto scene = MainScene::createScene();
				auto transition = TransitionCrossFade::create(0.5f, scene);
				Director::getInstance()->replaceScene(transition);
			} else {
				auto scene = PrmScene::createScene();
				auto transition = TransitionCrossFade::create(0.5f, scene);
				Director::getInstance()->replaceScene(transition);
			}

		}

		break;

	}

	}
	touchFlg_ = false;
}
void SelTag::update(float dt) {

}

