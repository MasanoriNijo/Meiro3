#ifndef __neomeiro__Cource__
#define __neomeiro__Cource__

#include "cocos2d.h"
USING_NS_CC;
class Cource: public cocos2d::Sprite {
protected:
	Cource();
	virtual ~Cource();
	bool init() override;
	bool initWithTexture(Texture2D *texture) override;

	const int ballCatg = 1 << 0;
	const int itemCatg = 1 << 1;
	const int courceCatg = 1 << 2;
	const int startCatg = 1 << 3;
	const int goalCatg = 1 << 4;

private:
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
public:

	float scale_ = 1.0f;
	int w = 20;
	int t=4;
	static Cource* createWithTexture(Texture2D *texture);
	cocos2d::Size frameSize;
	enum class CourceState {
		T1, T2, T3, T4
	};

	enum class CourceType {
		C00,
		C01,
		C02,
		C03,
		C04,
		C05,
		C06,
		C07,
		C08,
		C09,
		C10,
		C11,
		C12,
		C13,
		C14,
		C15
	};

	Vec2 mapPt; //マップ上の位置

	int _madeNo; //順番。
	bool moveFlg;
	void update(float dt) override;
	void setUpdateAction(std::function<void(Cource*, float)> action);
	void SetCource_old(CourceType c); //指定のコースタイプにする。物理データ込み
	void SetCource(CourceType c); //指定のコースタイプにする。	物理データ込み改良版
	void SetCourceA(CourceType c); //指定のコースタイプにする物理データなし。
	void SetBody_(bool x); //物理データを入れる入れない。
	void ResetCource(); //コースを初期状態にする。

	std::string GetCourceName(); //現在のコース情報を表示

	void Fin();

	std::function<void(Cource*, float)> onUpDateListener;
	std::function<void(Cource*)> onFinishListener;
	std::function<void(Cource*)> onContactListener;

	//2線分間の最短距離を計算、交差する場合:-1,平行な場合:-2。
	float TrkCrossChk(Cource* c1);
	float TrkCrossChk(cocos2d::Vec2 Pt11, cocos2d::Vec2 Pt12,
			cocos2d::Vec2 Pt21, cocos2d::Vec2 Pt22);
//線分直線ptと点ｘの平行距離
	float LinePointLength(cocos2d::Vec2 Pt11, cocos2d::Vec2 Pt12,
			cocos2d::Vec2 x);
	float TrackPointLength(cocos2d::Vec2 x);
	float GetRad();

	void SetRnd(); //あっとランダムにコースを生成
	void SetIndex(int index); //指定のインデックスでコースを作成。
	void SetIndexA(int index); //指定のインデックスでコースを作成。
	void Action1();
	void Action2();
	void Action3();
	void Action4();

	CREATE_FUNC(Cource)
	;
	// CREATEWITHTEXTURE_FUNC(Cource);
CC_SYNTHESIZE_RETAIN(cocos2d::PhysicsBody *,_body,Body)
	;CC_SYNTHESIZE_RETAIN(cocos2d::PhysicsBody *,_body2,Body2)
	;CC_SYNTHESIZE_RETAIN(cocos2d::PhysicsBody *,_body3,Body3)
	;CC_SYNTHESIZE_RETAIN(cocos2d::PhysicsBody *,_body4,Body4)
	;CC_SYNTHESIZE_RETAIN(cocos2d::PhysicsBody *,_body5,Body5)
	;CC_SYNTHESIZE_RETAIN(cocos2d::Node *,_nd1,Nd1);//ボデイを付与させる仮のノード
	;CC_SYNTHESIZE_RETAIN(cocos2d::Node *,_nd2,Nd2);//ボデイを付与させる仮のノード
	;CC_SYNTHESIZE_RETAIN(cocos2d::Node *,_nd3,Nd3);//ボデイを付与させる仮のノード
	;CC_SYNTHESIZE_RETAIN(cocos2d::Node *,_nd4,Nd4);//ボデイを付与させる仮のノード
	;CC_SYNTHESIZE_RETAIN(cocos2d::Node *,_nd5,Nd5);//ボデイを付与させる仮のノード
	;CC_SYNTHESIZE(CourceState,_courceState,CourceState)
	;CC_SYNTHESIZE(CourceType,_courceType,CourceType)
	;CC_SYNTHESIZE(cocos2d::Vector<cocos2d::SpriteFrame *>,_frames,Frames)
	;
};
#endif // __HELLOWORLD_SCENE_H__
