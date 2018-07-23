#include "cocos2d.h"
#include "Ball.h"
#include "cmath"

USING_NS_CC;

Ball::Ball() :
		_dumy(NULL), _ballstate(BallState::T1), moveFlg(NULL), updateFlg(false), _frames(
		NULL), _updateFlg(false), _level(1), _updateListener(NULL), chk1(false), chk2(false), cnt1(0), cnt2(
				0), lifePoint(3), _mMeder(NULL), _dctPt(NULL), _dctPt2(NULL) {

}
Ball::~Ball() {

	CC_SAFE_RELEASE_NULL(_dumy);
	CC_SAFE_RELEASE_NULL(_mMeder);
	CC_SAFE_RELEASE_NULL(_dctPt);
	CC_SAFE_RELEASE_NULL(_dctPt2);
}

bool Ball::init() {

	if (!Sprite::initWithFile("balls.png")) {
		return false;
	}
	auto winSize = Director::getInstance()->getWinSize();

	frameSize = Size(this->getContentSize().width / BALL_FRAME_COUNT, this->getContentSize().height);

	this->setTextureRect(Rect(frameSize.width, 0, frameSize.width, frameSize.height));

//	this->setDctPt(Sprite::createWithTexture(this->getTexture()));
//	this->getDctPt()->setTextureRect(Rect(frameSize.width, 0, frameSize.width, frameSize.height));
//	this->getDctPt()->setScale(0.5);
//
//	this->setDctPt(Sprite::createWithTexture(this->getTexture()));
//	this->getDctPt()->setTextureRect(Rect(frameSize.width, 0, frameSize.width, frameSize.height));
//	this->getDctPt()->setScale(0.5);
//
//	this->setDctPt2(Sprite::create("dotr.png"));

//Vector<SpriteFrame *> frames;
	/*
	 for (int i = 0; i < BALL_FRAME_COUNT; ++i) {
	 auto frame = SpriteFrame::create("ball.png",
	 Rect(frameSize.width * i, 0, frameSize.width,
	 frameSize.height));
	 _frames.pushBack(frame);

	 }
	 */
	this->setDumy(Sprite::createWithTexture(this->getTexture(), this->getTextureRect()));
	this->getDumy()->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
	this->addChild(this->getDumy());
	this->getDumy()->setVisible(false);
	/*
	 auto material = PHYSICSBODY_MATERIAL_DEFAULT;
	 material.restitution = 0.8f;
	 material.friction = 0;
	 material.density = 0.1f;


	 this->setBody(PhysicsBody::createCircle(frameSize.width / 2, material));
	 this->setPhysicsBody(this->_body);
	 //this->veloLimit = 20;
	 this->_body->setGravityEnable(false);
	 this->_body->setContactTestBitmask(ballCatg);
	 this->_body->setCategoryBitmask(ballCatg);
	 this->_body->setCollisionBitmask(courceCatg);
	 this->_body->setContactTestBitmask(itemCatg | startCatg | goalCatg);
	 this->_body->setTag(0);
	 this->_body->setDynamic(true);
	 this->_body->setRotationEnable(false);	//��]�����Ȃ��B
	 this->_body->setVelocityLimit(this->veloLimit);
	 _body->setGravityEnable(false);
	 */
	return true;
}
void Ball::setContactAction(std::function<void(Ball*)> action) {

	this->onContactListener = action;

}
void Ball::setUpdateAction(std::function<void(Ball*)> action) {

	this->unscheduleUpdate();
	this->onUpDateListener = action;
	updateFlg = true;
	this->scheduleUpdate();

}
void Ball::update(float dt) {

	if (onUpDateListener && updateFlg) {
		onUpDateListener(this);
	}

}

void Ball::Fin() {

	if (this->onFinishListener) {
		onFinishListener(this);
	}

}
void Ball::NomlMove3(float dt, Vec2 dct_) {

	if (dt == 0) {
		return;
	}

	//指定した方向の分岐点まで進む。

	//現在の自分のポイントをセット
	mapPt_.set(_mMeder->ChgPositionFromImageToMap(this->getPosition()));

	//前回のセットのチェイスが完了しない場合実行。
//	if (!this->chsFlg) {
//		this->ChaseA(dt);
//		if (this->chsFlg) {
//			this->NomlMove3(ndt_, dct_);
//		}
//		//const char *str0 = "ch01";
//		//log("%s", str0);
//		return;
//	}

// return;
///const char *str2 = "ch02";
//log("%s", str2);

//	mapImgPt_.set(_mMeder->ChgPositionFromMapToImage(mapPt_));

	aa = this->ChgKaku(dct_.getAngle() - M_PI / 8);
	aa /= 45;
	aa_ = (int) aa;
	spd_ = spd1 + (dct_.length() - asobi_) * 4;
	if (spd_ < spd1) {
		spd_ = spd1;
	}
	if (spd_ > spd2) {
		spd_ = spd2;
	}

	if (dct_.length() < asobi_) {

		const char *str0 = "dct_.length() < asobi_";
		log("%s", str0);

		if (!this->chsFlg) {
			this->ChaseA(dt);

			if (this->chsFlg) {

				this->NomlMove3(ndt_, dct_);
			}

			return;
		}
		return;
	} else {

		const char *str1 = "dct_.length() > asobi_";
		log("%s", str1);

		switch (aa_) {

		case 0: {

			if (this->dct_ != 2) {
				mapPt_.set(_mMeder->GetJunctionPoint(mapPt_, Vec2(1, 0)));
				mapImgPt_.set(_mMeder->ChgPositionFromMapToImage(mapPt_));
				movePt_.set(this->ChaseA(mapImgPt_, this->getPosition(), spd_, dt));
				this->dct_ = 2;
			}
			break;
		}
		case 1: {

			if (this->dct_ != 2) {
				mapPt_.set(_mMeder->GetJunctionPoint(mapPt_, Vec2(1, 0)));
				mapImgPt_.set(_mMeder->ChgPositionFromMapToImage(mapPt_));
				movePt_.set(this->ChaseA(mapImgPt_, this->getPosition(), spd_, dt));
				this->dct_ = 2;
			} else if (this->dct_ != 3) {
				mapPt_.set(_mMeder->GetJunctionPoint(mapPt_, Vec2(0, -1)));
				mapImgPt_.set(_mMeder->ChgPositionFromMapToImage(mapPt_));
				movePt_.set(this->ChaseA(mapImgPt_, this->getPosition(), spd_, dt));
				this->dct_ = 3;
			}
			break;

		}
		case 2: {

			if (this->dct_ != 3) {
				mapPt_.set(_mMeder->GetJunctionPoint(mapPt_, Vec2(0, -1)));
				mapImgPt_.set(_mMeder->ChgPositionFromMapToImage(mapPt_));
				movePt_.set(this->ChaseA(mapImgPt_, this->getPosition(), spd_, dt));
				this->dct_ = 3;
			}
			break;

		}
		case 3: {

			if (this->dct_ != 3) {
				mapPt_.set(_mMeder->GetJunctionPoint(mapPt_, Vec2(0, -1)));
				mapImgPt_.set(_mMeder->ChgPositionFromMapToImage(mapPt_));
				movePt_.set(this->ChaseA(mapImgPt_, this->getPosition(), spd_, dt));
				this->dct_ = 3;
			} else if (this->dct_ != 4) {
				mapPt_.set(_mMeder->GetJunctionPoint(mapPt_, Vec2(-1, 0)));
				mapImgPt_.set(_mMeder->ChgPositionFromMapToImage(mapPt_));
				movePt_.set(this->ChaseA(mapImgPt_, this->getPosition(), spd_, dt));
				this->dct_ = 4;
			}
			break;

		}
		case 4: {
			if (this->dct_ != 4) {
				mapPt_.set(_mMeder->GetJunctionPoint(mapPt_, Vec2(-1, 0)));
				mapImgPt_.set(_mMeder->ChgPositionFromMapToImage(mapPt_));
				movePt_.set(this->ChaseA(mapImgPt_, this->getPosition(), spd_, dt));
				this->dct_ = 4;
			}
			break;
		}
		case 5: {

			if (this->dct_ != 4) {
				mapPt_.set(_mMeder->GetJunctionPoint(mapPt_, Vec2(-1, 0)));
				mapImgPt_.set(_mMeder->ChgPositionFromMapToImage(mapPt_));
				movePt_.set(this->ChaseA(mapImgPt_, this->getPosition(), spd_, dt));
				this->dct_ = 4;
			} else if (this->dct_ != 1) {
				mapPt_.set(_mMeder->GetJunctionPoint(mapPt_, Vec2(0, 1)));
				mapImgPt_.set(_mMeder->ChgPositionFromMapToImage(mapPt_));
				movePt_.set(this->ChaseA(mapImgPt_, this->getPosition(), spd_, dt));
				this->dct_ = 1;
			}

			break;
		}
		case 6: {
			if (this->dct_ != 1) {
				mapPt_.set(_mMeder->GetJunctionPoint(mapPt_, Vec2(0, 1)));
				mapImgPt_.set(_mMeder->ChgPositionFromMapToImage(mapPt_));
				movePt_.set(this->ChaseA(mapImgPt_, this->getPosition(), spd_, dt));
				this->dct_ = 1;
			}

			break;
		}
		case 7: {
			if (this->dct_ != 1) {
				mapPt_.set(_mMeder->GetJunctionPoint(mapPt_, Vec2(0, 1)));
				mapImgPt_.set(_mMeder->ChgPositionFromMapToImage(mapPt_));
				movePt_.set(this->ChaseA(mapImgPt_, this->getPosition(), spd_, dt));
				this->dct_ = 1;
			} else if (this->dct_ != 2) {
				mapPt_.set(_mMeder->GetJunctionPoint(mapPt_, Vec2(1, 0)));
				mapImgPt_.set(_mMeder->ChgPositionFromMapToImage(mapPt_));
				movePt_.set(this->ChaseA(mapImgPt_, this->getPosition(), spd_, dt));
				this->dct_ = 2;
			}
			break;

		}
		}
		if (!this->chsFlg) {
			this->ChaseA(dt);

			if (this->chsFlg) {
				this->NomlMove3(ndt_, dct_);
			}

			return;
		}
		return;
	}
}

void Ball::NomlMove(float dt, Vec2 dct_) {

	//前回のセットのチェイスが完了しない場合実行。
	if (!this->chsFlg) {
		this->ChaseA(dt);

		if (this->chsFlg) {

			this->NomlMove(ndt_, dct_);
		}

		//const char *str0 = "ch01";
		//log("%s", str0);
		return;
	}

	//遊び
	if (dct_.length() < asobi_) {
		return;
	}

	aa = this->ChgKaku(dct_.getAngle() - M_PI / 8);
	aa /= 45;

	aa_ = (int) aa;

	spd_ = spd1 + (dct_.length() - asobi_) * 8;

	if (spd_ < spd1) {
		spd_ = spd1;
	}

	if (spd_ > spd2) {
		spd_ = spd2;
	}

	/*
	 if (aa_ == k) {
	 straitTime_ += dt;
	 if (straitTime_ > straitTime) {
	 spd_ = spd2;
	 }
	 } else {
	 straitTime_ = 0;
	 spd_ = spd1;
	 }
	 */
	//aa_ = k;
	//this->spd_;
	/*
	 movePt_.set(
	 this->ChaseA(this->getPosition() + dct_ * 100, this->getPosition(),
	 spd_, dt));

	 this->setPosition(movePt_);
	 */
	// return;
	///const char *str2 = "ch02";
	//log("%s", str2);
	mapPt_.set(_mMeder->ChgPositionFromImageToMap(this->getPosition()));
	mapImgPt_.set(_mMeder->ChgPositionFromMapToImage(mapPt_));

	if (dct_.length() == 0) {

		movePt_.set(this->ChaseA(mapImgPt_, this->getPosition(), spd_, dt));
		this->setPosition(movePt_);
		return;
	}

	switch (aa_) {

	case 0: {

		if (_mMeder->GetMapStatus(mapPt_ + Vec2(1, 0)) != 3) {
			movePt_.set(this->ChaseA(mapImgPt_ + Vec2(w, 0), this->getPosition(), spd_, dt));
			this->dct_ = 2;
		} else {
			movePt_.set(this->ChaseA(mapImgPt_, this->getPosition(), spd_, dt));
			this->dct_ = 0;
		}
		break;
	}
	case 1: {

		if (this->dct_ == 3 || this->dct_ != 2) {
			if (_mMeder->GetMapStatus(mapPt_ + Vec2(1, 0)) != 3) {
				movePt_.set(this->ChaseA(mapImgPt_ + Vec2(w, 0), this->getPosition(), spd_ / 2, dt));
				this->dct_ = 2;
				break;
			} else if (_mMeder->GetMapStatus(mapPt_ + Vec2(0, -1)) != 3) {
				movePt_.set(this->ChaseA(mapImgPt_ + Vec2(0, -w), this->getPosition(), spd_, dt));
				this->dct_ = 3;
				break;
			}
		}
		if (this->dct_ == 2) {
			if (_mMeder->GetMapStatus(mapPt_ + Vec2(0, -1)) != 3) {
				movePt_.set(this->ChaseA(mapImgPt_ + Vec2(0, -w), this->getPosition(), spd_ / 2, dt));
				this->dct_ = 3;
				break;
			} else if (_mMeder->GetMapStatus(mapPt_ + Vec2(1, 0)) != 3) {
				movePt_.set(this->ChaseA(mapImgPt_ + Vec2(w, 0), this->getPosition(), spd_, dt));
				this->dct_ = 2;
				break;
			}
		}
		movePt_.set(this->ChaseA(mapImgPt_, this->getPosition(), spd_, dt));
		this->dct_ = 0;

		break;
	}
	case 2: {

		if (_mMeder->GetMapStatus(mapPt_ + Vec2(0, -1)) != 3) {
			movePt_.set(this->ChaseA(mapImgPt_ + Vec2(0, -w), this->getPosition(), spd_, dt));
			this->dct_ = 3;
		} else {
			movePt_.set(this->ChaseA(mapImgPt_, this->getPosition(), spd_, dt));
			this->dct_ = 0;
		}
		break;
	}
	case 3: {

		if (this->dct_ == 4 || this->dct_ != 3) {
			if (_mMeder->GetMapStatus(mapPt_ + Vec2(0, -1)) != 3) {
				movePt_.set(this->ChaseA(mapImgPt_ + Vec2(0, -w), this->getPosition(), spd_ / 2, dt));
				this->dct_ = 3;
				break;
			} else if (_mMeder->GetMapStatus(mapPt_ + Vec2(-1, 0)) != 3) {
				movePt_.set(this->ChaseA(mapImgPt_ + Vec2(-w, 0), this->getPosition(), spd_, dt));
				this->dct_ = 4;
				break;
			}
		}
		if (this->dct_ == 3) {
			if (_mMeder->GetMapStatus(mapPt_ + Vec2(-1, 0)) != 3) {
				movePt_.set(this->ChaseA(mapImgPt_ + Vec2(-w, 0), this->getPosition(), spd_ / 2, dt));
				this->dct_ = 4;
				break;
			} else if (_mMeder->GetMapStatus(mapPt_ + Vec2(0, -1)) != 3) {
				movePt_.set(this->ChaseA(mapImgPt_ + Vec2(0, -w), this->getPosition(), spd_, dt));
				this->dct_ = 3;
				break;
			}
		}
		movePt_.set(this->ChaseA(mapImgPt_, this->getPosition(), spd_, dt));
		this->dct_ = 0;

		break;
	}
	case 4: {
		if (_mMeder->GetMapStatus(mapPt_ + Vec2(-1, 0)) != 3) {
			movePt_.set(this->ChaseA(mapImgPt_ + Vec2(-w, 0), this->getPosition(), spd_, dt));
			this->dct_ = 4;
		} else {
			movePt_.set(this->ChaseA(mapImgPt_, this->getPosition(), spd_, dt));
			this->dct_ = 0;
		}
		break;
	}
	case 5: {

		if (this->dct_ == 1 || this->dct_ != 4) {
			if (_mMeder->GetMapStatus(mapPt_ + Vec2(-1, 0)) != 3) {
				movePt_.set(this->ChaseA(mapImgPt_ + Vec2(-w, 0), this->getPosition(), spd_ / 2, dt));
				this->dct_ = 4;
				break;
			} else if (_mMeder->GetMapStatus(mapPt_ + Vec2(0, 1)) != 3) {
				movePt_.set(this->ChaseA(mapImgPt_ + Vec2(0, w), this->getPosition(), spd_, dt));
				this->dct_ = 1;
				break;
			}
		}
		if (this->dct_ == 4) {
			if (_mMeder->GetMapStatus(mapPt_ + Vec2(0, 1)) != 3) {
				movePt_.set(this->ChaseA(mapImgPt_ + Vec2(0, w), this->getPosition(), spd_ / 2, dt));
				this->dct_ = 1;
				break;
			} else if (_mMeder->GetMapStatus(mapPt_ + Vec2(-1, 0)) != 3) {
				movePt_.set(this->ChaseA(mapImgPt_ + Vec2(-w, 0), this->getPosition(), spd_, dt));
				this->dct_ = 4;
				break;
			}
		}

		movePt_.set(this->ChaseA(mapImgPt_, this->getPosition(), spd_, dt));
		this->dct_ = 0;

		break;
	}
	case 6: {
		if (_mMeder->GetMapStatus(mapPt_ + Vec2(0, 1)) != 3) {
			movePt_.set(this->ChaseA(mapImgPt_ + Vec2(0, w), this->getPosition(), spd_, dt));
			this->dct_ = 1;
		} else {
			movePt_.set(this->ChaseA(mapImgPt_, this->getPosition(), spd_, dt));
			this->dct_ = 0;
		}
		break;
	}
	case 7: {
		if (this->dct_ == 2 || this->dct_ != 1) {
			if (_mMeder->GetMapStatus(mapPt_ + Vec2(0, 1)) != 3) {
				movePt_.set(this->ChaseA(mapImgPt_ + Vec2(0, w), this->getPosition(), spd_ / 2, dt));
				this->dct_ = 1;
				break;
			} else if (_mMeder->GetMapStatus(mapPt_ + Vec2(1, 0)) != 3) {
				movePt_.set(this->ChaseA(mapImgPt_ + Vec2(w, 0), this->getPosition(), spd_, dt));
				this->dct_ = 2;
				break;
			}
		}
		if (this->dct_ == 1) {
			if (_mMeder->GetMapStatus(mapPt_ + Vec2(1, 0)) != 3) {
				movePt_.set(this->ChaseA(mapImgPt_ + Vec2(w, 0), this->getPosition(), spd_ / 2, dt));
				this->dct_ = 2;
				break;
			} else if (_mMeder->GetMapStatus(mapPt_ + Vec2(0, 1)) != 3) {
				movePt_.set(this->ChaseA(mapImgPt_ + Vec2(0, w), this->getPosition(), spd_, dt));
				this->dct_ = 1;
				break;
			}
		}
		this->chsFlg = false;
		movePt_.set(this->ChaseA(mapImgPt_, this->getPosition(), spd_, dt));
		this->dct_ = 0;
		break;
	}

	}

	this->setPosition(movePt_);

}
void Ball::NomlMove2(float dt, Vec2 dct_) {

	//前回のセットのチェイスが完了しない場合実行。
	if (!this->chsFlg) {
		this->ChaseA(dt);

		if (this->chsFlg) {

			this->NomlMove(ndt_, dct_);
		}

		//const char *str0 = "ch01";
		//log("%s", str0);
		return;
	}

	//遊び
	if (dct_.length() < asobi_) {

		//止まっていたら交差点まで進む

		return;
	}

	aa = this->ChgKaku(dct_.getAngle() - M_PI / 8);
	aa /= 45;

	aa_ = (int) aa;

	spd_ = spd1 + (dct_.length() - asobi_) * 5;

	if (spd_ < spd1) {
		spd_ = spd1;
	}

	if (spd_ > spd2) {
		spd_ = spd2;
	}

	/*
	 if (aa_ == k) {
	 straitTime_ += dt;
	 if (straitTime_ > straitTime) {
	 spd_ = spd2;
	 }
	 } else {
	 straitTime_ = 0;
	 spd_ = spd1;
	 }
	 */
	//aa_ = k;
	//this->spd_;
	/*
	 movePt_.set(
	 this->ChaseA(this->getPosition() + dct_ * 100, this->getPosition(),
	 spd_, dt));

	 this->setPosition(movePt_);
	 */
	// return;
	///const char *str2 = "ch02";
	//log("%s", str2);
	mapPt_.set(_mMeder->ChgPositionFromImageToMap(this->getPosition()));
	mapImgPt_.set(_mMeder->ChgPositionFromMapToImage(mapPt_));

	if (dct_.length() == 0) {

		movePt_.set(this->ChaseA(mapImgPt_, this->getPosition(), spd_, dt));
		this->setPosition(movePt_);
		return;
	}

	switch (aa_) {

	case 0: {

		if (_mMeder->GetMapStatus(mapPt_ + Vec2(1, 0)) != 3) {
			movePt_.set(this->ChaseA(mapImgPt_ + Vec2(w, 0), this->getPosition(), spd_, dt));
			this->dct_ = 2;
		} else {
			movePt_.set(this->ChaseA(mapImgPt_, this->getPosition(), spd_, dt));
			this->dct_ = 0;
		}
		break;
	}
	case 1: {

		if (this->dct_ == 3 || this->dct_ != 2) {
			if (_mMeder->GetMapStatus(mapPt_ + Vec2(1, 0)) != 3) {
				movePt_.set(this->ChaseA(mapImgPt_ + Vec2(w, 0), this->getPosition(), spd_ / 2, dt));
				this->dct_ = 2;
				break;
			} else if (_mMeder->GetMapStatus(mapPt_ + Vec2(0, -1)) != 3) {
				movePt_.set(this->ChaseA(mapImgPt_ + Vec2(0, -w), this->getPosition(), spd_, dt));
				this->dct_ = 3;
				break;
			}
		}
		if (this->dct_ == 2) {
			if (_mMeder->GetMapStatus(mapPt_ + Vec2(0, -1)) != 3) {
				movePt_.set(this->ChaseA(mapImgPt_ + Vec2(0, -w), this->getPosition(), spd_ / 2, dt));
				this->dct_ = 3;
				break;
			} else if (_mMeder->GetMapStatus(mapPt_ + Vec2(1, 0)) != 3) {
				movePt_.set(this->ChaseA(mapImgPt_ + Vec2(w, 0), this->getPosition(), spd_, dt));
				this->dct_ = 2;
				break;
			}
		}
		movePt_.set(this->ChaseA(mapImgPt_, this->getPosition(), spd_, dt));
		this->dct_ = 0;

		break;
	}
	case 2: {

		if (_mMeder->GetMapStatus(mapPt_ + Vec2(0, -1)) != 3) {
			movePt_.set(this->ChaseA(mapImgPt_ + Vec2(0, -w), this->getPosition(), spd_, dt));
			this->dct_ = 3;
		} else {
			movePt_.set(this->ChaseA(mapImgPt_, this->getPosition(), spd_, dt));
			this->dct_ = 0;
		}
		break;
	}
	case 3: {

		if (this->dct_ == 4 || this->dct_ != 3) {
			if (_mMeder->GetMapStatus(mapPt_ + Vec2(0, -1)) != 3) {
				movePt_.set(this->ChaseA(mapImgPt_ + Vec2(0, -w), this->getPosition(), spd_ / 2, dt));
				this->dct_ = 3;
				break;
			} else if (_mMeder->GetMapStatus(mapPt_ + Vec2(-1, 0)) != 3) {
				movePt_.set(this->ChaseA(mapImgPt_ + Vec2(-w, 0), this->getPosition(), spd_, dt));
				this->dct_ = 4;
				break;
			}
		}
		if (this->dct_ == 3) {
			if (_mMeder->GetMapStatus(mapPt_ + Vec2(-1, 0)) != 3) {
				movePt_.set(this->ChaseA(mapImgPt_ + Vec2(-w, 0), this->getPosition(), spd_ / 2, dt));
				this->dct_ = 4;
				break;
			} else if (_mMeder->GetMapStatus(mapPt_ + Vec2(0, -1)) != 3) {
				movePt_.set(this->ChaseA(mapImgPt_ + Vec2(0, -w), this->getPosition(), spd_, dt));
				this->dct_ = 3;
				break;
			}
		}
		movePt_.set(this->ChaseA(mapImgPt_, this->getPosition(), spd_, dt));
		this->dct_ = 0;

		break;
	}
	case 4: {
		if (_mMeder->GetMapStatus(mapPt_ + Vec2(-1, 0)) != 3) {
			movePt_.set(this->ChaseA(mapImgPt_ + Vec2(-w, 0), this->getPosition(), spd_, dt));
			this->dct_ = 4;
		} else {
			movePt_.set(this->ChaseA(mapImgPt_, this->getPosition(), spd_, dt));
			this->dct_ = 0;
		}
		break;
	}
	case 5: {

		if (this->dct_ == 1 || this->dct_ != 4) {
			if (_mMeder->GetMapStatus(mapPt_ + Vec2(-1, 0)) != 3) {
				movePt_.set(this->ChaseA(mapImgPt_ + Vec2(-w, 0), this->getPosition(), spd_ / 2, dt));
				this->dct_ = 4;
				break;
			} else if (_mMeder->GetMapStatus(mapPt_ + Vec2(0, 1)) != 3) {
				movePt_.set(this->ChaseA(mapImgPt_ + Vec2(0, w), this->getPosition(), spd_, dt));
				this->dct_ = 1;
				break;
			}
		}
		if (this->dct_ == 4) {
			if (_mMeder->GetMapStatus(mapPt_ + Vec2(0, 1)) != 3) {
				movePt_.set(this->ChaseA(mapImgPt_ + Vec2(0, w), this->getPosition(), spd_ / 2, dt));
				this->dct_ = 1;
				break;
			} else if (_mMeder->GetMapStatus(mapPt_ + Vec2(-1, 0)) != 3) {
				movePt_.set(this->ChaseA(mapImgPt_ + Vec2(-w, 0), this->getPosition(), spd_, dt));
				this->dct_ = 4;
				break;
			}
		}

		movePt_.set(this->ChaseA(mapImgPt_, this->getPosition(), spd_, dt));
		this->dct_ = 0;

		break;
	}
	case 6: {
		if (_mMeder->GetMapStatus(mapPt_ + Vec2(0, 1)) != 3) {
			movePt_.set(this->ChaseA(mapImgPt_ + Vec2(0, w), this->getPosition(), spd_, dt));
			this->dct_ = 1;
		} else {
			movePt_.set(this->ChaseA(mapImgPt_, this->getPosition(), spd_, dt));
			this->dct_ = 0;
		}
		break;
	}
	case 7: {
		if (this->dct_ == 2 || this->dct_ != 1) {
			if (_mMeder->GetMapStatus(mapPt_ + Vec2(0, 1)) != 3) {
				movePt_.set(this->ChaseA(mapImgPt_ + Vec2(0, w), this->getPosition(), spd_ / 2, dt));
				this->dct_ = 1;
				break;
			} else if (_mMeder->GetMapStatus(mapPt_ + Vec2(1, 0)) != 3) {
				movePt_.set(this->ChaseA(mapImgPt_ + Vec2(w, 0), this->getPosition(), spd_, dt));
				this->dct_ = 2;
				break;
			}
		}
		if (this->dct_ == 1) {
			if (_mMeder->GetMapStatus(mapPt_ + Vec2(1, 0)) != 3) {
				movePt_.set(this->ChaseA(mapImgPt_ + Vec2(w, 0), this->getPosition(), spd_ / 2, dt));
				this->dct_ = 2;
				break;
			} else if (_mMeder->GetMapStatus(mapPt_ + Vec2(0, 1)) != 3) {
				movePt_.set(this->ChaseA(mapImgPt_ + Vec2(0, w), this->getPosition(), spd_, dt));
				this->dct_ = 1;
				break;
			}
		}
		this->chsFlg = false;
		movePt_.set(this->ChaseA(mapImgPt_, this->getPosition(), spd_, dt));
		this->dct_ = 0;
		break;
	}

	}

	this->setPosition(movePt_);

}

void Ball::NomlMove4(float dt, Vec2 dct_) {

//	そもそもｄｔ＝0では実行しない。
	if (dt == 0) {
		return;
	}

	if (dct_.length() == 0) {
//止まっていたら交差点まで進む
		if (!jncSetFlg) {
			movePt_.set(this->ChaseA(JuncPt, this->getPosition(), spd_, dt));
			this->setPosition(movePt_);
			if (this->JuncMapPt != Vec2::ZERO) {
				this->mapPt_.set(this->JuncMapPt);
				mapImgPt_.set(_mMeder->ChgPositionFromMapToImage(mapPt_));
			}
			jncSetFlg = true;
		}
		if (!this->chsFlg) {
			this->ChaseA(dt);
			return;
		} else {

		}
	} else if (dct_.length() < asobi_) {
		//タッチしている状態のみの遊びのとき何もしない。

		return;
	} else {
		jncSetFlg = false;	//ジャンクションセットフラグを外す。

		//動くスピードを決定する。
		spd_ = spd1 + (dct_.length() - asobi_) * 3;
		if (spd_ < spd1) {
			spd_ = spd1;
		}
		if (spd_ > spd2) {
			spd_ = spd2;
		}

		//	今回の方向を決定。

		aa = this->ChgKaku(dct_.getAngle() - M_PI / 12);
		aa /= 30;
		aa_ = (int) aa;

//		if (this->dct_ == aa_) {//今回の方向が、前回と同じか判定！
//
//			if (!this->chsFlg) {	//前回のセットのチェイスが完了しない場合実行。
//				this->ChaseA(dt);
//				if (this->chsFlg) {
//					this->NomlMove4(ndt_, dct_);
//				}
//				return;
//			}
//		} else {//前回と方向が、違う場合、再度方向を設定！

//		//現在地を再設定
//		mapPt_.set(_mMeder->ChgPositionFromImageToMap(this->getPosition()));
//		chA.set(_mMeder->ChgPositionFromMapToImage(mapPt_));

		int dctA;

		switch (aa_) {

		case 0: {

			if (_mMeder->GetMapStatus(mapPt_ + Vec2(1, 0)) != 3) {
				dctA = 2;
			} else {
				dctA = 0;
			}

			break;
		}
		case 1: {

			if (_mMeder->GetMapStatus(mapPt_ + Vec2(1, 0)) != 3) {
				dctA = 2;
				break;
			} else if (_mMeder->GetMapStatus(mapPt_ + Vec2(0, -1)) != 3) {
				dctA = 3;
				break;
			}
			dctA = 0;
			break;
		}
		case 2: {

			if (_mMeder->GetMapStatus(mapPt_ + Vec2(0, -1)) != 3) {
				dctA = 3;
				break;
			} else if (_mMeder->GetMapStatus(mapPt_ + Vec2(1, 0)) != 3) {
				dctA = 2;
				break;
			}

			dctA = 0;
			break;
		}

		case 3: {

			if (_mMeder->GetMapStatus(mapPt_ + Vec2(0, -1)) != 3) {
				dctA = 3;
			} else {
				dctA = 0;
			}
			break;
		}
		case 4: {

			if (_mMeder->GetMapStatus(mapPt_ + Vec2(0, -1)) != 3) {
				dctA = 3;
				break;
			} else if (_mMeder->GetMapStatus(mapPt_ + Vec2(-1, 0)) != 3) {
				dctA = 4;
				break;
			}
			dctA = 0;

			break;
		}

		case 5: {

			if (_mMeder->GetMapStatus(mapPt_ + Vec2(-1, 0)) != 3) {
				dctA = 4;
				break;
			} else if (_mMeder->GetMapStatus(mapPt_ + Vec2(0, -1)) != 3) {
				dctA = 3;
				break;
			}
			dctA = 0;

			break;
		}

		case 6: {
			if (_mMeder->GetMapStatus(mapPt_ + Vec2(-1, 0)) != 3) {
				dctA = 4;
			} else {
				dctA = 0;
			}
			break;
		}

		case 7: {
			if (_mMeder->GetMapStatus(mapPt_ + Vec2(-1, 0)) != 3) {
				dctA = 4;
				break;
			} else if (_mMeder->GetMapStatus(mapPt_ + Vec2(0, 1)) != 3) {
				dctA = 1;
				break;
			}

			dctA = 0;

			break;
		}

		case 8: {

			if (_mMeder->GetMapStatus(mapPt_ + Vec2(0, 1)) != 3) {
				dctA = 1;
				break;
			} else if (_mMeder->GetMapStatus(mapPt_ + Vec2(-1, 0)) != 3) {
				dctA = 4;
				break;
			}

			dctA = 0;

			break;
		}

		case 9: {

			if (_mMeder->GetMapStatus(mapPt_ + Vec2(0, 1)) != 3) {
				dctA = 1;
			} else {
				dctA = 0;
			}
			break;
		}
		case 10: {

			if (_mMeder->GetMapStatus(mapPt_ + Vec2(0, 1)) != 3) {
				dctA = 1;
				break;
			} else if (_mMeder->GetMapStatus(mapPt_ + Vec2(1, 0)) != 3) {
				dctA = 2;
				break;
			}
			dctA = 0;
			break;
		}

		case 11: {
			if (_mMeder->GetMapStatus(mapPt_ + Vec2(1, 0)) != 3) {
				dctA = 2;
				break;
			} else if (_mMeder->GetMapStatus(mapPt_ + Vec2(0, 1)) != 3) {
				dctA = 1;
				break;
			}
			dctA = 0;
			break;
		}

		}

		if (this->chsFlg) {	//前回のセットのチェイスが完了しない場合実行。
			SetChaseAFromDict(dctA, dt);
//			this->getDctPt()->setPosition(this->chA);
//			this->getDctPt2()->setPosition(this->JuncPt);

		} else {
			this->ChaseA(dt);
			if (this->chsFlg) {
				this->NomlMove4(ndt_, dct_);
			}
			return;
		}

	}
}

void Ball::NomlMove5(float dt, Vec2 dct_) {
	//	そもそもｄｔ＝0では実行しない。

	if (dt == 0) {
		return;
	}

	if (dct_.length() == 0) {
//		const char *str1 = "NomlMove5 (dct_.length() == 0)";
//		log("%s", str1);
		//止まっていたら交差点まで進む
		if (!jncSetFlg) {
			spd_=this->spd2;
			movePt_.set(this->ChaseA(JuncPt, this->getPosition(), spd_, dt));
			this->setPosition(movePt_);
			if (this->JuncMapPt != Vec2::ZERO) {
				this->mapPt_.set(this->JuncMapPt);
				mapImgPt_.set(_mMeder->ChgPositionFromMapToImage(mapPt_));
			}
			jncSetFlg = true;
		}
		if (!this->chsFlg) {
			this->ChaseA(dt);
			return;
		} else {

		}
	} else if (dct_.length() < asobi_) {
		//タッチしている状態のみの遊びのとき何もしない。

		return;
	} else {
		jncSetFlg = false;	//ジャンクションセットフラグを外す。

		//動くスピードを決定する。
//		spd_ = spd1 + (dct_.length() - asobi_) * 3;
//		if (spd_ < spd1) {
//			spd_ = spd1;
//		}
//		if (spd_ > spd2) {
//			spd_ = spd2;
//		}

		if (this->chsFlg) {	//前回のセットのチェイスが完了しない場合実行。

			const char *str1 = "NomlMove5 SetChaseAFromDict(this->GetDict(dct_), dt)の前";
			log("%s", str1);
			spd_=this->spd1;
			SetChaseAFromDict(this->GetDict(dct_,w*scale_), dt);

			if(this->moveDictPt!=Vec2(-1,-1)){
				this->_point1.set(this->_point2-this->moveDictPt);
//				this->_point1 += this->moveDictPt;
			}

//			this->NomlMove5(ndt_, dct_);
			//			this->getDctPt()->setPosition(this->chA);
			//			this->getDctPt2()->setPosition(this->JuncPt);

		} else {
			this->ChaseA(dt);
			if (this->chsFlg) {
				this->NomlMove5(ndt_, dct_);
			}
			return;
		}

	}
}

void Ball::NomlMove6(float dt, Vec2 DCT) {
	//	そもそもｄｔ＝0では実行しない。

	if (dt == 0) {
		const char *str0 = "NomlMove6 dt==0";
		log("%s", str0);

		return;
	}

	if (this->tchFlg) {

		if (!this->chsFlg) {

			const char *str1 = "NomlMove6 !this->chsFlg";
			log("%s", str1);
			this->ChaseA(dt);

		} else {
			const char *str2 = "NomlMove6 this->chsFlg";
			log("%s", str2);
			this->spd_ = this->spd1;
			Vec2 dct2_;
			dct2_.set(this->_point2 - this->_point1);
			SetChaseAFromDict(this->GetDict(dct2_, w * scale_), dt);
			if(this->moveDictPt!=Vec2(-1,-1)){
				this->_point1.set(this->_point2);
//				this->_point1 += this->moveDictPt;
			}else{
				return;
			}


		}

		//再帰、残りの時間があれば
		NomlMove6(ndt_, DCT);

	} else {
		this->spd_ = this->spd2;
		this->chv=this->spd_;
		this->jncSetFlg=false;
		this->chsFlg=true;
		this->NomlMove5(dt, DCT);
	}
}
int Ball::GetDict(Vec2 _dct, int w) {
	//w以上の方向長さのとき、方向を決定
	if (_dct.length() >= w) {

		int x = GetDict(_dct);

		switch (x) {

		case 0: {
			moveDictPt.set(Vec2::ZERO);
			break;
		}
		case 1: {
			moveDictPt.set(Vec2(0, w));
			break;
		}
		case 2: {
			moveDictPt.set(Vec2(w, 0));
			break;
		}
		case 3: {
			moveDictPt.set(Vec2(0, -w));
			break;
		}
		case 4: {
			moveDictPt.set(Vec2(-w, 0));
			break;
		}
		}

		return GetDict(_dct);
	} else {
		moveDictPt.set(Vec2(-1,-1));
		return 0;
	}

}
int Ball::GetDict(Vec2 _dct) {
//方向を決定
//	今回の方向を決定。

	aa = this->ChgKaku(_dct.getAngle() - M_PI / 12);
	aa /= 30;
	aa_ = (int) aa;

	int dctA;

	switch (aa_) {

	case 0: {

		if (_mMeder->GetMapStatus(mapPt_ + Vec2(1, 0)) != 3) {
			dctA = 2;
		} else {
			dctA = 0;
		}

		break;
	}
	case 1: {

		if (_mMeder->GetMapStatus(mapPt_ + Vec2(1, 0)) != 3) {
			dctA = 2;
			break;
		} else if (_mMeder->GetMapStatus(mapPt_ + Vec2(0, -1)) != 3) {
			dctA = 3;
			break;
		}
		dctA = 0;
		break;
	}
	case 2: {

		if (_mMeder->GetMapStatus(mapPt_ + Vec2(0, -1)) != 3) {
			dctA = 3;
			break;
		} else if (_mMeder->GetMapStatus(mapPt_ + Vec2(1, 0)) != 3) {
			dctA = 2;
			break;
		}

		dctA = 0;
		break;
	}

	case 3: {

		if (_mMeder->GetMapStatus(mapPt_ + Vec2(0, -1)) != 3) {
			dctA = 3;
		} else {
			dctA = 0;
		}
		break;
	}
	case 4: {

		if (_mMeder->GetMapStatus(mapPt_ + Vec2(0, -1)) != 3) {
			dctA = 3;
			break;
		} else if (_mMeder->GetMapStatus(mapPt_ + Vec2(-1, 0)) != 3) {
			dctA = 4;
			break;
		}
		dctA = 0;

		break;
	}

	case 5: {

		if (_mMeder->GetMapStatus(mapPt_ + Vec2(-1, 0)) != 3) {
			dctA = 4;
			break;
		} else if (_mMeder->GetMapStatus(mapPt_ + Vec2(0, -1)) != 3) {
			dctA = 3;
			break;
		}
		dctA = 0;

		break;
	}

	case 6: {
		if (_mMeder->GetMapStatus(mapPt_ + Vec2(-1, 0)) != 3) {
			dctA = 4;
		} else {
			dctA = 0;
		}
		break;
	}

	case 7: {
		if (_mMeder->GetMapStatus(mapPt_ + Vec2(-1, 0)) != 3) {
			dctA = 4;
			break;
		} else if (_mMeder->GetMapStatus(mapPt_ + Vec2(0, 1)) != 3) {
			dctA = 1;
			break;
		}

		dctA = 0;

		break;
	}

	case 8: {

		if (_mMeder->GetMapStatus(mapPt_ + Vec2(0, 1)) != 3) {
			dctA = 1;
			break;
		} else if (_mMeder->GetMapStatus(mapPt_ + Vec2(-1, 0)) != 3) {
			dctA = 4;
			break;
		}

		dctA = 0;

		break;
	}

	case 9: {

		if (_mMeder->GetMapStatus(mapPt_ + Vec2(0, 1)) != 3) {
			dctA = 1;
		} else {
			dctA = 0;
		}
		break;
	}
	case 10: {

		if (_mMeder->GetMapStatus(mapPt_ + Vec2(0, 1)) != 3) {
			dctA = 1;
			break;
		} else if (_mMeder->GetMapStatus(mapPt_ + Vec2(1, 0)) != 3) {
			dctA = 2;
			break;
		}
		dctA = 0;
		break;
	}

	case 11: {
		if (_mMeder->GetMapStatus(mapPt_ + Vec2(1, 0)) != 3) {
			dctA = 2;
			break;
		} else if (_mMeder->GetMapStatus(mapPt_ + Vec2(0, 1)) != 3) {
			dctA = 1;
			break;
		}
		dctA = 0;
		break;
	}

	}

	return dctA;

}
void Ball::SetChaseAFromDict(int dctA, float dt) {
//現在地を再設定
//	mapPt_.set(_mMeder->ChgPositionFromImageToMap(this->getPosition()));
//	mapImgPt_.set(_mMeder->ChgPositionFromMapToImage(mapPt_));
	const char *str2 = "SetChaseAFromDict(int dctA, float dt)";
	log("%s", str2);
	if (dctA == 0) {
//方向なしのとき
		this->dct_ = dctA;
		movePt_.set(this->ChaseA(mapImgPt_, this->getPosition(), spd_, dt));
		this->setPosition(movePt_);
		const char *str0 = "SetChaseAFromDict_dctA==0";
		log("%s", str0);

	}

	if (this->dct_ != dctA || this->chsFlg) {

		const char *str1 = "SetChaseAFromDict_ON";
		log("%s", str1);

		this->dct_ = dctA;

		Vec2 juncpt_;

		switch (dct_) {
//	停止
		case 0: {

			movePt_.set(this->ChaseA(mapImgPt_, this->getPosition(), spd_, dt));
			this->setPosition(movePt_);
			break;
		}
//	上
		case 1: {

//		this->ChaseA(mapImgPt_ + Vec2(0, w), this->getPosition(), spd_ / 2, dt);
			this->JuncMapPt.set(_mMeder->GetJunctionPoint(mapPt_, Vec2(0, 1)));
			mapPt_ += Vec2(0, 2);
//			mapImgPt_.set(_mMeder->ChgPositionFromMapToImage(mapPt_));
//			this->ChaseA(mapImgPt_, this->getPosition(), spd_ / 2, dt);
			break;
		}
//	→
		case 2: {
//		this->ChaseA(mapImgPt_ + Vec2(w, 0), this->getPosition(), spd_, dt);
			this->JuncMapPt.set(_mMeder->GetJunctionPoint(mapPt_, Vec2(1, 0)));
//			juncpt_.set(_mMeder->ChgPositionFromMapToImage(_mMeder->GetJunctionPoint(mapPt_, Vec2(1, 0))));
			mapPt_ += Vec2(2, 0);
//			mapImgPt_.set(_mMeder->ChgPositionFromMapToImage(mapPt_));
//			this->ChaseA(mapImgPt_, this->getPosition(), spd_ / 2, dt);

			break;
		}
//	↓
		case 3: {
//		this->ChaseA(mapImgPt_ + Vec2(0, -w), this->getPosition(), spd_, dt);
			this->JuncMapPt.set(_mMeder->GetJunctionPoint(mapPt_, Vec2(0, -1)));
//			juncpt_.set(_mMeder->ChgPositionFromMapToImage(_mMeder->GetJunctionPoint(mapPt_, Vec2(0, -1))));
			mapPt_ += Vec2(0, -2);
//			mapImgPt_.set(_mMeder->ChgPositionFromMapToImage(mapPt_));
//			this->ChaseA(mapImgPt_, this->getPosition(), spd_ / 2, dt);
			break;
		}
//	←
		case 4: {
//		this->ChaseA(mapImgPt_ + Vec2(-w, 0), this->getPosition(), spd_ / 2, dt);
			this->JuncMapPt.set(_mMeder->GetJunctionPoint(mapPt_, Vec2(-1, 0)));
//			juncpt_.set(_mMeder->ChgPositionFromMapToImage(_mMeder->GetJunctionPoint(mapPt_, Vec2(-1, 0))));
			mapPt_ += Vec2(-2, 0);
//			mapImgPt_.set(_mMeder->ChgPositionFromMapToImage(mapPt_));
//			this->ChaseA(mapImgPt_, this->getPosition(), spd_ / 2, dt);
			break;
		}

		}

		mapImgPt_.set(_mMeder->ChgPositionFromMapToImage(mapPt_));
		movePt_.set(this->ChaseA(mapImgPt_, this->getPosition(), spd_, dt));
		this->setPosition(movePt_);

		if (this->JuncMapPt != Vec2::ZERO) {

			this->JuncPt.set(_mMeder->ChgPositionFromMapToImage(this->JuncMapPt));
		}
	}
}
void Ball::ChgMapImagePt(Vec2 dPt) {

//	mapPt_+= Vec2(1, 0)*2;
//	movePt_.set(this->ChaseA(mapImgPt_ + Vec2(w, 0), this->getPosition(), spd_ / 2, dt));
//	mapImgPt_.set(_mMeder->ChgPositionFromMapToImage(mapPt_));
}

void Ball::AccellMove(Acceleration* acc) {

	if (this->updateFlg) {

		auto mpt = Vec2((float) acc->x * 50, (float) acc->y * 50);	//元500；
		this->AccellMove(mpt);
		//this->getBody()->applyImpulse(mpt);

	} else {

		this->getBody()->setVelocity(Vec2::ZERO);
	}

}

void Ball::AccellMove(Vec2 dctpt) {

//�����ɉ����đ��x��ς���
	bool fstFlg;

	if (dctpt.length() > 5) {
		dctpt.normalize();
		dctpt *= 30;

		//	dctpt-=force_;
		this->getBody()->applyImpulse(dctpt * 30);	//元300＿20170416

		//this->getBody()->applyForce(dctpt );

		//force_=dctpt;
		//fstFlg = true;
	} else {
		this->getBody()->setVelocity(Vec2::ZERO);
	}

	/*
	 if(fstFlg){
	 this->getBody()->setVelocity(dctpt * this->veloLimit);
	 }else{
	 this->getBody()->setVelocity(dctpt * this->veloLimit/2);
	 }

	 */
//this->getBody()->applyForce(dctpt);
}
void Ball::Action1() {

//	this->stopAllActions();
//	this->setTextureRect(
//			Rect(frameSize.width, 0, frameSize.width, frameSize.height));
//	this->veloLimit = 40;
//	this->_body->setVelocityLimit(this->veloLimit);
	auto delay_ = DelayTime::create(15.0);
	auto func_ = CallFuncN::create([this](Node* node) {
		//	this->veloLimit=20;
//		this->_body->setVelocityLimit(this->veloLimit);

			this->getDumy()->stopAllActions();
			this->getDumy()->setVisible(false);
			this->getDumy()->setScale(1);

			this->setTextureRect(Rect(0, 0, frameSize.width, frameSize.height));
		});

	auto seq_ = Sequence::create(delay_, func_, NULL);

	this->runAction(seq_);

	/*
	 this->setUpdateAction(
	 [this](Ball* bl) {

	 if (bl->getBallState()!=BallState::T3 && bl->getBallState()!=BallState::T4 )

	 if (bl->getBody()->getVelocity().getLength()>=10) {
	 bl->setBall(BallState::T2);
	 } else {
	 bl->setBall(BallState::T1);
	 }
	 }

	 );




	 this->setBall(BallState::T1);
	 this->setScale(0.7);
	 this->getBody()->setVelocityLimit(16);
	 */
}
void Ball::Action2() {

	this->getDumy()->stopAllActions();
	this->getDumy()->setVisible(true);
	this->getDumy()->setScale(1);

	int k;
	k = this->getLevel() / 2;

	if (k < 3) {
		k = 3;
	}

	auto big_ = ScaleBy::create(0.3, this->getLevel() / 2);

	auto seq_ = Sequence::create(big_, big_->reverse(), NULL);
	auto rept_ = RepeatForever::create(seq_);

	this->getDumy()->runAction(rept_);

}
void Ball::Action3() {
	this->getDumy()->stopAllActions();
	this->getDumy()->setVisible(false);
}
void Ball::Action4() {

}
