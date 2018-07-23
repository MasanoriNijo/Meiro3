#include "cocos2d.h"
#include "Kabe.h"
#include "Cource.h"
#include "cmath"
USING_NS_CC;

//const int FRAME_COUNT = 1;
/*
 const int ballCatg = 1 << 0;
 const int KabeCatg = 1 << 1;
 const int courceCatg = 1 << 2;
 const int startCatg = 1 << 3;
 const int goalCatg = 1 << 4;
 */
// on "init" you need to initialize your instance
Kabe::Kabe() {
}
Kabe::~Kabe() {

}
bool Kabe::init() {

	return true;
}

void Kabe::SetPrmRnd() {
	//パラメータをセットする。
	int a_ = arc4random() % static_cast<int>(11) * 10;
	if (a_ <= 0) {
		a_ = 2;
	}

	int b_ = arc4random() % static_cast<int>(11) * 10;

	if (b_ <= 0) {
		b_ = 1;
	}
	int c_ = arc4random() % static_cast<int>(11) * 10;
	if (c_ <= 0) {
		c_ = 2;
	}
	int d_ = arc4random() % static_cast<int>(11) * 10;
	if (d_ <= 0) {
		d_ = 1;
	}
	int e_ = arc4random() % static_cast<int>(11) * 10;
	if (e_ <= 0) {
		e_ =1;
	}
	int f_ = arc4random() % static_cast<int>(11) * 10;
	if (f_ <= 0) {
		f_ = 2;
	}
	int g_ = arc4random() % static_cast<int>(11) * 10;
	if (g_ <= 0) {
		g_ = 1;
	}
	int h_ = arc4random() % static_cast<int>(11) * 10;
	if (h_ <= 0) {
		h_ = 2;
	}
	int i_ = arc4random() % static_cast<int>(11) * 10;
	if (i_ <= 0) {
		i_ = 1;
	}

	this->SetPrm(a_, b_, c_, d_, e_, f_, g_, h_, i_);
//	this->SetPrm(a_, b_, c_, d_, e_, f_, g_, h_, i_);
}
void Kabe::SetPrm(int _tyokuPrm, int _edaPrm, int _zizokPrm, int _kabePrm, int _syokiCnt, int _tyokuPrm2,
		int _edaPrm2, int _zizokPrm2, int _kabePrm2) {

	this->syokiRen = _syokiCnt;	//初期パラメータの連続性

	this->thokuPrm = _tyokuPrm;	//初期直進性2-100

	this->edaPrm = _edaPrm;	//初期枝分かれ性1_100
	this->zizokPrm = _zizokPrm;	//初期連続性1_100
	this->kabePrm = _kabePrm;	//壁への回り込み性1_100

	madeStep = 0;	//0:初期、1：次

	this->thokuPrm2 = _tyokuPrm2;	//直進性2_100
	this->edaPrm2 = _edaPrm2;	//枝分かれ性1_100
	this->zizokPrm2 = _zizokPrm2;	//連続性2_100
	this->kabePrm2 = _kabePrm2;	//壁への回り込み性1_100

}
void Kabe::SetPrm(int index_) {

	this->index = index_;
	madeStep = 0;	//0:初期、1：次
	auto udf = UserDefault::getInstance();

	switch (this->index) {

	case 0: {
		const char *str0 = "Kabe::SetPrm(0)";
		log("%s", str0);

		this->thokuPrm = udf->getIntegerForKey("TYOKU_0", 5);
		this->edaPrm = udf->getIntegerForKey("EDA_0", 5);
		this->zizokPrm = udf->getIntegerForKey("ZIZOKU_0", 5);
		this->kabePrm = udf->getIntegerForKey("KABE_0", 5);
		this->syokiRen = udf->getIntegerForKey("SYOKI_0", 5);
		this->thokuPrm2 = udf->getIntegerForKey("TYOKU2_0", 5);
		this->edaPrm2 = udf->getIntegerForKey("EDA2_0", 5);
		this->zizokPrm2 = udf->getIntegerForKey("ZIZOKU2_0", 5);
		this->kabePrm2 = udf->getIntegerForKey("KABE2_0", 5);
		break;
	}
	case 1: {
		this->thokuPrm = udf->getIntegerForKey("TYOKU_1", 5);
		this->edaPrm = udf->getIntegerForKey("EDA_1", 5);
		this->zizokPrm = udf->getIntegerForKey("ZIZOKU_1", 5);
		this->kabePrm = udf->getIntegerForKey("KABE_1", 5);
		this->syokiRen = udf->getIntegerForKey("SYOKI_1", 5);
		this->thokuPrm2 = udf->getIntegerForKey("TYOKU2_1", 5);
		this->edaPrm2 = udf->getIntegerForKey("EDA2_1", 5);
		this->zizokPrm2 = udf->getIntegerForKey("ZIZOKU2_1", 5);
		this->kabePrm2 = udf->getIntegerForKey("KABE2_1", 5);
		break;
	}
	case 2: {
		this->thokuPrm = udf->getIntegerForKey("TYOKU_2", 5);
		this->edaPrm = udf->getIntegerForKey("EDA_2", 5);
		this->zizokPrm = udf->getIntegerForKey("ZIZOKU_2", 5);
		this->kabePrm = udf->getIntegerForKey("KABE_2", 5);
		this->syokiRen = udf->getIntegerForKey("SYOKI_2", 5);
		this->thokuPrm2 = udf->getIntegerForKey("TYOKU2_2", 5);
		this->edaPrm2 = udf->getIntegerForKey("EDA2_2", 5);
		this->zizokPrm2 = udf->getIntegerForKey("ZIZOKU2_2", 5);
		this->kabePrm2 = udf->getIntegerForKey("KABE2_2", 5);
		break;
	}
	case 3: {
		this->thokuPrm = udf->getIntegerForKey("TYOKU_3", 5);
		this->edaPrm = udf->getIntegerForKey("EDA_3", 5);
		this->zizokPrm = udf->getIntegerForKey("ZIZOKU_3", 5);
		this->kabePrm = udf->getIntegerForKey("KABE_3", 5);
		this->syokiRen = udf->getIntegerForKey("SYOKI_3", 5);
		this->thokuPrm2 = udf->getIntegerForKey("TYOKU2_3", 5);
		this->edaPrm2 = udf->getIntegerForKey("EDA2_3", 5);
		this->zizokPrm2 = udf->getIntegerForKey("ZIZOKU2_3", 5);
		this->kabePrm2 = udf->getIntegerForKey("KABE2_3", 5);
		break;
	}
	case 4: {
		this->thokuPrm = udf->getIntegerForKey("TYOKU_4", 5);
		this->edaPrm = udf->getIntegerForKey("EDA_4", 5);
		this->zizokPrm = udf->getIntegerForKey("ZIZOKU_4", 5);
		this->kabePrm = udf->getIntegerForKey("KABE_4", 5);
		this->syokiRen = udf->getIntegerForKey("SYOKI_4", 5);
		this->thokuPrm2 = udf->getIntegerForKey("TYOKU2_4", 5);
		this->edaPrm2 = udf->getIntegerForKey("EDA2_4", 5);
		this->zizokPrm2 = udf->getIntegerForKey("ZIZOKU2_4", 5);
		this->kabePrm2 = udf->getIntegerForKey("KABE2_4", 5);
		break;
	}
	case 5: {
		this->thokuPrm = udf->getIntegerForKey("TYOKU_5", 5);
		this->edaPrm = udf->getIntegerForKey("EDA_5", 5);
		this->zizokPrm = udf->getIntegerForKey("ZIZOKU_5", 5);
		this->kabePrm = udf->getIntegerForKey("KABE_5", 5);
		this->syokiRen = udf->getIntegerForKey("SYOKI_5", 5);
		this->thokuPrm2 = udf->getIntegerForKey("TYOKU2_5", 5);
		this->edaPrm2 = udf->getIntegerForKey("EDA2_5", 5);
		this->zizokPrm2 = udf->getIntegerForKey("ZIZOKU2_5", 5);
		this->kabePrm2 = udf->getIntegerForKey("KABE2_5", 5);
		break;
	}
	case 6: {
		this->thokuPrm = udf->getIntegerForKey("TYOKU_6", 5);
		this->edaPrm = udf->getIntegerForKey("EDA_6", 5);
		this->zizokPrm = udf->getIntegerForKey("ZIZOKU_6", 5);
		this->kabePrm = udf->getIntegerForKey("KABE_6", 5);
		this->syokiRen = udf->getIntegerForKey("SYOKI_6", 5);
		this->thokuPrm2 = udf->getIntegerForKey("TYOKU2_6", 5);
		this->edaPrm2 = udf->getIntegerForKey("EDA2_6", 5);
		this->zizokPrm2 = udf->getIntegerForKey("ZIZOKU2_6", 5);
		this->kabePrm2 = udf->getIntegerForKey("KABE2_6", 5);
		break;
	}
	case 7: {
		this->thokuPrm = udf->getIntegerForKey("TYOKU_7", 5);
		this->edaPrm = udf->getIntegerForKey("EDA_7", 5);
		this->zizokPrm = udf->getIntegerForKey("ZIZOKU_7", 5);
		this->kabePrm = udf->getIntegerForKey("KABE_7", 5);
		this->syokiRen = udf->getIntegerForKey("SYOKI_7", 5);
		this->thokuPrm2 = udf->getIntegerForKey("TYOKU2_7", 5);
		this->edaPrm2 = udf->getIntegerForKey("EDA2_7", 5);
		this->zizokPrm2 = udf->getIntegerForKey("ZIZOKU2_7", 5);
		this->kabePrm2 = udf->getIntegerForKey("KABE2_7", 5);
		break;
	}
	case 8: {
		this->thokuPrm = udf->getIntegerForKey("TYOKU_8", 5);
		this->edaPrm = udf->getIntegerForKey("EDA_8", 5);
		this->zizokPrm = udf->getIntegerForKey("ZIZOKU_8", 5);
		this->kabePrm = udf->getIntegerForKey("KABE_8", 5);
		this->syokiRen = udf->getIntegerForKey("SYOKI_8", 5);
		this->thokuPrm2 = udf->getIntegerForKey("TYOKU2_8", 5);
		this->edaPrm2 = udf->getIntegerForKey("EDA2_8", 5);
		this->zizokPrm2 = udf->getIntegerForKey("ZIZOKU2_8", 5);
		this->kabePrm2 = udf->getIntegerForKey("KABE2_8", 5);
		break;
	}
	case 9: {
		this->thokuPrm = udf->getIntegerForKey("TYOKU_9", 5);
		this->edaPrm = udf->getIntegerForKey("EDA_9", 5);
		this->zizokPrm = udf->getIntegerForKey("ZIZOKU_9", 5);
		this->kabePrm = udf->getIntegerForKey("KABE_9", 5);
		this->syokiRen = udf->getIntegerForKey("SYOKI_9", 5);
		this->thokuPrm2 = udf->getIntegerForKey("TYOKU2_9", 5);
		this->edaPrm2 = udf->getIntegerForKey("EDA2_9", 5);
		this->zizokPrm2 = udf->getIntegerForKey("ZIZOKU2_9", 5);
		this->kabePrm2 = udf->getIntegerForKey("KABE2_9", 5);
		break;
	}
	case 10: {
		this->thokuPrm = udf->getIntegerForKey("TYOKU_10", 5);
		this->edaPrm = udf->getIntegerForKey("EDA_10", 5);
		this->zizokPrm = udf->getIntegerForKey("ZIZOKU_10", 5);
		this->kabePrm = udf->getIntegerForKey("KABE_10", 5);
		this->syokiRen = udf->getIntegerForKey("SYOKI_10", 5);
		this->thokuPrm2 = udf->getIntegerForKey("TYOKU2_10", 5);
		this->edaPrm2 = udf->getIntegerForKey("EDA2_10", 5);
		this->zizokPrm2 = udf->getIntegerForKey("ZIZOKU2_10", 5);
		this->kabePrm2 = udf->getIntegerForKey("KABE2_10", 5);
		break;
	}
	case 11: {
		this->thokuPrm = udf->getIntegerForKey("TYOKU_11", 5);
		this->edaPrm = udf->getIntegerForKey("EDA_11", 5);
		this->zizokPrm = udf->getIntegerForKey("ZIZOKU_11", 5);
		this->kabePrm = udf->getIntegerForKey("KABE_11", 5);
		this->syokiRen = udf->getIntegerForKey("SYOKI_11", 5);
		this->thokuPrm2 = udf->getIntegerForKey("TYOKU2_11", 5);
		this->edaPrm2 = udf->getIntegerForKey("EDA2_11", 5);
		this->zizokPrm2 = udf->getIntegerForKey("ZIZOKU2_11", 5);
		this->kabePrm2 = udf->getIntegerForKey("KABE2_11", 5);
		break;
	}

	}

}

void Kabe::ResetKabe() {
	//パラメータはそのままでリセット
	if (madeStep == 1) {
		madeStep = 0;
		this->ChgPrm();
	}
	this->syokiRen_ = 0;

}

void Kabe::ChgPrm() {
	//パラメータ1を2へ反転する。
	madeStep = 1;

	const char *str0 = "Kabe::ChgPrm()";
	log("%s", str0);

	int t_; //直進性
	int e_; //枝分かれ性
	int z_; //連続性
	int k_; //壁への回り込み性

	t_ = this->thokuPrm2;
	e_ = this->edaPrm2;
	z_ = this->zizokPrm2;
	k_ = this->kabePrm2;
	this->thokuPrm2 = this->thokuPrm;
	this->edaPrm2 = this->edaPrm;
	this->zizokPrm2 = this->zizokPrm;
	this->kabePrm2 = this->kabePrm;

	this->thokuPrm = t_;
	this->edaPrm = e_;
	this->zizokPrm = z_;
	this->kabePrm = k_;

}
void Kabe::Fin() {

	if (this->onFinishListener) {
		onFinishListener(this);
	}

}

