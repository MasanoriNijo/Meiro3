#include "cocos2d.h"
#include "Item.h"
#include "Cource.h"
#include "cmath"
USING_NS_CC;

//const int FRAME_COUNT = 1;
/*
 const int ballCatg = 1 << 0;
 const int itemCatg = 1 << 1;
 const int courceCatg = 1 << 2;
 const int startCatg = 1 << 3;
 const int goalCatg = 1 << 4;
 */
// on "init" you need to initialize your instance
Item::Item() :
		_madeNo(0),  moveFlg(false), _itemState(ItemState::T1), _lifePoint(
				0), _scorePoint(0) {
}
Item::~Item() {

}
bool Item::init() {

	if (!Sprite::initWithFile("goal_flg3.png")) {
		return false;
	}

	frameSize = Size(this->getContentSize().width / 1,
			this->getContentSize().height / 1);

	//auto director = Director::getInstance();
	//auto winSize = director->getWinSize();


	auto scl_=ScaleTo::create(0.3f,0.8f);
	auto scl2_=ScaleTo::create(0.3f,1.0f);
	auto rept_=RepeatForever::create(Sequence::create(scl_,scl2_,NULL));
	this->runAction(rept_);
	this->setTextureRect(Rect(0, 0, frameSize.width, frameSize.height));
	/*
	 Vector<SpriteFrame *> frames;
	 for (int i = 0; i < 1; ++i) {
	 auto frame = SpriteFrame::create("igaguri.png",
	 Rect(frameSize.width * i, frameSize.height, frameSize.width,
	 frameSize.height));
	 _frames.pushBack(frame);

	 }
	 */
	/*
	 Vec2 PointsT[] = { Vec2(7, -20), Vec2(-12, -20), Vec2(-12, -2), Vec2(-2,
	 20), Vec2(8, 2) };
	 this->setBody(PhysicsBody::createPolygon(PointsT, 5));
	 */

	/*
	auto material = PHYSICSBODY_MATERIAL_DEFAULT;
	material.restitution = 1.0f;
	material.friction = 1.0f;

	this->setBody(PhysicsBody::createBox(Size(64, 64)));
	_body->setGravityEnable(false);
	_body->setDynamic(false);
	_body->setEnable(true);
	_body->setCollisionBitmask(itemCatg);
	_body->setCategoryBitmask(itemCatg);
	_body->setContactTestBitmask(ballCatg);
	_body->setTag(2);
	this->setPhysicsBody(_body);
*/
	/*
	 auto animation = Animation::createWithSpriteFrames(_frames);
	 animation->setDelayPerUnit(0.2);
	 auto anime = Animate::create(animation);

	 auto rept = RepeatForever::create(anime);
	 this->runAction(rept);
	 */
	//this->scheduleUpdate();
	//this->setState(ItemState::T12);
//	this->setScale(scale_);
	return true;
}

void Item::setUpdateAction(std::function<void(Item*, float)> action) {

	this->unscheduleUpdate();
	this->onUpDateListener = action;
	//updateFlg = true;
	this->scheduleUpdate();
}
void Item::update(float dt) {

	if (onUpDateListener) {
		onUpDateListener(this, dt);
	}

}

void Item::Fin() {

	if (this->onFinishListener) {
		onFinishListener(this);
	}

}

void Item::setPosition_(Cource* c, int JtNo) {

	Vec2 p1;
	p1.set(c->getPosition());
	Vec2 p2;
	p2.set(0, 0);
	Vec2 p3;
	p3.set(0, -40);

	this->setPosition(p1);

	switch (JtNo) {

	case 0: {

		this->setPosition(p1);

	}

	case 1: {

		p2.set(30, 30);

		this->setPosition(p1 + p2);

		break;
	}
	case 2: {

		p2.set(30, -30);

		this->setPosition(p1 + p2);

		break;
	}
	case 3: {

		p2.set(-30, -30);

		this->setPosition(p1 + p2);

		break;
	}
	case 4: {

		p2.set(-30, 30);

		this->setPosition(p1 + p2);

		break;
	}

	}

}

void Item::setPosition_(Vec2 p1, int JtNo) {

	Vec2 p2;
	p2.set(0, 0);
	Vec2 p3;
	p3.set(0, -40);

	this->setPosition(p1);

	switch (JtNo) {

	case 0: {

		this->setPosition(p1*scale_);

	}

	case 1: {

		p2.set(30, 30);

		this->setPosition((p1 + p2)*scale_);

		break;
	}
	case 2: {

		p2.set(30, -30);

		this->setPosition((p1 + p2)*scale_);

		break;
	}
	case 3: {

		p2.set(-30, -30);

		this->setPosition((p1 + p2)*scale_);

		break;
	}
	case 4: {

		p2.set(-30, 30);

		this->setPosition((p1 + p2)*scale_);

		break;
	}

	}

}
void Item::setRndState(int _Lvl) {

	int rnd = arc4random() % static_cast<int>(5) + 1;

	switch (rnd) {

	case 1: {
		this->setState(ItemState::T2);
		break;
	}
	case 2: {
		this->setState(ItemState::T4);
		break;
	}
	case 3: {
		this->setState(ItemState::T6);
		break;
	}
	case 4: {
		this->setState(ItemState::T8);
		break;
	}
	case 5: {
		this->setState(ItemState::T10);
		break;
	}

	}

}

void Item::setRndState() {

	int rnd = arc4random() % static_cast<int>(30);

	rnd++;

	switch (rnd) {

	case 1: {
		this->setState(ItemState::T1);
		break;
	}
	case 2: {
		this->setState(ItemState::T2);
		break;
	}
	case 3: {
		this->setState(ItemState::T3);
		break;
	}
	case 4: {
		this->setState(ItemState::T4);
		break;
	}
	case 5: {
		this->setState(ItemState::T5);
		break;
	}
	case 6: {
		this->setState(ItemState::T6);
		break;
	}
	case 7: {
		this->setState(ItemState::T7);
		break;
	}
	case 8: {
		this->setState(ItemState::T8);
		break;
	}
	case 9: {
		this->setState(ItemState::T9);
		break;
	}
	case 10: {
		this->setState(ItemState::T10);
		break;
	}
	case 11: {
		this->setState(ItemState::T11);
		break;
	}
	case 12: {
		this->setState(ItemState::T12);
		break;
	}

	}

}

void Item::setState(ItemState x) {

	this->setItemState(x);

	int x_ = 0;
	int y_ = 0;

	switch (x) {

	case ItemState::T1: {
		x_ = 0;
		y_ = 0;
		_lifePoint = 1;
		_scorePoint = 0;
		//_itemName = "SPEED UP!";
		//this->getBody()->setTag(4);
		break;
	}
	case ItemState::T2: {
		x_ = 1;
		y_ = 0;
		_lifePoint = 3;
		_scorePoint = 0;
		//_itemName = "SPEED UP!";
		//this->getBody()->setTag(4);
		break;
	}
	case ItemState::T3: {
		x_ = 2;
		y_ = 0;
		_lifePoint = -1;
		_scorePoint = 0;
		//_itemName = "OOOOOO!";
		//this->getBody()->setTag(6);
		break;
	}
	case ItemState::T4: {
		x_ = 3;
		y_ = 0;
		_lifePoint = 0;
		_scorePoint = 1;
		//_itemName = "OOOOOO!";
		//this->getBody()->setTag(6);
		break;
	}
	case ItemState::T5: {
		x_ = 0;
		y_ = 1;
		_lifePoint = 0;
		_scorePoint = 2;
		//_itemName = "BOMB!";
		//this->getBody()->setTag(7);
		break;
	}
	case ItemState::T6: {
		x_ = 1;
		y_ = 1;
		_lifePoint = 0;
		_scorePoint = 3;
		//_itemName = "BOMB!";
	//	this->getBody()->setTag(7);
		break;
	}
	case ItemState::T7: {
		x_ = 2;
		y_ = 1;
		_lifePoint = 0;
		_scorePoint = 4;
		//_itemName = "MAP!";
	//	this->getBody()->setTag(5);
		break;
	}
	case ItemState::T8: {
		x_ = 3;
		y_ = 1;
		_lifePoint = 0;
		_scorePoint = 5;
		//_itemName = "MAP!";
	//	this->getBody()->setTag(5);
		break;
	}
	case ItemState::T9: {
		x_ = 0;
		y_ = 2;
		_lifePoint = 0;
		_scorePoint = 6;
		//_itemName = "TIMEUP!";
	//	this->getBody()->setTag(8);
		break;
	}
	case ItemState::T10: {
		x_ = 1;
		y_ = 2;
		_lifePoint = 0;
		_scorePoint = 8;
		//_itemName = "TIMEUP!";
	//	this->getBody()->setTag(8);
		break;
	}
	case ItemState::T11: {
		x_ = 2;
		y_ = 2;
		_lifePoint = 0;
		_scorePoint = 9;
		//_itemName = "GOAL";
	//	this->getBody()->setTag(3);
		break;
	}
	case ItemState::T12: {
		x_ = 3;
		y_ = 2;
		_lifePoint = 0;
		_scorePoint = 10;
		//_itemName = "NULL";
		break;
	}

	}

	this->setTextureRect(
			Rect(frameSize.width * x_, frameSize.height * y_, frameSize.width,
					frameSize.height));
	this->setScale(scale_);
}
void Item::Action1() {
	auto scl_=ScaleTo::create(0.3f,0.8f);
	auto scl2_=ScaleTo::create(0.3f,1.0f);
	auto rept_=RepeatForever::create(Sequence::create(scl_,scl2_,NULL));
	this->runAction(rept_);
	this->setTextureRect(Rect(0, 0, frameSize.width, frameSize.height));
}
void Item::Action2() {

	//this->setVisible(false);
	this->stopAllActions();

	auto _big = ScaleTo::create(0.5, 2);
	auto _move = MoveBy::create(0.5, Vec2(0, 100));
	auto _fade = FadeTo::create(0.5, 0);

	auto _do1 = Spawn::create(_big, _move, NULL);
	auto _fin = CallFuncN::create([this](Node* node) {
		this->Fin();
	});
	auto _seq = Sequence::create(_do1, _fade, _fin, NULL);

	this->runAction(_seq);

}
void Item::Action3() {

}
void Item::Action4() {

}
