#ifndef __neomeiro__Item__
#define __neomeiro__Item__
#include "cocos2d.h"
#include "Cource.h"
class Item: public cocos2d::Sprite {
protected:
	Item();
	virtual ~Item();
	bool init() override;
	const int ballCatg = 1 << 0;
	const int itemCatg = 1 << 1;
	const int courceCatg = 1 << 2;
	const int startCatg = 1 << 3;
	const int goalCatg = 1 << 4;


private:
public:
	enum class ItemState {
		T1, T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12
	};
	int _madeNo; //���ԁB
	float scale_=0.5f;//�R�[�X�̃X�P�[���Ƃ��킹��B
	int _lifePoint;
	int _scorePoint;
	std::string _itemName;


	bool moveFlg;
	cocos2d::Size frameSize;
	void update(float dt) override;
	void setUpdateAction(std::function<void(Item*, float)> action);
	void ResetItem(); //�R�[�X��������Ԃɂ���B
	void Fin();
	std::function<void(Item*, float)> onUpDateListener;
	std::function<void(Item*)> onFinishListener;
	std::function<void(Item*)> onContactListener;
	void setRndState();//�����ƃ����_���ɐ���
	void setRndState(int _Lvl);//���x���ɉ����āA�A�C�e����ω�������B
	void setState(ItemState x);
	void setPosition_(Cource* c,int JtNo);
	void setPosition_(Vec2 pt,int JtNo);
	void Action1();
	void Action2();
	void Action3();
	void Action4();
	CREATE_FUNC(Item)
	//;CC_SYNTHESIZE_RETAIN(cocos2d::PhysicsBody *,_body,Body)
	;CC_SYNTHESIZE(ItemState,_itemState,ItemState)
	;CC_SYNTHESIZE(cocos2d::Vector<cocos2d::SpriteFrame *>,_frames,Frames)
	;
};
#endif // __HELLOWORLD_SCENE_H__
