#include "cocos2d.h"
#include "SizeSetBtnControler.h"
#include "SizeSetBtn.h"
#include "cmath"
USING_NS_CC;

//const int FRAME_COUNT = 1;
/*
 const int ballCatg = 1 << 0;
 const int SizeSetBtnControlerCatg = 1 << 1;
 const int courceCatg = 1 << 2;
 const int startCatg = 1 << 3;
 const int goalCatg = 1 << 4;
 */
// on "init" you need to initialize your instance
SizeSetBtnControler::SizeSetBtnControler() :
		_selectBtn(NULL), _slider(NULL), _selectState(SelectState::NOSELECT) {
}
SizeSetBtnControler::~SizeSetBtnControler() {
	CC_SAFE_RELEASE_NULL(_slider);
	CC_SAFE_RELEASE_NULL(_selectBtn);

}

bool SizeSetBtnControler::init() {

	if (!Node::init()) {
		return false;
	}
	const char *str4 = "SizeSetBtnControler::init()_1 ";
	log("%s", str4);
	this->setSlider(Slider::create());
	this->_slider->setPosition(-400,-400);
	const char *str5 = "SizeSetBtnControler::init()_2 ";
	log("%s", str5);

	return true;

}
void SizeSetBtnControler::AddSizeSetController(SizeSetBtn * ssbtn) {

	const char *str1 = "SizeSetBtnControler::AddSizeSetController_1";
	log("%s", str1);
	this->_member.pushBack(ssbtn);
//	ssbtn->setSlider(this->_slider);
//	this->addChild(ssbtn->getWakuBtn(),1);
	const char *str2 = "SizeSetBtnControler::AddSizeSetController_2";
	log("%s", str2);

}
void SizeSetBtnControler::TouchOnSel(Vec2 pt_) {
	//タッチしたとき

	_point1.set(pt_);
	_point2.set(pt_);
	switch (_selectState) {

	case SelectState::NOSELECT: {

		for (SizeSetBtn* tbtn : this->_member) {

			if (tbtn->ChkTouch(pt_) && !this->_selectBtn) {
				const char *str1 = "tbtn->ChkTouch(pt_)_true";
				log("%s", str1);
				this->setSelectBtn(tbtn);
				tbtn->setSlider(this->_slider);
				tbtn->selectFlg = true;
				this->setSelectState(SelectState::SELECT);
				this->setSelectBtn(tbtn);
				tbtn->ShowSlider(tbtn->Value);

			}

		}

		break;
	}
	case SelectState::SELECT: {

		this->_slider->SelectTumami(pt_);

		if (this->_slider->selFlg2 == false) {
			this->getSelectBtn()->getWakuBtn()->setOpacity(0);
			this->_slider->setPosition(-200, -200);
			this->getSelectBtn()->setSlider(NULL);
			this->setSelectBtn(NULL);
			this->setSelectState(SelectState::NOSELECT);
		}

		break;
	}
	case SelectState::SWAIP: {

		break;
	}

	}

}
void SizeSetBtnControler::SwaipSel(Vec2 pt_) {
	_point2.set(pt_);
	switch (_selectState) {

	case SelectState::NOSELECT: {

		break;
	}
	case SelectState::SELECT: {

		this->getSlider()->SlideMove(pt_);
		if (this->getSelectBtn()) {
			this->getSelectBtn()->SetAtai(this->getSlider()->Value_);
		}
		break;
	}
	case SelectState::SWAIP: {

		break;
	}

	}
}
void SizeSetBtnControler::TouchOffSel(Vec2 pt_) {

	_point1.set(Vec2::ZERO);
	_point2.set(Vec2::ZERO);

	switch (_selectState) {

	case SelectState::NOSELECT: {

		break;
	}
	case SelectState::SELECT: {

		break;
	}
	case SelectState::SWAIP: {

		break;
	}

	}
}

