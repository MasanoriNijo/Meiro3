#ifndef __neomeiro__Kabe__
#define __neomeiro__Kabe__
#include "cocos2d.h"
#include "Cource.h"
class Kabe: public cocos2d::Ref {
protected:
	Kabe();
	virtual ~Kabe();
	bool init();

private:
public:


	int index=0;//インデックス番号
	int syokiRen = 350;	//初期パラメータの連続性
	int syokiRen_ = 0;	//初期パラメータの連続性変数

	int thokuPrm = 40;	//初期直進性
	int edaPrm = 1000;	//初期枝分かれ性
	int zizokPrm = 10000;	//初期連続性
	int kabePrm = 100;	//壁への回り込み性

	bool fstFlg = true;

	int madeStep = 0;	//0:初期、1：次

	int thokuPrm2 = 10;	//直進性
	int edaPrm2 = 10;	//枝分かれ性
	int zizokPrm2 = 10;	//連続性
	int kabePrm2 = 10;	//壁への回り込み性

	bool kurl = false;	//くるくる性
	bool kurlCng = false;	//くるくる性

	Vec2 mMapPt; //壁メーダーの位置を保持
	int mDirect; //壁メーダーの進行方向を保持
	int mSetiKabe = 0; //壁メーダーの接している壁の方向を保持。接していない時は0
	void SetPrmRnd();
	void SetPrm(int _tyokuPrm, int _edaPrm, int _zizokPrm, int _kabePrm, int _syokiCnt, int _tyokuPrm2,
			int _edaPrm2, int _zizokPrm2, int _kabePrm2); //パラメータをセットする。
	void SetPrm(int index_);//パラメータ設定より決定。

	void ChgPrm();//パラメータ1と2を反転する。
	void ResetKabe();//パラメータはそのままでリセット
	void Fin();

	std::function<void(Kabe*)> onFinishListener;

	CREATE_FUNC(Kabe)

};
#endif // __HELLOWORLD_SCENE_H__
