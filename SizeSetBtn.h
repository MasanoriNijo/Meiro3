#ifndef __neomeiro__SizeSetBtn__
#define __neomeiro__SizeSetBtn__

#include "cocos2d.h"
#include "Slider.h"
USING_NS_CC;

class SizeSetBtn: public cocos2d::Node {
protected:
	SizeSetBtn();
	virtual ~SizeSetBtn();
	bool initWithFile(const std::string& filename);

private:
public:

	Size winSize;
	bool selectFlg = false; //全体で選択されているかどうか？
	bool tchFlg = false; //枠をタッチしたかどうか
	int touchID; //現在タッチされているID
	cocos2d::Size frameSize;
	void update(float dt) override;
	void SetAtai(int x);
	void ShowSlider();//スライダーを表示する。
	void ShowSlider(int x);//スライダーを表示する。	値をｘにする。
	void DelSlider();//スライダーを非表示にする
	int Value; //実際の値
	CREATE_FUNC(SizeSetBtn)
	static SizeSetBtn* create(const std::string& filename);
	;CC_SYNTHESIZE_RETAIN(Slider*, _slider,Slider)
	;CC_SYNTHESIZE_RETAIN(Sprite*, _wakuBtn,WakuBtn)
//	;CC_SYNTHESIZE_RETAIN(Menu*, _wakuM,WakuM)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Label*,_atai,Atai)
	std::function<void(SizeSetBtn*)> onNamaeSetListener;
	String Namae;
	String Namae1;
	String Namae2;
	bool ChkTouch(Vec2 pt);//メニュー以外で現在の枠のタッチ内か？
	void SetNamaeListenner(const std::string& namae_, const std::string& namae1_, const std::string& namae2_,
			int min_, int max_);

};
#endif // __HELLOWORLD_SCENE_H__
