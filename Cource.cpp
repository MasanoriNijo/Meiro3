#include "cocos2d.h"
#include "Cource.h"
#include "cmath"

#define ARRAY_LENGTH(array) (sizeof(array) / sizeof(array[0]))
USING_NS_CC;

//Size frameSize;
/*

 Vec2 pt_a[] = { Vec2(-30, 9), Vec2(-9, 9), Vec2(-9, 30) };
 Vec2 pt_a_x[] = { Vec2(9, 30), Vec2(9, 9), Vec2(30, 9) };
 Vec2 pt_a_y[] = { Vec2(-9, -30), Vec2(-9, -9), Vec2(-30, -9) };
 Vec2 pt_a_xy[] = { Vec2(30, -9), Vec2(9, -9), Vec2(9, -30) };

 Vec2 pt_b[] = { Vec2(-30, 9), Vec2(30, 9) };
 Vec2 pt_b_x[] = { Vec2(-30, 9), Vec2(30, 9) };
 Vec2 pt_b_y[] = { Vec2(30, -9), Vec2(-30, -9) };
 Vec2 pt_b_xy[] = { Vec2(30, -9), Vec2(-30, -9) };

 Vec2 pt_c[] = { Vec2(-9, -30), Vec2(-9, 3), Vec2(-3, 9), Vec2(30, 9) };
 Vec2 pt_c_x[] = { Vec2(-30, 9), Vec2(3, 9), Vec2(9, 3), Vec2(9, -30) };
 Vec2 pt_c_y[] = { Vec2(30, -9), Vec2(-3, -9), Vec2(-9, -3), Vec2(-9, 30) };
 Vec2 pt_c_xy[] = { Vec2(9, 30), Vec2(9, -3), Vec2(3, -9), Vec2(-30, -9) };

 Vec2 pt_d[] = { Vec2(9, 30), Vec2(9, -3), Vec2(3, -9), Vec2(-3, -9), Vec2(-9,
 -3), Vec2(-9, 30) };
 Vec2 pt_d_x[] = { Vec2(9, 30), Vec2(9, -3), Vec2(3, -9), Vec2(-3, -9), Vec2(-9,
 -3), Vec2(-9, 30) };
 Vec2 pt_d_y[] = { Vec2(-9, -30), Vec2(-9, 3), Vec2(-3, 9), Vec2(3, 9), Vec2(9,
 3), Vec2(9, -30) };
 Vec2 pt_d_xy[] = { Vec2(-9, -30), Vec2(-9, 3), Vec2(-3, 9), Vec2(3, 9), Vec2(9,
 3), Vec2(9, -30) };

 Vec2 pt_e[] = { Vec2(-9, -30), Vec2(-9, 30) };
 Vec2 pt_e_x[] = { Vec2(9, 30), Vec2(9, -30) };
 Vec2 pt_e_y[] = { Vec2(-9, -30), Vec2(-9, 30) };
 Vec2 pt_e_xy[] = { Vec2(9, 30), Vec2(9, -30) };

 Vec2 pt_f[] = { Vec2(30, 9), Vec2(-3, 9), Vec2(-9, 3), Vec2(-9, -3), Vec2(-3,
 -9), Vec2(30, -9) };
 Vec2 pt_f_x[] = { Vec2(-30, -9), Vec2(3, -9), Vec2(9, -3), Vec2(9, 3), Vec2(3,
 9), Vec2(-30, 9) };
 Vec2 pt_f_y[] = { Vec2(30, 9), Vec2(-3, 9), Vec2(-9, 3), Vec2(-9, -3), Vec2(-3,
 -9), Vec2(30, -9) };
 Vec2 pt_f_xy[] = { Vec2(-30, -9), Vec2(3, -9), Vec2(9, -3), Vec2(9, 3), Vec2(3,
 9), Vec2(-30, 9) };

 */
// on "init" you need to initialize your instance
Cource::Cource() :
		_courceState(CourceState::T1), _courceType(CourceType::C01), moveFlg(
				false), _body(NULL), _body2(NULL), _body3(NULL), _body4(NULL), _body5(
		NULL), _nd1(NULL), _nd2(NULL), _nd3(NULL), _nd4(NULL), _nd5(
		NULL), _madeNo(-1) {

}
Cource::~Cource() {

	CC_SAFE_RELEASE_NULL(_body);
	CC_SAFE_RELEASE_NULL(_body2);
	CC_SAFE_RELEASE_NULL(_body3);
	CC_SAFE_RELEASE_NULL(_body4);
	CC_SAFE_RELEASE_NULL(_body5);
	CC_SAFE_RELEASE_NULL(_nd1);
	CC_SAFE_RELEASE_NULL(_nd2);
	CC_SAFE_RELEASE_NULL(_nd3);
	CC_SAFE_RELEASE_NULL(_nd4);
	CC_SAFE_RELEASE_NULL(_nd5);
}

Cource* Cource::createWithTexture(Texture2D *texture) {
	Cource *sprite = new (std::nothrow) Cource();
	if (sprite && sprite->initWithTexture(texture)) {
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	sprite = NULL;
	return NULL;
}

bool Cource::init() {

	//Vec2初期化

	Vec2 pt_1[] = { Vec2(-9, -9), Vec2(-9, 9), Vec2(9, 9), Vec2(9, -9) };
	Vec2 pt_2[] = { Vec2(-9, 9), Vec2(-9, 30), Vec2(9, 30), Vec2(9, 9) };
	Vec2 pt_3[] = { Vec2(9, -9), Vec2(9, 9), Vec2(30, 9), Vec2(30, -9) };
	Vec2 pt_4[] = { Vec2(-9, -9), Vec2(9, -9), Vec2(9, -30), Vec2(-9, -30) };
	Vec2 pt_5[] = { Vec2(-30, 9), Vec2(-9, 9), Vec2(-9, -9), Vec2(-30, -9) };


	if (!Sprite::initWithFile("dumybody.png")) {
		return false;
	}

/*
	if (!Sprite::initWithFile("meiromap_c.png")) {
		return false;
	}

	frameSize = Size(this->getContentSize().width / 5,
			this->getContentSize().height / 3);

	auto director = Director::getInstance();
	auto winSize = director->getWinSize();

	this->setTextureRect(Rect(0, 0, frameSize.width, frameSize.height));
	this->scale_=(float)w/(float)60;
	//this->SetCourceA(CourceType::C01);

	return true;
*/




	frameSize = Size(this->getContentSize().width,
			this->getContentSize().height);

	auto director = Director::getInstance();
	auto winSize = director->getWinSize();

	this->setTextureRect(Rect(0, 0, 0, 0));

	this->scale_ = (float) w / (float) 60;

	for (int i = 0; i < ARRAY_LENGTH(pt_1); i++) {
		pt_1[i] *= scale_;
	}
	for (int i = 0; i < ARRAY_LENGTH(pt_2); i++) {
		pt_2[i] *= scale_;
	}
	for (int i = 0; i < ARRAY_LENGTH(pt_3); i++) {
		pt_3[i] *= scale_;
	}
	for (int i = 0; i < ARRAY_LENGTH(pt_4); i++) {
		pt_4[i] *= scale_;
	}
	for (int i = 0; i < ARRAY_LENGTH(pt_5); i++) {
		pt_5[i] *= scale_;
	}

	this->setNd1(Node::create());
	this->setBody(PhysicsBody::createPolygon(pt_1, 4));
	//this->setBody(PhysicsBody::createCircle(5));
	this->getBody()->setDynamic(false);
	_nd1->setPhysicsBody(_body);
	this->addChild(_nd1);

	this->setNd2(Node::create());
	//_nd2->setPosition(Vec2(0,20));
	this->setBody2(PhysicsBody::createPolygon(pt_2, 4));
	//this->setBody2(PhysicsBody::createCircle(5));
	this->getBody2()->setDynamic(false);
	_nd2->setPhysicsBody(_body2);
	this->addChild(_nd2);

	this->setNd3(Node::create());
	//_nd3->setPosition(Vec2(20,0));
	this->setBody3(PhysicsBody::createPolygon(pt_3, 4));
	//this->setBody3(PhysicsBody::createCircle(5));
	this->getBody3()->setDynamic(false);
	_nd3->setPhysicsBody(_body3);
	this->addChild(_nd3);

	this->setNd4(Node::create());
	//_nd4->setPosition(Vec2(0,-20));
	this->setBody4(PhysicsBody::createPolygon(pt_4, 4));
	//this->setBody4(PhysicsBody::createCircle(5));
	this->getBody4()->setDynamic(false);
	_nd4->setPhysicsBody(_body4);
	this->addChild(_nd4);

	this->setNd5(Node::create());
	//_nd5->setPosition(Vec2(-20,0));
	this->setBody5(PhysicsBody::createPolygon(pt_5, 4));
	//this->setBody5(PhysicsBody::createCircle(5));
	this->getBody5()->setDynamic(false);
	_nd5->setPhysicsBody(_body5);
	this->addChild(_nd5);


	return true;


}

bool Cource::initWithTexture(Texture2D *texture) {

	if (!Sprite::initWithTexture(texture)) {
		return false;
	}

	frameSize = Size(this->getContentSize().width / 5,
			this->getContentSize().height / 3);

	auto director = Director::getInstance();
	auto winSize = director->getWinSize();

	this->setTextureRect(Rect(0, 0, frameSize.width, frameSize.height));

	this->scale_ = (float) w / (float) 60;

//this->SetCourceA(CourceType::C01);

	return true;

}

void Cource::ResetCource() {

	if (this->getBody() != NULL) {
		this->getBody()->removeFromWorld();
		//	this->setBody(NULL);
	}
	if (this->getBody2() != NULL) {
		this->getBody2()->removeFromWorld();
		//	this->setBody2(NULL);
	}
	if (this->getBody3() != NULL) {
		this->getBody3()->removeFromWorld();
		//	this->setBody3(NULL);
	}
	if (this->getBody4() != NULL) {
		this->getBody4()->removeFromWorld();
		//this->setBody4(NULL);
	}
	if (this->getBody5() != NULL) {
		this->getBody5()->removeFromWorld();
		//this->setBody4(NULL);
	}
	CC_SAFE_RELEASE_NULL(_body);
	CC_SAFE_RELEASE_NULL(_body2);
	CC_SAFE_RELEASE_NULL(_body3);
	CC_SAFE_RELEASE_NULL(_body4);
	CC_SAFE_RELEASE_NULL(_body5);
}

void Cource::setUpdateAction(std::function<void(Cource*, float)> action) {

	this->unscheduleUpdate();
	this->onUpDateListener = action;
//updateFlg = true;
	this->scheduleUpdate();
}
void Cource::update(float dt) {

	if (onUpDateListener) {
		onUpDateListener(this, dt);
	}

}

void Cource::Fin() {

	if (this->onFinishListener) {
		onFinishListener(this);
	}

}

std::string Cource::GetCourceName() {

	std::string CsName = "";
	switch (this->getCourceType()) {
	case CourceType::C00: {
		CsName = "C00";
		break;
	}
	case CourceType::C01: {
		CsName = "C01";
		break;
	}
	case CourceType::C02: {
		CsName = "C02";
		break;
	}
	case CourceType::C03: {
		CsName = "C03";
		break;
	}
	case CourceType::C04: {
		CsName = "C04";
		break;
	}
	case CourceType::C05: {
		CsName = "C05";
		break;
	}
	case CourceType::C06: {
		CsName = "C06";
		break;
	}
	case CourceType::C07: {
		CsName = "C07";
		break;
	}
	case CourceType::C08: {
		CsName = "C08";
		break;
	}
	case CourceType::C09: {
		CsName = "C09";
		break;
	}
	case CourceType::C10: {
		CsName = "C10";
		break;
	}
	case CourceType::C11: {
		CsName = "C11";
		break;
	}
	case CourceType::C12: {
		CsName = "C12";
		break;
	}
	case CourceType::C13: {
		CsName = "C13";
		break;
	}
	case CourceType::C14: {
		CsName = "C14";
		break;
	}
	case CourceType::C15: {
		CsName = "C15";
		break;
	}

	}

	return CsName;
}
//SetIndex(int index)
void Cource::SetIndex(int index) {

	int rndA = index;
	switch (rndA) {
	case 0: {
		this->SetCource(CourceType::C00);
		break;
	}
	case 1: {
		this->SetCource(CourceType::C01);
		break;
	}
	case 2: {
		this->SetCource(CourceType::C02);
		break;
	}
	case 3: {
		this->SetCource(CourceType::C03);
		break;
	}
	case 4: {
		this->SetCource(CourceType::C04);
		break;
	}
	case 5: {
		this->SetCource(CourceType::C05);
		break;
	}
	case 6: {
		this->SetCource(CourceType::C06);
		break;
	}
	case 7: {
		this->SetCource(CourceType::C07);
		break;
	}
	case 8: {
		this->SetCource(CourceType::C08);
		break;
	}
	case 9: {
		this->SetCource(CourceType::C09);
		break;
	}
	case 10: {
		this->SetCource(CourceType::C10);
		break;
	}
	case 11: {
		this->SetCource(CourceType::C11);
		break;
	}
	case 12: {
		this->SetCource(CourceType::C12);
		break;
	}
	case 13: {
		this->SetCource(CourceType::C13);
		break;
	}
	case 14: {
		this->SetCource(CourceType::C14);
		break;
	}
	case 15: {
		this->SetCource(CourceType::C15);
		break;
	}
	}

}

void Cource::SetIndexA(int index) {

	int rndA = index;
	switch (rndA) {
	case 0: {
		this->SetCourceA(CourceType::C00);
		break;
	}
	case 1: {
		this->SetCourceA(CourceType::C01);
		break;
	}
	case 2: {
		this->SetCourceA(CourceType::C02);
		break;
	}
	case 3: {
		this->SetCourceA(CourceType::C03);
		break;
	}
	case 4: {
		this->SetCourceA(CourceType::C04);
		break;
	}
	case 5: {
		this->SetCourceA(CourceType::C05);
		break;
	}
	case 6: {
		this->SetCourceA(CourceType::C06);
		break;
	}
	case 7: {
		this->SetCourceA(CourceType::C07);
		break;
	}
	case 8: {
		this->SetCourceA(CourceType::C08);
		break;
	}
	case 9: {
		this->SetCourceA(CourceType::C09);
		break;
	}
	case 10: {
		this->SetCourceA(CourceType::C10);
		break;
	}
	case 11: {
		this->SetCourceA(CourceType::C11);
		break;
	}
	case 12: {
		this->SetCourceA(CourceType::C12);
		break;
	}
	case 13: {
		this->SetCourceA(CourceType::C13);
		break;
	}
	case 14: {
		this->SetCourceA(CourceType::C14);
		break;
	}
	case 15: {
		this->SetCourceA(CourceType::C15);
		break;
	}
	}

}

void Cource::SetRnd() {

	int rndA = arc4random() % static_cast<int>(16);
//rndA++;
	switch (rndA) {
	case 0: {
		this->SetCourceA(CourceType::C00);
		break;
	}
	case 1: {
		this->SetCourceA(CourceType::C01);
		break;
	}
	case 2: {
		this->SetCourceA(CourceType::C02);
		break;
	}
	case 3: {
		this->SetCourceA(CourceType::C03);
		break;
	}
	case 4: {
		this->SetCourceA(CourceType::C04);
		break;
	}
	case 5: {
		this->SetCourceA(CourceType::C05);
		break;
	}
	case 6: {
		this->SetCourceA(CourceType::C06);
		break;
	}
	case 7: {
		this->SetCourceA(CourceType::C07);
		break;
	}
	case 8: {
		this->SetCourceA(CourceType::C08);
		break;
	}
	case 9: {
		this->SetCourceA(CourceType::C09);
		break;
	}
	case 10: {
		this->SetCourceA(CourceType::C10);
		break;
	}
	case 11: {
		this->SetCourceA(CourceType::C11);
		break;
	}
	case 12: {
		this->SetCourceA(CourceType::C12);
		break;
	}
	case 13: {
		this->SetCourceA(CourceType::C13);
		break;
	}
	case 14: {
		this->SetCourceA(CourceType::C14);
		break;
	}
	case 15: {
		this->SetCourceA(CourceType::C15);
		break;
	}
	}

}

void Cource::SetBody_(bool x) {

	if (x) {

		this->SetCource(this->getCourceType());

	} else {
		this->SetCourceA(this->getCourceType());
	}

}

void Cource::SetCourceA(CourceType c_) {

	this->setCourceType(c_);

	this->ResetCource();

	Vec2 copy_ = Vec2::ZERO;
	int ptsize_ = 0;

//float _rad = 2 * M_PI / 360;

	switch (c_) {
	case CourceType::C00: {

		this->setTextureRect(Rect(0, 0, frameSize.width, frameSize.height));
		this->setVisible(false);
		break;
	}
	case CourceType::C01: {

		this->setTextureRect(Rect(0, 0, frameSize.width, frameSize.height));
		this->setVisible(true);
		break;
	}
	case CourceType::C02: {

		this->setTextureRect(
				Rect(frameSize.width * 1, frameSize.height * 0, frameSize.width,
						frameSize.height));
		this->setVisible(true);
		break;
	}
	case CourceType::C03: {
		this->setTextureRect(
				Rect(frameSize.width * 2, frameSize.height * 0, frameSize.width,
						frameSize.height));
		this->setVisible(true);
		break;
	}
	case CourceType::C04: {
		this->setTextureRect(
				Rect(frameSize.width * 3, frameSize.height * 0, frameSize.width,
						frameSize.height));
		this->setVisible(true);
		break;
	}
	case CourceType::C05: {
		this->setTextureRect(
				Rect(frameSize.width * 4, frameSize.height * 0, frameSize.width,
						frameSize.height));
		this->setVisible(true);
		break;
	}
	case CourceType::C06: {
		this->setTextureRect(
				Rect(frameSize.width * 0, frameSize.height * 1, frameSize.width,
						frameSize.height));
		this->setVisible(true);
		break;
	}
	case CourceType::C07: {
		this->setTextureRect(
				Rect(frameSize.width * 1, frameSize.height * 1, frameSize.width,
						frameSize.height));
		this->setVisible(true);
		break;
	}
	case CourceType::C08: {
		this->setTextureRect(
				Rect(frameSize.width * 2, frameSize.height * 1, frameSize.width,
						frameSize.height));
		this->setVisible(true);
		break;
	}
	case CourceType::C09: {
		this->setTextureRect(
				Rect(frameSize.width * 3, frameSize.height * 1, frameSize.width,
						frameSize.height));
		this->setVisible(true);
		break;
	}
	case CourceType::C10: {
		this->setTextureRect(
				Rect(frameSize.width * 4, frameSize.height * 1, frameSize.width,
						frameSize.height));
		this->setVisible(true);
		break;
	}
	case CourceType::C11: {
		this->setTextureRect(
				Rect(frameSize.width * 0, frameSize.height * 2, frameSize.width,
						frameSize.height));
		this->setVisible(true);
		break;
	}
	case CourceType::C12: {
		this->setTextureRect(
				Rect(frameSize.width * 1, frameSize.height * 2, frameSize.width,
						frameSize.height));
		this->setVisible(true);
		break;
	}
	case CourceType::C13: {
		this->setTextureRect(
				Rect(frameSize.width * 2, frameSize.height * 2, frameSize.width,
						frameSize.height));
		this->setVisible(true);
		break;
	}

	case CourceType::C14: {
		this->setTextureRect(
				Rect(frameSize.width * 3, frameSize.height * 2, frameSize.width,
						frameSize.height));
		this->setVisible(true);
		break;
	}
	case CourceType::C15: {
		this->setTextureRect(
				Rect(frameSize.width * 4, frameSize.height * 2, frameSize.width,
						frameSize.height));
		this->setVisible(true);
		break;
	}

	}
//this->setScale(scale_);
}
void Cource::SetCource(CourceType c_) {

	this->setCourceType(c_);




	switch (c_) {
	case CourceType::C00: {

		this->getBody()->setEnable(false);
		this->getBody2()->setEnable(false);
		this->getBody3()->setEnable(false);
		this->getBody4()->setEnable(false);
		this->getBody5()->setEnable(false);


		break;
	}
	case CourceType::C01: {

		this->getBody()->setEnable(true);
		this->getBody2()->setEnable(true);
		this->getBody3()->setEnable(false);
		this->getBody4()->setEnable(false);
		this->getBody5()->setEnable(false);

		break;
	}
	case CourceType::C02: {

		this->getBody()->setEnable(true);
		this->getBody2()->setEnable(false);
		this->getBody3()->setEnable(true);
		this->getBody4()->setEnable(false);
		this->getBody5()->setEnable(false);
		break;
	}
	case CourceType::C03: {
		this->getBody()->setEnable(true);
		this->getBody2()->setEnable(true);
		this->getBody3()->setEnable(true);
		this->getBody4()->setEnable(false);
		this->getBody5()->setEnable(false);
		break;
	}
	case CourceType::C04: {
		this->getBody()->setEnable(true);
		this->getBody2()->setEnable(false);
		this->getBody3()->setEnable(false);
		this->getBody4()->setEnable(true);
		this->getBody5()->setEnable(false);
		break;
	}
	case CourceType::C05: {
		this->getBody()->setEnable(true);
		this->getBody2()->setEnable(true);
		this->getBody3()->setEnable(false);
		this->getBody4()->setEnable(true);
		this->getBody5()->setEnable(false);
		break;
	}
	case CourceType::C06: {
		this->getBody()->setEnable(true);
		this->getBody2()->setEnable(false);
		this->getBody3()->setEnable(true);
		this->getBody4()->setEnable(true);
		this->getBody5()->setEnable(false);
		break;
	}
	case CourceType::C07: {
		this->getBody()->setEnable(true);
		this->getBody2()->setEnable(true);
		this->getBody3()->setEnable(true);
		this->getBody4()->setEnable(true);
		this->getBody5()->setEnable(false);
		break;
	}
	case CourceType::C08: {
		this->getBody()->setEnable(true);
		this->getBody2()->setEnable(false);
		this->getBody3()->setEnable(false);
		this->getBody4()->setEnable(false);
		this->getBody5()->setEnable(true);
		break;
	}
	case CourceType::C09: {
		this->getBody()->setEnable(true);
		this->getBody2()->setEnable(true);
		this->getBody3()->setEnable(false);
		this->getBody4()->setEnable(false);
		this->getBody5()->setEnable(true);
		break;
	}
	case CourceType::C10: {
		this->getBody()->setEnable(true);
		this->getBody2()->setEnable(false);
		this->getBody3()->setEnable(true);
		this->getBody4()->setEnable(false);
		this->getBody5()->setEnable(true);
		break;
	}
	case CourceType::C11: {
		this->getBody()->setEnable(true);
		this->getBody2()->setEnable(true);
		this->getBody3()->setEnable(true);
		this->getBody4()->setEnable(false);
		this->getBody5()->setEnable(true);
		break;
	}
	case CourceType::C12: {
		this->getBody()->setEnable(true);
		this->getBody2()->setEnable(false);
		this->getBody3()->setEnable(false);
		this->getBody4()->setEnable(true);
		this->getBody5()->setEnable(true);
		break;
	}
	case CourceType::C13: {
		this->getBody()->setEnable(true);
		this->getBody2()->setEnable(true);
		this->getBody3()->setEnable(false);
		this->getBody4()->setEnable(true);
		this->getBody5()->setEnable(true);
		break;
	}

	case CourceType::C14: {
		this->getBody()->setEnable(true);
		this->getBody2()->setEnable(false);
		this->getBody3()->setEnable(true);
		this->getBody4()->setEnable(true);
		this->getBody5()->setEnable(true);
		break;
	}
	case CourceType::C15: {
		this->getBody()->setEnable(true);
		this->getBody2()->setEnable(true);
		this->getBody3()->setEnable(true);
		this->getBody4()->setEnable(true);
		this->getBody5()->setEnable(true);
		break;
	}

	}

	if (_body != NULL) {

		this->getBody()->setCollisionBitmask(ballCatg);
		this->getBody()->setCategoryBitmask(courceCatg);
		//this->getBody()->setContactTestBitmask(ballCatg);
		this->getBody()->setTag(1);
		this->setVisible(true);
		//this->setScale(scale_);

		//	auto material = PHYSICSBODY_MATERIAL_DEFAULT;
		//	material.restitution = 0.0f;
		//for (auto x : this->getBody()->getShapes()) {
		//x->setRestitution(0.0f);
		//}

	} else {
		this->setVisible(false);
	}

}

void Cource::SetCource_old(CourceType c_) {

	this->setCourceType(c_);

	Vec2 pt_a[] = { Vec2(-30, 9), Vec2(-9, 9), Vec2(-9, 30) };
	Vec2 pt_a_x[] = { Vec2(9, 30), Vec2(9, 9), Vec2(30, 9) };
	Vec2 pt_a_y[] = { Vec2(-9, -30), Vec2(-9, -9), Vec2(-30, -9) };
	Vec2 pt_a_xy[] = { Vec2(30, -9), Vec2(9, -9), Vec2(9, -30) };

	Vec2 pt_b[] = { Vec2(-30, 9), Vec2(30, 9) };
	Vec2 pt_b_x[] = { Vec2(-30, 9), Vec2(30, 9) };
	Vec2 pt_b_y[] = { Vec2(30, -9), Vec2(-30, -9) };
	Vec2 pt_b_xy[] = { Vec2(30, -9), Vec2(-30, -9) };

	Vec2 pt_c[] = { Vec2(-9, -30), Vec2(-9, 3), Vec2(-3, 9), Vec2(30, 9) };
	Vec2 pt_c_x[] = { Vec2(-30, 9), Vec2(3, 9), Vec2(9, 3), Vec2(9, -30) };
	Vec2 pt_c_y[] = { Vec2(30, -9), Vec2(-3, -9), Vec2(-9, -3), Vec2(-9, 30) };
	Vec2 pt_c_xy[] = { Vec2(9, 30), Vec2(9, -3), Vec2(3, -9), Vec2(-30, -9) };

	Vec2 pt_d[] = { Vec2(9, 30), Vec2(9, -3), Vec2(3, -9), Vec2(-3, -9), Vec2(
			-9, -3), Vec2(-9, 30) };
	Vec2 pt_d_x[] = { Vec2(9, 30), Vec2(9, -3), Vec2(3, -9), Vec2(-3, -9), Vec2(
			-9, -3), Vec2(-9, 30) };
	Vec2 pt_d_y[] = { Vec2(-9, -30), Vec2(-9, 3), Vec2(-3, 9), Vec2(3, 9), Vec2(
			9, 3), Vec2(9, -30) };
	Vec2 pt_d_xy[] = { Vec2(-9, -30), Vec2(-9, 3), Vec2(-3, 9), Vec2(3, 9),
			Vec2(9, 3), Vec2(9, -30) };

	Vec2 pt_e[] = { Vec2(-9, -30), Vec2(-9, 30) };
	Vec2 pt_e_x[] = { Vec2(9, 30), Vec2(9, -30) };
	Vec2 pt_e_y[] = { Vec2(-9, -30), Vec2(-9, 30) };
	Vec2 pt_e_xy[] = { Vec2(9, 30), Vec2(9, -30) };

	Vec2 pt_f[] = { Vec2(30, 9), Vec2(-3, 9), Vec2(-9, 3), Vec2(-9, -3), Vec2(
			-3, -9), Vec2(30, -9) };
	Vec2 pt_f_x[] = { Vec2(-30, -9), Vec2(3, -9), Vec2(9, -3), Vec2(9, 3), Vec2(
			3, 9), Vec2(-30, 9) };
	Vec2 pt_f_y[] = { Vec2(30, 9), Vec2(-3, 9), Vec2(-9, 3), Vec2(-9, -3), Vec2(
			-3, -9), Vec2(30, -9) };
	Vec2 pt_f_xy[] = { Vec2(-30, -9), Vec2(3, -9), Vec2(9, -3), Vec2(9, 3),
			Vec2(3, 9), Vec2(-30, 9) };

	for (int i = 0; i < ARRAY_LENGTH(pt_a); i++) {
		pt_a[i] *= scale_;
	}
	for (int i = 0; i < ARRAY_LENGTH(pt_a_x); i++) {
		pt_a_x[i] *= scale_;
	}
	for (int i = 0; i < ARRAY_LENGTH(pt_a_y); i++) {
		pt_a_y[i] *= scale_;
	}
	for (int i = 0; i < ARRAY_LENGTH(pt_a_xy); i++) {
		pt_a_xy[i] *= scale_;
	}
	for (int i = 0; i < ARRAY_LENGTH(pt_b); i++) {
		pt_b[i] *= scale_;
	}
	for (int i = 0; i < ARRAY_LENGTH(pt_b_x); i++) {
		pt_b_x[i] *= scale_;
	}
	for (int i = 0; i < ARRAY_LENGTH(pt_b_y); i++) {
		pt_b_y[i] *= scale_;
	}
	for (int i = 0; i < ARRAY_LENGTH(pt_b_xy); i++) {
		pt_b_xy[i] *= scale_;
	}
	for (int i = 0; i < ARRAY_LENGTH(pt_c); i++) {
		pt_c[i] *= scale_;
	}
	for (int i = 0; i < ARRAY_LENGTH(pt_c_x); i++) {
		pt_c_x[i] *= scale_;
	}
	for (int i = 0; i < ARRAY_LENGTH(pt_c_y); i++) {
		pt_c_y[i] *= scale_;
	}
	for (int i = 0; i < ARRAY_LENGTH(pt_c_xy); i++) {
		pt_c_xy[i] *= scale_;
	}
	for (int i = 0; i < ARRAY_LENGTH(pt_d); i++) {
		pt_d[i] *= scale_;
	}
	for (int i = 0; i < ARRAY_LENGTH(pt_d_x); i++) {
		pt_d_x[i] *= scale_;
	}
	for (int i = 0; i < ARRAY_LENGTH(pt_d_y); i++) {
		pt_d_y[i] *= scale_;
	}
	for (int i = 0; i < ARRAY_LENGTH(pt_d_xy); i++) {
		pt_d_xy[i] *= scale_;
	}
	for (int i = 0; i < ARRAY_LENGTH(pt_e); i++) {
		pt_e[i] *= scale_;
	}
	for (int i = 0; i < ARRAY_LENGTH(pt_e_x); i++) {
		pt_e_x[i] *= scale_;
	}
	for (int i = 0; i < ARRAY_LENGTH(pt_e_y); i++) {
		pt_e_y[i] *= scale_;
	}
	for (int i = 0; i < ARRAY_LENGTH(pt_e_xy); i++) {
		pt_e_xy[i] *= scale_;
	}
	for (int i = 0; i < ARRAY_LENGTH(pt_f); i++) {
		pt_f[i] *= scale_;
	}
	for (int i = 0; i < ARRAY_LENGTH(pt_f_x); i++) {
		pt_f_x[i] *= scale_;
	}
	for (int i = 0; i < ARRAY_LENGTH(pt_f_y); i++) {
		pt_f_y[i] *= scale_;
	}
	for (int i = 0; i < ARRAY_LENGTH(pt_f_xy); i++) {
		pt_f_xy[i] *= scale_;
	}
	Vec2 copy_ = Vec2::ZERO;

	int ptsize_ = 0;

	this->ResetCource();

	switch (c_) {
	case CourceType::C00: {

		this->setTextureRect(Rect(0, 0, frameSize.width, frameSize.height));
		this->setVisible(false);
		break;
	}
	case CourceType::C01: {

		this->setTextureRect(Rect(0, 0, frameSize.width, frameSize.height));
		this->setBody(PhysicsBody::createEdgeChain(pt_d, 6));
		this->setPhysicsBody(_body);

		break;
	}
	case CourceType::C02: {

		this->setTextureRect(
				Rect(frameSize.width * 1, frameSize.height * 0, frameSize.width,
						frameSize.height));
		this->setBody(PhysicsBody::createEdgeChain(pt_f, 6));
		this->setPhysicsBody(_body);
		break;
	}
	case CourceType::C03: {
		this->setTextureRect(
				Rect(frameSize.width * 2, frameSize.height * 0, frameSize.width,
						frameSize.height));
		this->setBody(PhysicsBody::createEdgeChain(pt_a_x, 3));
		this->setBody2(PhysicsBody::createEdgeChain(pt_c_y, 4));
		_body->addShape(this->getBody2()->getShape(0));
		this->setPhysicsBody(_body);
		break;
	}
	case CourceType::C04: {
		this->setTextureRect(
				Rect(frameSize.width * 3, frameSize.height * 0, frameSize.width,
						frameSize.height));
		this->setBody(PhysicsBody::createEdgeChain(pt_d_y, 6));
		this->setPhysicsBody(_body);
		break;
	}
	case CourceType::C05: {
		this->setTextureRect(
				Rect(frameSize.width * 4, frameSize.height * 0, frameSize.width,
						frameSize.height));
		this->setBody(PhysicsBody::createEdgeChain(pt_e, 2));
		this->setBody2(PhysicsBody::createEdgeChain(pt_e_x, 2));
		_body->addShape(this->getBody2()->getShape(0));
		this->setPhysicsBody(_body);
		break;
	}
	case CourceType::C06: {
		this->setTextureRect(
				Rect(frameSize.width * 0, frameSize.height * 1, frameSize.width,
						frameSize.height));
		this->setBody(PhysicsBody::createEdgeChain(pt_c, 4));
		this->setBody2(PhysicsBody::createEdgeChain(pt_a_xy, 3));
		_body->addShape(this->getBody2()->getShape(0));
		this->setPhysicsBody(_body);
		break;
	}
	case CourceType::C07: {
		this->setTextureRect(
				Rect(frameSize.width * 1, frameSize.height * 1, frameSize.width,
						frameSize.height));
		this->setBody(PhysicsBody::createEdgeChain(pt_e, 2));
		this->setBody2(PhysicsBody::createEdgeChain(pt_a_x, 3));
		_body->addShape(this->getBody2()->getShape(0));
		this->setBody3(PhysicsBody::createEdgeChain(pt_a_xy, 3));
		_body->addShape(this->getBody3()->getShape(0));
		this->setPhysicsBody(_body);
		break;
	}
	case CourceType::C08: {
		this->setTextureRect(
				Rect(frameSize.width * 2, frameSize.height * 1, frameSize.width,
						frameSize.height));
		this->setBody(PhysicsBody::createEdgeChain(pt_f_x, 6));
		this->setPhysicsBody(_body);
		break;
	}
	case CourceType::C09: {
		this->setTextureRect(
				Rect(frameSize.width * 3, frameSize.height * 1, frameSize.width,
						frameSize.height));
		this->setBody(PhysicsBody::createEdgeChain(pt_a, 3));
		this->setBody2(PhysicsBody::createEdgeChain(pt_c_xy, 4));
		_body->addShape(this->getBody2()->getShape(0));

		this->setPhysicsBody(_body);
		break;
	}
	case CourceType::C10: {
		this->setTextureRect(
				Rect(frameSize.width * 4, frameSize.height * 1, frameSize.width,
						frameSize.height));
		this->setBody(PhysicsBody::createEdgeChain(pt_b, 2));
		this->setBody2(PhysicsBody::createEdgeChain(pt_b_y, 2));
		_body->addShape(this->getBody2()->getShape(0));

		this->setPhysicsBody(_body);
		break;
	}
	case CourceType::C11: {
		this->setTextureRect(
				Rect(frameSize.width * 0, frameSize.height * 2, frameSize.width,
						frameSize.height));
		this->setBody(PhysicsBody::createEdgeChain(pt_a, 3));
		this->setBody2(PhysicsBody::createEdgeChain(pt_a_x, 3));
		_body->addShape(this->getBody2()->getShape(0));
		this->setBody3(PhysicsBody::createEdgeChain(pt_b_y, 2));
		_body->addShape(this->getBody3()->getShape(0));

		this->setPhysicsBody(_body);
		break;
	}
	case CourceType::C12: {
		this->setTextureRect(
				Rect(frameSize.width * 1, frameSize.height * 2, frameSize.width,
						frameSize.height));
		this->setBody(PhysicsBody::createEdgeChain(pt_c_x, 4));
		this->setBody2(PhysicsBody::createEdgeChain(pt_a_y, 3));
		_body->addShape(this->getBody2()->getShape(0));

		this->setPhysicsBody(_body);
		break;
	}
	case CourceType::C13: {
		this->setTextureRect(
				Rect(frameSize.width * 2, frameSize.height * 2, frameSize.width,
						frameSize.height));
		this->setBody(PhysicsBody::createEdgeChain(pt_a, 3));
		this->setBody2(PhysicsBody::createEdgeChain(pt_a_y, 3));
		_body->addShape(this->getBody2()->getShape(0));
		this->setBody3(PhysicsBody::createEdgeChain(pt_e_x, 2));
		_body->addShape(this->getBody3()->getShape(0));

		this->setPhysicsBody(_body);
		break;
	}

	case CourceType::C14: {
		this->setTextureRect(
				Rect(frameSize.width * 3, frameSize.height * 2, frameSize.width,
						frameSize.height));
		this->setBody(PhysicsBody::createEdgeChain(pt_b, 2));
		this->setBody2(PhysicsBody::createEdgeChain(pt_a_y, 3));
		_body->addShape(this->getBody2()->getShape(0));
		this->setBody3(PhysicsBody::createEdgeChain(pt_a_xy, 3));
		_body->addShape(this->getBody3()->getShape(0));

		this->setPhysicsBody(_body);
		break;
	}
	case CourceType::C15: {
		this->setTextureRect(
				Rect(frameSize.width * 4, frameSize.height * 2, frameSize.width,
						frameSize.height));
		this->setBody(PhysicsBody::createEdgeChain(pt_a, 3));
		this->setBody2(PhysicsBody::createEdgeChain(pt_a_y, 3));
		_body->addShape(this->getBody2()->getShape(0));
		this->setBody3(PhysicsBody::createEdgeChain(pt_a_x, 3));
		_body->addShape(this->getBody3()->getShape(0));
		this->setBody4(PhysicsBody::createEdgeChain(pt_a_xy, 3));
		_body->addShape(this->getBody4()->getShape(0));

		this->setPhysicsBody(_body);
		break;
	}

	}

	if (_body != NULL) {

		this->getBody()->setCollisionBitmask(ballCatg);
		this->getBody()->setCategoryBitmask(courceCatg);
		//this->getBody()->setContactTestBitmask(ballCatg);
		this->getBody()->setTag(1);
		this->setVisible(true);
		//this->setScale(scale_);

		//	auto material = PHYSICSBODY_MATERIAL_DEFAULT;
		//	material.restitution = 0.0f;
		//for (auto x : this->getBody()->getShapes()) {
		//x->setRestitution(0.0f);
		//}

	} else {
		this->setVisible(false);
	}

}

float Cource::GetRad() {

	return -this->getRotation() / 180 * M_PI;
//return Rad0;

}

float Cource::TrkCrossChk(cocos2d::Vec2 Pt11, cocos2d::Vec2 Pt12,
		cocos2d::Vec2 Pt21, cocos2d::Vec2 Pt22) {

	Vec2 _pt11 = Vec2::ZERO;
	Vec2 _pt12 = Pt12 - Pt11;
	Vec2 _pt21 = Pt21 - Pt11;
	Vec2 _pt22 = Pt22 - Pt11;

	float _rad = _pt12.getAngle();
//CC_RADIANS_TO_DEGREES( radian )
	_rad += 2 * M_PI;
	while (_rad >= 2 * M_PI) {
		_rad -= 2 * M_PI;
	}

	_pt12.rotate(Vec2::ZERO, -_rad);
	_pt21.rotate(Vec2::ZERO, -_rad);
	_pt22.rotate(Vec2::ZERO, -_rad);

//交差しているかのチェック。
	if (_pt21.y != _pt22.y) {

		float A = (_pt22.x * _pt21.y - _pt21.x * _pt22.y) / (_pt21.y - _pt22.y);

		if (A >= 0 && A <= _pt12.x) {

			if (_pt21.y * _pt22.y < 0) {
				return -1;
			}
		}
	}

	float d = 0;
	float d_ = 0;

	d = LinePointLength(Pt11, Pt12, Pt21);
	d_ = LinePointLength(Pt11, Pt12, Pt22);
	if (d > d_) {
		d = d_;
	}
	d_ = LinePointLength(Pt21, Pt22, Pt11);
	if (d > d_) {
		d = d_;
	}
	d_ = LinePointLength(Pt21, Pt22, Pt12);
	if (d > d_) {
		d = d_;
	}

	return d;

}

float Cource::LinePointLength(Vec2 Pt11, Vec2 Pt12, Vec2 x) {

	Vec2 _pt11 = Vec2::ZERO;
	Vec2 _pt12 = Pt12 - Pt11;
	Vec2 A = x - Pt11;

	float _rad = _pt12.getAngle();
//CC_RADIANS_TO_DEGREES( radian )
	_rad += 2 * M_PI;
	while (_rad >= 2 * M_PI) {
		_rad -= 2 * M_PI;
	}

	_pt12.rotate(Vec2::ZERO, -_rad);
	A.rotate(Vec2::ZERO, -_rad);

	if (A.x <= 0) {
		return A.getLength();
	} else if (A.x >= _pt12.x) {
		return A.getDistance(_pt12);
	} else {

		return abs(A.y);
	}

}

void Cource::Action1() {

	this->onUpDateListener = NULL;

}
void Cource::Action2() {

}
void Cource::Action3() {

}
void Cource::Action4() {

}
