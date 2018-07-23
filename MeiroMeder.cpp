#include "MeiroMeder.h"

USING_NS_CC;
#include <string>
#include <fstream>
#include <vector>
// ヘッダファイルインクルード
//#include "cocos-ext.h"
#include "platform/android/jni/JniHelper.h"
// 呼び出すメソッドが書かれているパッケージ名とjavaクラス名
#define  CLASS_NAME "org/cocos2dx/cpp/AppActivity"
#define TWEET "tweet"
#define OPENRNK "openRankPark"
#define SENDSCR "sendRankParkScore"
#define WRITEDETA "writeDeta"
#define READDETA "readDeta"
USING_NS_CC;
MeiroMeder::MeiroMeder() :
		maderCnt(0), _Maders(NULL), _msgLabel(NULL) {

}
MeiroMeder::~MeiroMeder() {
	this->MemoryClear();
	CC_SAFE_RELEASE_NULL(_Maders);
	CC_SAFE_RELEASE_NULL(_msgLabel);
}
MeiroMeder* MeiroMeder::create(int x_, int y_, int t_) {

	MeiroMeder* mMeder = new MeiroMeder();

	if (mMeder) {

		mMeder->autorelease();
//		this->InitMap(Vec2(x_, y_), t_);
//		this->winSize = Director::getInstance()->getWinSize();
//		this->ctPt.set(winSize.width / 2, winSize.height / 2);

		return mMeder;

	} else {
		CC_SAFE_DELETE(mMeder);

		return nullptr;
	}
}
MeiroMeder * MeiroMeder::create() {
	auto mMeder = new MeiroMeder();
	if (mMeder) {
		mMeder->autorelease();
		return mMeder;
	} else {
		CC_SAFE_DELETE(mMeder);
//pool=NULL;
		return nullptr;
	}
}

void MeiroMeder::MemoryClear() {

	for (vector<int>::iterator it = mMap.begin(); it != mMap.end();) {
//delete it;
		it = mMap.erase(it);
	}

	for (vector<Vec2>::iterator it = mMaders.begin(); it != mMaders.end();) {
// delete it;
		it = mMaders.erase(it);
	}

	for (vector<int>::iterator it = mMaderDirects.begin(); it != mMaderDirects.end();) {
// delete it;
		it = mMaderDirects.erase(it);
	}

	for (vector<Vec2>::iterator it = mAns.begin(); it != mAns.end();) {
// delete it;
		it = mAns.erase(it);
	}

//	 if (mMap) {
//this->mMap.clear();
	this->mMap.shrink_to_fit();
//std::vector<int>().swap(this->mMap);
//	 }	//0:なし、1：外壁、2：壁、3：壁メーダー、4：start、5：goal
//	 if (mMader) {

//this->mMaders.clear();
	this->mMaders.shrink_to_fit();
//std::vector<cocos2d::Vec2>().swap(this->mMaders);
//	 }	//壁メーダーの位置を保持
//	 if (mMaderDirects) {
//this->mMaderDirects.clear();
	this->mMaderDirects.shrink_to_fit();
//std::vector<int>().swap(this->mMaderDirects);
//	 }	//壁メーダーの進行方向を保持
//	 if (mAns) {
//this->mAns.clear();
	this->mAns.shrink_to_fit();
//std::vector<cocos2d::Vec2>().swap(this->mAns);	//アンサールートを保持。
//	 }

}

void MeiroMeder::InitMap_Prm(Vec2 cSize) {

	auto udf = UserDefault::getInstance();
	int a = udf->getIntegerForKey("MADER_CNT", 5);
	int b = udf->getIntegerForKey("TYOKU", 5);
	int c = udf->getIntegerForKey("EDA", 5);
	int d = udf->getIntegerForKey("ZIZOKU", 5);
	int e = udf->getIntegerForKey("KABE", 5);
	int f = udf->getIntegerForKey("SYOKI", 5);
	int g = udf->getIntegerForKey("TYOKU2", 5);
	int h = udf->getIntegerForKey("EDA2", 5);
	int i = udf->getIntegerForKey("ZIZOKU2", 5);
	int j = udf->getIntegerForKey("KABE2", 5);

	this->InitMap(cSize, a, b, c, d, e, f, g, h, i, j);

}

void MeiroMeder::InitMap(Vec2 cSize, int maderCnt, int tPrm_, int ePrm_, int zPrm_, int kPrm_, int syokiCnt,
		int tPrm, int ePrm, int zPrm, int kPrm) {

	this->thokuPrm = tPrm; //直進性
	this->edaPrm = ePrm; //枝から新規発生性
	this->zizokPrm = zPrm; //継続性
	this->kabePrm = kPrm; //壁に回りこみ性
	this->syokiRen = syokiCnt;
	this->InitMap(cSize, maderCnt, tPrm_, ePrm_, zPrm_, kPrm_);

}

void MeiroMeder::InitMap(Vec2 cSize, int maderCnt, int t, int e, int z, int k) {

	this->thokuPrm2 = t; //直進性
	this->edaPrm = e; //枝から新規発生性
	this->zizokPrm = z; //継続性
	this->kabePrm = k; //壁に回りこみ性

//	this->thokuPrm_ = t;
//	this->edaPrm_ = e;
//	this->zizokPrm_ = z;
//	this->kabePrm_ = k;

	this->InitMap(cSize, maderCnt);
}

void MeiroMeder::InitMap(Vec2 cSize, int maderCnt, int t, int e, int z) {

	this->thokuPrm2 = this->thokuPrm;
	this->edaPrm2 = this->edaPrm;
	this->zizokPrm2 = this->zizokPrm;

	this->thokuPrm = t;
	this->edaPrm = e;
	this->zizokPrm = z;

	this->InitMap(cSize, maderCnt);
}
//迷路作成プロセス
//Vec2 courceSize;//コースのサイズを指定。偶数
//std::vector<int> mMap;//0:なし、1：成長壁、2：メーダーがいる壁,3：終了壁、4：start、5：goal
//std::vector<Vec2> mMaders;//壁メーダーの位置を保持
void MeiroMeder::InitMap(Vec2 cSize, int x) {

//_time = 0;

	this->maderCnt = x;
	this->courceSize.set(cSize);
	madeRate = 0;
	madeRateAll = 0;
	_madeFin=false;
	mMap.clear();
	mMaders.clear();
	mMaderDirects.clear();
	mAns.clear();
	int xx = (int) cSize.x * (int) cSize.y;
	this->setMaders(KabePool::create(this->maderCnt));
	this->getMaders()->AllPop();
//	this->getMaders()->AllPop(this->thokuPrm, this->edaPrm, this->zizokPrm, this->kabePrm, this->syokiRen,
//			this->thokuPrm2, this->edaPrm, this->zizokPrm, this->kabePrm);

//外壁を作成する。
	for (int i = 0; i < xx; i++) {

		if (i % (int) cSize.x == 0 || i % (int) cSize.x == (int) cSize.x - 1 || i < (int) cSize.x
				|| i > (int) cSize.x * (int) cSize.y - (int) cSize.x) {

			if (i % 2 == 0) {
				mMap.push_back(1);
			} else {
				mMap.push_back(3);
			}

		} else {
			mMap.push_back(0);
		}

	}
	madeRateAll = xx - (int) ((cSize.x - 1) / 2) * (int) ((cSize.y - 1) / 2)
			- (int) ((cSize.x - 1) / 2) * (int) ((cSize.y - 1) / 2);
	this->GoalPt.set(courceSize - Vec2(2, 2));
	this->StartPt.set(Vec2(1, 1));

//それぞれの壁メーダーをセットする。
	long span = (2 * courceSize.x + 2 * courceSize.y) / x;
//	int rnd = arc4random()
//			% static_cast<int>((int) (2 * courceSize.x + 2 * courceSize.y));

	for (int i = 0; i < maderCnt; i++) {
		int rnd = arc4random() % static_cast<int>((int) (2 * courceSize.x + 2 * courceSize.y));
//rnd= arc4random() % static_cast<int>((int)(courceSize.x+courceSize.y));
//		Vec2 xx = MaderSet(0, GetMapIndex(GetWakuPosition(span * i + rnd)));
		Vec2 xx = MaderSet(0, GetMapIndex(GetWakuPosition(rnd)));

//Vec2 xx = MaderSet(0,rnd);
		if (!xx.equals(Vec2(-1, -1))) {

			mMaders.push_back(xx);
			SetMapStatus(xx, 2);
			int dct_ = ChgDirect(xx, -1);
			mMaderDirects.push_back(dct_);
			mMaderKabes.push_back(0);

			this->getMaders()->getMember().at(i)->mMapPt.set(xx);
			this->getMaders()->getMember().at(i)->mDirect = dct_;
			this->getMaders()->getMember().at(i)->mSetiKabe = 0;

		} else {
			break;
		}

	}
	this->GetMadeRate();

//	TTFConfig ttfConfig("HGRPP1.TTC", 40, GlyphCollection::DYNAMIC);
//
//	this->setMsgLabel(Label::createWithTTF(ttfConfig, "a迷路作成中!"));
////	_msgLabel->setPosition(winSize.width / 2, winSize.height - 30);
//	_msgLabel->setScale(1.0f);
//	_msgLabel->setColor(Color3B::WHITE);
//	_msgLabel->setAnchorPoint(Vec2(0.5, 0.5));
//	_msgLabel->setAlignment(TextHAlignment::CENTER);

	const char *str0 = "MeiroMeder::InitMap";
	log("%s", str0);

}
//	迷路の実際のサイズを表示
Vec2 MeiroMeder::GetMeiroSize() {
	const char *str0 = "MeiroMeder::GetMeiroSize()";
	log("%s", str0);
	this->winSize = Director::getInstance()->getWinSize();
	this->ctPt.set(winSize.width / 2, winSize.height / 2);

	MeiroSize.x = (courceSize.x - 1) * (float) w * this->scale_;
	MeiroSize.y = (courceSize.y - 1) * (float) w * this->scale_;

	MoveRect.setRect(ctPt.x, ctPt.y, MeiroSize.x - winSize.width, MeiroSize.y - winSize.height);

	min_x = ctPt.x;
	min_y = ctPt.y;

	max_x = MeiroSize.x - winSize.width / 2;
	max_y = MeiroSize.y - winSize.height / 2;

//	オフセットポイントも作成
	OffSetPt.set(ctPt - Vec2(MeiroSize.x / 2, MeiroSize.y / 2));
	if (OffSetPt.x < OffSetPt0.x || OffSetPt.y < OffSetPt0.y) {
		OffSetPt.set(OffSetPt0);
	}

	this->MeiroCenter.set(MeiroSize.x / 2, MeiroSize.y / 2);

	return MeiroSize;

}

Vec2 MeiroMeder::GetMovePoint(Vec2 pt) {

//	pt -= OffSetPt;
//	-this->_player->getPosition() + this->ctPt
	//まずは中心にセット
//	MovePoint.x = -(max_x + OffSetPt0.x) + this->ctPt.x;
//	MovePoint.y = -(max_y + OffSetPt0.y) + this->ctPt.y;
	MovePoint.set(this->ctPt - this->MeiroCenter);

	if (this->MeiroSize.x + this->OffSetPt0.x * 2 > winSize.width) {

		if (min_x - OffSetPt.x >= pt.x) {
			MovePoint.x = OffSetPt.x;
		} else if (min_x - OffSetPt.x < pt.x && max_x + OffSetPt.x >= pt.x) {

			MovePoint.x = (-pt.x + this->ctPt.x);

		} else {
			if (min_x - OffSetPt.x < max_x + OffSetPt.x) {
				MovePoint.x = -(max_x + OffSetPt.x) + this->ctPt.x;
			}
		}

	}

	if (this->MeiroSize.y + this->OffSetPt0.y * 2 > winSize.height) {

		if (min_y - OffSetPt.y >= pt.y) {
			MovePoint.y = OffSetPt.y;
		} else if (min_y - OffSetPt.y < pt.y && max_y + OffSetPt.y >= pt.y) {

			MovePoint.y = (-pt.y + this->ctPt.y);

		} else {

			if (min_y - OffSetPt.y < max_y + OffSetPt.y) {
				MovePoint.y = -(max_y + OffSetPt.y) + this->ctPt.y;
			}
		}

	}
	return MovePoint;

}

void MeiroMeder::ResetMap() {

	this->InitMap(this->courceSize, this->maderCnt);
	this->getMaders()->AllReset();

	return;

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

//this->maderCnt = x;
//this->courceSize.set(cSize);
	mMap.clear();
	mMaders.clear();
	mMaderDirects.clear();
	mMaderKabes.clear();
	mAns.clear();
	this->syokiRen_ = 0;
	madeRate = 0;
	int xx = (int) this->courceSize.x * (int) this->courceSize.y;

//外壁を作成する。
	for (int i = 0; i < xx; i++) {

		if (i % (int) courceSize.x == 0 || i % (int) courceSize.x == (int) courceSize.x - 1
				|| i < (int) courceSize.x
				|| i > (int) courceSize.x * (int) courceSize.y - (int) courceSize.x) {

			if (i % 2 == 0) {
				mMap.push_back(1);
			} else {
				mMap.push_back(3);
			}

		} else {
			mMap.push_back(0);
		}
	}

//それぞれの壁メーダーをセットする。
	long span = (2 * courceSize.x + 2 * courceSize.y) / this->maderCnt;
	int rnd = arc4random() % static_cast<int>((int) (courceSize.x + courceSize.y));

	for (int i = 0; i < maderCnt; i++) {
//rnd= arc4random() % static_cast<int>((int)(courceSize.x+courceSize.y));
		Vec2 xx = MaderSet(0, GetMapIndex(GetWakuPosition(span * i + rnd)));
//Vec2 xx = MaderSet(0,rnd);
		if (!xx.equals(Vec2(-1, -1))) {
			mMaders.push_back(xx);
			SetMapStatus(xx, 2);
			mMaderDirects.push_back(ChgDirect(xx, -1));
			mMaderKabes.push_back(0);
		} else {
			break;
		}

	}

}

Vec2 MeiroMeder::GetJunctionPoint(Vec2 nowPt, Vec2 dctPt) {
	//現在のポイントから指定の方向へ次のジャンクションポイント（一本道以外のポイント）を探す.

//	位置を補正。
	if ((int) nowPt.x % 2 == 0 || (int) nowPt.y % 2 == 0) {
		nowPt -= dctPt;
		if (this->GetMapStatus(nowPt) == 3 || this->GetMapStatus(nowPt) == -1) {
			nowPt += dctPt;
			return nowPt;
		}

	}

	if (this->GetMapStatus(nowPt) == 3 || this->GetMapStatus(nowPt) == -1) {
		return Vec2::ZERO;
	}

	Vec2 ptA;
	Vec2 ptB;
	ptA.set(dctPt);
	ptB.set(dctPt);
	ptA.rotate(Vec2::ZERO, M_PI / 2);
	ptB.rotate(Vec2::ZERO, -M_PI / 2);

	if (this->GetMapStatus(nowPt + dctPt) != 3 && this->GetMapStatus(nowPt + dctPt) != -1) {
		//	①まず進めるか？
		if (this->GetMapStatus(nowPt + dctPt * 2 + ptA) != 3
				|| this->GetMapStatus(nowPt + dctPt * 2 + ptB) != 3) {
			//	②進んだ先に分かれ道があるか？
			return nowPt + dctPt * 2;
		} else {
			//再帰
			return this->GetJunctionPoint(nowPt + dctPt * 2, dctPt);
		}

	} else {

		return nowPt;
	}

}

void MeiroMeder::SetMapStatus(Vec2 pt, int sts) {

	int i = this->GetMapIndex(pt);

	if (i >= 0) {
		mMap.at(i) = sts;
	}
}

int MeiroMeder::GetMapStatus(Vec2 pt) {

	int i = this->GetMapIndex(pt);

	if (i >= 0) {
		return mMap.at(i);
	} else {
		return -1;
	}
}

//壁かどうかチェックする
bool MeiroMeder::ChkKabe(int index) {

	Vec2 pt;
	pt.set(this->GetMapPosition(index));

	if (pt.x == 0 || pt.x == courceSize.x - 1 || pt.y == 0 || pt.y == courceSize.y - 1) {
		return true;
	} else {
		return false;
	}

}

//インデックスよりマップのポジションを返す
Vec2 MeiroMeder::GetMapPosition(int index) {

	Vec2 pt;

	if (index >= 0 && index < mMap.size()) {
		pt.x = index % (int) this->courceSize.x;
		pt.y = index / (int) this->courceSize.x;
	} else {
		pt.x = -1;
		pt.y = -1;
	}
	return pt;
}

//指定のポイントのコースの迷路インデックスを返す。
int MeiroMeder::GetMapIndex(Vec2 pt) {
	if (pt.x < 0 || pt.y < 0 || pt.x >= courceSize.x || pt.y >= courceSize.y) {
		return -1; //範囲外の場合-1を返す。
	}
	int xx = (int) pt.x + (int) (courceSize.x * pt.y);
	return xx;
}

Vec2 MeiroMeder::ChgPositionFromMapToImage(Vec2 mapPt_) {
//マップのポイントを実際のspriteのポジションに変換
	float x_ = mapPt_.x;
	float y_ = mapPt_.y;

	x_ -= 1;
	y_ -= 1;

	x_ *= (scale_ * w);
	y_ *= (scale_ * w);

	x_ += (scale_ * w);
	y_ += (scale_ * w);

	Vec2 ans_;
	ans_.set(x_, y_);

	return ans_;

}
Vec2 MeiroMeder::ChgPositionFromImageToMap(Vec2 imgPt_) {
//spriteのポイントを実際のマップのポジションに変換

	int x_ = imgPt_.x;
	int y_ = imgPt_.y;

	x_ -= w / 2;
	y_ -= w / 2;

	x_ /= (scale_ * w);
	y_ /= (scale_ * w);

	x_ += 1;
	y_ += 1;

	Vec2 ans_;
	ans_.set(x_, y_);

	return ans_;

}
Vec2 MeiroMeder::ChgPositionFromImageToMap2(Vec2 imgPt_) {
//spriteのポイントを実際のマップのポジションに変換
//奇数のみ

	int x_ = imgPt_.x;
	int y_ = imgPt_.y;

	x_ -= w * scale_;
	y_ -= w * scale_;

	x_ /= (scale_ * w * 2);
	y_ /= (scale_ * w * 2);

	x_ *= 2;
	y_ *= 2;

	x_ += 1;
	y_ += 1;

	Vec2 ans_;
	ans_.set(x_, y_);

	return ans_;

}
int MeiroMeder::GetMadeRate() {
	//現在の進捗率パーセントを算出
	int k = 0;

	for (int i = 0; i < mMap.size(); i++) {

		if (mMap.at(i) == 3) {
			k++;
		}

	}

	float xx = (float) k / (float) madeRateAll;
	xx *= 100;
	int ans = (int) xx;
	madeRate = ans;
	return (int) ans;

}
bool MeiroMeder::MeiroMadeStep() {

	int rnd1;
	int rnd2;

	this->syokiRen_++;

	this->GetMadeRate();

	if (this->syokiRen <= this->madeRate) {

		this->madeStep = 1;

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

	for (int i = 0; i < this->maderCnt; i++) {

		if (this->_Maders->getMember().at(i)->syokiRen <this->madeRate
				&& this->_Maders->getMember().at(i)->madeStep == 0) {
			this->_Maders->getMember().at(i)->ChgPrm();
		}

		if (this->_Maders->getMember().at(i)->zizokPrm == 100) {
			rnd1 = 1;
		} else {
			rnd1 = arc4random() % static_cast<int>(this->_Maders->getMember().at(i)->zizokPrm);
		}

		if (rnd1 == 0) {

			this->SetMapStatus(mMaders.at(i), 1);
			//メーダーを他に移す。
			if (this->_Maders->getMember().at(i)->edaPrm == 100) {
				rnd2 = 1;
			} else {
				rnd2 = arc4random() % static_cast<int>(this->_Maders->getMember().at(i)->edaPrm);
			}

			if (rnd2 != 0) {
				mMaders.at(i).set(MaderSet(2));
			} else {
				mMaders.at(i).set(MaderSet(1));
			}

		} else if (!MaderMove(i, this->_Maders->getMember().at(i)->thokuPrm,
				this->_Maders->getMember().at(i)->kabePrm)) {
			//動けなかった場合、メーダーを別の壁に移動させる。

			const char *str0 = "kabe idou";
			log("%s", str0);
			mMaders.at(i).set(MaderSet(0));

			mMaderKabes.at(i) = 0;

			if (this->_Maders->getMember().at(i)->edaPrm == 100) {
				rnd2 = 1;
			} else {
				rnd2 = arc4random() % static_cast<int>(this->_Maders->getMember().at(i)->edaPrm);
			}

			if (rnd2 != 0) {
				mMaders.at(i).set(MaderSet(2));
				const char *str0 = "枝へ移動";
				log("%s", str0);

			} else {
				const char *str0 = "壁へ移動";
				log("%s", str0);
				mMaders.at(i).set(MaderSet(1));
			}
		}

//最終的に全てで検索
		if (mMaders.at(i).x == -1) {

			const char *str0 = "//最終的に全てで検索";
			log("%s", str0);
			mMaders.at(i).set(MaderSet(0));

		}

	}
	if (MaderSet(0).x == -1) {
		const char *str0 = "迷路作成完了！";
		log("%s", str0);
		_madeFin=true;
		return false;
	} else {
		return true;
	}
}
void MeiroMeder::MeiroMadeAll() {

	while (MeiroMadeStep()) {
//	this->ShowMsg(this->getPlayer()->getPosition(), "MEIRO MADE!");
	}
}

void MeiroMeder::MeiroMadePercent(int parcent_) {
	//迷路を指定のパーセントまで作る。

	if (parcent_ < 0) {
		parcent_ = 0;
	} else if (parcent_ > 100) {
		parcent_ = 100;
	}

	while (this->madeRate < parcent_) {
		if (!this->MeiroMadeStep()) {
			break;
		}
	}

}

//動ける方向（1-4）を現在の方向dctから時計回りに探す。ない場合-1を返す。
int MeiroMeder::ChgDirect(Vec2 pt, int dct) {
	int dct_;
	dct_ = dct;
	int rnd = arc4random() % static_cast<int>(2);
	for (int i = 0; i < 5; i++) {

		if (rnd == 0) {
			dct_++;
		} else {
			dct_--;
		}

		if (dct_ > 4) {
			dct_ = 1;
		}

		if (dct_ < 1) {
			dct_ = 4;
		}

		if (MoveChk(pt, dct_)) {
			return dct_;
		}
	}

	return -1;
}
//指定の方向に移動可能かどうかチェック。
bool MeiroMeder::MoveChk(Vec2 pt, int direct) {
//指定の方向に移動可能かどうかチェック。
	Vec2 pt1;
	Vec2 dpt;
	dpt.set(GetDirection(direct));

	pt1.set(pt + dpt);
	if (GetMapStatus(pt1) == 0) {
		pt1.set(pt + dpt + dpt);
		if (GetMapStatus(pt1) == 0) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

Vec2 MeiroMeder::GetWakuPosition(long index) {

	Vec2 pt;
	int i = index;
	do {

		if (i - courceSize.x < 0) {
			pt.x = i;
			pt.y = 0;
			return pt;
		}
		i -= courceSize.x;

		if (i - courceSize.y < 0) {
			pt.x = courceSize.x - 1;
			pt.y = i;
			return pt;
		}
		i -= courceSize.y;

		if (i - courceSize.x < 0) {
			pt.x = courceSize.x - i;
			pt.y = courceSize.y - 1;
			return pt;
		}
		i -= courceSize.x;

		if (i - courceSize.y < 0) {
			pt.x = 0;
			pt.y = courceSize.y - i;
			return pt;
		}
		i -= courceSize.y;

	} while (true);

}
Vec2 MeiroMeder::MaderSet(int pos, int stindex) {
	int rnd = stindex;

	while (rnd > courceSize.x * courceSize.y - 1) {
		rnd = rnd - courceSize.x * courceSize.y + 1;
	}
	while (rnd < 0) {
		rnd = rnd + courceSize.x * courceSize.y - 1;
	}
	switch (pos) {

	case 0: {
		for (int i = rnd; i < courceSize.x * courceSize.y; i++) {
			if (mMap.at(i) == 1) {
				return GetMapPosition(i);
			}
		}

		for (int i = 0; i < rnd; i++) {
			if (mMap.at(i) == 1) {
				return GetMapPosition(i);
			}
		}
		break;
	}
	case 1: {
		for (int i = rnd; i < courceSize.x * courceSize.y; i++) {
			if (mMap.at(i) == 1 && ChkKabe(i)) {
				return GetMapPosition(i);
			}
		}

		for (int i = 0; i < rnd; i++) {
			if (mMap.at(i) == 1 && ChkKabe(i)) {
				return GetMapPosition(i);
			}
		}
		break;
	}
	case 2: {
		for (int i = rnd; i < courceSize.x * courceSize.y; i++) {
			if (mMap.at(i) == 1 && !ChkKabe(i)) {
				return GetMapPosition(i);
			}
		}

		for (int i = 0; i < rnd; i++) {
			if (mMap.at(i) == 1 && !ChkKabe(i)) {
				return GetMapPosition(i);
			}
		}
		break;
	}
	}
	return Vec2(-1, -1);
}
//メーダーをセットする。フリーのメーダーのセット可能位置を探す。0:全部、1：壁のみ、2：枝のみ
Vec2 MeiroMeder::MaderSet(int pos) {
//ランダムスタート
	int rnd = arc4random() % static_cast<int>(courceSize.x * courceSize.y);

	switch (pos) {

	case 0: {
		for (int i = rnd; i < courceSize.x * courceSize.y; i++) {
			if (mMap.at(i) == 1) {
				return GetMapPosition(i);
			}
		}

		for (int i = 0; i < rnd; i++) {
			if (mMap.at(i) == 1) {
				return GetMapPosition(i);
			}
		}
		break;
	}
	case 1: {
		for (int i = rnd; i < courceSize.x * courceSize.y; i++) {
			if (mMap.at(i) == 1 && ChkKabe(i)) {
				return GetMapPosition(i);
			}
		}

		for (int i = 0; i < rnd; i++) {
			if (mMap.at(i) == 1 && ChkKabe(i)) {
				return GetMapPosition(i);
			}
		}
		break;
	}
	case 2: {
		for (int i = rnd; i < courceSize.x * courceSize.y; i++) {
			if (mMap.at(i) == 1 && !ChkKabe(i)) {
				return GetMapPosition(i);
			}
		}

		for (int i = 0; i < rnd; i++) {
			if (mMap.at(i) == 1 && !ChkKabe(i)) {
				return GetMapPosition(i);
			}
		}
		break;
	}
	}
	return Vec2(-1, -1);

}

Vec2 MeiroMeder::GetDirection(int index) {

	Vec2 dpt = Vec2::ZERO;

	switch (index) {
	case 1: {
		dpt.y += 1;
		break;
	}
	case 2: {
		dpt.x += 1;
		break;
	}
	case 3: {
		dpt.y -= 1;
		break;
	}
	case 4: {
		dpt.x -= 1;
		break;
	}

	}

	return dpt;

}
//指定のインデックスのメーダーが移動する。

bool MeiroMeder::MaderMove(int index, int chokPrm, int kabePrm) {

//方向を変えるか判定
	int rnd_ = 1;
	int rnd2_ = 1;
	if (chokPrm < 100) {
		rnd_ = arc4random() % static_cast<int>(chokPrm);
	}
	if (kabePrm < 100) {
		rnd2_ = arc4random() % static_cast<int>(kabePrm);
	}
	if (rnd_ == 0) {
		mMaderDirects.at(index) = this->ChgDirect(mMaders.at(index), mMaderDirects.at(index));
	} else if (mMaderKabes.at(index) > 0 && rnd2_ > 0) {
//壁にそっているか判定
		if (MoveChk(mMaders.at(index), mMaderKabes.at(index))) {

			//壁の方向は、元の進行方向の逆になればいい。
			int x = mMaderDirects.at(index);
			x += 2;
			if (x > 4) {
				x -= 4;
			}
			mMaderDirects.at(index) = mMaderKabes.at(index);
			mMaderKabes.at(index) = x;
		}
	}
	if (!MoveChk(mMaders.at(index), mMaderDirects.at(index))) {
//指示されている方向に移動できなかったら、壁パラメーターを見て、別の移動できる方向を探すか,終了する。

		int rnd3_ = 1;

		if (kabePrm < 100) {
			rnd3_ = arc4random() % static_cast<int>(kabePrm);
		}

		if (rnd3_ > 0) {
			mMaderKabes.at(index) = mMaderDirects.at(index); //壁と認識する。
			mMaderDirects.at(index) = this->ChgDirect(mMaders.at(index), mMaderDirects.at(index));
		} else {

			mMaderDirects.at(index) = this->ChgDirect(mMaders.at(index), mMaderDirects.at(index));
			if (mMaderDirects.at(index) > 0) {
				SetMapStatus(mMaders.at(index), 1);
			} else {
				SetMapStatus(mMaders.at(index), 3);
			}

			int rnd4 = 1;
			if (this->_Maders->getMember().at(index)->edaPrm < 100) {
				rnd4 = arc4random() % static_cast<int>(this->_Maders->getMember().at(index)->edaPrm);
			}
			if (rnd4 != 0) {
				mMaders.at(index).set(MaderSet(2));
			} else {
				mMaders.at(index).set(MaderSet(1));
			}

			const char *str0 = "MeiroMeder::MaderMove chng";
			log("%s", str0);

			return false;
		}
	}
//上記の操作で、指示している移動方向が-1（移動できない）でない場合,実際に移動する。
	if (mMaderDirects.at(index) > 0) {
		Vec2 pt1;
		Vec2 dpt;
		dpt.set(Vec2::ZERO);
		pt1.set(mMaders.at(index));
		dpt.set(this->GetDirection(mMaderDirects.at(index)));

//実際にメーダーを指示した方向に進める。
//2マス進む
		SetMapStatus(pt1, 1); //現在のメーダーの位置ステータスを1：成長壁にする。
		pt1 += dpt;
		SetMapStatus(pt1, 3); //現在のメーダーの位置から1マス進んだ位置をステータスを3：終了壁にする。
		pt1 += dpt;
		SetMapStatus(pt1, 2); //現在のメーダーの位置から2マス進んだ位置をステータスを2：メーダー壁にする。
		mMaders.at(index).set(pt1); //メーダーの位置を変える

		return true;
	} else {
//移動できない場合、現在のメーダーの位置をステータス3：終了壁にして、Falseを返す。
		SetMapStatus(mMaders.at(index), 3);
		return false;
	}
}
bool MeiroMeder::MaderMove(int index, int chokPrm) {

//方向を変えるか判定
	int rnd_ = arc4random() % static_cast<int>(chokPrm);

	if (rnd_ == 0) {
		mMaderDirects.at(index) = this->ChgDirect(mMaders.at(index), mMaderDirects.at(index));
	}

//現在のめーだーが、指示されている方向（mMaderDirects）に移動できるか確認
	if (!MoveChk(mMaders.at(index), mMaderDirects.at(index))) {
//指示されている方向に移動できなかったら、別の移動できる方向を探す。

		mMaderKabes.at(index) = mMaderDirects.at(index); //壁と認識する。
		mMaderDirects.at(index) = this->ChgDirect(mMaders.at(index), mMaderDirects.at(index));

	}
//上記の操作で、指示している移動方向が-1（移動できない）でない場合,実際に移動する。
	if (mMaderDirects.at(index) > 0) {
		Vec2 pt1;
		Vec2 dpt;
		dpt.set(Vec2::ZERO);
		pt1.set(mMaders.at(index));
		dpt.set(this->GetDirection(mMaderDirects.at(index)));

//実際にメーダーを指示した方向に進める。
//2マス進む
		SetMapStatus(pt1, 1); //現在のメーダーの位置ステータスを1：成長壁にする。
		pt1 += dpt;
		SetMapStatus(pt1, 3); //現在のメーダーの位置から1マス進んだ位置をステータスを3：終了壁にする。
		pt1 += dpt;
		SetMapStatus(pt1, 2); //現在のメーダーの位置から2マス進んだ位置をステータスを2：メーダー壁にする。
		mMaders.at(index).set(pt1); //メーダーの位置を変える

		return true;
	} else {
//移動できない場合、現在のメーダーの位置をステータス3：終了壁にして、Falseを返す。
		SetMapStatus(mMaders.at(index), 3);
		return false;
	}
}

//指定のポイントの上下左右の状態より、コースNoを取得
int MeiroMeder::GetCourceNo(Vec2 pt) {

	int _1_ = 1;
	int _2_ = 1;
	int _3_ = 1;
	int _4_ = 1;

	Vec2 drct = Vec2::ZERO;

	if (GetMapStatus(Vec2(pt.x, pt.y + 1)) <= 0) {
		_1_ = 0;
	}

	if (GetMapStatus(Vec2(pt.x + 1, pt.y)) <= 0) {
		_2_ = 0;
	}
	if (GetMapStatus(Vec2(pt.x, pt.y - 1)) <= 0) {
		_3_ = 0;
	}
	if (GetMapStatus(Vec2(pt.x - 1, pt.y)) <= 0) {
		_4_ = 0;
	}
	if (_1_ == 0 && _2_ == 0 && _3_ == 0 && _4_ == 0) {
		return 0;
	}
	if (_1_ == 1 && _2_ == 0 && _3_ == 0 && _4_ == 0) {
		return 1;
	}
	if (_1_ == 0 && _2_ == 1 && _3_ == 0 && _4_ == 0) {
		return 2;
	}
	if (_1_ == 1 && _2_ == 1 && _3_ == 0 && _4_ == 0) {
		return 3;
	}
	if (_1_ == 0 && _2_ == 0 && _3_ == 1 && _4_ == 0) {
		return 4;
	}
	if (_1_ == 1 && _2_ == 0 && _3_ == 1 && _4_ == 0) {
		return 5;
	}
	if (_1_ == 0 && _2_ == 1 && _3_ == 1 && _4_ == 0) {
		return 6;
	}
	if (_1_ == 1 && _2_ == 1 && _3_ == 1 && _4_ == 0) {
		return 7;
	}
	if (_1_ == 0 && _2_ == 0 && _3_ == 0 && _4_ == 1) {
		return 8;
	}
	if (_1_ == 1 && _2_ == 0 && _3_ == 0 && _4_ == 1) {
		return 9;
	}
	if (_1_ == 0 && _2_ == 1 && _3_ == 0 && _4_ == 1) {
		return 10;
	}
	if (_1_ == 1 && _2_ == 1 && _3_ == 0 && _4_ == 1) {
		return 11;
	}
	if (_1_ == 0 && _2_ == 0 && _3_ == 1 && _4_ == 1) {
		return 12;
	}
	if (_1_ == 1 && _2_ == 0 && _3_ == 1 && _4_ == 1) {
		return 13;
	}
	if (_1_ == 0 && _2_ == 1 && _3_ == 1 && _4_ == 1) {
		return 14;
	}
	if (_1_ == 1 && _2_ == 1 && _3_ == 1 && _4_ == 1) {
		return 15;
	}

	return 0;

}

void MeiroMeder::MadeFarCource() {
//コース上でスタートからゴールまでの距離が一番長いものを探す。
	cntMaxA = 0;
	Vec2 stPt;
	Vec2 glPt;
//mMap.size()//重くなりすぎる。
//	for (int i = 0; i < mMap.size(); i++) {
//
//		if (mMap.at(i) != 3) {
//			const char *str2 = "MadeFarCource()";
//			log("%s", str2);
//			stPt.set(this->GetMapPosition(i));
//			glPt.set(this->MadeFarPoint(stPt));
//
//			if (cntMaxA < cntMax) {
//				const char *str2 = "MadeFarCource()_cntMaxA < cntMax";
//				log("%s", str2);
//				cntMaxA = cntMax;
//				StartPt.set(stPt);
//				GoalPt.set(glPt);
//			}
//		}
//	}

//適当に探す。

//	最初だけ右下
	for (int i = 0; i < mMap.size(); i++) {

		if (mMap.at(i) != 3) {
			const char *str2 = "MadeFarCource()";
			log("%s", str2);
			stPt.set(this->GetMapPosition(i));
			glPt.set(this->MadeFarPoint(stPt));

			if (cntMaxA < cntMax) {
				const char *str2 = "MadeFarCource()_cntMaxA < cntMax";
				log("%s", str2);
				cntMaxA = cntMax;
				StartPt.set(stPt);
				GoalPt.set(glPt);
				goto AAA;
			}
		}
	}

	AAA:

	int cnt = 0;

	for (int cnt = 0; cnt < 10; cnt++) {

		int k = arc4random() % static_cast<int>(mMap.size() / 2);

		for (int i = k; i < mMap.size(); i++) {

			if (mMap.at(i) != 3 && (int) this->GetMapPosition(i).x % 2 == 1
					&& (int) this->GetMapPosition(i).y % 2 == 1) {
				const char *str2 = "MadeFarCource()";
				log("%s", str2);
				stPt.set(this->GetMapPosition(i));
				glPt.set(this->MadeFarPoint(stPt));

				if (cntMaxA < cntMax) {
					const char *str2 = "MadeFarCource()_cntMaxA < cntMax";
					log("%s", str2);
					cntMaxA = cntMax;
					StartPt.set(stPt);
					GoalPt.set(glPt);

				}
				i = mMap.size();
			}

		}

	}

}

Vec2 MeiroMeder::MadeFarPoint(Vec2 pt1) {

	mAns.clear();
	mAns.push_back(pt1);

	Vec2 mypt;
	mypt.set(pt1);
	Vec2 fpt; //前のポイント
	Vec2 rpt; //左の寄りかかるポイント。
	int dct = 1; //現在の向き。

	Vec2 farPt;
	int cnt_ = 0;
	cntMax = 0;

//①左の寄りかかる壁を探す。
	while (GetMapStatus(mypt + Vec2(0, 1)) == 0) {
		mypt.set(mypt + Vec2(0, 1));
		mAns.push_back(mypt);
	}
	rpt.set(mypt + Vec2(0, 1));
	fpt.set(mypt + Vec2(1, 0));
	dct = 2;
	int xx = 0;
//②左に寄りかかっている状態で、前が空いているか確認しあいていたら進む。、、、
//	while (mypt != pt2) {
	while (xx < 60000) {
		switch (dct) {

		case 1: {
			if (GetMapStatus(mypt + Vec2(0, 1)) == 0) {
				mypt.set(mypt + Vec2(0, 1));
				AnsPtSet(mypt);
				//進んだ先で、左が空いていたら、左を向く。
				if (GetMapStatus(mypt + Vec2(-1, 0)) == 0) {
					dct = 4;
				}
			} else {
				//空いていなかったら、進まずに右を向く。
				dct = 2;
			}
			break;
		}
		case 2: {
			if (GetMapStatus(mypt + Vec2(1, 0)) == 0) {
				mypt.set(mypt + Vec2(1, 0));
				AnsPtSet(mypt);
				//進んだ先で、左が空いていたら、左を向く。
				if (GetMapStatus(mypt + Vec2(0, 1)) == 0) {
					dct = 1;
				}
			} else {
				//空いていなかったら、進まずに右を向く。
				dct = 3;
			}
			break;
		}
		case 3: {
			if (GetMapStatus(mypt + Vec2(0, -1)) == 0) {
				mypt.set(mypt + Vec2(0, -1));
				AnsPtSet(mypt);
				//進んだ先で、左が空いていたら、左を向く。
				if (GetMapStatus(mypt + Vec2(1, 0)) == 0) {
					dct = 2;
				}
			} else {
				//空いていなかったら、進まずに右を向く。
				dct = 4;
			}
			break;
		}
		case 4: {
			if (GetMapStatus(mypt + Vec2(-1, 0)) == 0) {
				mypt.set(mypt + Vec2(-1, 0));
				AnsPtSet(mypt);
				//進んだ先で、左が空いていたら、左を向く。
				if (GetMapStatus(mypt + Vec2(0, -1)) == 0) {
					dct = 3;
				}
			} else {
				//空いていなかったら、進まずに右を向く。
				dct = 1;
			}
			break;
		}
		}

		if (cntMax < mAns.size()) {

			cntMax = mAns.size();

			farPt.set(mypt);
		}

		xx++;
	}

	return farPt;

}

bool MeiroMeder::MadeAns(Vec2 pt1, Vec2 pt2) {

	mAns.clear();
	mAns.push_back(pt1);

	Vec2 mypt;
	mypt.set(pt1);
	Vec2 fpt; //前のポイント
	Vec2 rpt; //左の寄りかかるポイント。
	int dct = 1; //現在の向き。

//①左の寄りかかる壁を探す。
	while (GetMapStatus(mypt + Vec2(0, 1)) == 0) {
		mypt.set(mypt + Vec2(0, 1));
		mAns.push_back(mypt);
	}
	rpt.set(mypt + Vec2(0, 1));
	fpt.set(mypt + Vec2(1, 0));
	dct = 2;
	int xx = 0;
//②左に寄りかかっている状態で、前が空いているか確認しあいていたら進む。、、、
	while (mypt != pt2) {
//while (xx <1000) {
		switch (dct) {

		case 1: {
			if (GetMapStatus(mypt + Vec2(0, 1)) == 0) {
				mypt.set(mypt + Vec2(0, 1));
				AnsPtSet(mypt);
				//進んだ先で、左が空いていたら、左を向く。
				if (GetMapStatus(mypt + Vec2(-1, 0)) == 0) {
					dct = 4;
				}
			} else {
				//空いていなかったら、進まずに右を向く。
				dct = 2;
			}
			break;
		}
		case 2: {
			if (GetMapStatus(mypt + Vec2(1, 0)) == 0) {
				mypt.set(mypt + Vec2(1, 0));
				AnsPtSet(mypt);
				//進んだ先で、左が空いていたら、左を向く。
				if (GetMapStatus(mypt + Vec2(0, 1)) == 0) {
					dct = 1;
				}
			} else {
				//空いていなかったら、進まずに右を向く。
				dct = 3;
			}
			break;
		}
		case 3: {
			if (GetMapStatus(mypt + Vec2(0, -1)) == 0) {
				mypt.set(mypt + Vec2(0, -1));
				AnsPtSet(mypt);
				//進んだ先で、左が空いていたら、左を向く。
				if (GetMapStatus(mypt + Vec2(1, 0)) == 0) {
					dct = 2;
				}
			} else {
				//空いていなかったら、進まずに右を向く。
				dct = 4;
			}
			break;
		}
		case 4: {
			if (GetMapStatus(mypt + Vec2(-1, 0)) == 0) {
				mypt.set(mypt + Vec2(-1, 0));
				AnsPtSet(mypt);
				//進んだ先で、左が空いていたら、左を向く。
				if (GetMapStatus(mypt + Vec2(0, -1)) == 0) {
					dct = 3;
				}
			} else {
				//空いていなかったら、進まずに右を向く。
				dct = 1;
			}
			break;
		}
		}
		xx++;
	}

	return true;
}
void MeiroMeder::AnsPtSet(Vec2 pt) {

	if (mAns.size() > 1) {
		if (mAns.at(mAns.size() - 2) == pt) {
			mAns.pop_back();
		} else {
			mAns.push_back(pt);
		}
	} else {
		mAns.push_back(pt);
	}
}
void MeiroMeder::WriteDetaSQLite(int index) {
//SQLiteへ保存
//	std::string mMapDetaSt;
//
//	for (int i = 0; i < mMap.size(); i++) {
//		mMapDetaSt.append(StringUtils::toString((int) mMap.at(i)));
//	}
//
//	std::string str2 = mMapDetaSt;
//	char* cstr2 = new char[str2.size() + 1];
//	std::char_traits<char>::copy(cstr2, str2.c_str(), str2.size() + 1);
//
//	//SaveSQL::sqliteCreateTable();
//
//	std::string str = StringUtils::toString((int) index);
//	char* cstr = new char[str.size() + 1];
//	std::char_traits<char>::copy(cstr, str.c_str(), str.size() + 1);
//
//	//SaveSQL::sqliteSetValueForKey(cstr, cstr2);
//
//	delete[] cstr; // 開放
//	delete[] cstr2; // 開放

}
void MeiroMeder::WriteDeta_neo(int index) {

	JniMethodInfo t;
	std::string mMapDetaSt;
	Vec2 pt0;

//	for (int i = 0; i < mMap.size(); i++) {
//		mMapDetaSt.append(StringUtils::toString((int) mMap.at(i)));
//	}

	for (int i = 0; i < mMap.size(); i++) {

		pt0 = GetMapPosition(i);
		if ((int) pt0.x % 2 == 0 && (int) pt0.y % 2 == 0) {
			mMapDetaSt.append(StringUtils::toString((int) GetCourceNo(pt0)));
		}
	}

// クラス名とメソッド名を指定します。
//if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, WRITEDETA, "(I[I)V")) {
	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, WRITEDETA, "(ILjava/lang/String;)V")) {
		jstring jstr = t.env->NewStringUTF(mMapDetaSt.c_str());
		t.env->CallStaticVoidMethod(t.classID, t.methodID, index, jstr);
// 解放
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(jstr);

	}

}
void MeiroMeder::WriteDeta3(int index) {
//UserDefaulへ書き込み
	std::string mMapDetaSt;

	mMapDetaSt.append(DetaOut());

	auto udf = UserDefault::getInstance();
	switch (index) {

	case 0: {
		udf->setStringForKey("MEIRO_0", mMapDetaSt.c_str());
		const char *str1 = "udf->setStringForKey(MEIRO_0,N);";
		log("%s", str1);
		break;
	}
	case 1: {
		udf->setStringForKey("MEIRO_1", mMapDetaSt.c_str());
		const char *str0 = "udf->setStringForKey(MEIRO_1,N);";
		log("%s", str0);
		break;
	}
	case 2: {
		udf->setStringForKey("MEIRO_2", mMapDetaSt.c_str());
		break;
	}
	case 3: {
		udf->setStringForKey("MEIRO_3", mMapDetaSt.c_str());
		break;
	}
	case 4: {
		udf->setStringForKey("MEIRO_4", mMapDetaSt.c_str());
		break;
	}
	case 5: {
		udf->setStringForKey("MEIRO_5", mMapDetaSt.c_str());
		break;
	}
	case 6: {
		udf->setStringForKey("MEIRO_6", mMapDetaSt.c_str());
		break;
	}
	case 7: {
		udf->setStringForKey("MEIRO_7", mMapDetaSt.c_str());
		break;
	}
	case 8: {
		udf->setStringForKey("MEIRO_8", mMapDetaSt.c_str());
		break;
	}
	case 9: {
		udf->setStringForKey("MEIRO_9", mMapDetaSt.c_str());
		break;
	}
	case 10: {
		udf->setStringForKey("MEIRO_10", mMapDetaSt.c_str());
		break;
	}
	case 11: {
		udf->setStringForKey("MEIRO_11", mMapDetaSt.c_str());
		break;
	}
	case 12: {
		udf->setStringForKey("MEIRO_12", mMapDetaSt.c_str());
		break;
	}
	case 13: {
		udf->setStringForKey("MEIRO_13", mMapDetaSt.c_str());
		break;
	}
	case 14: {
		udf->setStringForKey("MEIRO_14", mMapDetaSt.c_str());
		break;
	}
	case 15: {
		udf->setStringForKey("MEIRO_15", mMapDetaSt.c_str());
		break;
	}
	case 16: {
		udf->setStringForKey("MEIRO_16", mMapDetaSt.c_str());
		break;
	}
	case 17: {
		udf->setStringForKey("MEIRO_17", mMapDetaSt.c_str());
		break;
	}
	case 18: {
		udf->setStringForKey("MEIRO_18", mMapDetaSt.c_str());
		break;
	}
	case 19: {
		udf->setStringForKey("MEIRO_19", mMapDetaSt.c_str());
		break;
	}
	case 20: {
		udf->setStringForKey("MEIRO_20", mMapDetaSt.c_str());
		break;
	}
	case 21: {
		udf->setStringForKey("MEIRO_21", mMapDetaSt.c_str());
		break;
	}
	case 22: {
		udf->setStringForKey("MEIRO_22", mMapDetaSt.c_str());
		break;
	}
	case 23: {
		udf->setStringForKey("MEIRO_23", mMapDetaSt.c_str());
		break;
	}
	case 24: {
		udf->setStringForKey("MEIRO_24", mMapDetaSt.c_str());
		break;
	}
	}

}
void MeiroMeder::WriteDeta(int index) {

	JniMethodInfo t;
	std::string mMapDetaSt;

//	mMapDetaSt.append(StringUtils::toString((int) courceSize.x));
//	mMapDetaSt.append(",");
//	mMapDetaSt.append(StringUtils::toString((int) courceSize.y));
//	mMapDetaSt.append("\n");
	for (int i = 0; i < mMap.size(); i++) {
		mMapDetaSt.append(StringUtils::toString((int) mMap.at(i)));
	}
//	mMapDetaSt.append("\n");
//	for (int i = 0; i < mAns.size(); i++) {
//		mMapDetaSt.append(StringUtils::toString((int) mAns.at(i).x));
//		mMapDetaSt.append(",");
//		mMapDetaSt.append(StringUtils::toString((int) mAns.at(i).y));
//	}

//this->ShowMsg(this->getPlayer()->getPosition(),"BBB");

// クラス名とメソッド名を指定します。
//if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, WRITEDETA, "(I[I)V")) {
	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, WRITEDETA, "(ILjava/lang/String;)V")) {
		jstring jstr = t.env->NewStringUTF(mMapDetaSt.c_str());
		t.env->CallStaticVoidMethod(t.classID, t.methodID, index, jstr);
// 解放
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(jstr);

	}

}

std::string MeiroMeder::DetaOut() {

	const char *str0 = "MeiroMeder::DetaOut()";
	log("%s", str0);

	std::string mMapDetaSt;
	mMapDetaSt.append(StringUtils::toString((int) this->courceSize.x) + "/");
	mMapDetaSt.append(StringUtils::toString((int) this->courceSize.y) + "/");
	mMapDetaSt.append(StringUtils::toString((int) this->StartPt.x) + "/");
	mMapDetaSt.append(StringUtils::toString((int) this->StartPt.y) + "/");
	mMapDetaSt.append(StringUtils::toString((int) this->GoalPt.x) + "/");
	mMapDetaSt.append(StringUtils::toString((int) this->GoalPt.y) + "/");

	for (int i = 0; i < this->mMap.size(); i++) {
		const char *str = "MeiroMeder::DetaOut(_add)";
		log("%s", str);
		mMapDetaSt.append(StringUtils::toString((int) this->mMap.at(i)));
	}

	return mMapDetaSt;

}

void MeiroMeder::ReadDeta3(int index) {

	auto udf = UserDefault::getInstance();
	String Str;
	switch (index) {

	case 0: {
		Str = udf->getStringForKey("MEIRO_0", "N");
		const char *str0 = "Str = udf->getStringForKey(MEIRO_0,N);";
		log("%s", str0);
		break;
	}
	case 1: {
		Str = udf->getStringForKey("MEIRO_1", "N");
		const char *str0 = "Str = udf->getStringForKey(MEIRO_1,N);";
		log("%s", str0);
		break;
	}
	case 2: {
		Str = udf->getStringForKey("MEIRO_2", "N");
		break;
	}
	case 3: {
		Str = udf->getStringForKey("MEIRO_3", "N");
		break;
	}
	case 4: {
		Str = udf->getStringForKey("MEIRO_4", "N");
		break;
	}
	case 5: {
		Str = udf->getStringForKey("MEIRO_5", "N");
		break;
	}
	case 6: {
		Str = udf->getStringForKey("MEIRO_6", "N");
		break;
	}
	case 7: {
		Str = udf->getStringForKey("MEIRO_7", "N");
		break;
	}
	case 8: {
		Str = udf->getStringForKey("MEIRO_8", "N");
		break;
	}
	case 9: {
		Str = udf->getStringForKey("MEIRO_9", "N");
		break;
	}
	case 10: {
		Str = udf->getStringForKey("MEIRO_10", "N");
		break;
	}
	case 11: {
		Str = udf->getStringForKey("MEIRO_11", "N");
		break;
	}
	case 12: {
		Str = udf->getStringForKey("MEIRO_12", "N");
		break;
	}
	case 13: {
		Str = udf->getStringForKey("MEIRO_13", "N");
		break;
	}
	case 14: {
		Str = udf->getStringForKey("MEIRO_14", "N");
		break;
	}
	case 15: {
		Str = udf->getStringForKey("MEIRO_15", "N");
		break;
	}
	case 16: {
		Str = udf->getStringForKey("MEIRO_16", "N");
		break;
	}
	case 17: {
		Str = udf->getStringForKey("MEIRO_17", "N");
		break;
	}
	case 18: {
		Str = udf->getStringForKey("MEIRO_18", "N");
		break;
	}
	case 19: {
		Str = udf->getStringForKey("MEIRO_19", "N");
		break;
	}
	case 20: {
		Str = udf->getStringForKey("MEIRO_20", "N");
		break;
	}
	case 21: {
		Str = udf->getStringForKey("MEIRO_21", "N");
		break;
	}
	case 22: {
		Str = udf->getStringForKey("MEIRO_22", "N");
		break;
	}
	case 23: {
		Str = udf->getStringForKey("MEIRO_23", "N");
		break;
	}
	case 24: {
		Str = udf->getStringForKey("MEIRO_24", "N");
		break;
	}
	}

//	String Str = UserDefault::getInstance()->getStringForKey("GALALLY", "N");

	CCString* pStr = CCString::create(Str._string);

	if (pStr->_string.substr(0, 1) == "N" || pStr->_string == "") {
		const char *str0 = "MeiroMeder::MeiroMadeFromFile_debug_N";
		log("%s", str0);
		return;
	}

//	int speedten_ = 0; //円の描写時間。小さいほど高得点
//	int ookisaten_ = 0; //円の大きさ。大きいほど高得点
//	int sinenten_ = 0; //真円度。低いほど高得点
//	int toziten_ = 0; //書き初めと終わりとの距離。短いほど高得点
//	int tokuten_ = 0;
//	float r = 0;
//	float g = 0;
//	float b = 0;

	String Bffer_;
	String hk = "@";

	int fsturn = -1;
	int turn = 0;
	int xx;

	mMap.clear();

	const char *str3 = "MeiroMeder::ReadDeta3";
	log("%s", str3);

	for (int i = 0; i < pStr->length(); i++) {

		String str_ = pStr->_string.substr(i, 1);

		if (fsturn < 5) {
			if (str_._string == "/") {

				fsturn++;
				switch (fsturn) {
				case 0: {

					const char *str0 = "this->courceSize.x = xx;";
					log("%s", str0);

					xx = Bffer_.intValue();
					this->courceSize.x = xx;
					Bffer_ = "";
					break;
				}

				case 1: {

					xx = Bffer_.intValue();
					this->courceSize.y = xx;
					Bffer_ = "";
					break;
				}
				case 2: {

					xx = Bffer_.intValue();
					this->StartPt.x = xx;
					Bffer_ = "";
					break;
				}
				case 3: {

					xx = Bffer_.intValue();
					this->StartPt.y = xx;
					Bffer_ = "";
					break;
				}
				case 4: {

					xx = Bffer_.intValue();
					this->GoalPt.x = xx;
					Bffer_ = "";
					break;
				}
				case 5: {

					xx = Bffer_.intValue();
					this->GoalPt.y = xx;
					Bffer_ = "";

					const char *str0 = "this->GoalPt.y = xx;";
					log("%s", str0);

					break;
				}

				}
			} else {
				Bffer_.append(str_._string);
			}
		} else {

			mMap.push_back(str_.intValue());
			const char *str4 = "mMap.push_back(str_.intValue());";
			log("%s", str4);
		}
	}

}

String MeiroMeder::ReadDeta(int index) {

	JniMethodInfo t;
	std::string mMapDetaSt;

//if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, WRITEDETA, "(I[I)V")) {
	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, READDETA, "(I)Ljava/lang/String;")) {
		jstring jstr = (jstring) t.env->CallStaticObjectMethod(t.classID, t.methodID, index);
		const char* str = t.env->GetStringUTFChars(jstr, NULL);
		mMapDetaSt = str;
// 解放
		t.env->ReleaseStringUTFChars(jstr, str);
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(jstr);
	}
	return mMapDetaSt;

}
String MeiroMeder::ReadDeta2(int index) {

	CCDictionary* meirodata_;

	int index_ = (index - 1) / 100;
	index_++;

	switch (index_) {

	case 1: {
		meirodata_ = CCDictionary::createWithContentsOfFile("meirodata_1.plist");
		break;
	}
	case 2: {
		meirodata_ = CCDictionary::createWithContentsOfFile("meirodata_2.plist");
		break;
	}
	case 3: {
		meirodata_ = CCDictionary::createWithContentsOfFile("meirodata_3.plist");
		break;
	}
	case 4: {
		meirodata_ = CCDictionary::createWithContentsOfFile("meirodata_4.plist");
		break;
	}
	case 5: {
		meirodata_ = CCDictionary::createWithContentsOfFile("meirodata_5.plist");
		break;
	}
	case 6: {
		meirodata_ = CCDictionary::createWithContentsOfFile("meirodata_6.plist");
		break;
	}
	case 7: {
		meirodata_ = CCDictionary::createWithContentsOfFile("meirodata_7.plist");
		break;
	}
	case 8: {
		meirodata_ = CCDictionary::createWithContentsOfFile("meirodata_8.plist");
		break;
	}
	case 9: {
		meirodata_ = CCDictionary::createWithContentsOfFile("meirodata_9.plist");
		break;
	}
	case 10: {
		meirodata_ = CCDictionary::createWithContentsOfFile("meirodata_10.plist");
		break;
	}

	}

//meirodata_ = CCDictionary::createWithContentsOfFile(
//	"meirodata_" + StringUtils::toString((int) index_) + ".plist");

	CCString* map = (CCString*) meirodata_->objectForKey("meiro_" + StringUtils::toString((int) index));
//  CCObject *dic= item->objectAtIndex(0);
//  CCObject *map = ((cocos2d::CCDictionary*)(dic))->objectForKey("m"+StringUtils::toString((int)index));

	return map->getCString();

}
bool MeiroMeder::MeiroMadeFromFile_debug_neo(int index) {
//mMap.clear();
//mMaders.clear();
//mMaderDirects.clear();
	mAns.clear();

	String Str = this->ReadDeta(index);
	CCString* pStr = CCString::create(Str._string);

	if (pStr->_string.substr(0, 1) == "N" || pStr->_string == "") {
		const char *str0 = "MeiroMeder::MeiroMadeFromFile_debug_N";
		log("%s", str0);
		return false;
	}

	for (int i = 0; i < mMap.size(); i++) {
		std::string str_ = pStr->_string.substr(i, 1);
		auto str = Value(str_);
		int k = str.asInt();
		mMap.at(i) = k;

	}

	return true;

}
bool MeiroMeder::MeiroMadeFromFile_debug(int index) {
//mMap.clear();
//mMaders.clear();
//mMaderDirects.clear();
	mAns.clear();

	String Str = this->ReadDeta(index);
	CCString* pStr = CCString::create(Str._string);

	if (pStr->_string.substr(0, 1) == "N" || pStr->_string == "") {
		const char *str0 = "MeiroMeder::MeiroMadeFromFile_debug_N";
		log("%s", str0);
		return false;
	}

	for (int i = 0; i < mMap.size(); i++) {
		std::string str_ = pStr->_string.substr(i, 1);
		auto str = Value(str_);
		int k = str.asInt();
		mMap.at(i) = k;

	}

	return true;

}
bool MeiroMeder::MeiroMadeFromSQLite(int index) {
//SQLiteファイルより読み込み

//SaveSQL::sqliteCreateTable();

//	mAns.clear();
//	const char *str1 = "MeiroMeder::MeiroMadeFromSQLite";
//	log("%s", str1);
//
//	std::string str = StringUtils::toString((int) index);
//	char* cstr = new char[str.size() + 1]; // メモリ確保
//	std::strcpy(cstr, str.c_str());        // コピー
//
//	//const char *cstr2 = this->getSQLite()->sqliteGetValueForKey(cstr);
//
////	std::string str2 = std::string(cstr2);
//
////	log("%s", cstr2);
//
//	String Str = str2;
//	CCString* pStr = CCString::create(Str._string);
//
//	if (pStr->_string.substr(0, 1) == "N" || pStr->_string == "") {
//		const char *str0 = "MeiroMeder::MeiroMadeFromSQLite_N";
//		log("%s", str0);
//		return false;
//	}
//
//	for (int i = 0; i < mMap.size(); i++) {
////		const char *str0 = "MeiroMeder::MeiroMadeFromSQLite_Y";
////		log("%s", str0);
//		std::string str_ = pStr->_string.substr(i, 1);
//		auto str = Value(str_);
//		int k = str.asInt();
//		mMap.at(i) = k;
//
//	}
//
////	delete[] cstr; // 開放
////	delete[] cstr2; // 開放

	return true;
}
void MeiroMeder::MeiroMadeFromFile(int index) {

//mMap.clear();
//mMaders.clear();
//mMaderDirects.clear();
	mAns.clear();

	String Str = this->ReadDeta2(index);
	CCString* pStr = CCString::create(Str._string);

	for (int i = 0; i < mMap.size(); i++) {
		std::string str_ = pStr->_string.substr(i, 1);
		auto str = Value(str_);
		int k = str.asInt();
		mMap.at(i) = k;

	}
}

int MeiroMeder::GetLevelStatus(int lvl_) {
//0:ロック、1以上はクリヤ数とアンロック状態を示す。

	int ans_;

	switch (lvl_) {

	case 1: {
		ans_ = UserDefault::getInstance()->getIntegerForKey("LEVEL1_STATUS", 0);
		break;
	}
	case 2: {
		ans_ = UserDefault::getInstance()->getIntegerForKey("LEVEL2_STATUS", -1);
		break;
	}
	case 3: {
		ans_ = UserDefault::getInstance()->getIntegerForKey("LEVEL3_STATUS", -1);
		break;
	}
	case 4: {
		ans_ = UserDefault::getInstance()->getIntegerForKey("LEVEL4_STATUS", -1);
		break;
	}
	case 5: {
		ans_ = UserDefault::getInstance()->getIntegerForKey("LEVEL5_STATUS",-1);
		break;
	}
	case 6: {
		ans_ = UserDefault::getInstance()->getIntegerForKey("LEVEL6_STATUS",-1);
		break;
	}
	case 7: {
		//リリース時には、デフォルトを-1に戻す。
		ans_ = UserDefault::getInstance()->getIntegerForKey("LEVEL7_STATUS", -1);
		break;
	}

	}

	return ans_;

}
void MeiroMeder::SetLevelStatus(int lvl_, int atai_) {

	switch (lvl_) {

	case 1: {
		UserDefault::getInstance()->setIntegerForKey("LEVEL1_STATUS", atai_);
		break;
	}
	case 2: {
		UserDefault::getInstance()->setIntegerForKey("LEVEL2_STATUS", atai_);
		break;
	}
	case 3: {
		UserDefault::getInstance()->setIntegerForKey("LEVEL3_STATUS", atai_);
		break;
	}
	case 4: {
		UserDefault::getInstance()->setIntegerForKey("LEVEL4_STATUS", atai_);
		break;
	}
	case 5: {
		UserDefault::getInstance()->setIntegerForKey("LEVEL5_STATUS", atai_);
		break;
	}
	case 6: {
		UserDefault::getInstance()->setIntegerForKey("LEVEL6_STATUS", atai_);
		break;
	}
	case 7: {
		UserDefault::getInstance()->setIntegerForKey("LEVEL7_STATUS", atai_);
		break;
	}
	}
}
void MeiroMeder::AddLevelStatus(int lvl_, int d_) {

	int atai_;

	switch (lvl_) {

	case 1: {
		atai_ = this->GetLevelStatus(1);
		atai_ += d_;
		if (atai_ < 0) {
			atai_ = 0;
		}
		UserDefault::getInstance()->setIntegerForKey("LEVEL1_STATUS", atai_);
		if (atai_ > 2 && this->GetLevelStatus(1 + 1) == -1) {
			//ひとつ上のレベルを解放
			this->SetLevelStatus(1 + 1, 0);
		}
		break;
	}
	case 2: {
		atai_ = this->GetLevelStatus(2);
		atai_ += d_;
		if (atai_ < 0) {
			atai_ = 0;
		}
		UserDefault::getInstance()->setIntegerForKey("LEVEL2_STATUS", atai_);
		if (atai_ >2 && this->GetLevelStatus(2 + 1) == -1) {
			//ひとつ上のレベルを解放
			this->SetLevelStatus(2 + 1, 0);
		}
		break;
	}
	case 3: {
		atai_ = this->GetLevelStatus(3);
		atai_ += d_;
		if (atai_ < 0) {
			atai_ = 0;
		}
		UserDefault::getInstance()->setIntegerForKey("LEVEL3_STATUS", atai_);
		if (atai_ > 2 && this->GetLevelStatus(3 + 1) == -1) {
			//ひとつ上のレベルを解放
			this->SetLevelStatus(3 + 1, 0);
		}
		break;
	}
	case 4: {
		atai_ = this->GetLevelStatus(4);
		atai_ += d_;
		if (atai_ < 0) {
			atai_ = 0;
		}
		UserDefault::getInstance()->setIntegerForKey("LEVEL4_STATUS", atai_);
		if (atai_ > 2 && this->GetLevelStatus(4 + 1) == -1) {
			//ひとつ上のレベルを解放
			this->SetLevelStatus(4 + 1, 0);
		}
		break;
	}
	case 5: {
		atai_ = this->GetLevelStatus(5);
		atai_ += d_;
		if (atai_ < 0) {
			atai_ = 0;
		}
		UserDefault::getInstance()->setIntegerForKey("LEVEL5_STATUS", atai_);
		if (atai_ > 2 && this->GetLevelStatus(5 + 1) == -1) {
			//ひとつ上のレベルを解放
			this->SetLevelStatus(5 + 1, 0);
		}
		break;
	}
	case 6: {
		atai_ = this->GetLevelStatus(6);
		atai_ += d_;
		if (atai_ < 0) {
			atai_ = 0;
		}
		UserDefault::getInstance()->setIntegerForKey("LEVEL6_STATUS", atai_);
		if (atai_ > 2 && this->GetLevelStatus(6 + 1) == -1) {
			//ひとつ上のレベルを解放
			this->SetLevelStatus(6 + 1, 0);
		}
		break;
	}
	case 7: {
		atai_ = this->GetLevelStatus(7);
		atai_ += d_;
		if (atai_ < 0) {
			atai_ = 0;
		}
		UserDefault::getInstance()->setIntegerForKey("LEVEL7_STATUS", atai_);

		break;
	}
	}

}

void MeiroMeder::SetLevel(int lvl_) {
//レベル別にパラメーターをセットする。0のときは、ユーザーセットをしたもの。任意設定
	Level = lvl_;
	switch (lvl_) {

	case 0: {
		auto udf = UserDefault::getInstance();
		int a_ = udf->getIntegerForKey("MADER_CNT", 5);
		int b_ = udf->getIntegerForKey("TYOKU", 5);
		int c_ = udf->getIntegerForKey("EDA", 5);
		int d_ = udf->getIntegerForKey("ZIZOKU", 5);
		int e_ = udf->getIntegerForKey("KABE", 5);
		int f_ = udf->getIntegerForKey("SYOKI", 5);
		int g_ = udf->getIntegerForKey("TYOKU2", 5);
		int h_ = udf->getIntegerForKey("EDA2", 5);
		int i_ = udf->getIntegerForKey("ZIZOKU2", 5);
		int j_ = udf->getIntegerForKey("KABE2", 5);
		int k_ = udf->getIntegerForKey("COURCE_X", 5);

		if (k_ % 2 == 0) {
			k_++;
		}
		int l_ = udf->getIntegerForKey("COURCE_Y", 5);
		if (l_ % 2 == 0) {
			l_++;
		}
		InitMap(Vec2(k_, l_), a_, b_, c_, d_, e_, f_, g_, h_, i_, j_);

		break;
	}
	case 1: {
		const char *str1 = "MeiroMeder::SetLevel(int lvl_=1)";
		log("%s", str1);
		InitMap(Vec2(31, 31), 2);
		this->getMaders()->getMember().at(0)->SetPrm(2,25,100,750,50,20,25,50,50);
		this->getMaders()->getMember().at(1)->SetPrm(30,25,50,100,50,2,25,100,100);
		break;
	}
	case 2: {
		InitMap(Vec2(31, 51),2);
		this->getMaders()->getMember().at(0)->SetPrm(2,25,80,100,50,2,25,100,100);
		this->getMaders()->getMember().at(1)->SetPrmRnd();
		break;
	}
	case 3: {
		InitMap(Vec2(81, 101), 3);
		this->getMaders()->getMember().at(0)->SetPrmRnd();
		this->getMaders()->getMember().at(1)->SetPrmRnd();
		this->getMaders()->getMember().at(2)->SetPrm(2,25,100,100,50,2,25,100,100);
		break;
	}
	case 4: {
		InitMap(Vec2(121, 121), 2);
		this->getMaders()->getMember().at(0)->SetPrmRnd();
		this->getMaders()->getMember().at(1)->SetPrm(2,25,100,100,50,2,25,100,100);
		break;
	}
	case 5: {
		InitMap(Vec2(121, 201), 4);
		this->getMaders()->getMember().at(0)->SetPrm(2,25,30,100,50,20,25,100,100);
		this->getMaders()->getMember().at(1)->SetPrmRnd();

		this->getMaders()->getMember().at(2)->SetPrmRnd();
		this->getMaders()->getMember().at(3)->SetPrm(20,25,50,100,50,2,25,100,100);
		break;
	}
	case 6: {
		InitMap(Vec2(201, 201), 5);
		this->getMaders()->getMember().at(0)->SetPrm(70,25,100,100,50,2,25,100,100);
		this->getMaders()->getMember().at(1)->SetPrm(50,25,500,100,50,2,25,100,100);
		this->getMaders()->getMember().at(2)->SetPrm(2,25,100,100,50,2,25,100,100);
		this->getMaders()->getMember().at(3)->SetPrmRnd();
		this->getMaders()->getMember().at(4)->SetPrmRnd();

		break;
	}
	case 7: {
		auto udf = UserDefault::getInstance();
		int a_ = udf->getIntegerForKey("MADER_CNT", 5);
		int b_ = udf->getIntegerForKey("TYOKU", 5);
		int c_ = udf->getIntegerForKey("EDA", 5);
		int d_ = udf->getIntegerForKey("ZIZOKU", 5);
		int e_ = udf->getIntegerForKey("KABE", 5);
		int f_ = udf->getIntegerForKey("SYOKI", 5);
		int g_ = udf->getIntegerForKey("TYOKU2", 5);
		int h_ = udf->getIntegerForKey("EDA2", 5);
		int i_ = udf->getIntegerForKey("ZIZOKU2", 5);
		int j_ = udf->getIntegerForKey("KABE2", 5);
		int k_ = udf->getIntegerForKey("COURCE_X", 5);

		if (k_ % 2 == 0) {
			k_++;
		}
		int l_ = udf->getIntegerForKey("COURCE_Y", 5);
		if (l_ % 2 == 0) {
			l_++;
		}
		InitMap(Vec2(k_, l_), a_, b_, c_, d_, e_, f_, g_, h_, i_, j_);
		break;
	}

	}

}
int MeiroMeder::GetMeiroStatus(int index) {

	auto udf = UserDefault::getInstance();

	switch (index) {

	case 0: {

		return udf->getIntegerForKey("ID0", 0);
		break;
	}

	case 1: {
		return udf->getIntegerForKey("ID1", 0);
		break;
	}
	case 2: {
		return udf->getIntegerForKey("ID2", 0);
		break;
	}
	case 3: {
		return udf->getIntegerForKey("ID3", 0);
		break;
	}
	case 4: {
		return udf->getIntegerForKey("ID4", 0);
		break;
	}
	case 5: {
		return udf->getIntegerForKey("ID5", 0);
		break;
	}
	case 6: {
		return udf->getIntegerForKey("ID6", 0);
		break;
	}
	case 7: {
		return udf->getIntegerForKey("ID7", 0);
		break;
	}
	case 8: {
		return udf->getIntegerForKey("ID8", 0);
		break;
	}

	}

	return 0;

}
void MeiroMeder::SetMeiroStatus(int index, int status) {

	auto udf = UserDefault::getInstance();

	switch (index) {

	case 0: {

		return udf->setIntegerForKey("ID0", status);
		break;
	}

	case 1: {
		return udf->setIntegerForKey("ID1", status);
		break;
	}
	case 2: {
		return udf->setIntegerForKey("ID2", status);
		break;
	}
	case 3: {
		return udf->setIntegerForKey("ID3", status);
		break;
	}
	case 4: {
		return udf->setIntegerForKey("ID4", status);
		break;
	}
	case 5: {
		return udf->setIntegerForKey("ID5", status);
		break;
	}
	case 6: {
		return udf->setIntegerForKey("ID6", status);
		break;
	}
	case 7: {
		return udf->setIntegerForKey("ID7", status);
		break;
	}
	}

}
