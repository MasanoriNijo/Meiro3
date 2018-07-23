#include "cocos2d.h"
#include "SizeSetBtn.h"
#include "cmath"
USING_NS_CC;

//const int FRAME_COUNT = 1;
/*
 const int ballCatg = 1 << 0;
 const int SizeSetBtnCatg = 1 << 1;
 const int courceCatg = 1 << 2;
 const int startCatg = 1 << 3;
 const int goalCatg = 1 << 4;
 */
// on "init" you need to initialize your instance
SizeSetBtn::SizeSetBtn() :
		_slider(NULL), _wakuBtn(NULL), _atai(NULL) {
}
SizeSetBtn::~SizeSetBtn() {
	CC_SAFE_RELEASE_NULL(_slider);
	CC_SAFE_RELEASE_NULL(_wakuBtn);

	CC_SAFE_RELEASE_NULL(_atai);
}

SizeSetBtn* SizeSetBtn::create(const std::string& filename) {
	SizeSetBtn *ret = new SizeSetBtn();
	if (ret && ret->initWithFile(filename)) {
		ret->autorelease();

		return ret;
	}
	CC_SAFE_DELETE(ret);

	return ret;
}
bool SizeSetBtn::initWithFile(const std::string& filename) {

	if (!Node::init()) {
		return false;
	}

//	this->addChild(_slider,1);
	auto director = Director::getInstance();
	winSize.setSize(director->getWinSize().width, director->getWinSize().height);

	this->setWakuBtn(Sprite::create(filename));
	this->addChild(this->getWakuBtn(), 2);
	this->_wakuBtn->setOpacity(0);

	TTFConfig ttfConfig3("HGRPP1.TTC", 40, GlyphCollection::DYNAMIC);
	this->setAtai(Label::createWithTTF(ttfConfig3, "123"));
	this->getAtai()->setColor(Color3B::WHITE);
	_atai->setAnchorPoint(Vec2(0.5, 0.5));
//_atai->setAnchorPoint(Vec2::ZERO);
	_atai->setAlignment(TextHAlignment::CENTER);
//_atai->enableOutline(Color4B::BLACK, 2);
//_atai->setVisible(false);
//	_atai->setPosition(this->_wakuBtn->getContentSize().width/2,this->_wakuBtn->getContentSize().height/2);
	this->addChild(_atai, 1);
//	this->scheduleUpdate();

	return true;
}

void SizeSetBtn::ShowSlider(int x) {

	this->SetAtai(x);
	this->ShowSlider();
	this->scheduleUpdate();

}

void SizeSetBtn::ShowSlider() {
	//スライダーを表示する。
	const char *str0 = "SizeSetBtn::ShowSlider()";
	log("%s", str0);
	this->tchFlg = true;
	this->_wakuBtn->setOpacity(255);
	this->scheduleUpdate();
	if (_slider) {
		this->_wakuBtn->setOpacity(255);
		this->_slider->setScale(0);
		this->_slider->setPosition(this->getPosition());
		this->_slider->setVisible(true);
		this->onNamaeSetListener(this);

		if (this->getPosition().y > winSize.height / 2) {

			auto move_ = MoveTo::create(0.1f, Vec2(winSize.width / 2, this->getPosition().y - 130));
			auto big_ = ScaleTo::create(0.1f, 1);
			auto fade_ = FadeIn::create(0.1f);
			auto spwn_ = Spawn::create(move_, big_, NULL);
			this->_slider->runAction(spwn_);

		} else {

			auto move_ = MoveTo::create(0.1f, Vec2(winSize.width / 2, this->getPosition().y + 130));
			auto big_ = ScaleTo::create(0.1f, 1);
			auto fade_ = FadeIn::create(0.1f);
			auto spwn_ = Spawn::create(move_, big_, NULL);
			this->_slider->runAction(spwn_);

		}

	}

}

void SizeSetBtn::DelSlider() {
	//スライダーを非表示にする
	this->tchFlg = false;
	this->_wakuBtn->setOpacity(0);
	this->unscheduleUpdate();
	if (_slider) {
		this->_slider->setVisible(false);
		this->_slider->setPosition(-200, -200);
	}

}

void SizeSetBtn::SetNamaeListenner(const std::string& namae_, const std::string& namae1_,
		const std::string& namae2_, int min_, int max_) {

	this->onNamaeSetListener = [this,namae_,namae1_,namae2_,min_,max_](SizeSetBtn * stbtn_) {
		this->_slider->getAtai()->setVisible(false);
		this->_slider->getNamae()->setString(namae_);
		this->_slider->getNamae1()->setString(namae1_);
		this->_slider->getNamae2()->setString(namae2_);
		this->_slider->MinValue = min_;
		this->_slider->MaxValue = max_;
		this->_slider->Value_ = this->Value;
		this->_slider->SlideMove(this->Value);
		this->_slider->touchID=this->touchID;

	};

}
bool SizeSetBtn::ChkTouch(Vec2 pt) {
	//メニュー以外で現在の枠のタッチ内か？
	const char *str2 = "SizeSetBtn::ChkTouch(Vec2 pt)";
	log("%s", str2);
	Rect rct_; // = this->getWakuBtn()->getBoundingBox();
	rct_.setRect(this->getPosition().x - this->getWakuBtn()->getContentSize().width / 2,
			this->getPosition().y - this->getWakuBtn()->getContentSize().height / 2,
			this->getWakuBtn()->getContentSize().width, this->getWakuBtn()->getContentSize().height);

	return rct_.containsPoint(pt);

}
void SizeSetBtn::SetAtai(int x) {
	this->Value = x;
	this->getAtai()->setString("" + StringUtils::toString((int) x));
	if (this->getSlider() && this->tchFlg) {
		this->getSlider()->SlideMove(x);
	}
}
void SizeSetBtn::update(float dt) {

	if (this->getSlider()) {

		if (this->tchFlg) {
			if (this->Value != this->getSlider()->Value_) {
				this->Value = this->getSlider()->Value_;
				this->getAtai()->setString("" + StringUtils::toString((int) this->Value));
			}
		}
	}
}
