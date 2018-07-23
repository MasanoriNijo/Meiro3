#ifndef __neomeiro__Ball__
#define __neomeiro__Ball__

#include "cocos2d.h"
#include "Sprite2.h"
#include "MeiroMeder.h"
USING_NS_CC;

class Ball: public Sprite2 {
protected:

	const int ballCatg = 1 << 0;
	const int itemCatg = 1 << 1;
	const int courceCatg = 1 << 2;
	const int startCatg = 1 << 3;
	const int goalCatg = 1 << 4;

	const int BALL_FRAME_COUNT = 2;

	Ball();
	virtual ~Ball();

	bool init() override;
	//Player _player;

private:

public:
	enum class BallState {

		T1, T2, T3, T4

	};

	float scale_ = 0.5f; //コースのスケールとあわせる。
	int w = 20;
	int d = 4;
	Vec2 force_; //前回の力

	bool moveFlg;
	bool chk1;
	bool chk2;
	int cnt1;
	int cnt2;
	int veloLimit = 30; //40
	int lifePoint;

	cocos2d::Size frameSize;
	void update(float dt) override;
	void Action1();
	void Action2();
	void Action3();
	void Action4();
	bool updateFlg;CC_SYNTHESIZE(std::function<void(Ball*)> ,_updateListener,UpDateListener)
	;
	std::function<void(Ball*)> onUpDateListener;
	std::function<void(Ball*)> onFinishListener;
	std::function<void(Ball*)> onContactListener;
	void setUpdateAction(std::function<void(Ball*)> action);
	void setContactAction(std::function<void(Ball*)> action);
	void Fin();

	void AccellMove(Acceleration* acc);
	void AccellMove(Vec2 dctpt);
	//void setPlayer(Player _player);

	//物理演算を使用しない操作
	Vec2 mapPt_; //マップ上のポイント
	Vec2 mapImgPt_; //マップ上のポイントをイメージポイントに変換
	Vec2 movePt_;

	int asobi_ = 5;
	float spd1 = 300;
	float spd2 = 600;

	float spd_ = 200;
	float aa;
	int aa_;

	int GetDict(Vec2 _dct);//方向を決定
	int GetDict(Vec2 _dct,int w );//w以上の方向長さのとき、方向を決定
	Vec2 moveDictPt;//決定した移動ベクトル


	int dct_ = 0; //現在の方向、上下左右、1,2,3,4
	int dct = 0; //前回の方向、上下左右、1,2,3,4

	Vec2 _point1;//始めのタッチ
	Vec2 _point2;//スワイプタッチ。
	Vec2 _touchMapImgPt;//タッチ時のマップ上の位置
	Vec2 _mpoint;//動くポイント
	bool tchFlg;//画面のタッチを監視


	float straitTime = 0.6f;
	float straitTime_ = 0;
	void NomlMove(float dt, Vec2 dct_);
	void NomlMove2(float dt, Vec2 dct_);
	void NomlMove3(float dt, Vec2 dct_); //分岐点まで進み続ける
	void NomlMove4(float dt, Vec2 dct_); //分岐点まで進み続ける。これが最新
	void NomlMove5(float dt, Vec2 pt2_); //分岐点まで進み続ける
	void NomlMove6(float dt, Vec2 pt2_);
	void ChgMapImagePt(Vec2 dPt);
	void SetChaseAFromDict(int dct_, float dt);


	Vec2 JuncPt;
	Vec2 JuncMapPt;
	bool jncSetFlg = false;

	bool movContFlg = false; //動き続けるフラグ

	CREATE_FUNC(Ball)
	;CC_SYNTHESIZE(BallState,_ballstate,BallState)
	;CC_SYNTHESIZE(cocos2d::Vector<cocos2d::SpriteFrame *>,_frames,Frames)
	//;CC_SYNTHESIZE_RETAIN(cocos2d::PhysicsBody *,_body,Body)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Sprite *,_dumy,Dumy)
	;CC_SYNTHESIZE(bool,_updateFlg,UpDateFlg)
	;CC_SYNTHESIZE(int,_level,Level)
	;CC_SYNTHESIZE_RETAIN(MeiroMeder*, _mMeder, MMeder)
	;CC_SYNTHESIZE_RETAIN(Sprite*, _dctPt, DctPt)
	;CC_SYNTHESIZE_RETAIN(Sprite*, _dctPt2, DctPt2)
	;
};

#endif // __HELLOWORLD_SCENE_H__
