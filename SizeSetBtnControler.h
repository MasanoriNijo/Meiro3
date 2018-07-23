#ifndef __neomeiro__SizeSetBtnControler__
#define __neomeiro__SizeSetBtnControler__

#include "cocos2d.h"
#include "SizeSetBtn.h"
#include "slider.h"
USING_NS_CC;

class SizeSetBtnControler: public cocos2d::Node {
protected:
	SizeSetBtnControler();
	virtual ~SizeSetBtnControler();
	bool init() override;

private:
public:

	Vec2 _point1;
	Vec2 _point2;

	Size winSize;
	bool tchFlg = false; //枠をタッチしたかどうか
	int touchID = 0; //現在タッチされているID

	CREATE_FUNC(SizeSetBtnControler)

	;CC_SYNTHESIZE_RETAIN(Slider*, _slider,Slider)
//	cocos2d::Vector<SizeSetBtn *> _member;
	;CC_SYNTHESIZE(cocos2d::Vector<SizeSetBtn *>,_member,Member)
	;CC_SYNTHESIZE_RETAIN(SizeSetBtn*, _selectBtn,SelectBtn)
	;

	enum class SelectState {

		NOSELECT, SELECT, SWAIP

	};
	;CC_SYNTHESIZE(SelectState,_selectState,SelectState)
	;

	void AddSizeSetController(SizeSetBtn* ssbtn);
	void TouchOnSel(Vec2 pt_); //タッチしたとき
	void SwaipSel(Vec2 pt_);
	void TouchOffSel(Vec2 pt_);

};
#endif // __HELLOWORLD_SCENE_H__
