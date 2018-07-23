/*
 * Sprite2.h
 *
 *  Created on: 2017/03/05
 *      Author: m.nijo
 */

#ifndef SPRITE2_H_
#define SPRITE2_H_
#include "cocos2d.h"
#include "math.h"
USING_NS_CC;
class Sprite2: public cocos2d::Sprite {

protected:

	Sprite2();
	virtual ~Sprite2();

private:

	Vec2 pt_; //計算用変数
	Vec2 pt2_; //計算用変数
	Vec2 pt3_; //計算用変数
	float x_;

public:

	void setVisible(bool flg) override;
	static Sprite2* create();//Nodeで作成する
	static Sprite2* create(const std::string& filename);
	static Sprite2* createWithTexture(Texture2D *texture);
	static Sprite2* createWithTexture(Texture2D *texture,Rect rct_);

	//ピン止めするように回転する
	void SetRot(float kaku_);
	void SetPos(Vec2 pt_);
	void SetRotPos(float kaku_, Vec2 pt_);

	//pointボデイを作成する。
	void MadePoint();
	void ShowPoint(bool flg);
	void SetPointPos(Vec2 pt);
	bool pointFlg; //ポイントフラグ
	void DelShow(); //エフェクトで消える。
	void DelShow(Vec2 pt_); //エフェクトで消える。

	//ピン止めするように回転する.親ノードの親ノードに所属している場合
	void SetRot2(float kaku_);
	void SetPos2(Vec2 pt_);
	void SetRotPos2(float kaku_, Vec2 pt_);

	Vec2 GetLocalPt(Vec2 pt_); //親ノードのポイントをローカルポイントに変換する。

	//角度を変換する0-2Π(Vec2用反時計）、0-360°(sprite用時計回り）
	float ChgKaku(float degree);
	float ChgRad(float kaku);
	float NomlKaku(float kaku);
	float NomlRad(float rad);
	bool BetweenKaku(float x, float min_, float max_);
	bool BetweenRad(float x, float min_, float max_);

	bool chsingFlg=false; //追従中フラグ
	bool chsFlg=false; //追従が完了したかどうか？
	float ndt_=0;//追従完成時の残りのタイム
	void ChaseA(Vec2 A,  float v_, float dt);
	float ChaseA(float A, float chaser_, float v_, float dt);

	Vec2 ChaseA(Vec2 A, Vec2 chaser_, float v_, float dt);

	Vec2 chA;
	Vec2 chch;
	float chv=200;

	Vec2 ChaseA(float dt);//前回の条件で実行する。完了したらTrue返す。
//移動予測して追う
	float ChaseB(float A, float vA, float chaser_, float v_, float dt);
	Vec2 ChaseB(Vec2 A, Vec2 vA, Vec2 chaser_, float v_, float dt);
	//ランダムに移動
	Vec2 rndR_; //ランダム回転半径
	float rndrad_; //ランダム回転速度ラジアン
	float ChaseC(float A, float chaser_, float v_, float dt);
	Vec2 ChaseC(Vec2 A, Vec2 chaser_, float v_, float dt);

	//ピン止めするように回転する.親ノードの親ノードの親ノードに所属している場合
	void SetRot3(float kaku_);
	void SetPos3(Vec2 pt_);
	void SetRotPos3(float kaku_, Vec2 pt_);
	;CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*,_parentSp,ParentSp)
	; //想定するペアレンツノード
CC_SYNTHESIZE(Vec2,_pinPt,PinPt)
	; //ピン止め位置
CC_SYNTHESIZE(Vec2,_ctPt,CtPt)
	; //スプライト内のピン位置
CC_SYNTHESIZE_RETAIN(cocos2d::PhysicsBody *,_body,Body)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*,_point,Point)
	;CC_SYNTHESIZE(cocos2d::Vector<cocos2d::SpriteFrame *>,_pointFrame,PointFrame)
	;

};

#endif /* SPRITE2_H_ */
