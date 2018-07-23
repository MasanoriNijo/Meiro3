#include "MainScene_Debug.h"
#include "TitleScene.h"
#include "IMobileCocos2dxModule.h"
#include "ParticleSystemPool.h"
#include "NParticleSystemQuad.h"
#include "CourcePool.h"
#include "Cource.h"
#include "ItemPool.h"
#include "Item.h"
#include "MeiroMeder.h"
#include "Ball.h"
#include "cmath"
#include "SelectScene.h"
#include "platform/android/jni/JniHelper.h"

// 呼び出すメソッドが書かれているパッケージ名とjavaクラス名
#define  CLASS_NAME "org/cocos2dx/cpp/AppActivity"
#define TWEET "tweet"
#define OPENRNK "openRankPark"
#define SENDSCR "sendRankParkScore"
#define WRITEDETA "writeDeta"
#define READDETA "readDeta"
USING_NS_CC;

//USING_NS_CC_EXT;
//重力ベクトル
//const Vec2 GRAVITY_ACCERATION = Vec2(0, -10);
//const Vec2 NONGRAVITY = Vec2(0, 0);

MainScene_Debug::MainScene_Debug() :
		_meiroImg2(NULL), _meiroImg(NULL), _ansBase(NULL), _mapImg(NULL), _mMeder(
		NULL), _touchlistener(
		NULL), _contactlistener(
		NULL), _dots(
		NULL), _time(0), _sec(0), pcnt(0), _goalMap(NULL), _startMap(
		NULL), _timeUp(
		NULL), _levelShow(NULL), _goal(
		NULL), _youBest(NULL), _dctCnt(NULL), _mapCnt(NULL), _spdCnt(
		NULL), _bomCnt(NULL), dctCnt(0), mapCnt(0), spdCnt(0), bomCnt(0), bestLvl(
				0), nowLvl(0), restTime(0), _backGround(NULL), _backGround1(
		NULL), _backGround2(
		NULL), _scoreLabel(NULL), _bestLabel(NULL), _lifeLabel(NULL), _msgLabel(
		NULL), _playScore(0), _bestScore(0), _state(GameState::READY), _attackState(
				AttackState::A), _attackFlg(false), _world(NULL), _level(1), updateFlg(
				false), _courcePool(NULL), _dot0(
		NULL), _nomove1(
		NULL), _nomove2(NULL), _meiscene(NULL), _player(NULL), _itemPool(
		NULL), _menu1(NULL), _menu2(NULL), _menu3(
		NULL), _menu4(NULL), _menu5(NULL), _menu6(NULL), _menu7(NULL), _btn1(
		NULL), _btn2(
		NULL), _btn3(
		NULL), _btn4(NULL), _btn5(NULL), _btn6(NULL), _btn7(NULL), _cources(
		NULL), _items(
		NULL), _ready(
		NULL), _start(NULL), _tryAgainM(NULL), _menuM(NULL), _tryAgainI(
		NULL), _menuI(NULL), _lvlLavel(NULL), retryFlg(false) {
}

MainScene_Debug::~MainScene_Debug() {

	CC_SAFE_RELEASE_NULL(_meiroImg2);
	CC_SAFE_RELEASE_NULL(_meiroImg);
	CC_SAFE_RELEASE_NULL(_ansBase);
	CC_SAFE_RELEASE_NULL(_mapImg);
	CC_SAFE_RELEASE_NULL(_mMeder);
	CC_SAFE_RELEASE_NULL(_touchlistener);
	CC_SAFE_RELEASE_NULL(_contactlistener);
	//CC_SAFE_RELEASE_NULL(_dots);
	CC_SAFE_RELEASE_NULL(_goalMap);
	CC_SAFE_RELEASE_NULL(_startMap);
	CC_SAFE_RELEASE_NULL(_timeUp);
	CC_SAFE_RELEASE_NULL(_levelShow);
	CC_SAFE_RELEASE_NULL(_goal);
	CC_SAFE_RELEASE_NULL(_youBest);
	CC_SAFE_RELEASE_NULL(_dctCnt);
	CC_SAFE_RELEASE_NULL(_mapCnt);
	CC_SAFE_RELEASE_NULL(_spdCnt);
	CC_SAFE_RELEASE_NULL(_bomCnt);
	CC_SAFE_RELEASE_NULL(_backGround);
	CC_SAFE_RELEASE_NULL(_backGround1);
	CC_SAFE_RELEASE_NULL(_backGround2);
	CC_SAFE_RELEASE_NULL(_scoreLabel);
	CC_SAFE_RELEASE_NULL(_bestLabel);
	CC_SAFE_RELEASE_NULL(_lifeLabel);
	CC_SAFE_RELEASE_NULL(_msgLabel);
	//CC_SAFE_RELEASE_NULL(_world);
	CC_SAFE_RELEASE_NULL(_courcePool);
	CC_SAFE_RELEASE_NULL(_dot0);
	CC_SAFE_RELEASE_NULL(_nomove1);
	CC_SAFE_RELEASE_NULL(_nomove2);
	CC_SAFE_RELEASE_NULL(_meiscene);
	CC_SAFE_RELEASE_NULL(_player);
	CC_SAFE_RELEASE_NULL(_itemPool);
	CC_SAFE_RELEASE_NULL(_menu1);
	CC_SAFE_RELEASE_NULL(_menu2);
	CC_SAFE_RELEASE_NULL(_menu3);
	CC_SAFE_RELEASE_NULL(_menu4);
	CC_SAFE_RELEASE_NULL(_menu5);
	CC_SAFE_RELEASE_NULL(_menu6);
	CC_SAFE_RELEASE_NULL(_menu7);
	CC_SAFE_RELEASE_NULL(_btn1);
	CC_SAFE_RELEASE_NULL(_btn2);
	CC_SAFE_RELEASE_NULL(_btn3);
	CC_SAFE_RELEASE_NULL(_btn4);
	CC_SAFE_RELEASE_NULL(_btn5);
	CC_SAFE_RELEASE_NULL(_btn6);
	CC_SAFE_RELEASE_NULL(_btn7);
	//CC_SAFE_RELEASE_NULL(_cources);
	//CC_SAFE_RELEASE_NULL(_items);
	CC_SAFE_RELEASE_NULL(_ready);
	CC_SAFE_RELEASE_NULL(_start);
	CC_SAFE_RELEASE_NULL(_tryAgainM);
	CC_SAFE_RELEASE_NULL(_menuM);
	CC_SAFE_RELEASE_NULL(_tryAgainI);
	CC_SAFE_RELEASE_NULL(_menuI);
	CC_SAFE_RELEASE_NULL(_lvlLavel);

	for (int i = _cources.size() - 1; i >= 0; i--) {
		_cources.at(i)->removeFromParent();
		_cources.eraseObject(_cources.at(i));
	}

	for (int i = _items.size() - 1; i >= 0; i--) {
		_items.at(i)->removeFromParent();
		_items.eraseObject(_items.at(i));
	}

}

Scene* MainScene_Debug::createScene() {

	auto scene = Scene::createWithPhysics();

	//物理エンジン
	auto world = scene->getPhysicsWorld();

	//world->setGravity(GRAVITY_ACCERATION);
	world->setGravity(Vec2::ZERO);
//#if COCOS2D_DEBUG >0

	//world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

//#endif

	world->setSpeed(6.0);

	//this->setWorld(world);

	// 'layer' is an autorelease object
	auto layer = MainScene_Debug::create();

	// add layer as a child to scene
	scene->addChild(layer);

	return scene;
}
void MainScene_Debug::onAcceleration(Acceleration* acc, Event* unused_event) {

	//_lifeLabel->setString("ACC:" + StringUtils::toString((float) acc->x));
	if (_player != NULL) {

		//_player->AccellMove(Vec2(acc->x, acc->y));
		_player->AccellMove(acc);
	}

}

void MainScene_Debug::MemoryClear() {

	for (int i = _cources.size() - 1; i >= 0; i--) {
		_cources.at(i)->removeFromParent();
		_cources.eraseObject(_cources.at(i));

	}
	for (int i = _dots.size() - 1; i >= 0; i--) {
		_dots.at(i)->removeFromParent();
		_dots.eraseObject(_dots.at(i));

	}
	for (int i = _items.size() - 1; i >= 0; i--) {
		_items.at(i)->removeFromParent();
		_items.eraseObject(_items.at(i));

	}

	if (this->getMMeder() != NULL) {
		this->getMMeder()->MemoryClear();

	}

}
/*
 void MainScene_Debug::WriteDeta(int index) {

 JniMethodInfo t;
 // クラス名とメソッド名を指定します。
 if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, WRITEDETA,
 "(I)V")) {
 // voidなので、CallStaticVoidMethodで呼ぶ
 t.env->CallStaticVoidMethod(t.classID, t.methodID, index);
 // 解放
 t.env->DeleteLocalRef(t.classID);
 }

 }
 */
void MainScene_Debug::WriteDeta(int index) {

	//this->ShowMsg(this->getPlayer()->getPosition(), "AAA");

	/*
	 std::vector<int> mMapDeta;

	 mMapDeta.push_back(this->getMMeder()->courceSize.x);
	 mMapDeta.push_back(this->getMMeder()->courceSize.y);

	 for (int i = 0; i < this->getMMeder()->mMap.size(); i++) {
	 mMapDeta.push_back(this->getMMeder()->mMap.at(i));
	 }
	 for (int i = 0; i < this->getMMeder()->mAns.size(); i++) {
	 mMapDeta.push_back(this->getMMeder()->mAns.at(i).x);
	 mMapDeta.push_back(this->getMMeder()->mAns.at(i).y);
	 }

	 int x[mMapDeta.size()];

	 for (int i = 0; i < mMapDeta.size(); i++) {

	 x[i] = mMapDeta.at(i);

	 }
	 */

	JniMethodInfo t;
	std::string mMapDetaSt;

	mMapDetaSt.append(
			StringUtils::toString((int) this->getMMeder()->courceSize.x));
	mMapDetaSt.append(",");
	mMapDetaSt.append(
			StringUtils::toString((int) this->getMMeder()->courceSize.y));
	mMapDetaSt.append("\n");
	for (int i = 0; i < this->getMMeder()->mMap.size(); i++) {
		mMapDetaSt.append(
				StringUtils::toString((int) this->getMMeder()->mMap.at(i)));
	}
	mMapDetaSt.append("\n");
	for (int i = 0; i < this->getMMeder()->mAns.size(); i++) {
		mMapDetaSt.append(
				StringUtils::toString((int) this->getMMeder()->mAns.at(i).x));
		mMapDetaSt.append(",");
		mMapDetaSt.append(
				StringUtils::toString((int) this->getMMeder()->mAns.at(i).y));
	}

	//this->ShowMsg(this->getPlayer()->getPosition(),"BBB");

	// クラス名とメソッド名を指定します。
	//if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, WRITEDETA, "(I[I)V")) {
	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, WRITEDETA,
			"(ILjava/lang/String;)V")) {
		jstring jstr = t.env->NewStringUTF(mMapDetaSt.c_str());
		t.env->CallStaticVoidMethod(t.classID, t.methodID, index, jstr);
		// 解放
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(jstr);

	}

}

void MainScene_Debug::DrawMeiro2() {

	int ccnt = 0;
	for (int i = 0; i < this->getMMeder()->mMap.size(); i++) {

		Vec2 pt = this->getMMeder()->GetMapPosition(i);
		if ((int) pt.x % 2 == 0 && (int) pt.y % 2 == 0) {
			auto c1 = _cources.at(ccnt);
			c1->SetIndexA(this->getMMeder()->GetCourceNo(pt));
			ccnt++;
		}
	}

}

void MainScene_Debug::DrawMeiroDumy(int x) {

	_cources.reserve(0);

	int cnt = 0;

	Vec2 pt;

	pt.x -= 5;
	pt.y -= 5;

	for (int i = 0; i < 10; i++) {

		for (int k = 0; k < 10; k++) {

			if ((int) pt.x % 2 == 0 && (int) pt.y % 2 == 0) {

				//cnt++;
				if (cnt == x + 1) {
					//		return;
				}
				//Cource* c1;
				//c1 = _courcePool->pop();
				auto c1 = Cource::create();
				//c1->autorelease();
				//c1->retain();
				if (c1 != NULL) {

					//c1->retain();
					//c1->autorelease();
					_cources.pushBack(c1);
					c1->mapPt.set(pt);
					c1->SetIndex(this->getMMeder()->GetCourceNo(pt));
					c1->setPosition(Vec2(pt.x * w * 0.5, pt.y * w * 0.5));
					this->_meiscene->addChild(c1, 2);

				}
			}
			pt.x += 1;
		}
		pt.x -= 10;
		pt.y += 1;

	}

}
void MainScene_Debug::DrawMeiro(int x) {

	_cources.reserve(0);

	int cnt = 0;
	for (int i = 0; i < this->getMMeder()->mMap.size(); i++) {

		Vec2 pt = this->getMMeder()->GetMapPosition(i);

		if ((int) pt.x % 2 == 0 && (int) pt.y % 2 == 0) {

			cnt++;
			if (cnt == x + 1) {
				return;
			}
			//Cource* c1;
			//c1 = _courcePool->pop();
			auto c1 = Cource::create();
			//c1->autorelease();
			//c1->retain();
			if (c1 != NULL) {

				//c1->retain();
				//c1->autorelease();
				_cources.pushBack(c1);
				c1->mapPt.set(pt);
				c1->SetIndex(this->getMMeder()->GetCourceNo(pt));
				c1->setPosition(Vec2(pt.x * w * 0.5, pt.y * w * 0.5));
				this->_meiscene->addChild(c1, 2);
				//c1->release();
				//bom時場合わけ。

				if (i % (int) this->getMMeder()->courceSize.x == 0
						|| i % (int) this->getMMeder()->courceSize.x
								== (int) this->getMMeder()->courceSize.x - 1) {
					c1->setTag(5);
				} else if (i / (int) this->getMMeder()->courceSize.x == 0
						|| i / (int) this->getMMeder()->courceSize.x
								== (int) this->getMMeder()->courceSize.y - 1) {
					c1->setTag(10);
				} else {
					c1->setTag(0);
				}

				if (i % (int) this->getMMeder()->courceSize.x == 0
						&& i / (int) this->getMMeder()->courceSize.x == 0) {
					c1->setTag(3);
				}
				if (i % (int) this->getMMeder()->courceSize.x == 0
						&& i / (int) this->getMMeder()->courceSize.x
								== (int) this->getMMeder()->courceSize.y - 1) {
					c1->setTag(6);
				}
				if (i % (int) this->getMMeder()->courceSize.x
						== (int) this->getMMeder()->courceSize.x - 1
						&& i / (int) this->getMMeder()->courceSize.x
								== (int) this->getMMeder()->courceSize.y - 1) {
					c1->setTag(12);
				}
				if (i % (int) this->getMMeder()->courceSize.x
						== (int) this->getMMeder()->courceSize.x - 1
						&& i / (int) this->getMMeder()->courceSize.x == 0) {
					c1->setTag(9);
				}

			}
		}
	}

}

void MainScene_Debug::DrawMeiro() {

	int ccnt = (this->getMMeder()->courceSize.x + 1) / 2
			* (this->getMMeder()->courceSize.y + 1) / 2;

//this->setCourcePool(CourcePool::create(ccnt));
//_courcePool->retain();

	_cources.reserve(ccnt);

	for (int i = 0; i < this->getMMeder()->mMap.size(); i++) {

		Vec2 pt = this->getMMeder()->GetMapPosition(i);
		if ((int) pt.x % 2 == 0 && (int) pt.y % 2 == 0) {

			if (i % 4 == 0) {
				this->getMMeder()->mMap.push_back(1);
			} else {
				this->getMMeder()->mMap.push_back(3);
			}

			//Cource* c1;
			//c1 = _courcePool->pop();
			auto c1 = Cource::create();
			//c1->autorelease();
			//c1->retain();
			if (c1 != NULL) {
				//c1->retain();
				//c1->autorelease();
				_cources.pushBack(c1);
				c1->SetIndexA(this->getMMeder()->GetCourceNo(pt));
				c1->setPosition(Vec2(pt.x * 30 * scale_, pt.y * 30 * scale_));
				this->_meiscene->addChild(c1, 2);
				//c1->release();
				//bom時場合わけ。

				if (i % (int) this->getMMeder()->courceSize.x == 0
						|| i % (int) this->getMMeder()->courceSize.x
								== (int) this->getMMeder()->courceSize.x - 1) {
					c1->setTag(5);
				} else if (i / (int) this->getMMeder()->courceSize.x == 0
						|| i / (int) this->getMMeder()->courceSize.x
								== (int) this->getMMeder()->courceSize.y - 1) {
					c1->setTag(10);
				} else {
					c1->setTag(0);
				}

				if (i % (int) this->getMMeder()->courceSize.x == 0
						&& i / (int) this->getMMeder()->courceSize.x == 0) {
					c1->setTag(3);
				}
				if (i % (int) this->getMMeder()->courceSize.x == 0
						&& i / (int) this->getMMeder()->courceSize.x
								== (int) this->getMMeder()->courceSize.y - 1) {
					c1->setTag(6);
				}
				if (i % (int) this->getMMeder()->courceSize.x
						== (int) this->getMMeder()->courceSize.x - 1
						&& i / (int) this->getMMeder()->courceSize.x
								== (int) this->getMMeder()->courceSize.y - 1) {
					c1->setTag(12);
				}
				if (i % (int) this->getMMeder()->courceSize.x
						== (int) this->getMMeder()->courceSize.x - 1
						&& i / (int) this->getMMeder()->courceSize.x == 0) {
					c1->setTag(9);
				}

			}
		}
	}

}

void MainScene_Debug::DrawMeiro3() {

	int ccnt = (this->getMMeder()->courceSize.x + 1) / 2
			* (this->getMMeder()->courceSize.y + 1) / 2;

	if (this->getMapImg()) {
		this->getMapImg()->removeFromParent();
	}

	this->setMapImg(DrawNode::create());
	this->_meiscene->addChild(this->_mapImg, 5);
	const char *str0 = "MainScene_Debug::DrawMeiro3";
	log("%s", str0);
//this->getMapImg()
//int w = 32;
	Vec2 pt0;
	Vec2 pt1;
	Vec2 pt2;
	Vec2 pt3;
	Vec2 pt4;
	float scl = scale_;
	for (int i = 0; i < this->getMMeder()->mMap.size(); i++) {

		pt0 = this->getMMeder()->GetMapPosition(i);
		pt1 = pt0 + Vec2(0, 1);
		pt2 = pt0 + Vec2(1, 0);
		pt3 = pt0 + Vec2(0, -1);
		pt4 = pt0 + Vec2(-1, 0);
		if ((int) pt0.x % 2 == 0 && (int) pt0.y % 2 == 0) {

			switch (this->getMMeder()->GetCourceNo(pt0)) {

			case 0: {
				break;
			}
			case 1: {
				this->_mapImg->drawSegment(pt0 * w * scl, pt1 * w * scl,
						10 * scl, Color4F::RED);
				//this->_mapImg->drawSegment(pt0*w*scl,pt2*w*scl,10*scl,Color4F::GREEN);
				//this->_mapImg->drawSegment(pt0*w*scl,pt3*w*scl,10*scl,Color4F::GREEN);
				//this->_mapImg->drawSegment(pt0*w*scl,pt4*w*scl,10*scl,Color4F::GREEN);
				break;
			}
			case 2: {
				//this->_mapImg->drawSegment(pt0*w*scl,pt1*w*scl,10*scl,Color4F::GREEN);
				this->_mapImg->drawSegment(pt0 * w * scl, pt2 * w * scl,
						10 * scl, Color4F::RED);
				//this->_mapImg->drawSegment(pt0*w*scl,pt3*w*scl,10*scl,Color4F::GREEN);
				//this->_mapImg->drawSegment(pt0*w*scl,pt4*w*scl,10*scl,Color4F::GREEN);
				break;
			}
			case 3: {
				this->_mapImg->drawSegment(pt0 * w * scl, pt1 * w * scl,
						10 * scl, Color4F::RED);
				this->_mapImg->drawSegment(pt0 * w * scl, pt2 * w * scl,
						10 * scl, Color4F::RED);
				//this->_mapImg->drawSegment(pt0*w*scl,pt3*w*scl,10*scl,Color4F::GREEN);
				//this->_mapImg->drawSegment(pt0*w*scl,pt4*w*scl,10*scl,Color4F::GREEN);
				break;
			}
			case 4: {
				//this->_mapImg->drawSegment(pt0*w*scl,pt1*w*scl,10*scl,Color4F::GREEN);
				//this->_mapImg->drawSegment(pt0*w*scl,pt2*w*scl,10*scl,Color4F::GREEN);
				this->_mapImg->drawSegment(pt0 * w * scl, pt3 * w * scl,
						10 * scl, Color4F::RED);
				//this->_mapImg->drawSegment(pt0*w*scl,pt4*w*scl,10*scl,Color4F::GREEN);
				break;
			}
			case 5: {
				this->_mapImg->drawSegment(pt0 * w * scl, pt1 * w * scl,
						10 * scl, Color4F::RED);
				//this->_mapImg->drawSegment(pt0*w*scl,pt2*w*scl,10*scl,Color4F::GREEN);
				this->_mapImg->drawSegment(pt0 * w * scl, pt3 * w * scl,
						10 * scl, Color4F::RED);
				//this->_mapImg->drawSegment(pt0*w*scl,pt4*w*scl,10*scl,Color4F::GREEN);
				break;
			}
			case 6: {
				//this->_mapImg->drawSegment(pt0*w*scl,pt1*w*scl,10*scl,Color4F::GREEN);
				this->_mapImg->drawSegment(pt0 * w * scl, pt2 * w * scl,
						10 * scl, Color4F::RED);
				this->_mapImg->drawSegment(pt0 * w * scl, pt3 * w * scl,
						10 * scl, Color4F::RED);
				//this->_mapImg->drawSegment(pt0*w*scl,pt4*w*scl,10*scl,Color4F::GREEN);
				break;
			}
			case 7: {
				this->_mapImg->drawSegment(pt0 * w * scl, pt1 * w * scl,
						10 * scl, Color4F::RED);
				this->_mapImg->drawSegment(pt0 * w * scl, pt2 * w * scl,
						10 * scl, Color4F::RED);
				this->_mapImg->drawSegment(pt0 * w * scl, pt3 * w * scl,
						10 * scl, Color4F::RED);
				//this->_mapImg->drawSegment(pt0*w*scl,pt4*w*scl,10*scl,Color4F::GREEN);
				break;
			}
			case 8: {
				//this->_mapImg->drawSegment(pt0*w*scl,pt1*w*scl,10*scl,Color4F::GREEN);
				//this->_mapImg->drawSegment(pt0*w*scl,pt2*w*scl,10*scl,Color4F::GREEN);
				//this->_mapImg->drawSegment(pt0*w*scl,pt3*w*scl,10*scl,Color4F::GREEN);
				this->_mapImg->drawSegment(pt0 * w * scl, pt4 * w * scl,
						10 * scl, Color4F::RED);
				break;
			}
			case 9: {
				this->_mapImg->drawSegment(pt0 * w * scl, pt1 * w * scl,
						10 * scl, Color4F::RED);
				//this->_mapImg->drawSegment(pt0*w*scl,pt2*w*scl,10*scl,Color4F::GREEN);
				//this->_mapImg->drawSegment(pt0*w*scl,pt3*w*scl,10*scl,Color4F::GREEN);
				this->_mapImg->drawSegment(pt0 * w * scl, pt4 * w * scl,
						10 * scl, Color4F::RED);
				break;
			}
			case 10: {
				//this->_mapImg->drawSegment(pt0*w*scl,pt1*w*scl,10*scl,Color4F::GREEN);
				this->_mapImg->drawSegment(pt0 * w * scl, pt2 * w * scl,
						10 * scl, Color4F::RED);
				//this->_mapImg->drawSegment(pt0*w*scl,pt3*w*scl,10*scl,Color4F::GREEN);
				this->_mapImg->drawSegment(pt0 * w * scl, pt4 * w * scl,
						10 * scl, Color4F::RED);
				break;
			}
			case 11: {
				this->_mapImg->drawSegment(pt0 * w * scl, pt1 * w * scl,
						10 * scl, Color4F::RED);
				this->_mapImg->drawSegment(pt0 * w * scl, pt2 * w * scl,
						10 * scl, Color4F::RED);
				//this->_mapImg->drawSegment(pt0*w*scl,pt3*w*scl,10*scl,Color4F::GREEN);
				this->_mapImg->drawSegment(pt0 * w * scl, pt4 * w * scl,
						10 * scl, Color4F::RED);
				break;
			}
			case 12: {
				//this->_mapImg->drawSegment(pt0*w*scl,pt1*w*scl,10*scl,Color4F::GREEN);
				//this->_mapImg->drawSegment(pt0*w*scl,pt2*w*scl,10*scl,Color4F::GREEN);
				this->_mapImg->drawSegment(pt0 * w * scl, pt3 * w * scl,
						10 * scl, Color4F::RED);
				this->_mapImg->drawSegment(pt0 * w * scl, pt4 * w * scl,
						10 * scl, Color4F::RED);
				break;
			}
			case 13: {
				this->_mapImg->drawSegment(pt0 * w * scl, pt1 * w * scl,
						10 * scl, Color4F::RED);
				//this->_mapImg->drawSegment(pt0*w*scl,pt2*w*scl,10*scl,Color4F::GREEN);
				this->_mapImg->drawSegment(pt0 * w * scl, pt3 * w * scl,
						10 * scl, Color4F::RED);
				this->_mapImg->drawSegment(pt0 * w * scl, pt4 * w * scl,
						10 * scl, Color4F::RED);
				break;
			}
			case 14: {
				//this->_mapImg->drawSegment(pt0*w*scl,pt1*w*scl,10*scl,Color4F::GREEN);
				this->_mapImg->drawSegment(pt0 * w * scl, pt2 * w * scl,
						10 * scl, Color4F::RED);
				this->_mapImg->drawSegment(pt0 * w * scl, pt3 * w * scl,
						10 * scl, Color4F::RED);
				this->_mapImg->drawSegment(pt0 * w * scl, pt4 * w * scl,
						10 * scl, Color4F::RED);
				break;
			}
			case 15: {
				this->_mapImg->drawSegment(pt0 * w * scl, pt1 * w * scl,
						10 * scl, Color4F::RED);
				this->_mapImg->drawSegment(pt0 * w * scl, pt2 * w * scl,
						10 * scl, Color4F::RED);
				this->_mapImg->drawSegment(pt0 * w * scl, pt3 * w * scl,
						10 * scl, Color4F::RED);
				this->_mapImg->drawSegment(pt0 * w * scl, pt4 * w * scl,
						10 * scl, Color4F::RED);
				break;
			}

			}

		}
	}
//	}

}
//迷路画像で迷路を最終的に生成する
void MainScene_Debug::DrawMeiro4() {

	int ccnt = (this->getMMeder()->courceSize.x + 1) / 2
			* (this->getMMeder()->courceSize.y + 1) / 2;

	CC_SAFE_RELEASE_NULL(_mapImg);

	if (this->getMeiroImg()) {
		this->getMeiroImg()->removeFromParent();
		//this->getMeiroImg()->release();
	}
	if (this->getMeiroImg2()) {
		this->getMeiroImg2()->removeFromParent();
		//this->getMeiroImg2()->release();
	}

	auto udf = UserDefault::getInstance();

	int _lvl = UserDefault::getInstance()->getIntegerForKey("LEVEL", 1);

	this->setMeiroImg(
			SpriteBatchNode::create(
					"meiromap_" + StringUtils::toString((int) _lvl) + ".png"));
	this->_meiscene->addChild(_meiroImg, 2);
	this->setMeiroImg2(
			SpriteBatchNode::create(
					"meiromap_" + StringUtils::toString((int) _lvl) + ".png"));
	this->_meiscene->addChild(_meiroImg2, 2);
	auto m = this->getMeiroImg();

	Vec2 pt0;
	Vec2 pt1;
	Vec2 pt2;
	Vec2 pt3;
	Vec2 pt4;
	float scl = scale_;
	for (int i = 0; i < this->getMMeder()->mMap.size(); i++) {

		if (i == 40000) {
			m = this->getMeiroImg2();
		}

		//int w = 32;
		pt0 = this->getMMeder()->GetMapPosition(i);
		pt1 = pt0 + Vec2(0, 1);
		pt2 = pt0 + Vec2(1, 0);
		pt3 = pt0 + Vec2(0, -1);
		pt4 = pt0 + Vec2(-1, 0);
		if ((int) pt0.x % 2 == 0 && (int) pt0.y % 2 == 0) {

			switch (this->getMMeder()->GetCourceNo(pt0)) {

			case 0: {
				break;
			}
			case 1: {

				cocos2d::Sprite *tile = Sprite::createWithTexture(
						m->getTexture());
				tile->setTextureRect(Rect(w * 0 + d, w * 0 + d, w, w));
				tile->setPosition(pt0 * w * scl);
				m->addChild(tile);

				break;
			}
			case 2: {
				cocos2d::Sprite *tile = Sprite::createWithTexture(
						m->getTexture());
				tile->setTextureRect(Rect(w * 1 + 3 * d, w * 0 + d, w, w));
				tile->setPosition(pt0 * w * scl);
				m->addChild(tile);
				break;
			}
			case 3: {
				cocos2d::Sprite *tile = Sprite::createWithTexture(
						m->getTexture());
				tile->setTextureRect(Rect(w * 2 + 5 * d, w * 0 + d, w, w));
				tile->setPosition(pt0 * w * scl);
				m->addChild(tile);
				break;
			}
			case 4: {
				cocos2d::Sprite *tile = Sprite::createWithTexture(
						m->getTexture());
				tile->setTextureRect(Rect(w * 3 + 7 * d, w * 0 + d, w, w));
				tile->setPosition(pt0 * w * scl);
				m->addChild(tile);
				break;
			}
			case 5: {
				cocos2d::Sprite *tile = Sprite::createWithTexture(
						m->getTexture());
				tile->setTextureRect(Rect(w * 4 + 9 * d, w * 0 + d, w, w));
				tile->setPosition(pt0 * w * scl);
				m->addChild(tile);
				break;
			}
			case 6: {
				cocos2d::Sprite *tile = Sprite::createWithTexture(
						m->getTexture());
				tile->setTextureRect(Rect(w * 0 + d, w * 1 + 3 * d, w, w));
				tile->setPosition(pt0 * w * scl);
				m->addChild(tile);
				break;
			}
			case 7: {
				cocos2d::Sprite *tile = Sprite::createWithTexture(
						m->getTexture());
				tile->setTextureRect(Rect(w * 1 + 3 * d, w * 1 + 3 * d, w, w));
				tile->setPosition(pt0 * w * scl);
				m->addChild(tile);
				break;
			}
			case 8: {
				cocos2d::Sprite *tile = Sprite::createWithTexture(
						m->getTexture());
				tile->setTextureRect(Rect(w * 2 + 5 * d, w * 1 + 3 * d, w, w));
				tile->setPosition(pt0 * w * scl);
				m->addChild(tile);
				break;
			}
			case 9: {
				cocos2d::Sprite *tile = Sprite::createWithTexture(
						m->getTexture());
				tile->setTextureRect(Rect(w * 3 + 7 * d, w * 1 + 3 * d, w, w));
				tile->setPosition(pt0 * w * scl);
				m->addChild(tile);
				break;
			}
			case 10: {
				cocos2d::Sprite *tile = Sprite::createWithTexture(
						m->getTexture());
				tile->setTextureRect(Rect(w * 4 + 9 * d, w * 1 + 3 * d, w, w));
				tile->setPosition(pt0 * w * scl);
				m->addChild(tile);
				break;
			}
			case 11: {
				cocos2d::Sprite *tile = Sprite::createWithTexture(
						m->getTexture());
				tile->setTextureRect(Rect(w * 0 + d, w * 2 + 5 * d, w, w));
				tile->setPosition(pt0 * w * scl);
				m->addChild(tile);
				break;
			}
			case 12: {
				cocos2d::Sprite *tile = Sprite::createWithTexture(
						m->getTexture());
				tile->setTextureRect(Rect(w * 1 + 3 * d, w * 2 + 5 * d, w, w));
				tile->setPosition(pt0 * w * scl);
				m->addChild(tile);
				break;
			}
			case 13: {
				cocos2d::Sprite *tile = Sprite::createWithTexture(
						m->getTexture());
				tile->setTextureRect(Rect(w * 2 + 5 * d, w * 2 + 5 * d, w, w));
				tile->setPosition(pt0 * w * scl);
				m->addChild(tile);
				break;
			}
			case 14: {
				cocos2d::Sprite *tile = Sprite::createWithTexture(
						m->getTexture());
				tile->setTextureRect(Rect(w * 3 + 7 * d, w * 2 + 5 * d, w, w));
				tile->setPosition(pt0 * w * scl);
				m->addChild(tile);
				break;
			}
			case 15: {
				cocos2d::Sprite *tile = Sprite::createWithTexture(
						m->getTexture());
				tile->setTextureRect(Rect(w * 4 + 9 * d, w * 2 + 5 * d, w, w));
				tile->setPosition(pt0 * w * scl);
				m->addChild(tile);
				break;
			}
			}

		}
	}

}
//現在の状態でアンサードットを配列する。

void MainScene_Debug::DrawAns() {

	this->DrawAns(0);

}

void MainScene_Debug::DrawAns(int L) {

	/*
	 // オブサーバに通知イベントを登録します
	 IMobileCocos2dxModule::addObserver(this, IMobileCocos2dxModule::DID_CLOSE,
	 "1021505", callfuncO_selector(MainScene_Debug::observerEventActionClose));
	 // 広告を表示します
	 IMobileCocos2dxModule::show("1021505");

	 this->ansFlg = true;
	 */
//ゼロの場合、全て表示。
	for (int i = _dots.size() - 1; i >= 0; i--) {
		_dots.at(i)->removeFromParent();
		_dots.eraseObject(_dots.at(i));
	}

	int LL = 0;

	this->setAnsBase(
			SpriteBatchNode::create("dotr.png",
					this->getMMeder()->mAns.size()));
	//this->addChild(this->getAnsBase(), 5);

	//this->ShowMsg(this->getPlayer()->getPosition(),StringUtils::toString((int)this->getMMeder()->mAns.size()));
	_meiscene->addChild(this->getAnsBase(), 5);
	this->getAnsBase()->setVisible(true);
	for (int i = 1; i < this->getMMeder()->mAns.size(); i++) {
		//this->ShowMsg(this->getPlayer()->getPosition(),StringUtils::toString((int)i));
		//auto dot = SpriteBatchNode::create("dctpoint.png");
		cocos2d::Sprite *dot = Sprite::createWithTexture(
				_ansBase->getTexture());
		//auto dot = Sprite::createWithTexture(bachnode->getTexture());
		dot->setPosition(this->getMMeder()->mAns.at(i).x * w * scale_,
				this->getMMeder()->mAns.at(i).y * w * scale_);
		dot->setTag(1);
		dot->setVisible(true);
		//dot->retain();
		//dot->autorelease();
		this->_dots.pushBack(dot);
		//_meiscene->addChild(dot, 3);
		this->getAnsBase()->addChild(dot);
		//this->getDots().pushBack(dot);

		LL++;

		if (LL >= L && L > 0) {
			return;
		}
	}

}

void MainScene_Debug::MapShow(float tm, float scale) {

	Vec2 mov_ = (this->_player->getPosition()
			- Vec2(winSize.width / 2, winSize.height / 2)) * scale;

	this->_player->getBody()->setDynamic(false);

	auto big_ = ScaleBy::create(0.5, scale);
	auto move_ = MoveBy::create(0.5, mov_);
	auto spawn_ = Spawn::create(big_, move_, NULL);
	auto delay_ = DelayTime::create(tm);
	auto func_ = CallFuncN::create([this](Node* node) {
		this->_player->getBody()->setDynamic(true);
		//this->runAction(Follow::create(_player));

		});
	auto seq_ = Sequence::create(spawn_, delay_, spawn_->reverse(), func_,
	NULL);
	this->_meiscene->runAction(seq_);

}

void MainScene_Debug::MapShow(float tm) {

	float scale1 = (winSize.width - 20)
			/ (this->getMMeder()->courceSize.x * 30 * scale_);
	float scale2 = (winSize.height - 20)
			/ (this->getMMeder()->courceSize.y * 30 * scale_);

	float scale = 1;

	if (scale1 > scale2) {
		scale = scale2;
	} else {
		scale = scale1;
	}

	if (scale > 1) {
		scale = 1;
	}
	Vec2 wincenpt = Vec2(winSize.width / 2, winSize.height / 2);
	Vec2 mcenpt = Vec2::ZERO;
	mcenpt.set((this->getMMeder()->courceSize * 60) * scale_ / 4);

	Vec2 mov_ = (mcenpt - wincenpt) * scale + wincenpt;
	Vec2 mov2_ = this->_player->getPosition() - mov_;
	this->_player->getBody()->setDynamic(false);
	this->_state = GameState::STOP;
	auto big_ = ScaleBy::create(0.5f, scale);
	auto move_ = MoveBy::create(0.5f, mov_);
	auto move2_ = MoveBy::create(0.5f, mov2_);
	auto spawn_ = Spawn::create(big_, move2_, NULL);
	auto delay_ = DelayTime::create(tm);
	auto func_ = CallFuncN::create([this](Node* node) {
		this->_player->getBody()->setDynamic(true);
		//this->runAction(Follow::create(_player));
			this->_state=GameState::PLAY;
		});

	auto seq_ = Sequence::create(spawn_, delay_, spawn_->reverse(), func_,
	NULL);
//auto seq_ = Sequence::create(move2_,delay_, move2_->reverse(), func_,NULL);

	this->_meiscene->runAction(seq_);

}
void MainScene_Debug::observerEventActionClose(Ref* pSender) {
	/*
	 if (!ansFlg) {
	 // 広告が閉じられた後の処理を記述します
	 float scale1 = (winSize.width - 20)
	 / (this->getMMeder()->courceSize.x * 30 * scale_);
	 float scale2 = (winSize.height - 20)
	 / (this->getMMeder()->courceSize.y * 30 * scale_);

	 float scale = 1;

	 if (scale1 > scale2) {
	 scale = scale2;
	 } else {
	 scale = scale1;
	 }

	 if (scale > 1) {
	 scale = 1;
	 }

	 Vec2 wincenpt = Vec2(winSize.width / 2, winSize.height / 2);
	 Vec2 mcenpt = Vec2::ZERO;
	 mcenpt.set((this->getMMeder()->courceSize * 60 * scale_) / 4);

	 Vec2 mov_ = (mcenpt - wincenpt) * scale + wincenpt;
	 Vec2 mov2_ = -this->getPosition() + wincenpt - mov_;
	 this->_player->getBody()->setDynamic(false);

	 auto big_ = ScaleBy::create(0.5f, scale);
	 auto move_ = MoveBy::create(0.5f, mov_);
	 auto move2_ = MoveBy::create(0.5f, mov2_);
	 auto spawn_ = Spawn::create(big_, move2_, NULL);
	 //auto delay_ = DelayTime::create(tm);
	 auto func_ = CallFuncN::create([this](Node* node) {
	 this->_player->getBody()->setDynamic(true);
	 //this->runAction(Follow::create(_player));

	 });
	 auto seq_ = Sequence::create(spawn_, NULL);
	 //auto seq_ = Sequence::create(move2_,delay_, move2_->reverse(), func_,NULL);

	 this->_meiscene->runAction(seq_);

	 } else {

	 //アンサードットを表示

	 for (int i = _dots.size() - 1; i >= 0; i--) {
	 _dots.at(i)->removeFromParent();
	 _dots.eraseObject(_dots.at(i));
	 }

	 int LL = 0;

	 this->setAnsBase(SpriteBatchNode::create("dotg.png"));
	 _meiscene->addChild(this->getAnsBase(), 3);
	 for (int i = 1; i < this->getMMeder()->mAns.size(); i++) {

	 //auto dot = SpriteBatchNode::create("dctpoint.png");
	 cocos2d::Sprite *dot = Sprite::createWithTexture(
	 _ansBase->getTexture());
	 //auto dot = Sprite::createWithTexture(bachnode->getTexture());
	 dot->setPosition(this->getMMeder()->mAns.at(i).x * w * scale_,
	 this->getMMeder()->mAns.at(i).y * w * scale_);
	 dot->setTag(1);
	 dot->setVisible(true);
	 //dot->retain();
	 //dot->autorelease();
	 this->_dots.pushBack(dot);
	 //_meiscene->addChild(dot, 3);
	 this->getAnsBase()->addChild(dot);
	 //this->getDots().pushBack(dot);

	 LL++;

	 if (LL >= L && L > 0) {
	 return;
	 }

	 }

	 }
	 */
}
void MainScene_Debug::MapShow(bool x) {
	const char *str0 = "MainScene_Debug::MapShow";
	log("%s", str0);
	if (mapFlg == x) {
		return;
	}

	mapFlg = x;
	if (x) {

		/*
		 // オブサーバに通知イベントを登録します
		 IMobileCocos2dxModule::addObserver(this,
		 IMobileCocos2dxModule::DID_CLOSE, "1021470",
		 callfuncO_selector(MainScene_Debug::observerEventActionClose));
		 // 広告を表示します
		 IMobileCocos2dxModule::show("1021470");
		 this->ansFlg = false;
		 */
		float scale1 = (winSize.width - 20)
				/ (this->getMMeder()->courceSize.x * 30 * scale_);
		float scale2 = (winSize.height - 20)
				/ (this->getMMeder()->courceSize.y * 30 * scale_);

		float scale = 1;

		if (scale1 > scale2) {
			scale = scale2;
		} else {
			scale = scale1;
		}

		if (scale > 1) {
			scale = 1;
		}

		Vec2 wincenpt = Vec2(winSize.width / 2, winSize.height / 2);
		Vec2 mcenpt = Vec2::ZERO;
		mcenpt.set((this->getMMeder()->courceSize * 60 * scale_) / 4);

		Vec2 mov_ = (mcenpt - wincenpt) * scale + wincenpt;
		Vec2 mov2_ = -this->getPosition() + wincenpt - mov_;
		//this->_player->getBody()->setDynamic(false);

		auto big_ = ScaleBy::create(0.5f, scale);
		auto move_ = MoveBy::create(0.5f, mov_);
		auto move2_ = MoveBy::create(0.5f, mov2_);
		auto spawn_ = Spawn::create(big_, move2_, NULL);
		//auto delay_ = DelayTime::create(tm);
		auto func_ = CallFuncN::create([this](Node* node) {
			//this->_player->getBody()->setDynamic(true);
			//this->runAction(Follow::create(_player));

			});
		auto seq_ = Sequence::create(spawn_, NULL);
		//auto seq_ = Sequence::create(move2_,delay_, move2_->reverse(), func_,NULL);

		this->_meiscene->runAction(seq_);

	} else {

		Vec2 wincenpt = Vec2(winSize.width / 2, winSize.height / 2);
		Vec2 mcenpt = Vec2::ZERO;
		mcenpt.set((this->getMMeder()->courceSize * 60) / 4);

		//Vec2 mov_ = (mcenpt - wincenpt) * scale + wincenpt;
		//Vec2 mov2_ = -this->getPosition()+wincenpt - mov_;
		//this->_player->getBody()->setDynamic(false);

		auto big_ = ScaleTo::create(0.5f, 1.0f);
		auto move_ = MoveTo::create(0.5f, Vec2::ZERO);
		//auto move2_ = MoveBy::create(0.5f, mov2_);
		auto spawn_ = Spawn::create(big_, move_, NULL);
		auto delay_ = DelayTime::create(1);
		auto func_ = CallFuncN::create([this](Node* node) {
			//this->_player->getBody()->setDynamic(true);
			//this->runAction(Follow::create(_player));
				this->updateFlg=true;
			});
		auto seq_ = Sequence::create(spawn_, delay_, func_, NULL);
		//auto seq_ = Sequence::create(move2_,delay_, move2_->reverse(), func_,NULL);

		this->_meiscene->runAction(seq_);

	}

}

void MainScene_Debug::MapInitShow(bool x) {

//広告無しのMapShow
	mapFlg = x;
	if (x) {

		this->ansFlg = false;

		float scale1 = (winSize.width - 20)
				/ (this->getMMeder()->courceSize.x * 30 * scale_);
		float scale2 = (winSize.height - 20)
				/ (this->getMMeder()->courceSize.y * 30 * scale_);

		float scale = 1;

		if (scale1 > scale2) {
			scale = scale2;
		} else {
			scale = scale1;
		}

		if (scale > 1) {
			scale = 1;
		}

		Vec2 wincenpt = Vec2(winSize.width / 2, winSize.height / 2);
		Vec2 mcenpt = Vec2::ZERO;
		mcenpt.set((this->getMMeder()->courceSize * 60 * scale_) / 4);

		Vec2 mov_ = (mcenpt - wincenpt) * scale + wincenpt;
		Vec2 mov2_ = -this->getPosition() + wincenpt - mov_;
		//this->_player->getBody()->setDynamic(false);

		auto big_ = ScaleBy::create(0.5f, scale);
		auto move_ = MoveBy::create(0.5f, mov_);
		auto move2_ = MoveBy::create(0.5f, mov2_);
		auto spawn_ = Spawn::create(big_, move2_, NULL);
		//auto delay_ = DelayTime::create(tm);
		auto func_ = CallFuncN::create([this](Node* node) {
			//	this->_player->getBody()->setDynamic(true);
			//this->runAction(Follow::create(_player));

			});
		auto seq_ = Sequence::create(spawn_, NULL);
		//auto seq_ = Sequence::create(move2_,delay_, move2_->reverse(), func_,NULL);

		this->_meiscene->runAction(seq_);

	} else {

		Vec2 wincenpt = Vec2(winSize.width / 2, winSize.height / 2);
		Vec2 mcenpt = Vec2::ZERO;
		mcenpt.set((this->getMMeder()->courceSize * 60) / 4);

		//Vec2 mov_ = (mcenpt - wincenpt) * scale + wincenpt;
		//Vec2 mov2_ = -this->getPosition()+wincenpt - mov_;
		//this->_player->getBody()->setDynamic(false);

		auto big_ = ScaleTo::create(0.5f, 1.0f);
		auto move_ = MoveTo::create(0.5f, Vec2::ZERO);
		//auto move2_ = MoveBy::create(0.5f, mov2_);
		auto spawn_ = Spawn::create(big_, move_, NULL);
		auto delay_ = DelayTime::create(1);
		auto func_ = CallFuncN::create([this](Node* node) {
			//this->_player->getBody()->setDynamic(true);
			//this->runAction(Follow::create(_player));
				this->updateFlg=true;
			});
		auto seq_ = Sequence::create(spawn_, delay_, func_, NULL);
		//auto seq_ = Sequence::create(move2_,delay_, move2_->reverse(), func_,NULL);

		this->_meiscene->runAction(seq_);

	}
	const char *str0 = "MainScene_Debug::MapInitShow";
	log("%s", str0);
}

void MainScene_Debug::SpeedUp() {

//debug
	this->onStageClear();

	auto audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
	audioEngine->playEffect("status01.mp3");

	this->ShowMsg(_player->getPosition(), "SPEED UP!");
	this->_player->Action1();

}

void MainScene_Debug::Bomb(Vec2 pt) {

	auto audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
	audioEngine->playEffect("bom.mp3");

	for (Cource* x : _cources) {
		if (x->getPosition().distance(pt) < 50) {
			x->SetIndex(x->getTag());
		}
	}

}
void MainScene_Debug::SetGoal() {

//Item* goal_;
//goal_ = this->_itemPool->pop();
//goal_ = this->_itemPool->pop();
//goal_->autorelease();
//goal_->retain();
	auto goal_ = Item::create();

	int x = (this->getMMeder()->courceSize.x - 1) * w;
	int y = (this->getMMeder()->courceSize.y - 1) * w;

	if (goal_ != NULL) {
		//goal_->autorelease();
		//goal_->retain();

		this->_items.pushBack(goal_);
		goal_->setState(Item::ItemState::T11);
		goal_->setPosition_(Vec2(x, y), 3);
		//goal_->setPosition_(this->_cources.at(5), 3);
		goal_->setScale(w / 64.0f);
		goal_->setVisible(true);
		this->_meiscene->addChild(goal_, 1);
		//goal_->release();
		//this->ShowMsg(goal_->getPosition(),"goalmade!");

	}
	x = (this->getMMeder()->courceSize.x - 1) / 2 * w;
	y = (this->getMMeder()->courceSize.y - 1) / 2 * w;
	y += 12;
	x += 10;
	this->setGoalMap(Sprite::create("goal2.png"));
	this->getGoalMap()->setAnchorPoint(Vec2(1, 0));
	this->getGoalMap()->setPosition(x, y);
	this->getGoalMap()->setScale(0.4);
	this->_meiscene->addChild(this->getGoalMap(), 1);

	x = -10;
	y = -15;

	this->setStartMap(Sprite::create("start1.png"));
	this->getStartMap()->setAnchorPoint(Vec2(0, 1));
	this->getStartMap()->setPosition(x, y);
	this->getStartMap()->setScale(0.4);
	this->_meiscene->addChild(this->getStartMap(), 1);
}
void MainScene_Debug::SetItemRnd(int x) {

//this->setItemPool(ItemPool::create(10));
//_itemPool->retain();

//Item* itm_;
	int x_ = (this->getMMeder()->courceSize.x - 1) / 2;
	int y_ = (this->getMMeder()->courceSize.y - 1) / 2;

	for (int i = 0; i < x; i++) {

		//itm_ = this->_itemPool->pop();
		auto itm_ = Item::create();
		//itm_->autorelease();
		//itm_->retain();
		if (itm_ != NULL) {

			int rndx = 2 + arc4random() % static_cast<int>(x_ - 4);
			int rndy = 2 + arc4random() % static_cast<int>(y_ - 4);

			rndx *= 60;
			rndy *= 60;

			//->autorelease();
			//itm_->retain();

			this->_items.pushBack(itm_);
			itm_->setRndState(x);
			itm_->setPosition_(Vec2(rndx, rndy), i % 4 + 1);

			itm_->setScale(32.0f / 64.0f * scale_);
			itm_->setVisible(true);
			this->_meiscene->addChild(itm_, 2);
			//itm_->release();
			//this->ShowMsg(goal_->getPosition(),"goalmade!");

		}

	}

}
// on "init" you need to initialize your instance
bool MainScene_Debug::init() {

	if (!Layer::init()) {
		return false;
	}
//毎回のアップデート
	this->scheduleUpdate();

	this->winSize = Director::getInstance()->getWinSize();

//加速度センサーを有効にする。

	this->gravFlg = UserDefault::getInstance()->getBoolForKey("grvFlg", true);

	if (this->gravFlg) {

		//	this->setAccelerometerEnabled(true);
		//	this->setAccelerometerInterval(0.5f);

	}
//debug
//this->setScale(0.5f);

	this->setnoMove1(ParallaxNode::create());
	this->addChild(_nomove1);
	this->setnoMove2(ParallaxNode::create());
	this->addChild(_nomove2, 6);
	this->setmeiScene(Layer::create());
	this->addChild(_meiscene, 2);
//ボタンを作る

	this->setBtn1(
			MenuItemImage::create("tweet_btn.png", "tweet_p_btn.png",
					[this](Ref* ref) {

						if(this->dctCnt>=1) {
							//this->dctCnt--;
							this->getDctCnt()->setString(
									"x" + StringUtils::toString((int) this->dctCnt));

//debug 迷路情報を保存する
							auto udf = UserDefault::getInstance();
							//this->getMMeder()->WriteDeta(udf->getIntegerForKey("INDEX",0));
							this->getMMeder()->WriteDetaSQLite(udf->getIntegerForKey("INDEX",0));
							if(this->dctCnt==0) {
								this->getBtn2()->setVisible(false);
								this->getDctCnt()->setVisible(false);
							}

						}

					}));

	this->setMenu1(Menu::create(_btn1, NULL));
	_menu1->alignItemsVerticallyWithPadding(25);
	_menu1->setPosition(40, winSize.height - 40);
	_nomove2->addChild(_menu1, 2, Vec2::ZERO, _menu1->getPosition());

	this->setBtn2(
			MenuItemImage::create("directpt.png", "directpt_p.png",
					[this](Ref* ref) {
						this->getMMeder()->MadeAns(Vec2((int)((_player->getPosition().x+5)/w*2),(int)((_player->getPosition().y+5)/w*2)),this->getMMeder()->courceSize - Vec2(2, 2));
						this->DrawAns(0);
						this->MapShow(false);
					}));

	this->setMenu2(Menu::create(_btn2, NULL));
	_menu2->alignItemsVerticallyWithPadding(25);
	_menu2->setPosition(40, 40);
	_nomove2->addChild(_menu2, 2, Vec2::ZERO, _menu2->getPosition());

	this->setBtn3(
			MenuItemImage::create("map.png", "map_p.png", [this](Ref* ref) {

				if(this->mapCnt>=1) {
					//this->mapCnt--;
					this->getMapCnt()->setString(
							"x" + StringUtils::toString((int) this->mapCnt));

					//debug
					this->updateFlg=true;
					this->MapShow(true);
					this->meiroDrawFlg=true;
					this->getMMeder()->MeiroMadeAll();
					this->DrawMeiro3();
					//this->ShowMsg(Vec2(300,300),"迷路作成完了！");
					this->ShowMsg(Vec2(winSize.width/2,winSize.height/2),"迷路作成完了！");

					if(this->mapCnt==0) {
						this->getBtn3()->setVisible(false);
						this->getMapCnt()->setVisible(false);
					}
				}

			}));

	this->setMenu3(Menu::create(_btn3, NULL));
	_menu3->alignItemsVerticallyWithPadding(25);
	_menu3->setPosition(160, 40);
	_nomove2->addChild(_menu3, 2, Vec2::ZERO, _menu3->getPosition());

	this->setBtn4(
			MenuItemImage::create("speedup.png", "speedup_p.png",
					[this](Ref* ref) {
						if(this->spdCnt>=1) {
							//this->spdCnt--;
							this->getSpdCnt()->setString(
									"x" + StringUtils::toString((int) this->spdCnt));

							this->MapShow(true);

							if(this->getMeiroImg2()) {
								this->getMeiroImg2()->setVisible(false);
							}
							if(this->getMeiroImg()) {
								this->getMeiroImg()->setVisible(false);
							}

							for(int i=0;i<100;i++) {
								this->getMMeder()->MeiroMadeStep();
							}
							this->DrawMeiro3();

							if(this->spdCnt==0) {
								this->getBtn4()->setVisible(false);
								this->getSpdCnt()->setVisible(false);
							}
						}

					}));

	this->setMenu4(Menu::create(_btn4, NULL));
	_menu4->alignItemsVerticallyWithPadding(25);
	_menu4->setPosition(280, 40);
	_nomove2->addChild(_menu4, 2, Vec2::ZERO, _menu4->getPosition());

	this->setBtn5(
			MenuItemImage::create("timer.png", "timer_p.png", [this](Ref* ref) {
				if(this->bomCnt>=1) {
					//this->bomCnt--;

					//debug 迷路を初期化する
					this->updateFlg=false;

					this->MapShow(true);

					if(this->getMapImg()) {
						_mapImg->removeFromParent();
					}

					this->getMMeder()->ResetMap();
					this->DrawMeiro3();

					if(this->getMeiroImg2()) {
						this->getMeiroImg2()->setVisible(false);
					}
					if(this->getMeiroImg()) {
						this->getMeiroImg()->setVisible(false);
					}

					if(this->bomCnt==0) {
						this->getBtn5()->setVisible(false);
						this->getBomCnt()->setVisible(false);
					}
				}

			}));

	this->setMenu5(Menu::create(_btn5, NULL));
	_menu5->alignItemsVerticallyWithPadding(25);
	_menu5->setPosition(400, 40);
	_nomove2->addChild(_menu5, 2, Vec2::ZERO, _menu5->getPosition());

	this->setBtn6(
			MenuItemImage::create("backbtn.png", "backbtn_p.png",
					[this](Ref* ref) {

						auto cfnc_=CallFuncN::create([this](Node* n) {
									this->MemoryClear();
									this->setVisible(false);

								});
						auto delay_=DelayTime::create(0.5f);

						auto cfnc2_=CallFuncN::create([this](Node* n) {

									auto scene=SelectScene::createScene();
									Director::getInstance()->purgeCachedData();
									auto transition=TransitionCrossFade::create(0.5,scene);
									Director::getInstance()->replaceScene(transition);

								});
						this->runAction(Sequence::create(cfnc_,delay_,cfnc2_,NULL));
					}));

	this->setMenu6(Menu::create(_btn6, NULL));
	_menu6->alignItemsVerticallyWithPadding(25);
	_menu6->setPosition(winSize.width - 40, winSize.height - 40);
	_nomove2->addChild(_menu6, 2, Vec2::ZERO, _menu6->getPosition());

	this->setBtn7(
			MenuItemImage::create("tweet_btn.png", "tweet_p_btn.png",
					[this](Ref* ref) {

						auto udf = UserDefault::getInstance();
						int ind=udf->getIntegerForKey("INDEX", 0);
						this->MeiroDetaRenzoku(ind);

					}));

	this->setMenu7(Menu::create(_btn7, NULL));
	_menu7->alignItemsVerticallyWithPadding(25);
	_menu7->setPosition(winSize.width / 2, winSize.height - 40);
	_nomove2->addChild(_menu7, 2, Vec2::ZERO, _menu7->getPosition());

	this->setBackGround(Sprite::create("back.png"));
	_backGround->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2.0));
	_nomove1->addChild(_backGround, 1, Vec2::ZERO, _backGround->getPosition());

	this->setTouchListenner(EventListenerTouchOneByOne::create());
	_touchlistener->onTouchBegan = [this](Touch* touch,Event* event) {

		if(!this->gravFlg) {
			this->_point1.set(touch->getLocation());
			return true;
		} else {
			return true;
		}
	};

	this->setTouchListenner(EventListenerTouchOneByOne::create());
	_touchlistener->onTouchBegan = [this](Touch* touch,Event* event) {

		if(!this->gravFlg) {
			this->_point1.set(touch->getLocation());
			return true;
		} else {
			return true;
		}
	};

	_touchlistener->onTouchMoved = [this](Touch* touch,Event* event) {
		//this->setPosition(this->getPosition()+touch->getDelta());
		// this->_point1.set(this->_point2);
			this->_point2.set(touch->getLocation());
		//	this->_tpt2.set(touch->getLocation());

		};
	_touchlistener->onTouchEnded = [this](Touch* touch,Event* event) {

		this->_point1.set(Vec2::ZERO);
		this->_point2.set(Vec2::ZERO);

	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(
			_touchlistener, this);

//接触感知
	/*
	 this->setContactListenner(EventListenerPhysicsContact::create());

	 _contactlistener->onContactBegin = [this](PhysicsContact& contact) {

	 if((contact.getShapeA()->getBody()->getTag()==0
	 && contact.getShapeB()->getBody()->getTag()==3)||
	 (contact.getShapeA()->getBody()->getTag()==3
	 && contact.getShapeB()->getBody()->getTag()==0)
	 ) {

	 if(!goalFlg) {
	 goalFlg=true;
	 //this->onStageClear();
	 }

	 }

	 if((contact.getShapeA()->getBody()->getTag()==0
	 && contact.getShapeB()->getBody()->getTag()==4)||
	 (contact.getShapeA()->getBody()->getTag()==4
	 && contact.getShapeB()->getBody()->getTag()==0)
	 ) {

	 auto audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
	 audioEngine->playEffect("heal02.mp3");

	 this->ShowMsg(_player->getPosition()+Vec2(0,30),"SPEED UP!");
	 this->getSpdCnt()->setVisible(true);
	 this->getBtn4()->setVisible(true);
	 this->spdCnt++;
	 this->getSpdCnt()->setString(
	 "x" + StringUtils::toString((int) this->spdCnt));

	 if(contact.getShapeB()->getBody()->getTag()==0) {
	 contact.getShapeA()->getBody()->getNode()->setVisible(false);
	 contact.getShapeA()->getBody()->setEnable(false);
	 } else {
	 contact.getShapeB()->getBody()->getNode()->setVisible(false);
	 contact.getShapeB()->getBody()->setEnable(false);
	 }

	 }
	 if((contact.getShapeA()->getBody()->getTag()==0
	 && contact.getShapeB()->getBody()->getTag()==5)||
	 (contact.getShapeA()->getBody()->getTag()==5
	 && contact.getShapeB()->getBody()->getTag()==0)
	 ) {

	 auto audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
	 audioEngine->playEffect("heal02.mp3");

	 this->ShowMsg(_player->getPosition()+Vec2(0,30),"MAP!");
	 this->getMapCnt()->setVisible(true);
	 this->getBtn3()->setVisible(true);
	 this->mapCnt++;
	 this->getMapCnt()->setString(
	 "x" + StringUtils::toString((int) this->mapCnt));

	 if(contact.getShapeB()->getBody()->getTag()==0) {
	 contact.getShapeA()->getBody()->getNode()->setVisible(false);
	 contact.getShapeA()->getBody()->setEnable(false);
	 } else {
	 contact.getShapeB()->getBody()->getNode()->setVisible(false);
	 contact.getShapeB()->getBody()->setEnable(false);
	 }

	 }
	 if((contact.getShapeA()->getBody()->getTag()==0
	 && contact.getShapeB()->getBody()->getTag()==6)||
	 (contact.getShapeA()->getBody()->getTag()==6
	 && contact.getShapeB()->getBody()->getTag()==0)
	 ) {

	 auto audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
	 audioEngine->playEffect("heal02.mp3");

	 this->ShowMsg(_player->getPosition()+Vec2(0,30),"DIRECTER!");
	 this->getDctCnt()->setVisible(true);
	 this->getBtn2()->setVisible(true);
	 this->dctCnt++;
	 this->getDctCnt()->setString(
	 "x" + StringUtils::toString((int) this->dctCnt));

	 if(contact.getShapeB()->getBody()->getTag()==0) {
	 contact.getShapeA()->getBody()->getNode()->setVisible(false);
	 contact.getShapeA()->getBody()->setEnable(false);
	 } else {
	 contact.getShapeB()->getBody()->getNode()->setVisible(false);
	 contact.getShapeB()->getBody()->setEnable(false);
	 }

	 }

	 if((contact.getShapeA()->getBody()->getTag()==0
	 && contact.getShapeB()->getBody()->getTag()==7)||
	 (contact.getShapeA()->getBody()->getTag()==7
	 && contact.getShapeB()->getBody()->getTag()==0)
	 ) {

	 auto audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
	 audioEngine->playEffect("heal02.mp3");

	 this->ShowMsg(_player->getPosition()+Vec2(0,30),"BOMB!");
	 this->getBomCnt()->setVisible(true);
	 this->getBtn5()->setVisible(true);

	 this->bomCnt++;
	 this->getBomCnt()->setString(
	 "x" + StringUtils::toString((int) this->bomCnt));

	 if(contact.getShapeB()->getBody()->getTag()==0) {
	 contact.getShapeA()->getBody()->getNode()->setVisible(false);
	 contact.getShapeA()->getBody()->setEnable(false);
	 } else {
	 contact.getShapeB()->getBody()->getNode()->setVisible(false);
	 contact.getShapeB()->getBody()->setEnable(false);
	 }

	 }
	 if((contact.getShapeA()->getBody()->getTag()==0
	 && contact.getShapeB()->getBody()->getTag()==8)||
	 (contact.getShapeA()->getBody()->getTag()==8
	 && contact.getShapeB()->getBody()->getTag()==0)
	 ) {

	 auto audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
	 audioEngine->playEffect("heal02.mp3");

	 //int ttm=UserDefault::getInstance()->getIntegerForKey("nowLvl", 1);
	 int ttm =10;
	 this->ShowMsg(_player->getPosition()+Vec2(0,30),"TIME! +"+ StringUtils::toString((int) ttm));
	 this->restTime+=ttm;

	 if(contact.getShapeB()->getBody()->getTag()==0) {
	 contact.getShapeA()->getBody()->getNode()->setVisible(false);
	 contact.getShapeA()->getBody()->setEnable(false);
	 } else {
	 contact.getShapeB()->getBody()->getNode()->setVisible(false);
	 contact.getShapeB()->getBody()->setEnable(false);
	 }

	 }

	 return true;
	 };
	 */
//	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(
//			_contactlistener, this);
//ベストスコアーを登録
	this->setBestScore(
			UserDefault::getInstance()->getIntegerForKey("bestScore", 0));

	TTFConfig ttfConfig("Dual-300.ttf", 48, GlyphCollection::DYNAMIC);
	TTFConfig ttfConfig2("Dual-300.ttf", 36, GlyphCollection::DYNAMIC);
	this->setScoreLabel(Label::createWithTTF(ttfConfig, "SCORE 0"));
	this->getScoreLabel()->setColor(Color3B::WHITE);
	_scoreLabel->setAnchorPoint(Vec2::ZERO);
	_scoreLabel->setAlignment(TextHAlignment::LEFT);
	_scoreLabel->enableOutline(Color4B::BLACK, 3);
//_scoreLabel->enableShadow(Color4B::GRAY, Size(2, -2), 8);
	_scoreLabel->setPosition(20, winSize.height - 65);
	_scoreLabel->setScale(0.7f);
//_scoreLabel->enableShadow()

//ttfConfig2.outlineSize = 3;
	this->setBestLabel(Label::createWithTTF(ttfConfig, "BEST 3"));
	this->getBestLabel()->setColor(Color3B::WHITE);
	_bestLabel->setAnchorPoint(Vec2::ZERO);
	_bestLabel->setAlignment(TextHAlignment::LEFT);
	_bestLabel->enableOutline(Color4B::BLACK, 3);
	_bestLabel->setScale(0.7f);
	_bestLabel->setPosition(_scoreLabel->getPosition() + Vec2(0, -50));

	this->setLifeLabel(Label::createWithTTF(ttfConfig, "Life 3"));
//this->getLifeLabel()->setColor(Color3B(255,37,143));
	this->getLifeLabel()->setColor(Color3B::MAGENTA);
	_lifeLabel->setAnchorPoint(Vec2(1, 0));
	_lifeLabel->setAlignment(TextHAlignment::RIGHT);
	_lifeLabel->enableOutline(Color4B::BLACK, 2);
	_lifeLabel->setScale(0.7f);
	_lifeLabel->setPosition(winSize.width - 20, winSize.height - 60);

	auto udf = UserDefault::getInstance();
	//udf->setIntegerForKey("STAGECNT",0);
	//udf->setIntegerForKey("LEVEL",0);

	_scoreLabel->setString(
			"Level:"
					+ StringUtils::toString(
							(int) udf->getIntegerForKey("LEVEL", 0)));
	_bestLabel->setString(
			"Stage:"
					+ StringUtils::toString(
							(int) udf->getIntegerForKey("STAGECNT", 0)));
	_lifeLabel->setString(
			"TopLvl:" + StringUtils::toString((int) this->bestLvl));

	_scoreLabel->setVisible(false);
	_bestLabel->setVisible(false);
	_lifeLabel->setVisible(false);

	_nomove2->addChild(_bestLabel, 1, Vec2::ZERO, _bestLabel->getPosition());
	_nomove2->addChild(_scoreLabel, 1, Vec2::ZERO, _scoreLabel->getPosition());
	this->addChild(_lifeLabel, 5);

	const char *str0 = "MainScene_Debug::init()_0";
	log("%s", str0);
//this->addChild(_scoreLabel, 5);
//_nomove->setScale(4);

//メッセージラベル

	TTFConfig ttfConfig3("Dual-300.ttf", 32, GlyphCollection::DYNAMIC);
//ttfConfig2.outlineSize = 1;

	this->setMsgLabel(Label::createWithTTF(ttfConfig3, "CMB!"));
	this->getMsgLabel()->setColor(Color3B::WHITE);
//_msgLabel->setAnchorPoint(Vec2(0.5f,0.5f));
//_msgLabel->setAnchorPoint(Vec2::ZERO);
	_msgLabel->setAlignment(TextHAlignment::LEFT);
	_msgLabel->enableOutline(Color4B::BLACK, 2);
	_msgLabel->setVisible(false);
	//this->addChild(_msgLabel, 5);
	_nomove2->addChild(_msgLabel, 5, Vec2::ZERO, _msgLabel->getPosition());
//this->_actturn = 0;

//アイテムカウントラベル
	TTFConfig ttfConfig4("Dual-300.ttf", 24, GlyphCollection::DYNAMIC);
	this->setDctCnt(Label::createWithTTF(ttfConfig4, "x0"));
	this->getDctCnt()->setColor(Color3B::WHITE);
	_dctCnt->setAlignment(TextHAlignment::LEFT);
	_dctCnt->enableOutline(Color4B::BLACK, 2);
	_dctCnt->setVisible(false);
	//_dctCnt->setScale(0.3f);
	_dctCnt->setPosition(Vec2(90, 10));
	this->getBtn2()->addChild(_dctCnt, 1);
	this->getBtn2()->setVisible(false);

	this->setMapCnt(Label::createWithTTF(ttfConfig4, "x0"));
	this->getMapCnt()->setColor(Color3B::WHITE);
	_mapCnt->setAlignment(TextHAlignment::LEFT);
	_mapCnt->enableOutline(Color4B::BLACK, 2);
	_mapCnt->setVisible(false);
	_mapCnt->setPosition(Vec2(90, 10));
	//_mapCnt->setScale(0.3f);
	this->getBtn3()->addChild(_mapCnt, 1);
	this->getBtn3()->setVisible(false);

	this->setSpdCnt(Label::createWithTTF(ttfConfig4, "x0"));
	this->getSpdCnt()->setColor(Color3B::WHITE);
	_spdCnt->setAlignment(TextHAlignment::LEFT);
	_spdCnt->enableOutline(Color4B::BLACK, 2);
	_spdCnt->setVisible(false);
	//_spdCnt->setScale(0.3f);
	_spdCnt->setPosition(Vec2(90, 10));
	this->getBtn4()->addChild(_spdCnt, 1);
	this->getBtn4()->setVisible(false);

	this->setBomCnt(Label::createWithTTF(ttfConfig4, "x0"));
	this->getBomCnt()->setColor(Color3B::WHITE);
	_bomCnt->setAlignment(TextHAlignment::LEFT);
	_bomCnt->enableOutline(Color4B::BLACK, 2);
	_bomCnt->setVisible(false);
	//_bomCnt->setScale(0.3f);
	_bomCnt->setPosition(Vec2(90, 10));
	this->getBtn5()->addChild(_bomCnt, 1);
	this->getBtn5()->setVisible(false);

//imobile add
	IMobileCocos2dxModule::setVisibility(
			UserDefault::getInstance()->getIntegerForKey("adViewId"), false);

	const char *str1 = "MainScene_Debug::init()_1";
	log("%s", str1);

	/*
	 this->setItemPool(ItemPool::create(10));
	 _itemPool->retain();
	 this->setCourcePool(CourcePool::create(MEIRO_GAZO_SIZE));
	 _courcePool->retain();
	 */
//プレイヤーをセットする。
	this->setPlayer(Ball::create());
//_player->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	_player->setPosition(Vec2(30 * scale_, 30 * scale_));
	//_player->getBody()->setDynamic(false);
	_player->setVisible(false);
	_player->setScale(scale_);
	this->_meiscene->addChild(_player, 6);

	if (!this->gravFlg) {
		this->setDot0(Sprite::create("yazi.png"));
		this->_dot0->setScale(0.6f);
		this->_dot0->setVisible(false);
		this->_meiscene->addChild(_dot0, 5);
	}

//_player->setVisible(true);
//自動スクロール

	if (_player) {
		//auto rct=cocos2d::Rect(100,100);
		//auto follow_ = Follow::create(_player, Rect(-800, -800, 800, 800));
		//_meiscene->runAction(follow_);
		//this->runAction(Follow::create(_player));
	}

//this->updateFlg = true;
	this->onUpDateListener = [this](MainScene_Debug* sender) {

		if(_player!=NULL) {

			Vec2 pt;
			pt.set(_player->getPosition());
			pt*=(float)1/(float)w;
			pt*=2;
			//	ReSetCource(pt);

			/*
			 int i;
			 int k;
			 Vec2 pt;
			 pt.set(_player->getPosition());
			 pt*=1/w;
			 pt*=2;
			 int x_=pt.x;
			 int y_=pt.y;
			 Vec2 pt_;
			 pt_.set(x_,y_);
			 pt_.x-=3;
			 pt_.y-=3;

			 for ( i=0;i<6;i++) {

			 for ( k=0;k<6;k++) {
			 if ((int) pt_.x % 2 == 0 && (int) pt_.y % 2 == 0) {

			 if(this->FindCource(pt_)==NULL) {

			 Cource* C=this->GetOuterCource(pt);
			 if(C!=NULL) {
			 //			C->mapPt.set(pt_);
			 //C->SetIndex(this->getMMeder()->GetCourceNo(C->mapPt));
			 //			C->setPosition(Vec2(pt_.x *w*0.5, pt_.y * w*0.5));
			 //		C->setPosition(this->_player->getPosition());
			 //			C->setVisible(true);
			 //	if(C->getBody()!=NULL) {
			 //		C->getBody()->setEnable(true);
			 //	}
			 }
			 }

			 }
			 pt_.x+=1;
			 }
			 pt_.y++;
			 pt_.x-=6;
			 }
			 */

		}
		if(!this->gravFlg) {

			Vec2 dpt=this->_point2-this->_point1;
			//dpt.normalize();
			//	this->_player->AccellMove(dpt);
			dpt.normalize();
			this->_dot0->setPosition(this->_player->getPosition()+dpt*23);
			this->_dot0->setRotation(-dpt.getAngle()/M_PI*180-90);
		}

	};

	this->onsecUpDateListener = [this](MainScene_Debug* sender) {
		/*
		 for (Cource* x : this->_cources) {

		 if (_player->getPosition().getDistance(x->getPosition()) > 200) {
		 x->SetBody_(false);
		 } else if(_player->getPosition().getDistance(x->getPosition()) < 100) {
		 x->SetBody_(true);
		 }

		 }
		 */
		/*
		 if(!this->gravFlg) {

		 Vec2 dpt=this->_point2-this->_point1;
		 dpt.normalize();
		 this->_player->AccellMove(dpt*20);
		 this->_dot0->setPosition(this->_player->getPosition()+dpt*23);
		 this->_dot0->setRotation(-dpt.getAngle()/M_PI*180-90);
		 }
		 */
	};

//パーてくる

//this->setBallOut(ParticleSystemPool::create("foodclash.plist",1));
	/*
	 this->setPtcl1(ParticleSystemPool::create("playereffect.plist", 5));
	 this->getPtcl1()->retain();
	 this->setPtcl2(ParticleSystemPool::create("playereffect.plist", 5));
	 this->getPtcl2()->retain();
	 */

	const char *str2 = "MainScene_Debug::init()_2";
	log("%s", str2);

//Vector初期化
	this->setMMeder(MeiroMeder::create());
	return true;
}
void MainScene_Debug::ReSetCource(Vec2 pt) {

	bool chgFlg = false;
	Vec2 pt_;
	Vec2 DPT;
	if (this->_cources.size() > 0) {
		pt_.set(this->_cources.at(0)->mapPt);
	} else {
		return;
	}
	pt_.x += 4;
	pt_.y += 4;

	if (pt_.x - pt.x > 3) {
		DPT.x -= 2;
		chgFlg = true;
	}
	if (pt_.x - pt.x < -3) {
		DPT.x += 2;
		chgFlg = true;
	}
	if (pt_.y - pt.y > 3) {
		DPT.y -= 2;
		chgFlg = true;
	}
	if (pt_.y - pt.y < -3) {
		DPT.y += 2;
		chgFlg = true;
	}

	if (chgFlg) {
		for (Cource* x : this->_cources) {

			x->mapPt += DPT;

			x->SetIndex(this->getMMeder()->GetCourceNo(x->mapPt));
			x->setPosition(x->mapPt * w * 0.5);

		}
	}
}
Cource* MainScene_Debug::FindCource(Vec2 pt) {

	for (Cource* x : this->_cources) {

		if (x->mapPt == pt) {
			return x;
		}

	}
	return NULL;
}

Cource* MainScene_Debug::GetOuterCource(Vec2 pt) {

	Vec2 pt_;
	pt_.set(pt);
	Cource* c_;
	for (Cource* x : this->_cources) {

		if (c_ == NULL) {
			c_ = x;
		}
		if (x != NULL) {
			if (x->mapPt.distance(pt) > c_->mapPt.distance(pt)) {
				c_ = x;
			}
		}
	}

	return c_;

}
void MainScene_Debug::secupdate() {

	_sec++;

	if (_sec == 20) {

		_sec = 0;

		if (onsecUpDateListener && updateFlg) {
			onsecUpDateListener(this);
		}

	}

}

void MainScene_Debug::update(float dt) {
	if (this->getPlayer() != NULL) {

		//if (_state == GameState::PLAY) {
		//	this->restTime -= dt;
		//	if (this->restTime < 0) {
		//_state = GameState::GAMEOVER;
		//		this->onGameOver();
		//		return;
		//	}
		//}

		if (goalFlg == true) {
			//goalFlg=true;
			this->onStageClear();
		}
		//	const char *str0 = "MainScene_Debug::update";
		//	log("%s", str0);
		//	_scoreLabel->setString(
		//			"Time:" + StringUtils::toString((int) this->restTime));
		//_bestLabel->setString(
		//		"Level:" + StringUtils::toString((int) this->nowLvl));
		//_lifeLabel->setString(
		//		"TopLvl:" + StringUtils::toString((int) this->bestLvl));
		/*
		 _scoreLabel->setString(
		 "ths:" + StringUtils::toString((int) this->getPosition().x)
		 + ","
		 + StringUtils::toString((int) this->getPosition().y));

		 _bestLabel->setString(
		 "ply:" + StringUtils::toString((int) _player->getPosition().x)
		 + ","
		 + StringUtils::toString(
		 (int) _player->getPosition().y));

		 _lifeLabel->setString(
		 "mei:" + StringUtils::toString((int) _meiscene->getPosition().x)
		 + ","
		 + StringUtils::toString(
		 (int) _meiscene->getPosition().y));
		 */
	}

	if (this->onUpDateListener && updateFlg) {

		onUpDateListener(this);
	}

	if (_state == GameState::PLAY) {

		secupdate();
	}

}

void MainScene_Debug::StageLvlShow() {

	auto udf = UserDefault::getInstance();

	int lvl_ = udf->getIntegerForKey("LEVEL", 1);
	int index_ = udf->getIntegerForKey("INDEX", 0);
	int stage_ = index_ % 100;

	if (stage_ == 0) {
		stage_ = 100;
	}
	this->getLifeLabel()->setScale(1.0f);
	this->getLifeLabel()->setVisible(false);
	this->getLifeLabel()->setPosition(0, 0);//this->winSize.width / 2, this->winSize.height / 2);

	this->getLifeLabel()->setString(
			"Level:" + StringUtils::toString((int) lvl_) + " Stage:"
					+ StringUtils::toString((int) stage_));

	Vec2 pos2(100, -200);

	auto kakudai_ = ScaleBy::create(0.5, 3);
	auto kieru_ = FadeTo::create(3, 0);
	auto move_ = MoveTo::create(0.5, pos2);
	auto visivl_ = CallFuncN::create([](Node * node) {
		node->setVisible(true);
	});
	this->getLifeLabel()->runAction(
			Sequence::create(visivl_, kakudai_,
					Spawn::create(kakudai_->reverse(), move_, NULL), NULL));
	//_msgLabel->runAction(Spawn::create(kieru, move_, NULL));

}

void MainScene_Debug::ShowMsg(cocos2d::Vec2 pt, std::string msg) {

	_msgLabel->setString(msg);
	_msgLabel->setVisible(true);
	_msgLabel->setOpacity(255);
	_msgLabel->setColor(Color3B(0, 237, 192));
	_msgLabel->enableShadow();
	auto pos2 = Vec2(pt.x, pt.y);
	_msgLabel->setPosition(pt);
	auto kakudai = ScaleBy::create(0.5, 3);
	auto kieru = FadeTo::create(3, 0);
	auto move_ = MoveTo::create(0.5, pos2);
	auto visinull = CallFuncN::create([](Node * node) {
		node->setVisible(false);
	});

	_msgLabel->runAction(Spawn::create(kieru, move_, NULL));

}
cocos2d::Vec2 MainScene_Debug::madeRndPos() {

	float xpos = arc4random() % static_cast<int>(winSize.width);
	float ypos = arc4random() % static_cast<int>(winSize.height);
	return Vec2(xpos, ypos);

}

bool MainScene_Debug::inWinSize(Vec2 pos) {

	if (pos.x > 0 && pos.x < winSize.width && pos.y > 0
			&& pos.y < winSize.height) {
		return true;
	}
	return false;

}

cocos2d::Vec2 MainScene_Debug::madeRndPosOuter() {

	float xpos = arc4random() % static_cast<int>(winSize.width + 100);
	float ypos = arc4random() % static_cast<int>(winSize.height + 100);
	int men = arc4random() % 4;

	switch (men) {
	case 0:
		return Vec2(xpos - 50, winSize.height + 50);
		break;
	case 1:
		return Vec2(winSize.width + 50, ypos - 50);
		break;
	case 2:
		return Vec2(xpos - 50, -50);
		break;

	case 3:
		return Vec2(-50, ypos - 50);
		break;

	default:
		return Vec2(winSize.width + 50, -50);
		break;
	}

	return Vec2::ZERO;

}

void MainScene_Debug::onReady() {

	const char *str0 = "MainScene_Debug::onReady()";
	log("%s", str0);

	_state = GameState::READY;

//ラベルを表示
	_scoreLabel->setVisible(true);
	_bestLabel->setVisible(true);
	//_lifeLabel->setVisible(true);

	auto center = Vec2(winSize.width / 2, winSize.height / 2 + 70);
	this->setReady(Sprite::create("ready1.png"));

	_ready->setPosition(center);
	_ready->setScale(0);

	this->setStart(Sprite::create("start_2.png"));
	_start->runAction(
			Sequence::create(RotateBy::create(0.3, Vec3(0, 90, 0)),
					DelayTime::create(0.5),
					CCSpawn::create(
							EaseIn::create(ScaleTo::create(0.5, 5.0), 0.5),
							FadeOut::create(0.5), NULL),
					CallFunc::create([this] {
						//this->getPlayer()->Action1();
							this->_state = GameState::PLAY;
							this->updateFlg = true;
							if(this->_dot0!=NULL) {
								this->_dot0->setVisible(true);
							}
							this->getPlayer()->setVisible(true);
							//this->getPlayer()->getBody()->setDynamic(true);
							//this->getPlayer()->getBody()->setRotationEnable(false);
							//this->getPlayer()->getBody()->setAngularVelocity(0);
							auto udf = UserDefault::getInstance();
							/*
							 if (this->gravFlg && udf->getIntegerForKey("nowLvl",0)<11) {
							 this->getMMeder()->MeiroMadeAll();
							 udf->setIntegerForKey("MEIROINDEX",
							 udf->getIntegerForKey("MEIROINDEX", 0) + 1);
							 this->getMMeder()->WriteDeta(udf->getIntegerForKey("MEIROINDEX", 0));
							 udf->setIntegerForKey("STAGECNT",udf->getIntegerForKey("STAGECNT",0)+1);
							 if(udf->getIntegerForKey("STAGECNT",0)==100) {
							 udf->setIntegerForKey("STAGECNT",0);
							 udf->setIntegerForKey("nowLvl",udf->getIntegerForKey("nowLvl",0)+1);
							 udf->setIntegerForKey("LEVEL",udf->getIntegerForKey("LEVEL",0)+1);
							 }
							 auto scene = MainScene_Debug::createScene();
							 auto transition = TransitionCrossFade::create(0.5, scene);
							 Director::getInstance()->replaceScene(transition);
							 }
							 */
							this->MapShow(false);
						}), RemoveSelf::create(),
					NULL));

	_ready->runAction(
			Sequence::create(ScaleTo::create(0.25, 1), DelayTime::create(1.0),
					RotateBy::create(0.3, Vec3(0, 90, 0)),
					Sequence::create(
							CallFunc::create([this] {
								//this->StageLvlShow();
									this->_start->setRotation3D(Vec3(0, 270, 0));
									this->_nomove2->addChild(_start,5,Vec2::ZERO,_start->getPosition());
									//this->MapShow(false);
								}), RemoveSelf::create(),
							NULL)));

	_start->setPosition(center);
	this->_nomove2->addChild(_ready, 5, Vec2::ZERO, _ready->getPosition());

}

void MainScene_Debug::onPlay() {
	_state = GameState::PLAY;

}

void MainScene_Debug::onStageClear() {

	this->onUpDateListener = NULL;
	this->updateFlg = false;

	if (_state != GameState::PLAY) {
		return;
	}
	auto audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
	audioEngine->playEffect("gameclear.mp3");
	_state = GameState::GAMECLEAR;
//
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	this->getGoalMap()->setVisible(false);
	auto delay = DelayTime::create(0.1);
	auto stop = CallFunc::create([this] {

		this->getPlayer()->getBody()->setDynamic(false);
		int x = (this->getMMeder()->courceSize.x - 1) / 2 * 60;
		int y = (this->getMMeder()->courceSize.y - 1) / 2 * 60;
		Vec2 gpt = Vec2(x - 30, y - 30);
		auto move_ = MoveTo::create(0.2, gpt*scale_);
		this->getPlayer()->runAction(move_);

	});

	auto Seq = Sequence::create(delay, stop, NULL);
	this->runAction(Seq);

	auto udf = UserDefault::getInstance();
	udf->setIntegerForKey("restTime", 0);
	//udf->setIntegerForKey("nowLvl", this->nowLvl + 1);
	udf->setIntegerForKey("dctCnt", this->dctCnt);
	udf->setIntegerForKey("mapCnt", this->mapCnt);
	udf->setIntegerForKey("spdCnt", this->spdCnt);
	udf->setIntegerForKey("bomCnt", this->bomCnt);

	this->setTryAgainI(
			MenuItemImage::create("menu_btn.png", "menu_btn_p.png",
					[this,udf](Ref* ref) {
						Director::getInstance()->purgeCachedData();
						this->MemoryClear();
						auto scene=SelectScene::createScene();
						auto transition=TransitionCrossFade::create(0.5,scene);
						Director::getInstance()->replaceScene(transition);

					}));

	auto fadeout = EaseSineIn::create(FadeOut::create(0.5));
	auto rep = RepeatForever::create(
			Sequence::create(fadeout, fadeout->reverse(), nullptr));

	this->_tryAgainI->runAction(rep);

	this->setTryAgainM(Menu::create(_tryAgainI, NULL));

	this->_tryAgainM->alignItemsVerticallyWithPadding(40);
	_tryAgainM->setPosition(Vec2(winSize.width / 2, winSize.height / 2 - 100));
	_tryAgainM->setVisible(false);
	this->_nomove2->addChild(_tryAgainM, 5, Vec2::ZERO,
			_tryAgainM->getPosition());

	this->setGoal(Sprite::create("goal_2.png"));

	this->getGoal()->setPosition(
			Vec2(winSize.width / 2.0, winSize.height / 2 + 80));

	this->getGoal()->setScale(0);
	auto act1 = ScaleTo::create(0.5, 2);
	auto act2 = ScaleTo::create(0.5, 1);
	auto act3 = Sequence::create(act1, act2, DelayTime::create(0.3),
			CallFunc::create([this] {
				this->_tryAgainM->setVisible(true);
			}), NULL);
	this->getGoal()->runAction(act3);

	this->_nomove2->addChild(this->getGoal(), 5, Vec2::ZERO,
			this->getGoal()->getPosition());

	IMobileCocos2dxModule::setVisibility(
			UserDefault::getInstance()->getIntegerForKey("adViewId"), true);

}

void MainScene_Debug::onGameOver() {

//this->MemoryClear();
	auto udf = UserDefault::getInstance();
	udf->setBoolForKey("retryFlg", true);

	this->onUpDateListener = NULL;
	this->updateFlg = false;
	if (_state != GameState::PLAY) {
		return;
	}
	auto audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
	audioEngine->playEffect("playerout.mp3");
	_state = GameState::GAMEOVER;
	this->getPlayer()->getBody()->setDynamic(false);
	auto delay = DelayTime::create(0.5);
	auto stop = CallFunc::create([this] {

		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();

	});

	auto Seq = Sequence::create(delay, stop, NULL);
	this->runAction(Seq);

	this->setTryAgainI(
			MenuItemImage::create("tryagain_g.png", "tryagain_r.png",
					[this](Ref* ref) {
						this->MemoryClear();
						auto scene=MainScene_Debug::createScene();
						Director::getInstance()->purgeCachedData();
						auto transition=TransitionCrossFade::create(0.5,scene);
						Director::getInstance()->replaceScene(transition);

					}));
	auto fadeout = EaseSineIn::create(FadeOut::create(0.5));
	auto rep = RepeatForever::create(
			Sequence::create(fadeout, fadeout->reverse(), nullptr));

	this->_tryAgainI->runAction(rep);

	this->setMenuI(
			MenuItemImage::create("menu_g.png", "menu_r.png", [this](Ref* ref) {
				this->MemoryClear();
				auto scene=TitleScene::createScene();
				Director::getInstance()->purgeCachedData();
				auto transition=TransitionCrossFade::create(0.5,scene);
				Director::getInstance()->replaceScene(transition);

			}));

	this->setMenuM(Menu::create(_tryAgainI, _menuI, NULL));
//menu_e->autorelease();
	_menuM->alignItemsVerticallyWithPadding(40);
	_menuM->setPosition(Vec2(winSize.width / 2, winSize.height / 2 - 100));
	_menuM->setVisible(false);
	this->_nomove2->addChild(_menuM, 5, Vec2::ZERO, _menuM->getPosition());

	this->setTimeUp(Sprite::create("timeup_r.png"));

	this->getTimeUp()->setPosition(
			Vec2(winSize.width / 2.0, winSize.height / 2 + 80));

	this->getTimeUp()->setScale(0);
	auto act1 = ScaleTo::create(0.5, 2);
	auto act2 = ScaleTo::create(0.5, 1);
	auto act3 = Sequence::create(act1, act2, DelayTime::create(0.3),
			CallFunc::create([this] {
				this->_menuM->setVisible(true);
			}), NULL);
	this->getTimeUp()->runAction(act3);

//title->setZOrder(2);
	this->_nomove2->addChild(this->getTimeUp(), 5, Vec2::ZERO,
			this->getTimeUp()->getPosition());
//this->_nomove2->reorderChild(title, 5);
//ハイスコア登録

	if (this->nowLvl >= this->bestLvl && !this->retryFlg) {
		this->setYouBest(Sprite::create("youbest_r.png"));
		this->getYouBest()->setPosition(
				Vec2(winSize.width / 2.0, winSize.height / 2 + 180));
		//btime->setZOrder(2);
		this->_nomove2->addChild(this->getYouBest(), 2, Vec2::ZERO,
				this->getYouBest()->getPosition());
		UserDefault::getInstance()->setIntegerForKey("bestLvl", this->nowLvl);
		//InterfaceJNI::sendRankParkScore((int)_playTime);
	}

	IMobileCocos2dxModule::setVisibility(
			UserDefault::getInstance()->getIntegerForKey("adViewId"), true);

}

void MainScene_Debug::MapSet(int Lvl) {

//this->setMMeder(MeiroMeder::create());

	this->nowLvl = Lvl;
	auto udf = UserDefault::getInstance();

	this->bestLvl = udf->getIntegerForKey("bestLvl", 1);
	this->nowLvl = udf->getIntegerForKey("nowLvl", 1);
	this->dctCnt = udf->getIntegerForKey("dctCnt", 0);
	this->mapCnt = udf->getIntegerForKey("mapCnt", 0);
	this->spdCnt = udf->getIntegerForKey("spdCnt", 0);
	this->bomCnt = udf->getIntegerForKey("bomCnt", 0);
	this->restTime = (float) udf->getIntegerForKey("restTime", 0);
	this->retryFlg = udf->getBoolForKey("retryFlg", false);

//debug用
	this->dctCnt = 1;
	this->mapCnt = 1;
	this->spdCnt = 1;
	this->bomCnt = 1;

	if (this->dctCnt > 0) {
		this->getBtn2()->setVisible(true);
		this->getDctCnt()->setVisible(true);
		this->getDctCnt()->setString(
				"x" + StringUtils::toString((int) this->dctCnt));
	}
	if (this->mapCnt > 0) {
		this->getBtn3()->setVisible(true);
		this->getMapCnt()->setVisible(true);
		this->getMapCnt()->setString(
				"x" + StringUtils::toString((int) this->mapCnt));
	}
	if (this->spdCnt > 0) {
		this->getBtn4()->setVisible(true);
		this->getSpdCnt()->setVisible(true);
		this->getSpdCnt()->setString(
				"x" + StringUtils::toString((int) this->spdCnt));
	}
	if (this->bomCnt > 0) {
		this->getBtn5()->setVisible(true);
		this->getBomCnt()->setVisible(true);
		this->getBomCnt()->setString(
				"x" + StringUtils::toString((int) this->bomCnt));
	}

	int a_ = arc4random() % static_cast<int>(8) + 1;
	int b_ = arc4random() % static_cast<int>(60) + 1;
	int c_ = arc4random() % static_cast<int>(50) + 1;
	int d_ = arc4random() % static_cast<int>(100) + 10;
	int e_ = arc4random() % static_cast<int>(50) + 5;
	int f_ = arc4random() % static_cast<int>(100) + 1;
	int g_ = arc4random() % static_cast<int>(50) + 1;
	int h_ = arc4random() % static_cast<int>(100) + 1;
	int i_ = arc4random() % static_cast<int>(30) + 10;
	int j_ = arc4random() % static_cast<int>(20) + 10;

	switch (Lvl) {
	case 0: {
		int x_ = arc4random() % static_cast<int>(60) + 10;
		int y_ = 5000 / x_;

		if (x_ % 2 == 0) {
			x_--;
		}
		if (y_ % 2 == 0) {
			y_--;
		}

		int m_ = arc4random() % static_cast<int>(30) + 1;
		this->getMMeder()->InitMap(Vec2(x_, y_), m_);
		break;
	}
	case 1: {
		//this->getMMeder()->InitMap(Vec2(21, 21),  a_, b_, c_, d_, e_, f_, g_,
		//		h_, i_, j_);
		this->getMMeder()->InitMap(Vec2(81, 101), a_, b_, c_, d_, e_, f_, g_,
				h_, i_, j_);

		break;
	}
	case 2: {
		this->getMMeder()->InitMap(Vec2(101, 127), a_, b_, c_, d_, e_, f_, g_,
				h_, i_, j_);

		break;
	}
	case 3: {
		this->getMMeder()->InitMap(Vec2(121, 151), a_, b_, c_, d_, e_, f_, g_,
				h_, i_, j_);

		break;
	}
	case 4: {
		this->getMMeder()->InitMap(Vec2(141, 177), a_, b_, c_, d_, e_, f_, g_,
				h_, i_, j_);

		break;
	}
	case 5: {
		this->getMMeder()->InitMap(Vec2(161, 201), a_, b_, c_, d_, e_, f_, g_,
				h_, i_, j_);

		break;
	}
	case 6: {
		this->getMMeder()->InitMap(Vec2(181, 227), a_, b_, c_, d_, e_, f_, g_,
				h_, i_, j_);

		break;
	}
	case 7: {
		this->getMMeder()->InitMap(Vec2(201, 251), a_, b_, c_, d_, e_, f_, g_,
				h_, i_, j_);

		break;
	}
	case 8: {
		this->getMMeder()->InitMap(Vec2(221, 277), a_, b_, c_, d_, e_, f_, g_,
				h_, i_, j_);

		break;
	}
	case 9: {
		this->getMMeder()->InitMap(Vec2(231, 289), a_, b_, c_, d_, e_, f_, g_,
				h_, i_, j_);

		break;
	}
	case 10: {
		this->getMMeder()->InitMap(Vec2(251, 315), a_, b_, c_, d_, e_, f_, g_,
				h_, i_, j_);

		break;
	}
	default: {

		int a_ = arc4random() % static_cast<int>(10) + 5;
		int b_ = arc4random() % static_cast<int>(10) + 1;
		int c_ = arc4random() % static_cast<int>(5) + 1;
		int d_ = arc4random() % static_cast<int>(100) + 10;
		this->getMMeder()->InitMap(Vec2(251, 313), a_, b_, c_, d_);
		//this->restTime += 30;
		break;
	}

	}
	/*
	 TMXTiledMap* map = TMXTiledMap::create("meiro1.tmx");
	 //map->setPosition(0,0);
	 this->_meiscene->addChild(map,4);
	 */

	int icnt = (int) (this->getMMeder()->courceSize.x
			* this->getMMeder()->courceSize.y / 350) + 2;
//if (icnt > 4) {
//	icnt = 4;
//}
	//this->ShowMsg(Vec2(0, 0), "迷路作成スタート！");

	this->MapInitShow(true);

	const char *str0 = "MainScene_Debug::MapSet";
	log("%s", str0);

//this->getMMeder()->MeiroMadeAll();
//this->ShowMsg(Vec2(300,300),"迷路作成完了！");
	this->DrawMeiro();
//	this->getMMeder()->MadeAns(Vec2(2, 2),this->getMMeder()->courceSize - Vec2(2, 2));
//this->SetItemRnd(icnt);
	this->SetGoal();
//	this->DrawMeiro(20);
//	this->getMMeder()->MadeAns(Vec2(2, 2),
//			this->getMMeder()->courceSize - Vec2(2, 2));
	this->restTime += (int) ((this->getMMeder()->mAns.size()) / 4) + 15000;
//	this->ShowMsg(Vec2(100, 100), "迷路回答作成完了！");
//this->MapInitShow(true);
	const char *str1 = "MainScene_Debug::MapSet_end";
	log("%s", str1);
}

void MainScene_Debug::MeiroDetaRenzoku(int indx) {
	auto udf = UserDefault::getInstance();

	int index_;
	int lvl_;
	index_ = indx;

	for (int x = indx; x <= 1000; x++) {
		this->setMMeder(MeiroMeder::create());
		lvl_ = (x - 1) / 100 + 1;
		udf->setIntegerForKey("INDEX", x);
		udf->setIntegerForKey("LEVEL", lvl_);
		this->MapSet(lvl_);
		this->getMMeder()->ResetMap();
		//this->MapShow(true);
		this->getMMeder()->MeiroMadeAll();
		//this->DrawMeiro3();
		this->getMMeder()->WriteDeta(udf->getIntegerForKey("INDEX", 0));

	}

}

void MainScene_Debug::onEnterTransitionDidFinish() {
	//this->onReady();
	//return;

	if (UserDefault::getInstance()->getBoolForKey("bgmkey", true)) {
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(
				"bgm.mp3", true);
	}
	/*
	 int msize = 10 + arc4random() % static_cast<int>(90);
	 int md = arc4random() % static_cast<int>(30);

	 if (msize % 2 == 0) {
	 msize++;
	 }
	 */

	auto udf = UserDefault::getInstance();

	int _lvl = UserDefault::getInstance()->getIntegerForKey("LEVEL", 1);
	this->MapSet(_lvl);

//if (!this->gravFlg) {
//迷路情報より書き込む
	const char *str0 = "MainScene_Debug::onEnterTransitionDidFinish()";
	log("%s", str0);
	int index = udf->getIntegerForKey("INDEX", 0);
	//if (this->getMMeder()->MeiroMadeFromFile_debug(index)) {
	if (this->getMMeder()->MeiroMadeFromSQLite(index)) {
		//this->DrawMeiro(20);
		//this->DrawMeiroDumy(1);
		this->DrawMeiro3();
	} else {
		this->DrawMeiro3();
	}

	this->onReady();
//	}
}

