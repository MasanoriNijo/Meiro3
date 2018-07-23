/*
 * Sprite2.cpp
 *
 *  Created on: 2017/03/05
 *      Author: m.nijo
 */

#include "Sprite2.h"

const int zyaraCatg = 1 << 0;
const int handCatg = 1 << 1;
const int pointCatg = 1 << 2;
const int dmgCatg = 1 << 3;
const int nikuCatg = 1 << 4;
const int kabeCatg = 1 << 5;

Sprite2::Sprite2() :
		_point(NULL), _body(NULL), _parentSp(NULL) {
	// TODO 自動生成されたコンストラクター・スタブ

}
Sprite2::~Sprite2() {
	// TODO Auto-generated destructor stub
	CC_SAFE_RELEASE_NULL(_parentSp);
	CC_SAFE_RELEASE_NULL(_point);
	CC_SAFE_RELEASE_NULL(_body);

}
Sprite2* Sprite2::create() {
	Sprite2 *ret = new Sprite2();
	if (ret && ret->init()) {
		ret->autorelease();

		return ret;
	}
	CC_SAFE_DELETE(ret);

	return ret;
}
Sprite2* Sprite2::create(const std::string& filename) {
	Sprite2 *ret = new Sprite2();
	if (ret && ret->initWithFile(filename)) {
		ret->autorelease();

		return ret;
	}
	CC_SAFE_DELETE(ret);

	return ret;
}
Sprite2* Sprite2::createWithTexture(Texture2D *texture) {

	Sprite2 *ret = new Sprite2();
	if (ret && ret->initWithTexture(texture)) {
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return ret;

}

Sprite2* Sprite2::createWithTexture(Texture2D *texture, Rect rct_) {

	Sprite2 *ret = new Sprite2();
	if (ret && ret->initWithTexture(texture)) {
		ret->setTextureRect(rct_);
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);

	return ret;

}

void Sprite2::MadePoint() {

	this->setPoint(Sprite2::create("point2.png"));
	for (int i = 0; i < 4; ++i) {
		auto frame = SpriteFrame::createWithTexture(_point->getTexture(),
				Rect(60 * i, 0, 60, 60));
		_pointFrame.pushBack(frame);

	}
	for (int i = 2; i >= 1; i--) {
		auto frame = SpriteFrame::createWithTexture(_point->getTexture(),
				Rect(60 * i, 0, 60, 60));
		_pointFrame.pushBack(frame);

	}
	_point->setTextureRect(Rect(0, 0, 60, 60));

	auto animation = Animation::createWithSpriteFrames(_pointFrame);
	animation->setDelayPerUnit(0.1f);
	auto rot_ = RepeatForever::create(RotateBy::create(1, 180));
	auto rept = RepeatForever::create(Animate::create(animation));

	//_point->runAction(rot_);
	_point->runAction(rept);

	this->setBody(PhysicsBody::createCircle(15));
	_body->setGravityEnable(false);
	_body->setDynamic(true);
	_body->setEnable(true);
	_body->setRotationEnable(false);
	_body->setCollisionBitmask(zyaraCatg | kabeCatg | handCatg);
	_body->setCategoryBitmask(pointCatg);
	_body->setContactTestBitmask(zyaraCatg | kabeCatg | handCatg);
	_body->setTag(pointCatg);
	_point->setPhysicsBody(_body);
	//_body->setVelocity(Vec2(100,100));

	this->addChild(_point);

}
void Sprite2::ShowPoint(bool flg) {

	if (!_point) {
		return;
	}

	pointFlg = flg;
	_point->setVisible(flg);
	_body->setEnable(flg);

}
void Sprite2::DelShow(Vec2 pt_) {

	//return;

	if (!_point) {
		return;
	}

	//エフェクトで消える。
	int c = arc4random() % static_cast<int>(360);
	Vec2 pt;

	pt.set(pt_);
	pt.normalize();
	this->getBody()->setVelocity(pt * 100);
	/*
	 auto move_ = MoveBy::create(0.5, pt * 300);
	 auto func_ = CallFuncN::create([this](Node* nd) {

	 this->ShowPoint(false);

	 });

	 auto seq_ = Sequence::create(move_, func_, move_->reverse(), NULL);
	 _point->runAction(seq_);
	 */
}
void Sprite2::DelShow() {

	return;
	if (!_point) {
		return;
	}

	//エフェクトで消える。
	int c = arc4random() % static_cast<int>(360);
	Vec2 pt;

	pt.set(1, 0);
	pt.rotate(Vec2::ZERO, c);
	auto move_ = MoveBy::create(0.5, pt * 300);
	auto func_ = CallFuncN::create([this](Node* nd) {

		this->ShowPoint(false);

	});

	auto seq_ = Sequence::create(move_, func_, move_->reverse(), NULL);
	_point->runAction(seq_);

}
void Sprite2::SetPointPos(Vec2 pt) {
//比率
	if (!_point) {
		return;
	}

	pt.x *= this->getContentSize().width;
	pt.y *= this->getContentSize().height;

	_point->setPosition(pt);

}

void Sprite2::SetRot(float kaku_) {

	pt_.set(_ctPt);
	pt_.rotate(Vec2::ZERO, -CC_DEGREES_TO_RADIANS(kaku_));
	this->setPosition(_pinPt - pt_);
	this->setRotation(kaku_);

}
void Sprite2::SetPos(Vec2 pt_) {

	this->setPinPt(pt_);
	this->SetRot(this->getRotation());

}
void Sprite2::SetRotPos(float kaku_, Vec2 pt_) {
	this->setPinPt(pt_);
	this->SetRot(kaku_);
}

void Sprite2::SetRot2(float kaku_) {
	//ピン止めするように回転する.親ノードの親ノードに所属している場合
	pt_.set(_ctPt);
	kaku_ += _parentSp->getRotation();
	pt_.rotate(Vec2::ZERO, -CC_DEGREES_TO_RADIANS(kaku_));

	pt2_.set(
			_pinPt
					- Vec2(_parentSp->getContentSize().width / 2,
							_parentSp->getContentSize().height / 2));
	pt2_.rotate(Vec2::ZERO, -CC_DEGREES_TO_RADIANS(_parentSp->getRotation()));
	pt2_ += _parentSp->getPosition();

	this->setPosition(pt2_ - pt_);
	this->setRotation(kaku_);
}
void Sprite2::SetPos2(Vec2 pt_) {
	//ピン止めするように回転する.親ノードの親ノードに所属している場合
	this->setPinPt(pt_);
	this->SetRot2(this->getRotation());
}
void Sprite2::SetRotPos2(float kaku_, Vec2 pt_) {
	//ピン止めするように回転する.親ノードの親ノードに所属している場合
	this->setPinPt(pt_);
	this->SetRot2(kaku_);
}

void Sprite2::SetRot3(float kaku_) {
	//ピン止めするように回転する.親ノードの親ノードの親ノードに所属している場合
	pt_.set(_ctPt);
	kaku_ += _parentSp->getRotation();
	kaku_ += _parentSp->getParent()->getRotation();
	pt_.rotate(Vec2::ZERO, -CC_DEGREES_TO_RADIANS(kaku_));

	pt2_.set(
			_pinPt
					- Vec2(_parentSp->getContentSize().width / 2,
							_parentSp->getContentSize().height / 2));
	pt2_.rotate(Vec2::ZERO, -CC_DEGREES_TO_RADIANS(_parentSp->getRotation()));
	pt2_ += _parentSp->getPosition();

	pt3_.set(
			pt2_
					- Vec2(_parentSp->getParent()->getContentSize().width / 2,
							_parentSp->getParent()->getContentSize().height
									/ 2));
	pt3_.rotate(Vec2::ZERO,
			-CC_DEGREES_TO_RADIANS(_parentSp->getParent()->getRotation()));
	pt3_ += _parentSp->getParent()->getPosition();

	this->setPosition(pt3_ - pt_);
	this->setRotation(kaku_);
}
void Sprite2::SetPos3(Vec2 pt_) {
	//ピン止めするように回転する.親ノードの親ノードの親ノードに所属している場合
	this->setPinPt(pt_);
	this->SetRot3(this->getRotation());
}
void Sprite2::SetRotPos3(float kaku_, Vec2 pt_) {
	//ピン止めするように回転する.親ノードの親ノードの親ノードに所属している場合
	this->setPinPt(pt_);
	this->SetRot3(kaku_);
}
Vec2 Sprite2::GetLocalPt(Vec2 pt) {
	//ペアレントノードでの座標点を、このローカル座標に変換する。

	if (this->getParent()) {
		Node* nd = this->getParent();

		pt2_.set(this->getContentSize().width * this->getAnchorPoint().x,
				this->getContentSize().height * this->getAnchorPoint().y);
		pt2_.rotate(Vec2::ZERO, -CC_DEGREES_TO_RADIANS(this->getRotation()));
		pt_.set(pt - this->getPosition());
		pt_ -= pt2_;
		pt_.rotate(Vec2::ZERO, CC_DEGREES_TO_RADIANS(this->getRotation()));
	}

	return pt_;

}
void Sprite2::setVisible(bool flg) {

	Sprite::setVisible(flg);
	if (_body) {

		if (pointFlg) {
			_point->setVisible(flg);
			_body->setEnable(flg);
		} else {

			if (!flg) {
				_point->setVisible(flg);
				_body->setEnable(flg);
			}

		}

	}
}
float Sprite2::ChgKaku(float rad) {

	//反時計のRadian0-2ΠをSprite用の角度に変換する。時計回り0-360°
	x_ = -CC_RADIANS_TO_DEGREES(rad);

	return NomlKaku(x_);

}
float Sprite2::ChgRad(float kaku) {
	//時計周りの角度0-360度をVec2用のRadian0-2Πに変換する。反時計回り　Vec2用
	x_ = -CC_DEGREES_TO_RADIANS(kaku);
	return NomlRad(x_);
}
float Sprite2::NomlKaku(float kaku) {

	x_ = kaku;

	while (x_ >= 360) {
		x_ -= 360;
	}
	while (x_ < 0) {
		x_ += 360;
	}

	return x_;

}
float Sprite2::NomlRad(float rad) {

	x_ = rad;
	while (x_ >= 2 * M_PI) {
		x_ -= 2 * M_PI;
	}
	while (x_ < 0) {
		x_ += 2 * M_PI;
	}

	return x_;

}

bool Sprite2::BetweenKaku(float x, float min_, float max_) {

	//指定の間にあるかどうか？
	min_ = this->NomlKaku(min_);
	max_ = this->NomlKaku(max_);
	x = this->NomlKaku(x);

	if (min_ < max_) {
		if ((min_ < x) && (max_ > x)) {
			return true;
		} else {
			return false;
		}
	} else {
		if ((max_ > x && x >= 0) || (min_ < x && x <= 360)) {
			return true;
		} else {
			return false;
		}
	}

}
bool Sprite2::BetweenRad(float x, float min_, float max_) {
	//指定の間にあるかどうか？
	min_ = this->NomlRad(min_);
	max_ = this->NomlRad(max_);
	x = this->NomlRad(x);
	if (min_ < max_) {
		if ((min_ < x) && (max_ > x)) {
			return true;
		} else {
			return false;
		}
	} else {
		if ((max_ > x && x >= 0) || (min_ < x && x <= 2 * M_PI)) {
			return true;
		} else {
			return false;
		}
	}
}

Vec2 Sprite2::ChaseA(float dt) {

	ChaseA(chA, this->getPosition(), chv, dt);
	this->setPosition(pt_);
	return pt_;
}
Vec2 Sprite2::ChaseA(Vec2 A, Vec2 chaser_, float v_, float dt) {
	//chaser_をAに近づける。速度v_　時間dt_

	chA.set(A);
	chch.set(chaser_);
	chv = v_;

	pt_.set(chaser_);
	pt2_.set(A - chaser_);
	pt2_.normalize();

	if ((A - pt_).length() > v_ * dt) {
		chsFlg = false;
		pt_ += pt2_ * v_ * dt;

//			const char *str0 = "ChaseA_false";
//			log("%s", str0);
		ndt_ =0;
		return pt_;
	} else {

//		const char *str1 = "ChaseA_true";
//		log("%s", str1);
		ndt_ = dt - (A - pt_).length() / v_;
		pt_.set(A);
		chsFlg = true;
		chsingFlg = false;
		return pt_;
	}
}
float Sprite2::ChaseA(float A, float chaser_, float v_, float dt) {

	//chaser_をAに近づける。速度v_　時間dt_
	x_ = chaser_;
	chsFlg = true;
	if (A - x_ > v_ * dt) {
		chsFlg = false;
		x_ += v_ * dt;
	}
	if (A - x_ < -v_ * dt) {
		chsFlg = false;
		x_ -= v_ * dt;
	}

	return x_;

}

float Sprite2::ChaseB(float A, float vA, float chaser_, float v_, float dt) {
	//移動予測して追う
	x_ = chaser_;
	chsFlg = true;
	if (A + vA * dt - x_ > v_ * dt) {
		chsFlg = false;
		x_ += v_ * dt;
		return x_;
	}
	if (A + vA * dt - x_ < -v_ * dt) {
		chsFlg = false;
		x_ -= v_ * dt;
		return x_;
	}

	x_ = A;
	return x_;
}
Vec2 Sprite2::ChaseB(Vec2 A, Vec2 vA, Vec2 chaser_, float v_, float dt) {
	//移動予測して追う
	pt_.set(chaser_);

	pt2_.set(A + vA * dt - chaser_);
	pt2_.normalize();
	chsFlg = true;
	if ((A - pt_).length() > v_ * dt) {
		chsFlg = false;
		pt_ += pt2_ * v_ * dt;
	}

	return pt_;
}

//Vec2 rndR_; //ランダム回転半径
//Vec2 rndrad_; //ランダム回転速度ラジアン
float Sprite2::ChaseC(float A, float chaser_, float v_, float dt) {

	rndR_.rotate(Vec2::ZERO, rndrad_ * dt);

	x_ = chaser_;
	chsFlg = true;
	if (A + rndR_.x - x_ > v_ * dt) {
		chsFlg = false;
		x_ += v_ * dt;
	}
	if (A + rndR_.x - x_ < -v_ * dt) {
		chsFlg = false;
		x_ -= v_ * dt;
	}

	return x_;

}
Vec2 Sprite2::ChaseC(Vec2 A, Vec2 chaser_, float v_, float dt) {

	pt_.set(chaser_);
	rndR_.rotate(Vec2::ZERO, rndrad_ * dt);
	pt2_.set(A + rndR_ - chaser_);
	pt2_.normalize();
	//chsFlg = true;

//	if ((A - pt_).length() > v_ * dt) {
	chsFlg = false;
	pt_ += pt2_ * v_ * dt;
//	}

	return pt_;
}
