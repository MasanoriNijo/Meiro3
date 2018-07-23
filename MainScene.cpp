#include "MainScene.h"
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
#include "ModalLayer.h"
#include "platform/android/jni/JniHelper.h"

USING_NS_CC;

//USING_NS_CC_EXT;
//�d�̓x�N�g��
//const Vec2 GRAVITY_ACCERATION = Vec2(0, -10);
//const Vec2 NONGRAVITY = Vec2(0, 0);

MainScene::MainScene() :
		_meiroImg2(NULL), _meiroImg(NULL), _ansBase(NULL), _mapImg(NULL), _mMeder(
		NULL), _touchlistener(
		NULL), _contactlistener(
		NULL), _dots(
		NULL), _time(0), _sec(0), pcnt(0), _goalMap(NULL), _startMap(
		NULL), _timeUp(
		NULL), _levelShow(NULL), _goal(
		NULL), _youBest(NULL), _dctCnt(NULL), _mapCnt(NULL), _spdCnt(
		NULL), _bomCnt(NULL), dctCnt(0), mapCnt(0), spdCnt(0), bomCnt(0), bestLvl(0), nowLvl(0), restTime(0), _backGround(
		NULL), _backGround1(
		NULL), _backGround2(
		NULL), _scoreLabel(NULL), _bestLabel(NULL), _lifeLabel(NULL), _msgLabel(
		NULL), _playScore(0), _bestScore(0), _state(GameState::READY), _attackState(AttackState::A), _attackFlg(
				false), _world(NULL), _level(1), updateFlg(false), _courcePool(NULL), _dot0(
		NULL), _nomove1(
		NULL), _nomove2(NULL), _nomove3(NULL), _meiscene(NULL), _player(NULL), _itemPool(
		NULL), _menu1(NULL), _menu2(NULL), _menu3(
		NULL), _menu4(NULL), _menu5(NULL), _menu6(NULL), _menu7(NULL), _btn1(
		NULL), _btn2(
		NULL), _btn3(
		NULL), _btn4(NULL), _btn5(NULL), _btn6(NULL), _btn7(NULL), _cources(
		NULL), _items(
		NULL), _ready(
		NULL), _start(NULL), _tryAgainM(NULL), _menuM(NULL), _tryAgainI(
		NULL), _menuI(NULL), _lvlLavel(NULL), retryFlg(false), _ad(NULL), _setumei(NULL), _goal2(NULL), _touch1(
		NULL), _touch2(NULL), _hintImg(NULL), _hintM(NULL), _backImg(NULL), _backM(NULL), _mapShowImg(NULL), _mapM(
		NULL), _ansImg(NULL), _ansM(NULL), _hintWaku(NULL), _resultWaku(NULL) {
}

MainScene::~MainScene() {
	CC_SAFE_RELEASE_NULL(_meiroImg);
	CC_SAFE_RELEASE_NULL(_meiroImg2);
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
	CC_SAFE_RELEASE_NULL(_nomove3);
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
	CC_SAFE_RELEASE_NULL(_ad);
	CC_SAFE_RELEASE_NULL(_goal2);
	CC_SAFE_RELEASE_NULL(_setumei);
	CC_SAFE_RELEASE_NULL(_touch1);
	CC_SAFE_RELEASE_NULL(_touch2);
	CC_SAFE_RELEASE_NULL(_hintImg);
	CC_SAFE_RELEASE_NULL(_hintM);
	CC_SAFE_RELEASE_NULL(_backImg);
	CC_SAFE_RELEASE_NULL(_backM);
	CC_SAFE_RELEASE_NULL(_mapShowImg);
	CC_SAFE_RELEASE_NULL(_mapM);
	CC_SAFE_RELEASE_NULL(_ansImg);
	CC_SAFE_RELEASE_NULL(_ansM);
	CC_SAFE_RELEASE_NULL(_hintWaku);
	CC_SAFE_RELEASE_NULL(_resultWaku);

	//*使わない時は消す
	for (int i = _cources.size() - 1; i >= 0; i--) {
		_cources.at(i)->removeFromParent();
		_cources.eraseObject(_cources.at(i));
	}
//
	for (int i = _items.size() - 1; i >= 0; i--) {
		_items.at(i)->removeFromParent();
		_items.eraseObject(_items.at(i));
	}

}

Scene* MainScene::createScene() {

	auto scene = Scene::create();

	auto layer = MainScene::create();

	scene->addChild(layer);

	// return the scene
	return scene;

	/*

	 auto scene = Scene::createWithPhysics();

	 //�����G���W��
	 auto world = scene->getPhysicsWorld();

	 //world->setGravity(GRAVITY_ACCERATION);
	 world->setGravity(Vec2::ZERO);
	 //#if COCOS2D_DEBUG >0

	 world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	 //#endif

	 world->setSpeed(6.0);

	 //this->setWorld(world);

	 // 'layer' is an autorelease object
	 auto layer = MainScene::create();

	 // add layer as a child to scene
	 scene->addChild(layer);

	 return scene;

	 */
}

void MainScene::MemoryClear() {

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

void MainScene::WriteDeta(int index) {

	JniMethodInfo t;
	std::string mMapDetaSt;

	mMapDetaSt.append(StringUtils::toString((int) this->getMMeder()->courceSize.x));
	mMapDetaSt.append(",");
	mMapDetaSt.append(StringUtils::toString((int) this->getMMeder()->courceSize.y));
	mMapDetaSt.append("\n");
	for (int i = 0; i < this->getMMeder()->mMap.size(); i++) {
		mMapDetaSt.append(StringUtils::toString((int) this->getMMeder()->mMap.at(i)));
	}
	mMapDetaSt.append("\n");
	for (int i = 0; i < this->getMMeder()->mAns.size(); i++) {
		mMapDetaSt.append(StringUtils::toString((int) this->getMMeder()->mAns.at(i).x));
		mMapDetaSt.append(",");
		mMapDetaSt.append(StringUtils::toString((int) this->getMMeder()->mAns.at(i).y));
	}

	//this->ShowMsg(this->getPlayer()->getPosition(),"BBB");

	// �N���X���ƃ��\�b�h�����w�肵�܂��B
	//if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, WRITEDETA, "(I[I)V")) {
	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, WRITEDETA, "(ILjava/lang/String;)V")) {
		jstring jstr = t.env->NewStringUTF(mMapDetaSt.c_str());
		t.env->CallStaticVoidMethod(t.classID, t.methodID, index, jstr);
		// ���
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(jstr);

	}

}

void MainScene::DrawMeiroDumy(int x) {

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
void MainScene::DrawMeiro3_neo() {

	const char *str0 = "DrawMeiro3_neo()";
	log("%s", str0);

	int ccnt = (this->getMMeder()->courceSize.x + 1) / 2 * (this->getMMeder()->courceSize.y + 1) / 2;

	this->setMapImg(DrawNode::create());
	this->_meiscene->addChild(this->_mapImg, 1);
	this->_mapImg->setOpacity(0);

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
				this->_mapImg->drawSegment(pt0 * w * scl, pt1 * w * scl, t * scl, Color4F::WHITE);
				//this->_mapImg->drawSegment(pt0*w*scl,pt2*w*scl,10*scl,Color4F::BLACK);
				//this->_mapImg->drawSegment(pt0*w*scl,pt3*w*scl,10*scl,Color4F::BLACK);
				//this->_mapImg->drawSegment(pt0*w*scl,pt4*w*scl,10*scl,Color4F::BLACK);
				break;
			}
			case 2: {
				//this->_mapImg->drawSegment(pt0*w*scl,pt1*w*scl,10*scl,Color4F::BLACK);
				this->_mapImg->drawSegment(pt0 * w * scl, pt2 * w * scl, t * scl, Color4F::WHITE);
				//this->_mapImg->drawSegment(pt0*w*scl,pt3*w*scl,10*scl,Color4F::BLACK);
				//this->_mapImg->drawSegment(pt0*w*scl,pt4*w*scl,10*scl,Color4F::BLACK);
				break;
			}
			case 3: {
				this->_mapImg->drawSegment(pt0 * w * scl, pt1 * w * scl, t * scl, Color4F::WHITE);
				this->_mapImg->drawSegment(pt0 * w * scl, pt2 * w * scl, t * scl, Color4F::WHITE);
				//this->_mapImg->drawSegment(pt0*w*scl,pt3*w*scl,10*scl,Color4F::BLACK);
				//this->_mapImg->drawSegment(pt0*w*scl,pt4*w*scl,10*scl,Color4F::BLACK);
				break;
			}
			case 4: {
				//this->_mapImg->drawSegment(pt0*w*scl,pt1*w*scl,10*scl,Color4F::BLACK);
				//this->_mapImg->drawSegment(pt0*w*scl,pt2*w*scl,10*scl,Color4F::BLACK);
				this->_mapImg->drawSegment(pt0 * w * scl, pt3 * w * scl, t * scl, Color4F::WHITE);
				//this->_mapImg->drawSegment(pt0*w*scl,pt4*w*scl,10*scl,Color4F::BLACK);
				break;
			}
			case 5: {
				this->_mapImg->drawSegment(pt0 * w * scl, pt1 * w * scl, t * scl, Color4F::WHITE);
				//this->_mapImg->drawSegment(pt0*w*scl,pt2*w*scl,10*scl,Color4F::BLACK);
				this->_mapImg->drawSegment(pt0 * w * scl, pt3 * w * scl, t * scl, Color4F::WHITE);
				//this->_mapImg->drawSegment(pt0*w*scl,pt4*w*scl,10*scl,Color4F::BLACK);
				break;
			}
			case 6: {
				//this->_mapImg->drawSegment(pt0*w*scl,pt1*w*scl,10*scl,Color4F::BLACK);
				this->_mapImg->drawSegment(pt0 * w * scl, pt2 * w * scl, t * scl, Color4F::WHITE);
				this->_mapImg->drawSegment(pt0 * w * scl, pt3 * w * scl, t * scl, Color4F::WHITE);
				//this->_mapImg->drawSegment(pt0*w*scl,pt4*w*scl,10*scl,Color4F::BLACK);
				break;
			}
			case 7: {
				this->_mapImg->drawSegment(pt0 * w * scl, pt1 * w * scl, t * scl, Color4F::WHITE);
				this->_mapImg->drawSegment(pt0 * w * scl, pt2 * w * scl, t * scl, Color4F::WHITE);
				this->_mapImg->drawSegment(pt0 * w * scl, pt3 * w * scl, t * scl, Color4F::WHITE);
				//this->_mapImg->drawSegment(pt0*w*scl,pt4*w*scl,10*scl,Color4F::BLACK);
				break;
			}
			case 8: {
				//this->_mapImg->drawSegment(pt0*w*scl,pt1*w*scl,10*scl,Color4F::BLACK);
				//this->_mapImg->drawSegment(pt0*w*scl,pt2*w*scl,10*scl,Color4F::BLACK);
				//this->_mapImg->drawSegment(pt0*w*scl,pt3*w*scl,10*scl,Color4F::BLACK);
				this->_mapImg->drawSegment(pt0 * w * scl, pt4 * w * scl, t * scl, Color4F::WHITE);
				break;
			}
			case 9: {
				this->_mapImg->drawSegment(pt0 * w * scl, pt1 * w * scl, t * scl, Color4F::WHITE);
				//this->_mapImg->drawSegment(pt0*w*scl,pt2*w*scl,10*scl,Color4F::BLACK);
				//this->_mapImg->drawSegment(pt0*w*scl,pt3*w*scl,10*scl,Color4F::BLACK);
				this->_mapImg->drawSegment(pt0 * w * scl, pt4 * w * scl, t * scl, Color4F::WHITE);
				break;
			}
			case 10: {
				//this->_mapImg->drawSegment(pt0*w*scl,pt1*w*scl,10*scl,Color4F::BLACK);
				this->_mapImg->drawSegment(pt0 * w * scl, pt2 * w * scl, t * scl, Color4F::WHITE);
				//this->_mapImg->drawSegment(pt0*w*scl,pt3*w*scl,10*scl,Color4F::BLACK);
				this->_mapImg->drawSegment(pt0 * w * scl, pt4 * w * scl, t * scl, Color4F::WHITE);
				break;
			}
			case 11: {
				this->_mapImg->drawSegment(pt0 * w * scl, pt1 * w * scl, t * scl, Color4F::WHITE);
				this->_mapImg->drawSegment(pt0 * w * scl, pt2 * w * scl, t * scl, Color4F::WHITE);
				//this->_mapImg->drawSegment(pt0*w*scl,pt3*w*scl,10*scl,Color4F::BLACK);
				this->_mapImg->drawSegment(pt0 * w * scl, pt4 * w * scl, t * scl, Color4F::WHITE);
				break;
			}
			case 12: {
				//this->_mapImg->drawSegment(pt0*w*scl,pt1*w*scl,10*scl,Color4F::BLACK);
				//this->_mapImg->drawSegment(pt0*w*scl,pt2*w*scl,10*scl,Color4F::BLACK);
				this->_mapImg->drawSegment(pt0 * w * scl, pt3 * w * scl, t * scl, Color4F::WHITE);
				this->_mapImg->drawSegment(pt0 * w * scl, pt4 * w * scl, t * scl, Color4F::WHITE);
				break;
			}
			case 13: {
				this->_mapImg->drawSegment(pt0 * w * scl, pt1 * w * scl, t * scl, Color4F::WHITE);
				//this->_mapImg->drawSegment(pt0*w*scl,pt2*w*scl,10*scl,Color4F::BLACK);
				this->_mapImg->drawSegment(pt0 * w * scl, pt3 * w * scl, t * scl, Color4F::WHITE);
				this->_mapImg->drawSegment(pt0 * w * scl, pt4 * w * scl, t * scl, Color4F::WHITE);
				break;
			}
			case 14: {
				//this->_mapImg->drawSegment(pt0*w*scl,pt1*w*scl,10*scl,Color4F::BLACK);
				this->_mapImg->drawSegment(pt0 * w * scl, pt2 * w * scl, t * scl, Color4F::WHITE);
				this->_mapImg->drawSegment(pt0 * w * scl, pt3 * w * scl, t * scl, Color4F::WHITE);
				this->_mapImg->drawSegment(pt0 * w * scl, pt4 * w * scl, t * scl, Color4F::WHITE);
				break;
			}
			case 15: {
				this->_mapImg->drawSegment(pt0 * w * scl, pt1 * w * scl, t * scl, Color4F::WHITE);
				this->_mapImg->drawSegment(pt0 * w * scl, pt2 * w * scl, t * scl, Color4F::WHITE);
				this->_mapImg->drawSegment(pt0 * w * scl, pt3 * w * scl, t * scl, Color4F::WHITE);
				this->_mapImg->drawSegment(pt0 * w * scl, pt4 * w * scl, t * scl, Color4F::WHITE);
				break;
			}

			}

		}
	}

	this->_ad->AdAllOff();
	auto fade2_ = FadeIn::create(1.0f);
	this->_mapImg->runAction(fade2_);
}

void MainScene::DrawMeiro3() {

	int ccnt = (this->getMMeder()->courceSize.x + 1) / 2 * (this->getMMeder()->courceSize.y + 1) / 2;

	if (this->getMapImg()) {
		this->getMapImg()->removeFromParent();
	}

	this->setMapImg(DrawNode::create());
	this->_meiscene->addChild(this->_mapImg, 1);

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

		Color4F Color_;

//		if (!this->getMMeder()->madeStep == 0) {
//			Color_.RED;
//		} else {
//			Color_.BLACK;
//		}
		if (!this->getMMeder()->madeStep == 0) {

			if ((int) pt0.x % 2 == 0 && (int) pt0.y % 2 == 0) {

				switch (this->getMMeder()->GetCourceNo(pt0)) {

				case 0: {
					break;
				}
				case 1: {
					this->_mapImg->drawSegment(pt0 * w * scl, pt1 * w * scl, t * scl, Color4F::WHITE);
					//this->_mapImg->drawSegment(pt0*w*scl,pt2*w*scl,10*scl,Color4F::BLACK);
					//this->_mapImg->drawSegment(pt0*w*scl,pt3*w*scl,10*scl,Color4F::BLACK);
					//this->_mapImg->drawSegment(pt0*w*scl,pt4*w*scl,10*scl,Color4F::BLACK);
					break;
				}
				case 2: {
					//this->_mapImg->drawSegment(pt0*w*scl,pt1*w*scl,10*scl,Color4F::BLACK);
					this->_mapImg->drawSegment(pt0 * w * scl, pt2 * w * scl, t * scl, Color4F::WHITE);
					//this->_mapImg->drawSegment(pt0*w*scl,pt3*w*scl,10*scl,Color4F::BLACK);
					//this->_mapImg->drawSegment(pt0*w*scl,pt4*w*scl,10*scl,Color4F::BLACK);
					break;
				}
				case 3: {
					this->_mapImg->drawSegment(pt0 * w * scl, pt1 * w * scl, t * scl, Color4F::WHITE);
					this->_mapImg->drawSegment(pt0 * w * scl, pt2 * w * scl, t * scl, Color4F::WHITE);
					//this->_mapImg->drawSegment(pt0*w*scl,pt3*w*scl,10*scl,Color4F::BLACK);
					//this->_mapImg->drawSegment(pt0*w*scl,pt4*w*scl,10*scl,Color4F::BLACK);
					break;
				}
				case 4: {
					//this->_mapImg->drawSegment(pt0*w*scl,pt1*w*scl,10*scl,Color4F::BLACK);
					//this->_mapImg->drawSegment(pt0*w*scl,pt2*w*scl,10*scl,Color4F::BLACK);
					this->_mapImg->drawSegment(pt0 * w * scl, pt3 * w * scl, t * scl, Color4F::WHITE);
					//this->_mapImg->drawSegment(pt0*w*scl,pt4*w*scl,10*scl,Color4F::BLACK);
					break;
				}
				case 5: {
					this->_mapImg->drawSegment(pt0 * w * scl, pt1 * w * scl, t * scl, Color4F::WHITE);
					//this->_mapImg->drawSegment(pt0*w*scl,pt2*w*scl,10*scl,Color4F::BLACK);
					this->_mapImg->drawSegment(pt0 * w * scl, pt3 * w * scl, t * scl, Color4F::WHITE);
					//this->_mapImg->drawSegment(pt0*w*scl,pt4*w*scl,10*scl,Color4F::BLACK);
					break;
				}
				case 6: {
					//this->_mapImg->drawSegment(pt0*w*scl,pt1*w*scl,10*scl,Color4F::BLACK);
					this->_mapImg->drawSegment(pt0 * w * scl, pt2 * w * scl, t * scl, Color4F::WHITE);
					this->_mapImg->drawSegment(pt0 * w * scl, pt3 * w * scl, t * scl, Color4F::WHITE);
					//this->_mapImg->drawSegment(pt0*w*scl,pt4*w*scl,10*scl,Color4F::BLACK);
					break;
				}
				case 7: {
					this->_mapImg->drawSegment(pt0 * w * scl, pt1 * w * scl, t * scl, Color4F::WHITE);
					this->_mapImg->drawSegment(pt0 * w * scl, pt2 * w * scl, t * scl, Color4F::WHITE);
					this->_mapImg->drawSegment(pt0 * w * scl, pt3 * w * scl, t * scl, Color4F::WHITE);
					//this->_mapImg->drawSegment(pt0*w*scl,pt4*w*scl,10*scl,Color4F::BLACK);
					break;
				}
				case 8: {
					//this->_mapImg->drawSegment(pt0*w*scl,pt1*w*scl,10*scl,Color4F::BLACK);
					//this->_mapImg->drawSegment(pt0*w*scl,pt2*w*scl,10*scl,Color4F::BLACK);
					//this->_mapImg->drawSegment(pt0*w*scl,pt3*w*scl,10*scl,Color4F::BLACK);
					this->_mapImg->drawSegment(pt0 * w * scl, pt4 * w * scl, t * scl, Color4F::WHITE);
					break;
				}
				case 9: {
					this->_mapImg->drawSegment(pt0 * w * scl, pt1 * w * scl, t * scl, Color4F::WHITE);
					//this->_mapImg->drawSegment(pt0*w*scl,pt2*w*scl,10*scl,Color4F::BLACK);
					//this->_mapImg->drawSegment(pt0*w*scl,pt3*w*scl,10*scl,Color4F::BLACK);
					this->_mapImg->drawSegment(pt0 * w * scl, pt4 * w * scl, t * scl, Color4F::WHITE);
					break;
				}
				case 10: {
					//this->_mapImg->drawSegment(pt0*w*scl,pt1*w*scl,10*scl,Color4F::BLACK);
					this->_mapImg->drawSegment(pt0 * w * scl, pt2 * w * scl, t * scl, Color4F::WHITE);
					//this->_mapImg->drawSegment(pt0*w*scl,pt3*w*scl,10*scl,Color4F::BLACK);
					this->_mapImg->drawSegment(pt0 * w * scl, pt4 * w * scl, t * scl, Color4F::WHITE);
					break;
				}
				case 11: {
					this->_mapImg->drawSegment(pt0 * w * scl, pt1 * w * scl, t * scl, Color4F::WHITE);
					this->_mapImg->drawSegment(pt0 * w * scl, pt2 * w * scl, t * scl, Color4F::WHITE);
					//this->_mapImg->drawSegment(pt0*w*scl,pt3*w*scl,10*scl,Color4F::BLACK);
					this->_mapImg->drawSegment(pt0 * w * scl, pt4 * w * scl, t * scl, Color4F::WHITE);
					break;
				}
				case 12: {
					//this->_mapImg->drawSegment(pt0*w*scl,pt1*w*scl,10*scl,Color4F::BLACK);
					//this->_mapImg->drawSegment(pt0*w*scl,pt2*w*scl,10*scl,Color4F::BLACK);
					this->_mapImg->drawSegment(pt0 * w * scl, pt3 * w * scl, t * scl, Color4F::WHITE);
					this->_mapImg->drawSegment(pt0 * w * scl, pt4 * w * scl, t * scl, Color4F::WHITE);
					break;
				}
				case 13: {
					this->_mapImg->drawSegment(pt0 * w * scl, pt1 * w * scl, t * scl, Color4F::WHITE);
					//this->_mapImg->drawSegment(pt0*w*scl,pt2*w*scl,10*scl,Color4F::BLACK);
					this->_mapImg->drawSegment(pt0 * w * scl, pt3 * w * scl, t * scl, Color4F::WHITE);
					this->_mapImg->drawSegment(pt0 * w * scl, pt4 * w * scl, t * scl, Color4F::WHITE);
					break;
				}
				case 14: {
					//this->_mapImg->drawSegment(pt0*w*scl,pt1*w*scl,10*scl,Color4F::BLACK);
					this->_mapImg->drawSegment(pt0 * w * scl, pt2 * w * scl, t * scl, Color4F::WHITE);
					this->_mapImg->drawSegment(pt0 * w * scl, pt3 * w * scl, t * scl, Color4F::WHITE);
					this->_mapImg->drawSegment(pt0 * w * scl, pt4 * w * scl, t * scl, Color4F::WHITE);
					break;
				}
				case 15: {
					this->_mapImg->drawSegment(pt0 * w * scl, pt1 * w * scl, t * scl, Color4F::WHITE);
					this->_mapImg->drawSegment(pt0 * w * scl, pt2 * w * scl, t * scl, Color4F::WHITE);
					this->_mapImg->drawSegment(pt0 * w * scl, pt3 * w * scl, t * scl, Color4F::WHITE);
					this->_mapImg->drawSegment(pt0 * w * scl, pt4 * w * scl, t * scl, Color4F::WHITE);
					break;
				}

				}
			}

		} else {

			if ((int) pt0.x % 2 == 0 && (int) pt0.y % 2 == 0) {

				switch (this->getMMeder()->GetCourceNo(pt0)) {

				case 0: {
					break;
				}
				case 1: {
					this->_mapImg->drawSegment(pt0 * w * scl, pt1 * w * scl, t * scl, Color4F::RED);
					//this->_mapImg->drawSegment(pt0*w*scl,pt2*w*scl,10*scl,Color4F::RED);
					//this->_mapImg->drawSegment(pt0*w*scl,pt3*w*scl,10*scl,Color4F::RED);
					//this->_mapImg->drawSegment(pt0*w*scl,pt4*w*scl,10*scl,Color4F::RED);
					break;
				}
				case 2: {
					//this->_mapImg->drawSegment(pt0*w*scl,pt1*w*scl,10*scl,Color4F::RED);
					this->_mapImg->drawSegment(pt0 * w * scl, pt2 * w * scl, t * scl, Color4F::RED);
					//this->_mapImg->drawSegment(pt0*w*scl,pt3*w*scl,10*scl,Color4F::RED);
					//this->_mapImg->drawSegment(pt0*w*scl,pt4*w*scl,10*scl,Color4F::RED);
					break;
				}
				case 3: {
					this->_mapImg->drawSegment(pt0 * w * scl, pt1 * w * scl, t * scl, Color4F::RED);
					this->_mapImg->drawSegment(pt0 * w * scl, pt2 * w * scl, t * scl, Color4F::RED);
					//this->_mapImg->drawSegment(pt0*w*scl,pt3*w*scl,10*scl,Color4F::RED);
					//this->_mapImg->drawSegment(pt0*w*scl,pt4*w*scl,10*scl,Color4F::RED);
					break;
				}
				case 4: {
					//this->_mapImg->drawSegment(pt0*w*scl,pt1*w*scl,10*scl,Color4F::RED);
					//this->_mapImg->drawSegment(pt0*w*scl,pt2*w*scl,10*scl,Color4F::RED);
					this->_mapImg->drawSegment(pt0 * w * scl, pt3 * w * scl, t * scl, Color4F::RED);
					//this->_mapImg->drawSegment(pt0*w*scl,pt4*w*scl,10*scl,Color4F::RED);
					break;
				}
				case 5: {
					this->_mapImg->drawSegment(pt0 * w * scl, pt1 * w * scl, t * scl, Color4F::RED);
					//this->_mapImg->drawSegment(pt0*w*scl,pt2*w*scl,10*scl,Color4F::RED);
					this->_mapImg->drawSegment(pt0 * w * scl, pt3 * w * scl, t * scl, Color4F::RED);
					//this->_mapImg->drawSegment(pt0*w*scl,pt4*w*scl,10*scl,Color4F::RED);
					break;
				}
				case 6: {
					//this->_mapImg->drawSegment(pt0*w*scl,pt1*w*scl,10*scl,Color4F::RED);
					this->_mapImg->drawSegment(pt0 * w * scl, pt2 * w * scl, t * scl, Color4F::RED);
					this->_mapImg->drawSegment(pt0 * w * scl, pt3 * w * scl, t * scl, Color4F::RED);
					//this->_mapImg->drawSegment(pt0*w*scl,pt4*w*scl,10*scl,Color4F::RED);
					break;
				}
				case 7: {
					this->_mapImg->drawSegment(pt0 * w * scl, pt1 * w * scl, t * scl, Color4F::RED);
					this->_mapImg->drawSegment(pt0 * w * scl, pt2 * w * scl, t * scl, Color4F::RED);
					this->_mapImg->drawSegment(pt0 * w * scl, pt3 * w * scl, t * scl, Color4F::RED);
					//this->_mapImg->drawSegment(pt0*w*scl,pt4*w*scl,10*scl,Color4F::RED);
					break;
				}
				case 8: {
					//this->_mapImg->drawSegment(pt0*w*scl,pt1*w*scl,10*scl,Color4F::RED);
					//this->_mapImg->drawSegment(pt0*w*scl,pt2*w*scl,10*scl,Color4F::RED);
					//this->_mapImg->drawSegment(pt0*w*scl,pt3*w*scl,10*scl,Color4F::RED);
					this->_mapImg->drawSegment(pt0 * w * scl, pt4 * w * scl, t * scl, Color4F::RED);
					break;
				}
				case 9: {
					this->_mapImg->drawSegment(pt0 * w * scl, pt1 * w * scl, t * scl, Color4F::RED);
					//this->_mapImg->drawSegment(pt0*w*scl,pt2*w*scl,10*scl,Color4F::RED);
					//this->_mapImg->drawSegment(pt0*w*scl,pt3*w*scl,10*scl,Color4F::RED);
					this->_mapImg->drawSegment(pt0 * w * scl, pt4 * w * scl, t * scl, Color4F::RED);
					break;
				}
				case 10: {
					//this->_mapImg->drawSegment(pt0*w*scl,pt1*w*scl,10*scl,Color4F::RED);
					this->_mapImg->drawSegment(pt0 * w * scl, pt2 * w * scl, t * scl, Color4F::RED);
					//this->_mapImg->drawSegment(pt0*w*scl,pt3*w*scl,10*scl,Color4F::RED);
					this->_mapImg->drawSegment(pt0 * w * scl, pt4 * w * scl, t * scl, Color4F::RED);
					break;
				}
				case 11: {
					this->_mapImg->drawSegment(pt0 * w * scl, pt1 * w * scl, t * scl, Color4F::RED);
					this->_mapImg->drawSegment(pt0 * w * scl, pt2 * w * scl, t * scl, Color4F::RED);
					//this->_mapImg->drawSegment(pt0*w*scl,pt3*w*scl,10*scl,Color4F::RED);
					this->_mapImg->drawSegment(pt0 * w * scl, pt4 * w * scl, t * scl, Color4F::RED);
					break;
				}
				case 12: {
					//this->_mapImg->drawSegment(pt0*w*scl,pt1*w*scl,10*scl,Color4F::RED);
					//this->_mapImg->drawSegment(pt0*w*scl,pt2*w*scl,10*scl,Color4F::RED);
					this->_mapImg->drawSegment(pt0 * w * scl, pt3 * w * scl, t * scl, Color4F::RED);
					this->_mapImg->drawSegment(pt0 * w * scl, pt4 * w * scl, t * scl, Color4F::RED);
					break;
				}
				case 13: {
					this->_mapImg->drawSegment(pt0 * w * scl, pt1 * w * scl, t * scl, Color4F::RED);
					//this->_mapImg->drawSegment(pt0*w*scl,pt2*w*scl,10*scl,Color4F::RED);
					this->_mapImg->drawSegment(pt0 * w * scl, pt3 * w * scl, t * scl, Color4F::RED);
					this->_mapImg->drawSegment(pt0 * w * scl, pt4 * w * scl, t * scl, Color4F::RED);
					break;
				}
				case 14: {
					//this->_mapImg->drawSegment(pt0*w*scl,pt1*w*scl,10*scl,Color4F::RED);
					this->_mapImg->drawSegment(pt0 * w * scl, pt2 * w * scl, t * scl, Color4F::RED);
					this->_mapImg->drawSegment(pt0 * w * scl, pt3 * w * scl, t * scl, Color4F::RED);
					this->_mapImg->drawSegment(pt0 * w * scl, pt4 * w * scl, t * scl, Color4F::RED);
					break;
				}
				case 15: {
					this->_mapImg->drawSegment(pt0 * w * scl, pt1 * w * scl, t * scl, Color4F::RED);
					this->_mapImg->drawSegment(pt0 * w * scl, pt2 * w * scl, t * scl, Color4F::RED);
					this->_mapImg->drawSegment(pt0 * w * scl, pt3 * w * scl, t * scl, Color4F::RED);
					this->_mapImg->drawSegment(pt0 * w * scl, pt4 * w * scl, t * scl, Color4F::RED);
					break;
				}

				}

			}
		}
	}
//	}

}
//迷路画像から、迷路を描写
void MainScene::DrawMeiro4() {

	int ccnt = (this->getMMeder()->courceSize.x + 1) / 2 * (this->getMMeder()->courceSize.y + 1) / 2;

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

	this->setMeiroImg(SpriteBatchNode::create("meiromap_" + StringUtils::toString((int) _lvl) + ".png"));
	this->_meiscene->addChild(_meiroImg, 2);
	this->setMeiroImg2(SpriteBatchNode::create("meiromap_" + StringUtils::toString((int) _lvl) + ".png"));
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

				cocos2d::Sprite *tile = Sprite::createWithTexture(m->getTexture());
				tile->setTextureRect(Rect(w * 2 + d, w * 1 + d, w, w));
				tile->setPosition(pt0 * w * scl);
				tile->setRotation(90);
				m->addChild(tile);

				break;
			}
			case 2: {
				cocos2d::Sprite *tile = Sprite::createWithTexture(m->getTexture());
				tile->setTextureRect(Rect(w * 2 + 3 * d, w * 1 + d, w, w));
				tile->setPosition(pt0 * w * scl);
				tile->setRotation(180);
				m->addChild(tile);
				break;
			}
			case 3: {
				cocos2d::Sprite *tile = Sprite::createWithTexture(m->getTexture());
				tile->setTextureRect(Rect(w * 0 + 5 * d, w * 3 + d, w, w));
				tile->setPosition(pt0 * w * scl);
				tile->setRotation(0);
				m->addChild(tile);
				break;
			}
			case 4: {
				cocos2d::Sprite *tile = Sprite::createWithTexture(m->getTexture());
				tile->setTextureRect(Rect(w * 1 + 7 * d, w * 0 + d, w, w));
				tile->setPosition(pt0 * w * scl);
				m->addChild(tile);
				break;
			}
			case 5: {
				cocos2d::Sprite *tile = Sprite::createWithTexture(m->getTexture());
				tile->setTextureRect(Rect(w * 1 + 9 * d, w * 2 + d, w, w));
				tile->setPosition(pt0 * w * scl);
				m->addChild(tile);
				break;
			}
			case 6: {
				cocos2d::Sprite *tile = Sprite::createWithTexture(m->getTexture());
				tile->setTextureRect(Rect(w * 0 + d, w * 3 + 3 * d, w, w));
				tile->setPosition(pt0 * w * scl);
				tile->setRotation(90);
				m->addChild(tile);
				break;
			}
			case 7: {
				cocos2d::Sprite *tile = Sprite::createWithTexture(m->getTexture());
				tile->setTextureRect(Rect(w * 1 + 3 * d, w * 3 + 3 * d, w, w));
				tile->setPosition(pt0 * w * scl);
				tile->setRotation(90);
				m->addChild(tile);
				break;
			}
			case 8: {
				cocos2d::Sprite *tile = Sprite::createWithTexture(m->getTexture());
				tile->setTextureRect(Rect(w * 2 + 5 * d, w * 3 + 3 * d, w, w));
				tile->setPosition(pt0 * w * scl);

				m->addChild(tile);
				break;
			}
			case 9: {
				cocos2d::Sprite *tile = Sprite::createWithTexture(m->getTexture());
				tile->setTextureRect(Rect(w * 0 + 7 * d, w * 3 + 3 * d, w, w));
				tile->setPosition(pt0 * w * scl);
				tile->setRotation(-90);
				m->addChild(tile);
				break;
			}
			case 10: {
				cocos2d::Sprite *tile = Sprite::createWithTexture(m->getTexture());
				tile->setTextureRect(Rect(w * 1 + 9 * d, w * 2 + 3 * d, w, w));
				tile->setPosition(pt0 * w * scl);
				tile->setRotation(90);
				m->addChild(tile);
				break;
			}
			case 11: {
				cocos2d::Sprite *tile = Sprite::createWithTexture(m->getTexture());
				tile->setTextureRect(Rect(w * 1 + d, w * 3 + 5 * d, w, w));
				tile->setPosition(pt0 * w * scl);

				m->addChild(tile);
				break;
			}
			case 12: {
				cocos2d::Sprite *tile = Sprite::createWithTexture(m->getTexture());
				tile->setTextureRect(Rect(w * 0 + 3 * d, w * 3 + 5 * d, w, w));
				tile->setPosition(pt0 * w * scl);

				tile->setRotation(180);
				m->addChild(tile);
				break;
			}
			case 13: {
				cocos2d::Sprite *tile = Sprite::createWithTexture(m->getTexture());
				tile->setTextureRect(Rect(w * 1 + 5 * d, w * 3 + 5 * d, w, w));
				tile->setPosition(pt0 * w * scl);

				tile->setRotation(-90);
				m->addChild(tile);
				break;
			}
			case 14: {
				cocos2d::Sprite *tile = Sprite::createWithTexture(m->getTexture());
				tile->setTextureRect(Rect(w * 1 + 7 * d, w * 3 + 5 * d, w, w));
				tile->setPosition(pt0 * w * scl);
				tile->setRotation(180);
				m->addChild(tile);
				break;
			}
			case 15: {
				cocos2d::Sprite *tile = Sprite::createWithTexture(m->getTexture());
				tile->setTextureRect(Rect(w * 1 + 9 * d, w * 1 + 5 * d, w, w));
				tile->setPosition(pt0 * w * scl);
				m->addChild(tile);
				break;
			}
			}

		}
	}
	const char *str0 = "drawmeiro4";
	log("%s", str0);
}
//現在の状態でアンサードットを配列する。

void MainScene::DrawAns() {

	this->DrawAns(0);

}

void MainScene::DrawAns(int L) {
//Lはアンサーを表示する距離ポイント
	/*
	 if (!this->adFlg) {

	 IMobileCocos2dxModule::addObserver(this,
	 IMobileCocos2dxModule::DID_CLOSE, "1021505",
	 callfuncO_selector(MainScene::observerEventActionClose));

	 IMobileCocos2dxModule::show("1021505");
	 this->adFlg = true;
	 }
	 */
	this->ansFlg = true;
	auto udf = UserDefault::getInstance();
	int index = udf->getIntegerForKey("INDEX", 0);

	if (this->getMMeder()->GetMeiroStatus(index) < 3) {
		this->getMMeder()->SetMeiroStatus(index, 3);
	}

	for (int i = _dots.size() - 1; i >= 0; i--) {
		_dots.at(i)->removeFromParent();
		_dots.eraseObject(_dots.at(i));
	}

	int LL = 0;

	//Lがゼロの場合、全て表示。

	this->setAnsBase(SpriteBatchNode::create("dotr.png", this->getMMeder()->mAns.size()));
	_meiscene->addChild(this->getAnsBase(), 5);
	this->getAnsBase()->setVisible(true);
	for (int i = 1; i < this->getMMeder()->mAns.size(); i++) {

		cocos2d::Sprite *dot = Sprite::createWithTexture(_ansBase->getTexture());

		dot->setPosition(this->getMMeder()->mAns.at(i).x * w * scale_,
				this->getMMeder()->mAns.at(i).y * w * scale_);
		dot->setTag(1);
		dot->setVisible(true);

		this->_dots.pushBack(dot);
		this->getAnsBase()->addChild(dot);

		LL++;

		if (LL >= L && L > 0) {
			return;
		}
	}

}

void MainScene::MapShow(float tm, float scale) {

	Vec2 mov_ = (this->_player->getPosition() - Vec2(winSize.width / 2, winSize.height / 2)) * scale;

//	this->_player->getBody()->setDynamic(false);

	auto big_ = ScaleBy::create(0.5, scale);
	auto move_ = MoveBy::create(0.5, mov_);
	auto spawn_ = Spawn::create(big_, move_, NULL);
	auto delay_ = DelayTime::create(tm);
	auto func_ = CallFuncN::create([this](Node* node) {
//		this->_player->getBody()->setDynamic(true);
			//this->runAction(Follow::create(_player));

		});
	auto seq_ = Sequence::create(spawn_, delay_, spawn_->reverse(), func_,
	NULL);
	this->_meiscene->runAction(seq_);

}

void MainScene::MapShow(float tm) {

	float scale1 = (winSize.width - this->getMMeder()->OffSetPt.x * 2)
			/ (this->getMMeder()->courceSize.x * w * scale_);
	float scale2 = (winSize.height - this->getMMeder()->OffSetPt.y * 2)
			/ (this->getMMeder()->courceSize.y * w * scale_);

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
//	this->_player->getBody()->setDynamic(false);
	this->_state = GameState::STOP;
	auto big_ = ScaleBy::create(0.5f, scale);
	auto move2_ = MoveBy::create(0.5f, mov2_);
	auto spawn_ = Spawn::create(big_, move2_, NULL);
	auto delay_ = DelayTime::create(tm);
	auto func_ = CallFuncN::create([this](Node* node) {
		//	this->_player->getBody()->setDynamic(true);
		//this->runAction(Follow::create(_player));
			this->_state=GameState::PLAY;
		});

	auto seq_ = Sequence::create(spawn_, delay_, spawn_->reverse(), func_,
	NULL);
//auto seq_ = Sequence::create(move2_,delay_, move2_->reverse(), func_,NULL);

	this->_meiscene->runAction(seq_);

}
void MainScene::observerEventActionClose(Ref* pSender) {

	this->adFlg = false;
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

void MainScene::observerEventActionRead(Ref* pSender) {

	this->adReadFlg = true;
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

void MainScene::MapShow(bool x, float tm) {
	//マップ化を指定の秒数でセット。
	mapFlg = x;
	auto udf = UserDefault::getInstance();

	const char *str0 = "MainScene::MapShow";
	log("%s", str0);

	if (x) {
		this->updateFlg = false;
		int index = udf->getIntegerForKey("INDEX", 0);

		if (this->getMMeder()->GetMeiroStatus(index) < 2) {
			this->getMMeder()->SetMeiroStatus(index, 2);
		}

		this->ansFlg = false;

		float scale1 = (winSize.width - this->getMMeder()->OffSetPt.x * 2)
				/ (this->getMMeder()->courceSize.x * w * scale_);
		float scale2 = (winSize.height - this->getMMeder()->OffSetPt.y * 2)
				/ (this->getMMeder()->courceSize.y * w * scale_);

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
		mcenpt.set((this->getMMeder()->MeiroSize) / 2);

		Vec2 mov_ = (mcenpt - wincenpt) * scale + wincenpt;
		Vec2 mov2_ = -this->getPosition() + wincenpt - mov_;
		//	this->_player->getBody()->setDynamic(false);

		auto big_ = ScaleBy::create(tm, scale);
		auto move2_ = MoveBy::create(tm, mov2_);
		auto spawn_ = Spawn::create(big_, move2_, NULL);
		//auto delay_ = DelayTime::create(tm);
		auto func_ = CallFuncN::create([this](Node* node) {

			this->_player->Action2();

		});
		auto seq_ = Sequence::create(spawn_, func_, NULL);

		this->_meiscene->runAction(seq_);

	} else {

		auto big_ = ScaleTo::create(tm, 1.0f);
		auto move_ = MoveTo::create(tm, Vec2::ZERO);
		//auto move2_ = MoveBy::create(0.5f, mov2_);
		auto spawn_ = Spawn::create(big_, move_, NULL);
		auto delay_ = DelayTime::create(tm);
		auto func_ = CallFuncN::create([this](Node* node) {
			if (this->_player != NULL) {
				_player->Action3();
			}
		});
		auto delay2_ = DelayTime::create(tm);
		auto func2_ = CallFuncN::create([this](Node* node) {
			//	this->_player->getBody()->setDynamic(true);
				this->updateFlg=true;
			});
		auto seq_ = Sequence::create(spawn_, delay_, func_, delay2_, func2_,
		NULL);
		//auto seq_ = Sequence::create(move2_,delay_, move2_->reverse(), func_,NULL);

		this->_meiscene->runAction(seq_);
		//this->getPlayer()->Action3();
	}

}

void MainScene::MapShow(bool x) {

	auto udf = UserDefault::getInstance();

	if (x) {
		mapFlg = true;
		mapPtBefore.set(this->_meiscene->getPosition());
		int index = udf->getIntegerForKey("INDEX", 0);

		if (this->getMMeder()->GetMeiroStatus(index) < 2) {
			this->getMMeder()->SetMeiroStatus(index, 2);
		}

		this->ansFlg = false;

		float scale1 = (winSize.width - this->getMMeder()->OffSetPt.x * 2)
				/ (this->getMMeder()->courceSize.x * w * scale_);
		float scale2 = (winSize.height - this->getMMeder()->OffSetPt.y * 2)
				/ (this->getMMeder()->courceSize.y * w * scale_);

		float scale = 1;

		if (scale1 > scale2) {
			scale = scale2;
		} else {
			scale = scale1;
		}

		if (scale > 1) {
			scale = 1;
		}
		mapScale_ = scale;
//		Vec2 wincenpt = Vec2(winSize.width / 2, winSize.height / 2);
//		Vec2 mcenpt = Vec2::ZERO;
//		mcenpt.set((this->getMMeder()->MeiroSize) / 2);
//
//		Vec2 mov_ = (mcenpt - wincenpt) * scale + wincenpt;
//		Vec2 mov2_ = -this->getPosition() + wincenpt - mov_;
//		//	this->_player->getBody()->setDynamic(false);
		Vec2 mov2_;
		mov2_.set(this->ctPt - this->getMMeder()->MeiroCenter * scale);

		auto big_ = ScaleTo::create(0.5f, scale);
		auto move2_ = MoveTo::create(0.5f, mov2_);
		auto spawn_ = Spawn::create(big_, move2_, NULL);
		//auto delay_ = DelayTime::create(tm);
		auto func_ = CallFuncN::create([this,scale](Node* node) {

//			this->_player->Action2();

				auto big_ = ScaleBy::create(0.3, 1/scale);
				auto seq_ = Sequence::create(big_, big_->reverse(), NULL);
				auto rept_ = RepeatForever::create(seq_);

				this->getGoal2()->runAction(rept_);
				this->_player->runAction(rept_->clone());

			});
		auto seq_ = Sequence::create(spawn_, func_, NULL);

		this->_meiscene->runAction(seq_);

	} else {

		auto big_ = ScaleTo::create(0.5f, 1.0f);
		auto move_ = MoveTo::create(0.5f, mapPtBefore);
		//auto move2_ = MoveBy::create(0.5f, mov2_);
		auto spawn_ = Spawn::create(big_, move_, NULL);
		auto delay_ = DelayTime::create(0.5);
		auto func_ = CallFuncN::create([this](Node* node) {
			if (this->_player != NULL) {

				this->getGoal2()->stopAllActions();
				this->getGoal2()->Action1();
				this->_player->stopAllActions();
				_player->setScale(scale_);
				this->mapFlg = false;
			}

		});

		auto delay2_ = DelayTime::create(0.5);
		auto func2_ = CallFuncN::create([this](Node* node) {

		});

		auto seq_ = Sequence::create(spawn_, delay_, func_, NULL);
		//auto seq_ = Sequence::create(move2_,delay_, move2_->reverse(), func_,NULL);

		this->_meiscene->runAction(seq_);
		//this->getPlayer()->Action3();
	}

}

void MainScene::MapInitShow(bool x) {

	//即座に変更する
	auto udf = UserDefault::getInstance();

	if (x) {

		mapFlg = true;
		mapPtBefore.set(this->_meiscene->getPosition());
		int index = udf->getIntegerForKey("INDEX", 0);

		if (this->getMMeder()->GetMeiroStatus(index) < 2) {
			this->getMMeder()->SetMeiroStatus(index, 2);
		}

		this->ansFlg = false;

		float scale1 = (winSize.width - this->getMMeder()->OffSetPt.x * 2)
				/ (this->getMMeder()->courceSize.x * w * scale_);
		float scale2 = (winSize.height - this->getMMeder()->OffSetPt.y * 2)
				/ (this->getMMeder()->courceSize.y * w * scale_);

		float scale = 1;

		if (scale1 > scale2) {
			scale = scale2;
		} else {
			scale = scale1;
		}

		if (scale > 1) {
			scale = 1;
		}
		mapScale_ = scale;

		Vec2 mov2_;
		mov2_.set(this->ctPt - this->getMMeder()->MeiroCenter * scale);

		auto big_ = ScaleBy::create(0.3, 1 / scale);
		auto seq_ = Sequence::create(big_, big_->reverse(), NULL);
		auto rept_ = RepeatForever::create(seq_);
		this->getGoal2()->runAction(rept_);
		this->_player->runAction(rept_->clone());
//		this->_meiscene->setOpacity(0);
		auto fade_ = FadeIn::create(1.0f);
		this->runAction(fade_);
		this->_meiscene->setScale(scale);
		this->_meiscene->setPosition(mov2_);
//		this->_meiscene->runAction(fade_);

	} else {

		if (this->_player != NULL) {

			this->getGoal2()->stopAllActions();
			this->getGoal2()->Action1();
			this->_player->stopAllActions();
			_player->setScale(scale_);
			this->mapFlg = false;
		}

		this->_meiscene->setScale(1);
		this->_meiscene->setPosition(mapPtBefore);

	}

}

void MainScene::SpeedUp() {

}

void MainScene::Bomb(Vec2 pt) {

	auto audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
	audioEngine->playEffect("bom.mp3");

	for (Cource* x : _cources) {
		if (x->getPosition().distance(pt) < 50) {
			x->SetIndex(x->getTag());
		}
	}

}
void MainScene::SetGoal() {

//	this->setGoal2(Item::create());

	int x = (this->getMMeder()->courceSize.x - 2) / 2 * w;
	int y = (this->getMMeder()->courceSize.y - 2) / 2 * w;

	this->GoalPt.set(this->getMMeder()->courceSize - Vec2(2, 2));

//	this->GoalPt.x=this->getMMeder()->courceSize.x - 2;
//	this->GoalPt.x=this->getMMeder()->courceSize.y - 2;
	//結果デバック時
//	x = 1.5f * w;
//	y = 2.5f * w;

//	_goal2->setState(Item::ItemState::T11);
//	_goal2->setPosition(Vec2(x, y));
//	_goal2->setScale(w / 64.0f);
//	_goal2->setVisible(true);
//	this->_meiscene->addChild(_goal2, 1);

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
// on "init" you need to initialize your instance
bool MainScene::init() {

	if (!Layer::init()) {
		return false;
	}

	this->fstFlg = true;
	this->setState(GameState::READY);

	this->winSize = Director::getInstance()->getWinSize();
	this->ctPt.set(winSize.width / 2, winSize.height / 2);

	this->setnoMove1(ParallaxNode::create());
	this->addChild(_nomove1);
	this->setnoMove2(ParallaxNode::create());
	this->addChild(_nomove2, 6);
	this->setnoMove3(Sprite2::create());
	this->addChild(_nomove3, 7);
	this->setmeiScene(Sprite2::create());
	this->getmeiScene()->setAnchorPoint(Vec2(0, 0));
	this->addChild(_meiscene, 1);

	this->setBackGround(Sprite::create("back5.png"));
	_backGround->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2.0));
	_nomove1->addChild(_backGround, 1, Vec2::ZERO, _backGround->getPosition());
	this->setBackGround2(Sprite::create("back4.png"));
	_backGround2->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2.0));
	_nomove2->addChild(_backGround2, 1, Vec2::ZERO, _backGround2->getPosition());

//	LayerColor* background = LayerColor::create(Color4B::WHITE, winSize.width + 100, winSize.height + 100);
//
//	background->setPosition(Vec2(-20, -50));
//	this->addChild(background);
	TTFConfig ttfConfig3("HGRPP1.TTC", 40, GlyphCollection::DYNAMIC);

	auto udf = UserDefault::getInstance();
	this->setBestLabel(
			Label::createWithTTF(ttfConfig3,
					"Level:" + StringUtils::toString((int) udf->getIntegerForKey("LEVEL", 0)) + "\r\nStage:"
							+ StringUtils::toString((int) udf->getIntegerForKey("STAGECNT", 0))));
	TTFConfig ttfConfig2("HGRPP1.TTC", 60, GlyphCollection::DYNAMIC);
	this->setScoreLabel(
			Label::createWithTTF(ttfConfig2,
					"Level:" + StringUtils::toString((int) udf->getIntegerForKey("LEVEL", 0)) + "\r\nStage:"
							+ StringUtils::toString((int) udf->getIntegerForKey("STAGECNT", 0))));

	_scoreLabel->setPosition(winSize.width / 2, winSize.height - 30);
	_scoreLabel->setScale(1.0f);
	_scoreLabel->setColor(Color3B::WHITE);
	_scoreLabel->setAnchorPoint(Vec2(0.5, 1));
	_scoreLabel->setAlignment(TextHAlignment::CENTER);

	_bestLabel->setPosition(winSize.width / 2, winSize.height - 100);
	_bestLabel->setScale(1.0f);
	_bestLabel->setColor(Color3B::WHITE);
	_bestLabel->setAnchorPoint(Vec2(0.5, 1));
	_bestLabel->setAlignment(TextHAlignment::CENTER);

	_scoreLabel->setString("Level:" + StringUtils::toString((int) udf->getIntegerForKey("LEVEL", 0)));
	_bestLabel->setString(
			"クリヤ回数:"
					+ StringUtils::toString(
							(int) this->getMMeder()->GetLevelStatus(
									(int) udf->getIntegerForKey("LEVEL", 0))));

	_scoreLabel->setVisible(false);
	_bestLabel->setVisible(false);

	_nomove2->addChild(_bestLabel, 1, Vec2::ZERO, _bestLabel->getPosition());
	_nomove2->addChild(_scoreLabel, 1, Vec2::ZERO, _scoreLabel->getPosition());

	this->setMsgLabel(Label::createWithTTF(ttfConfig3, "CMB!"));
	this->getMsgLabel()->setColor(Color3B::WHITE);
//_msgLabel->setAnchorPoint(Vec2(0.5f,0.5f));
//_msgLabel->setAnchorPoint(Vec2::ZERO);
	_msgLabel->setAlignment(TextHAlignment::LEFT);
	_msgLabel->setPosition(this->ctPt);
	_msgLabel->setVisible(true);
	//_nomove2->addChild(_msgLabel, 1, Vec2::ZERO, _msgLabel->getPosition());
	this->addChild(_msgLabel, 5);
	_msgLabel->setString("迷路生成中！");

	//操作方法を選択
//	this->gravFlg = UserDefault::getInstance()->getBoolForKey("grvFlg", false);
//	if (this->gravFlg) {
//		this->SetKatamukiListenner();
//	} else {
//		this->SetTouchListenner();
//	}

	this->setDot0(Sprite::create("yazi.png"));
	this->_dot0->setScale(0.6f);
	this->_dot0->setVisible(false);
	this->_meiscene->addChild(_dot0, 5);

	//imovileAD
	this->setAD(ImovileAd::create());
	_ad->SetObserver();
//	_ad->FstSet();

	_ad->AdShow(false, true, true, false, false, true);

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyReleased = CC_CALLBACK_2(MainScene::onKeyReleased, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	return true;
}

void MainScene::SetContactListenner() {
	this->setContactListenner(EventListenerPhysicsContact::create());

	_contactlistener->onContactBegin = [this](PhysicsContact& contact) {

		if((contact.getShapeA()->getBody()->getTag()==0
						&& contact.getShapeB()->getBody()->getTag()==3)||
				(contact.getShapeA()->getBody()->getTag()==3
						&& contact.getShapeB()->getBody()->getTag()==0)
		) {

			if(!goalFlg) {
				goalFlg=true;
			}

		}

		return true;
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_contactlistener,
			this);
}

void MainScene::SetTouchListenner() {

	this->setTouchListenner(EventListenerTouchOneByOne::create());
	_touchlistener->onTouchBegan = [this](Touch* touch, Event *event) {

		//最初のタッチのみ
			if(!this->mapFlg) {
				//	this->ShowMsg(touch->getLocation(),"touch");
				if( !tch_ ) {
					tch_=true;
					this->_point1.set(touch->getLocation());
					this->_point2.set(touch->getLocation());
					this->_dot0->setVisible(true);
					this->getPlayer()->_touchMapImgPt.set(this->getPlayer()->getPosition());
					this->getPlayer()->_point1.set(this->_point1);
					this->getPlayer()->_point2.set(this->_point2);
					this->getPlayer()->tchFlg=true;

					return true;
				} else {
					return false;
				}
			} else {

				deltaPt.set(Vec2::ZERO);
				scalePt.set(Vec2::ZERO);
				if(this->_touch1==NULL) {
					this->setTouch1(touch);
				} else {
					if(this->_touch2==NULL) {
						this->setTouch2(touch);
					}
				}
				meiPt.set(this->_meiscene->getPosition());
				if(this->getTouch1() && this->getTouch2()) {
					this->mapScale_=this->_meiscene->getScale();
//					meiPt.set(this->_meiscene->getPosition());
					multctPt.set((this->getTouch2()->getLocation()+this->getTouch1()->getLocation())/2-meiPt);
					multTouchPt.set(this->getTouch2()->getLocation()-this->getTouch1()->getLocation());
				}
				return true;
			}

		};

	_touchlistener->onTouchMoved = [this](Touch * touch,Event* event) {

		if( !this->mapFlg ) {
			this->_point2.set(touch->getLocation());
			this->getPlayer()->_point2.set(this->_point2);
		} else {
			deltaPt+=touch->getDelta();
			if(this->getTouch1() && this->getTouch2()) {
//				multctPt.set((this->getTouch2()->getLocation()+this->getTouch1()->getLocation())/2);
			this->_meiscene->setScale(mapScale_*(this->getTouch2()->getLocation()-this->getTouch1()->getLocation()).length()/multTouchPt.length());
			scalePt.set((1-(this->getTouch2()->getLocation()-this->getTouch1()->getLocation()).length()/multTouchPt.length())*multctPt);
		}
		this->_meiscene->setPosition(deltaPt+meiPt+scalePt);
	}

};
	_touchlistener->onTouchEnded = [this](Touch * touch,Event* event) {

		if( !this->mapFlg ) {
			tch_=false;
			this->_point1.set(Vec2::ZERO);
			this->_point2.set(Vec2::ZERO);
			this->getPlayer()->_point1.set(this->_point1);
			this->getPlayer()->_point2.set(this->_point2);
			this->getPlayer()->tchFlg=false;
			this->_dot0->setVisible(false);
		} else {
//			if(this->_touch1==touch) {
			this->setTouch1(NULL);
//				mapScale_=this->_meiscene->getScale();
//			}
//			if(this->_touch2==touch) {
			this->setTouch2(NULL);
			mapScale_=this->_meiscene->getScale();

//			}

		}

	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_touchlistener,
			this);
}
void MainScene::SetKatamukiListenner() {

//	if (this->gravFlg) {
	this->setAccelerometerEnabled(true);
	this->setAccelerometerInterval(0.2f);
//	}
}
void MainScene::onAcceleration(Acceleration* acc, Event* unused_event) {

	//_lifeLabel->setString("ACC:" + StringUtils::toString((float) acc->x));
	if (_player) {

		this->_point1.set(0, 0);

		this->_point2.set(acc->x, acc->y);

		if (this->_point2.length() < 0.08f) {
			this->_point2.set(Vec2::ZERO);
		} else {
			this->_point2 *= 300;
		}

//		} else if (this->_point2.length() < 0.15f) {
//			this->_point2 *= 300;
//		} else {
//			this->_point2 *= 600;
//		}

		//_player->AccellMove(Vec2(acc->x, acc->y));
		//_player->AccellMove(acc);
	}

}
void MainScene::adShow(float d) {

	if (!_ad->adClickFlg) {

		adturn++;

		if (adturn % 2 == 0) {

			_ad->AdShow(false, false, false, true, false, false);
		} else {
			_ad->AdShow(false, false, false, false, true, false);
		}
	}
	/*
	 if (!this->adFlg) {
	 this->adFlg = true;
	 // オブサーバに通知イベントを登録します
	 IMobileCocos2dxModule::addObserver(this,
	 IMobileCocos2dxModule::DID_CLOSE, "1021505",
	 callfuncO_selector(MainScene::observerEventActionClose));
	 // 広告を表示します
	 IMobileCocos2dxModule::show("1021505");
	 this->adFlg = true;

	 }
	 */
}

void MainScene::AdShow(bool top_, bool down_, bool mid_, bool txt_, bool inst_, bool top2_) {
//広告の表示操作する。
//広告を表示する
//	IMobileCocos2dxModule::setVisibility(
//			UserDefault::getInstance()->getIntegerForKey("AD_ICON_TOP"), top_);
//	IMobileCocos2dxModule::setVisibility(
//			UserDefault::getInstance()->getIntegerForKey("AD_ICON_DOWN"),
//			down_);
//	IMobileCocos2dxModule::setVisibility(
//			UserDefault::getInstance()->getIntegerForKey("AD_ICON_MID"), mid_);
//
//	IMobileCocos2dxModule::setVisibility(
//			UserDefault::getInstance()->getIntegerForKey("AD_BANNER"), top2_);
//
//	if (txt_) {
//		IMobileCocos2dxModule::show(IMOBILE_TEXTPOPUP_SID);
//	}
//	if (inst_) {
//		IMobileCocos2dxModule::show(IMOBILE_FULLSCREENAD_SID);
//	}

}

void MainScene::adShow() {

	if (adReadFlg) {
		return;
	}

	if (!this->adFlg) {
		this->adFlg = true;
		// オブサーバに通知イベントを登録します
		IMobileCocos2dxModule::addObserver(this, IMobileCocos2dxModule::DID_CLOSE, "1021505",
				callfuncO_selector(MainScene::observerEventActionClose));
		IMobileCocos2dxModule::addObserver(this, IMobileCocos2dxModule::DID_CLICK, "1021505",
				callfuncO_selector(MainScene::observerEventActionRead));

		// 広告を表示します
		IMobileCocos2dxModule::show("1021505");
		this->adFlg = true;

	}
}
void MainScene::ReSetCource(Vec2 pt) {

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
Cource* MainScene::FindCource(Vec2 pt) {

	for (Cource* x : this->_cources) {

		if (x->mapPt == pt) {
			return x;
		}

	}
	return NULL;
}

Cource* MainScene::GetOuterCource(Vec2 pt) {

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
void MainScene::secupdate() {

	_sec++;

	if (_sec == 20) {

		_sec = 0;

		if (onsecUpDateListener && updateFlg) {
			onsecUpDateListener(this);
		}

	}

}

void MainScene::update(float dt) {

	switch (this->getState()) {

	case GameState::MADE: {
		this->onMade(dt);
		break;
	}
	case GameState::READY: {
		this->onReady(dt);
		break;
	}

	case GameState::PLAY: {
		this->onPlay(dt);
		break;
	}
	case GameState::STOP: {
		//	this->onReady(dt);
		break;
	}
	case GameState::GAMECLEAR: {
		this->onStageClear(dt);
		break;
	}

	}

	if (this->onUpDateListener && this->updateFlg) {
		onUpDateListener(this);
	}

}

void MainScene::StageLvlShow() {

	auto udf = UserDefault::getInstance();

	int lvl_ = udf->getIntegerForKey("LEVEL", 1);
	int index_ = udf->getIntegerForKey("INDEX", 0);
	int stage_ = index_ % 100;

	if (stage_ == 0) {
		stage_ = 100;
	}
	this->getLifeLabel()->setScale(1.0f);
	this->getLifeLabel()->setVisible(false);
	this->getLifeLabel()->setPosition(0, 0);		//this->winSize.width / 2, this->winSize.height / 2);

	this->getLifeLabel()->setString(
			"Level:" + StringUtils::toString((int) lvl_) + " Stage:" + StringUtils::toString((int) stage_));

	Vec2 pos2(100, -200);

	auto kakudai_ = ScaleBy::create(0.5, 3);
	auto kieru_ = FadeTo::create(3, 0);
	auto move_ = MoveTo::create(0.5, pos2);
	auto visivl_ = CallFuncN::create([](Node * node) {
		node->setVisible(true);
	});
	this->getLifeLabel()->runAction(
			Sequence::create(visivl_, kakudai_, Spawn::create(kakudai_->reverse(), move_, NULL),
			NULL));
	//_msgLabel->runAction(Spawn::create(kieru, move_, NULL));

}

void MainScene::ShowMsg(cocos2d::Vec2 pt, std::string msg) {

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
cocos2d::Vec2 MainScene::madeRndPos() {

	float xpos = arc4random() % static_cast<int>(winSize.width);
	float ypos = arc4random() % static_cast<int>(winSize.height);
	return Vec2(xpos, ypos);

}

bool MainScene::inWinSize(Vec2 pos) {

	if (pos.x > 0 && pos.x < winSize.width && pos.y > 0 && pos.y < winSize.height) {
		return true;
	}
	return false;

}

cocos2d::Vec2 MainScene::madeRndPosOuter() {

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
void MainScene::onMade(float dt) {

	if (fstFlg) {

		fstFlg = false;

//		this->getMMeder()->MeiroMadeAll();

	} else {
		//何もしない。
		this->getMMeder()->MeiroMadeStep();
		this->getMsgLabel()->setString(
				"迷路作成中!\r\n" + StringUtils::toString((int) this->getMMeder()->madeRate));

		if (this->getMMeder()->_madeFin) {

			auto fade_ = FadeOut::create(0.5f);
			_msgLabel->runAction(fade_);
			//	_msgLabel->setVisible(false);
			this->getMMeder()->MadeFarCource();

			//	保存するとき
			//	this->getMMeder()->WriteDeta3(_lvl);
			//	加古混むとき
			//	this->getMMeder()->ReadDeta3(_lvl);

			this->DrawMeiro3_neo();

			this->GoalPt.set(this->getMMeder()->GoalPt);
			this->StartPt.set(this->getMMeder()->StartPt);
			//ゴールを新たにセット
			this->setGoal2(Item::create());
			//	_goal2->setState(Item::ItemState::T11);
			//	_goal2->setAnchorPoint(Vec2(0.15,0.15));
			//	_goal2->setScale(0.9f);
			this->GoalPt.set(this->getMMeder()->GoalPt);
			_goal2->setPosition(this->getMMeder()->ChgPositionFromMapToImage(this->_mMeder->GoalPt));
			this->_meiscene->addChild(_goal2, 1);
			//プレイヤーをセット
			this->setPlayer(Ball::create());
			_player->w = this->w;
			_player->d = this->d;
			_player->scale_ = this->scale_;
			_player->setVisible(true);
			_player->setScale(scale_);
			_player->setPosition(this->getMMeder()->ChgPositionFromMapToImage(this->_mMeder->StartPt));
			_player->updateFlg = false;
			_player->setMMeder(this->getMMeder());
			_player->setLevel(nowLvl);
			this->_meiscene->addChild(_player, 6);

			this->fstFlg = true;
			this->_state = GameState::READY;
		}
	}

}
void MainScene::onReady(float dt) {

	if (fstFlg) {

		fstFlg = false;

		_scoreLabel->setVisible(true);
		_bestLabel->setVisible(true);

		this->setSetumei(Sprite::create("setumei.png"));
		_setumei->setPosition(Vec2(winSize.width / 2, winSize.height / 2 + 100));
		_setumei->setOpacity(0);

		auto fade_ = FadeIn::create(1);
		auto delay_ = DelayTime::create(1);
		auto funcs_ = CallFuncN::create([this](Node* nd) {
			this->MapShow(false);
			this->fstFlg=true;
			this->_state = GameState::PLAY;
			this->SetTouchListenner();
		});

		auto seq_ = Sequence::create(fade_, delay_, funcs_, fade_->reverse(), RemoveSelf::create(), NULL);
		_setumei->runAction(seq_);

		this->_nomove2->addChild(_setumei, 5, Vec2::ZERO, _setumei->getPosition());

//
//
//
//
//		this->_nomove2->addChild(_ready, 5, Vec2::ZERO, _ready->getPosition());
//
//		this->setStart(Sprite::create("start_2.png"));
//		_start->runAction(
//				Sequence::create(RotateBy::create(0.3, Vec3(0, 90, 0)), DelayTime::create(0.5),
//						CCSpawn::create(EaseIn::create(ScaleTo::create(0.5, 5.0), 0.5), FadeOut::create(0.5),
//						NULL), CallFunc::create([this] {
////							this->MapShow(false);
//							}), DelayTime::create(0.5f), CallFunc::create([this] {
//							//this->getPlayer()->Action1();
//								this->fstFlg=true;
//								this->_state = GameState::PLAY;
//								this->updateFlg = true;
//								this->_nomove2->addChild(_setumei,5,Vec2::ZERO,_setumei->getPosition());
//
//								if(this->_dot0!=NULL) {
//									this->_dot0->setVisible(true);
//								}
//								this->getPlayer()->setVisible(true);
//
//							}), DelayTime::create(0.5f), CallFunc::create([this] {
//
//							/*
//							 this->getPlayer()->getBody()->setDynamic(true);
//							 this->getPlayer()->getBody()->setRotationEnable(false);
//							 this->getPlayer()->getBody()->setAngularVelocity(0);
//							 */
//
//							this->getPlayer()->updateFlg=true;
//						}), RemoveSelf::create(),
//						NULL));
//
//		_start->setPosition(ctPt);
//
//		_ready->runAction(
//				Sequence::create(ScaleTo::create(0.25, 1), DelayTime::create(1.0),
//						RotateBy::create(0.3, Vec3(0, 90, 0)), Sequence::create(CallFunc::create([this] {
//							//this->StageLvlShow();
//								this->_start->setRotation3D(Vec3(0, 270, 0));
//								this->_nomove2->addChild(_start,5,Vec2::ZERO,_start->getPosition());
//								//this->MapShow(false);
//							}), RemoveSelf::create(),
//						NULL)));
//		const char *str0 = "onReady";
//		log("%s", str0);
	} else {
		//何もしない。
	}
}

void MainScene::onPlay(float dt) {

	if (fstFlg) {
		fstFlg = false;
		this->_player->chsFlg = true;		//チェースのはじめのセット
		this->_player->mapPt_.set(this->getMMeder()->StartPt);
		this->_player->mapImgPt_.set(
				this->_player->getMMeder()->ChgPositionFromMapToImage(this->_player->mapPt_));
		this->_player->setPosition(this->_player->mapImgPt_);

		this->getPlayer()->ChaseA(this->getPlayer()->getPosition(), this->getPlayer()->getPosition(), 1, dt);
		this->getPlayer()->JuncPt.set(this->getPlayer()->getPosition());
		this->_player->NomlMove5(dt, Vec2::ZERO);	//チェースのはじめのセット

//		this->addChild(this->getPlayer()->getDctPt(),2);
//		this->addChild(this->getPlayer()->getDctPt2(),2);
		const char *str0 = "onReady_fst";
		log("%s", str0);

	} else {
//		const char *str0 = "onReady_ren";
//		log("%s", str0);
		if (_player) {

			if (this->getAD()->adClickFlg && this->getAD()->adCloseFlg) {
				this->getAD()->adClickFlg = false;
				this->getAD()->adCloseFlg = false;
				this->SetMapAnswer();
				if (this->_hintM) {
					this->_hintM->removeFromParent();
				}
			}

//			if (_player->chsFlg && tch_ ) {
//				Vec2 ppt_;
//				ppt_.set(0,(this->_point2 - this->_point1).length());
//				ppt_.rotate(Vec2::ZERO, (float)((float)_player->dct_ * (M_PI / 2)));
//				this->_point1.set(this->_point2 - ppt_);
//			}

			dpt = this->_point2 - this->_point1;

//			if (!this->gravFlg) {
//				if (dpt.length() > sosaSpan_) {
//					dpt.normalize();
//					dpt *= sosaSpan_;
//					this->_point1.set(this->_point2 - dpt);
//				}
//			}
			if (!mapFlg) {
				this->_player->NomlMove5(dt, dpt);
				this->_meiscene->setPosition(
						this->_meiscene->ChaseA(this->getMMeder()->GetMovePoint(this->_player->getPosition()),
								this->_meiscene->getPosition(), 800, dt));

			}
			if (!mapFlg && !this->tch_) {

			}

//			this->setPosition(-this->_player->getPosition() + this->ctPt);

			//this->_player->AccellMove(dpt);
			//const char *str0 = "onPlay";
			//log("%s", str0);
			/*
			 _scoreLabel->setString(
			 "Map:" + StringUtils::toString((int) _player->mapPt_.x)
			 + "x"
			 + StringUtils::toString((int) _player->mapPt_.y));
			 */
			/*
			 _bestLabel->setString(
			 "sts"
			 + StringUtils::toString(
			 (int) this->getMMeder()->GetMapStatus(
			 _player->mapPt_)));
			 */
			/*
			 _bestLabel->setString(
			 "acc:" + StringUtils::toString((int) this->_point2.x) + "x"
			 + StringUtils::toString((int) this->_point2.y));
			 */
			/*
			 _bestLabel->setString(
			 "aa:" + StringUtils::toString((int) _player->aa));
			 */
			/*
			 _bestLabel->setString(
			 "Img:" + StringUtils::toString((int) _player->mapImgPt_.x)
			 + "x"
			 + StringUtils::toString(
			 (int) _player->mapImgPt_.y));
			 */

			/*
			 _bestLabel->setString(
			 "per:" + StringUtils::toString((int) _player->getPosition().x)
			 + "x"
			 + StringUtils::toString(
			 (int) _player->getPosition().y));
			 */
			dpt.set(this->_player->_point2 - this->_player->_point1);
			dpt.normalize();
			this->_dot0->setPosition(this->_player->getPosition() + dpt * 23);
			this->_dot0->setRotation(-dpt.getAngle() / M_PI * 180 - 90);

			if ((this->getPlayer()->getPosition() - this->_goal2->getPosition()).length()
					< w * scale_ * 0.5) {
				this->fstFlg = true;
				this->setState(GameState::GAMECLEAR);
			}
		}

	}

}

void MainScene::onStageClear(float dt) {

	if (fstFlg) {
		this->fstFlg = false;
		auto audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
		audioEngine->playEffect("gameclear.mp3");
		_state = GameState::GAMECLEAR;

		auto udf = UserDefault::getInstance();

//		int index = udf->getIntegerForKey("INDEX", 0);
//
//		udf->setIntegerForKey("CLEARINDEX", index);
//
//		this->setScore(0);
//
//		int sts_ = this->getMMeder()->GetMeiroStatus(index);
//
//		if (sts_ < 4) {
//
//			switch (sts_) {
//
//			case 1: {
//				//�����_��
//				this->getMMeder()->SetMeiroStatus(index, 6);
//				udf->setIntegerForKey("TTLPOINT",
//						udf->getIntegerForKey("TTLPOINT", 0) + 30 * udf->getIntegerForKey("LEVEL", 1));
//				this->setScore(30 * udf->getIntegerForKey("LEVEL", 1));
//				break;
//			}
//			case 2: {
//				//�⃁�_��
//				this->getMMeder()->SetMeiroStatus(index, 5);
//				udf->setIntegerForKey("TTLPOINT",
//						udf->getIntegerForKey("TTLPOINT", 0) + 5 * udf->getIntegerForKey("LEVEL", 1));
//				this->setScore(5 * udf->getIntegerForKey("LEVEL", 1));
//				break;
//			}
//			case 3: {
//				//�����_��
//				this->getMMeder()->SetMeiroStatus(index, 4);
//				udf->setIntegerForKey("TTLPOINT",
//						udf->getIntegerForKey("TTLPOINT", 0) + 1 * udf->getIntegerForKey("LEVEL", 1));
//				this->setScore(1 * udf->getIntegerForKey("LEVEL", 1));
//				break;
//			}
//
//			}
//
//		}

		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
//		this->getGoalMap()->setVisible(false);
		auto fade_ = FadeOut::create(0.2);
		auto move_ = MoveTo::create(0.2, _goal2->getPosition());
		auto spawn_ = Spawn::create(fade_, move_, NULL);
		this->getPlayer()->runAction(spawn_);

		auto delay2_ = DelayTime::create(0.5f);
		auto func2_ = CallFunc::create([this] {

			this->showResult();

		});

		auto Seq = Sequence::create(delay2_, func2_, NULL);
		this->runAction(Seq);

//		this->setGoal(Sprite::create("goal_2.png"));
//
//		this->getGoal()->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2 + 80));
//
//		this->getGoal()->setScale(0);
//		auto act1 = ScaleTo::create(0.5, 2);
//		auto act2 = ScaleTo::create(0.5, 1);
//		auto rept_ = Repeat::create(Sequence::create(act1, act2, NULL), 2);
//		auto big_ = ScaleTo::create(0.5, 5);
//		auto fade_ = FadeOut::create(0.5);
//		auto spawn_ = Spawn::create(big_, fade_, NULL);
//
//		auto act3 = Sequence::create(rept_, spawn_, DelayTime::create(0.2), CallFunc::create([this] {
//			this->showResult();
//		}), NULL);
//		this->getGoal()->runAction(act3);
//
//		this->_nomove2->addChild(this->getGoal(), 5, Vec2::ZERO, this->getGoal()->getPosition());

		_ad->AdShow(true, true, false, false, false, false);

	}
}
void MainScene::showHint() {

	this->setHintWaku(Sprite::create("hint.png"));
	_hintWaku->setPosition(winSize.width / 2, winSize.height / 2);

	this->setBackImg(MenuItemImage::create("modoru_btn.png", "modoru_p_btn.png", [this](Ref* ref) {

		int rnd = arc4random() % static_cast<int>(2);
		if(rnd==0) {
			this->_ad->AdShow(false,false,false,true,false,false);
		} else {
			this->_ad->AdShow(false,false,false,false,true,false);
		}
		this->_hintWaku->removeFromParent();
		this->_hintM->setVisible(true);
	}));

	this->setBackM(Menu::create(this->_backImg, NULL));
	this->_backM->alignItemsVerticallyWithPadding(5);
	_backM->setPosition(Vec2(this->_hintWaku->getContentSize().width / 2, 215));
	_backM->setAnchorPoint(Vec2(0.5, 0));

	_hintWaku->setScale(0.1f);
//	waku->setOpacity(0);
	auto fade_ = FadeIn::create(0.2f);
	auto big_ = EaseElasticOut::create(ScaleTo::create(0.8f, 1));
	auto spawn_ = Spawn::create(fade_, big_, NULL);
	_hintWaku->runAction(big_);

	_hintWaku->addChild(_backM);
	this->_nomove2->addChild(_hintWaku, 3, Vec2::ZERO, _hintWaku->getPosition());

	this->_hintM->setVisible(false);
}
void MainScene::SetMapAnswer() {
	//マップとアンさーボタンをセット
	this->setMapShowImg(MenuItemImage::create("map.png", "map_p.png", [this](Ref* ref) {

		if(mapFlg) {
			this->MapShow(false);
		} else {
			this->MapShow(true);
		}
	}));

	this->setMapM(Menu::create(this->_mapShowImg, NULL));
	this->_mapM->alignItemsVerticallyWithPadding(25);
	this->_mapM->setPosition(
			Vec2(this->winSize.width / 2, 0) + Vec2(0, _mapShowImg->getContentSize().height / 2 + 20));

	auto delay2_ = DelayTime::create(1.5f);
	_mapShowImg->setScale(0.1);
	auto big2_ = EaseElasticOut::create(ScaleTo::create(0.5f, 1));
	auto seq2_ = Sequence::create(delay2_, big2_, NULL);
	_mapShowImg->runAction(seq2_);

	_nomove2->addChild(this->_mapM, 2, Vec2::ZERO, this->_mapM->getPosition());

	this->setAnsImg(MenuItemImage::create("directpt.png", "directpt_p.png", [this](Ref* ref) {
		this->getMMeder()->MadeAns(_player->mapPt_,GoalPt);
		this->DrawAns(0);
	}));

	this->setAnsM(Menu::create(this->_ansImg, NULL));
	this->_ansM->alignItemsVerticallyWithPadding(25);
	_ansM->setPosition(
			Vec2(this->_ansImg->getContentSize().width / 2 + 20,
					this->_ansImg->getContentSize().height / 2 + 20));
	_ansImg->setScale(0.1);
	auto delay_ = DelayTime::create(1.5f);
	auto big_ = EaseElasticOut::create(ScaleTo::create(0.5f, 1));
	auto seq_ = Sequence::create(delay_, big_, NULL);
	_ansImg->runAction(seq_);
	_nomove2->addChild(_ansM, 2, Vec2::ZERO, _ansM->getPosition());

}

void MainScene::showResult() {

	this->_mMeder->AddLevelStatus(this->_mMeder->Level, 1);

	auto udf = UserDefault::getInstance();

	int index = udf->getIntegerForKey("INDEX", 0);
	int sts_ = this->getMMeder()->GetMeiroStatus(index);

	this->setResultWaku(Sprite::create("resultwaku3.png"));
//	this->_resultWaku->setPosition(winSize.width / 2, winSize.height / 2);

	this->setTryAgainI(MenuItemImage::create("tryagain_btn.png", "tryagain_btn_p.png", [this,udf](Ref* ref) {

//		_ad->AdShow(false,false,false,false,true,false);

			Director::getInstance()->purgeCachedData();
			this->MemoryClear();
			auto scene = MainScene::createScene();
			auto transition = TransitionCrossFade::create(0.5f, scene);
			Director::getInstance()->replaceScene(transition);

		}));

	auto fadeout = EaseSineIn::create(FadeOut::create(0.5));
	auto rep = RepeatForever::create(Sequence::create(fadeout, fadeout->reverse(), nullptr));

	this->_tryAgainI->runAction(rep);

	this->setMenuI(MenuItemImage::create("modoru_btn.png", "modoru_p_btn.png", [this,udf](Ref* ref) {

//		_ad->AdShow(false,false,false,false,true,false);

			Director::getInstance()->purgeCachedData();
			this->MemoryClear();
			auto scene=SelectScene::createScene();
			auto transition=TransitionCrossFade::create(0.5,scene);
			Director::getInstance()->replaceScene(transition);

		}));

	this->setTryAgainM(Menu::create(_tryAgainI, _menuI, NULL));
	this->_tryAgainM->alignItemsVerticallyWithPadding(5);
	_tryAgainM->setPosition(Vec2(_resultWaku->getContentSize().width / 2, 300));
	_tryAgainM->setAnchorPoint(Vec2(0.5, 0));

	this->_resultWaku->setPosition(this->_meiscene->getPosition() + this->_goal2->getPosition());
//	this->_resultWaku->setScale(0.01f);
	this->_resultWaku->setScale(0);
	auto fade_ = FadeIn::create(0.2f);
	auto big_ = ScaleTo::create(0.5f, 1);
	auto move_ = MoveTo::create(0.5f, this->ctPt);
	auto spawn_ = Spawn::create(big_, move_, NULL);
	this->_resultWaku->runAction(spawn_);

	this->_resultWaku->addChild(_tryAgainM);
	this->_nomove3->addChild(this->_resultWaku, 2);

}
void MainScene::onGameOver(float dt) {

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
	//this->getPlayer()->getBody()->setDynamic(false);
	auto delay = DelayTime::create(0.5);
	auto stop = CallFunc::create([this] {

		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();

	});

	auto Seq = Sequence::create(delay, stop, NULL);
	this->runAction(Seq);

	this->setTryAgainI(MenuItemImage::create("tryagain_g.png", "tryagain_r.png", [this](Ref* ref) {
		this->MemoryClear();
		auto scene=MainScene::createScene();
		Director::getInstance()->purgeCachedData();
		auto transition=TransitionCrossFade::create(0.5,scene);
		Director::getInstance()->replaceScene(transition);

	}));
	auto fadeout = EaseSineIn::create(FadeOut::create(0.5));
	auto rep = RepeatForever::create(Sequence::create(fadeout, fadeout->reverse(), nullptr));

	this->_tryAgainI->runAction(rep);

	this->setMenuI(MenuItemImage::create("menu_g.png", "menu_r.png", [this](Ref* ref) {
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

	this->getTimeUp()->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2 + 80));

	this->getTimeUp()->setScale(0);
	auto act1 = ScaleTo::create(0.5, 2);
	auto act2 = ScaleTo::create(0.5, 1);
	auto act3 = Sequence::create(act1, act2, DelayTime::create(0.3), CallFunc::create([this] {
		this->_menuM->setVisible(true);
	}), NULL);
	this->getTimeUp()->runAction(act3);

//title->setZOrder(2);
	this->_nomove2->addChild(this->getTimeUp(), 5, Vec2::ZERO, this->getTimeUp()->getPosition());
//this->_nomove2->reorderChild(title, 5);
//�n�C�X�R�A�o�^

	if (this->nowLvl >= this->bestLvl && !this->retryFlg) {
		this->setYouBest(Sprite::create("youbest_r.png"));
		this->getYouBest()->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2 + 180));
		//btime->setZOrder(2);
		this->_nomove2->addChild(this->getYouBest(), 2, Vec2::ZERO, this->getYouBest()->getPosition());
		UserDefault::getInstance()->setIntegerForKey("bestLvl", this->nowLvl);
		//InterfaceJNI::sendRankParkScore((int)_playTime);
	}

}

void MainScene::MapSet(int Lvl) {

//this->setMMeder(MeiroMeder::create());
//	this->DrawMeiro4();
	const char *str0 = "mapset";
	log("%s", str0);

	this->nowLvl = Lvl;
	auto udf = UserDefault::getInstance();

//	int a_ = arc4random() % static_cast<int>(8) + 5 * this->nowLvl;
//	int b_ = arc4random() % static_cast<int>(60) + 5 * this->nowLvl;
//	int c_ = arc4random() % static_cast<int>(50) + 5 * this->nowLvl;
//	int d_ = arc4random() % static_cast<int>(100) + 6 * this->nowLvl;
//	int e_ = arc4random() % static_cast<int>(50) + 5 * this->nowLvl;
//	int f_ = arc4random() % static_cast<int>(100) + 5 * this->nowLvl;
//	int g_ = arc4random() % static_cast<int>(50) + 5 * this->nowLvl;
//	int h_ = arc4random() % static_cast<int>(100) + 5 * this->nowLvl;
//	int i_ = arc4random() % static_cast<int>(30) + 1 * this->nowLvl;
//	int j_ = arc4random() % static_cast<int>(20) + 2 * this->nowLvl;

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
	if (j_ % 2 == 0) {
		j_++;
	}
	if (k_ % 2 == 0) {
		k_++;
	}
	int l_ = udf->getIntegerForKey("COURCE_Y", 5);

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
		this->getMMeder()->InitMap(Vec2(k_, l_), a_, b_, c_, d_, e_, f_, g_, h_, i_, j_);

		break;
	}
	case 2: {
		this->getMMeder()->InitMap(Vec2(69, 119), a_, b_, c_, d_, e_, f_, g_, h_, i_, j_);

		break;
	}
	case 3: {
		this->getMMeder()->InitMap(Vec2(69, 119), a_, b_, c_, d_, e_, f_, g_, h_, i_, j_);

		break;
	}
	case 4: {
		this->getMMeder()->InitMap(Vec2(69, 119), a_, b_, c_, d_, e_, f_, g_, h_, i_, j_);

		break;
	}
	case 5: {
		this->getMMeder()->InitMap(Vec2(69, 119), a_, b_, c_, d_, e_, f_, g_, h_, i_, j_);

		break;
	}
	case 6: {
		this->getMMeder()->InitMap(Vec2(69, 119), a_, b_, c_, d_, e_, f_, g_, h_, i_, j_);

		break;
	}
	case 7: {
		this->getMMeder()->InitMap(Vec2(69, 119), a_, b_, c_, d_, e_, f_, g_, h_, i_, j_);

		break;
	}
	case 8: {
		this->getMMeder()->InitMap(Vec2(221, 277), a_, b_, c_, d_, e_, f_, g_, h_, i_, j_);

		break;
	}
	case 9: {
		this->getMMeder()->InitMap(Vec2(69, 119), a_, b_, c_, d_, e_, f_, g_, h_, i_, j_);

		break;
	}
	case 10: {
		this->getMMeder()->InitMap(Vec2(69, 119), a_, b_, c_, d_, e_, f_, g_, h_, i_, j_);

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

	int icnt = (int) (this->getMMeder()->courceSize.x * this->getMMeder()->courceSize.y / 350) + 2;

//	this->MapInitShow(true);

	this->SetGoal();

}

void MainScene::setDebugBtn() {

	this->setHintImg(MenuItemImage::create("howto_btn.png", "howto_p_btn.png", [this](Ref* ref) {

		this->showHint();

	}));

	this->setHintM(Menu::create(this->_hintImg, NULL));
	this->_hintM->alignItemsVerticallyWithPadding(25);
	this->_hintM->setPosition(
			Vec2(this->_hintImg->getContentSize().width / 2 + 20,
					this->_hintImg->getContentSize().height / 2 + 20));
//	this->_hintM->setPosition(
//			Vec2(this->winSize.width, this->winSize.height)
//					- Vec2(this->_hintImg->getContentSize().width / 2 + 20,
//							this->_hintImg->getContentSize().height / 2 + 20));
//	this->addChild(this->_hintM, 2);
	_nomove2->addChild(_hintM, 2, Vec2::ZERO, _hintM->getPosition());

	this->setBtn6(MenuItemImage::create("modoru_btn.png", "modoru_p_btn.png", [this](Ref* ref) {

		if(mapFlg) {
			this->MapShow(false);
		} else {
			CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();

//							_ad->AdShow(false,false,false,false,true,false);

			auto cfnc_=CallFuncN::create([this](Node* n) {
						//	this->MemoryClear();
						//	this->setVisible(false);

					});
			auto delay_=DelayTime::create(0.5f);

			auto cfnc2_=CallFuncN::create([this](Node* n) {

						auto scene=SelectScene::createScene();
						//		Director::getInstance()->purgeCachedData();
						auto transition=TransitionCrossFade::create(0.5,scene);
						Director::getInstance()->replaceScene(transition);

					});
			this->runAction(Sequence::create(cfnc_,delay_,cfnc2_,NULL));
		}

	}));

	this->setMenu6(Menu::create(_btn6, NULL));
	_menu6->alignItemsVerticallyWithPadding(25);
	_menu6->setPosition(
			Vec2(this->winSize.width, 0)
					+ Vec2(-_btn6->getContentSize().width / 2 - 20, _btn6->getContentSize().height / 2 + 20));
	_nomove2->addChild(_menu6, 2, Vec2::ZERO, _menu6->getPosition());

	return;

	//ここで終わり
	this->setBtn3(MenuItemImage::create("map.png", "map_p.png", [this](Ref* ref) {

		if(! this->_ad->adClickFlg) {
			//	this->AdShow(false,false,false,true,false,false);
		}
		if(mapFlg) {
			this->MapShow(false);
		} else {
			this->MapShow(true);
		}
	}));
	this->setMenu3(Menu::create(_btn3, NULL));
	_menu3->alignItemsVerticallyWithPadding(25);
	_menu3->setPosition(
			Vec2(this->winSize.width - _btn3->getContentSize().width / 2 - 20,
					this->winSize.height - _btn3->getContentSize().height / 2 - 20));
	_nomove2->addChild(_menu3, 2, Vec2::ZERO, _menu3->getPosition());

	this->setBtn2(MenuItemImage::create("directpt.png", "directpt_p.png", [this](Ref* ref) {
		this->getMMeder()->MadeAns(_player->mapPt_,GoalPt);
		this->DrawAns(0);

	}));

	this->setMenu2(Menu::create(_btn2, NULL));
	_menu2->alignItemsVerticallyWithPadding(25);
	_menu2->setPosition(
			Vec2(_btn2->getContentSize().width / 2 + 20,
					this->winSize.height - _btn2->getContentSize().height / 2 - 20));
	_nomove2->addChild(_menu2, 2, Vec2::ZERO, _menu2->getPosition());

	return;

	this->setBtn1(MenuItemImage::create("speedup.png", "speedup_p.png", [this](Ref* ref) {

//debug 迷路情報を保存する
			auto udf = UserDefault::getInstance();

			this->getMMeder()->StartPt.set(this->getPlayer()->mapPt_);

			this->getMMeder()->WriteDeta3(udf->getIntegerForKey("INDEX",0));
			//this->getMMeder()->WriteDetaSQLite(udf->getIntegerForKey("INDEX",0));
		}));

	this->setMenu1(Menu::create(_btn1, NULL));
	_menu1->alignItemsVerticallyWithPadding(60);
	_menu1->setPosition(40, winSize.height - 40);
	_nomove2->addChild(_menu1, 2, Vec2::ZERO, _menu1->getPosition());

	this->setBtn3(MenuItemImage::create("speedup.png", "speedup_p.png", [this](Ref* ref) {

		//debug
			this->updateFlg=true;

			this->meiroDrawFlg=true;
			this->getMMeder()->MeiroMadeAll();
			this->ShowMsg(ctPt,"迷路進捗率：" + StringUtils::toString(this->_mMeder->madeRate));
			this->DrawMeiro3();
		//this->ShowMsg(Vec2(300,300),"迷路作成完了！");
//			this->ShowMsg(Vec2(winSize.width/2,winSize.height/2),"迷路作成完了！");
			this->MapShow(false);
		}));

	this->setMenu3(Menu::create(_btn3, NULL));
	_menu3->alignItemsVerticallyWithPadding(25);
	_menu3->setPosition(160, 40);
	_nomove2->addChild(_menu3, 2, Vec2::ZERO, _menu3->getPosition());

	this->setBtn4(MenuItemImage::create("speedup.png", "speedup_p.png", [this](Ref* ref) {

//		if(this->getMeiroImg2()) {
//			this->getMeiroImg2()->setVisible(false);
//		}
//		if(this->getMeiroImg()) {
//			this->getMeiroImg()->setVisible(false);
//		}

			madePercent+=5;
			this->getMMeder()->MeiroMadePercent(madePercent);

//			for(int i=0;i<10;i++) {
//				this->getMMeder()->MeiroMadeStep();
//			}
			this->ShowMsg(ctPt,"迷路進捗率：" + StringUtils::toString(this->_mMeder->madeRate));
			this->DrawMeiro3();

		}));

	this->setMenu4(Menu::create(_btn4, NULL));
	_menu4->alignItemsVerticallyWithPadding(25);
	_menu4->setPosition(260, 40);
	_nomove2->addChild(_menu4, 2, Vec2::ZERO, _menu4->getPosition());

	this->setBtn5(MenuItemImage::create("speedup.png", "speedup_p.png", [this](Ref* ref) {

		//this->bomCnt--;

		//debug 迷路を初期化する
			this->updateFlg=false;
		//this->SetPrm();
			this->MapShow(true);

			if(this->getMapImg()) {
				_mapImg->removeFromParent();
			}

			this->getMMeder()->ResetMap();
			madePercent=0;
			this->DrawMeiro3();
			this->ShowMsg(ctPt,"迷路進捗率：" + StringUtils::toString(this->_mMeder->madeRate));
//			if(this->getMeiroImg2()) {
//				this->getMeiroImg2()->setVisible(false);
//			}
//			if(this->getMeiroImg()) {
//				this->getMeiroImg()->setVisible(false);
//			}

		}));

	this->setMenu5(Menu::create(_btn5, NULL));
	_menu5->alignItemsVerticallyWithPadding(25);
	_menu5->setPosition(360, 40);
	_nomove2->addChild(_menu5, 2, Vec2::ZERO, _menu5->getPosition());

	this->setBtn7(MenuItemImage::create("speedup.png", "speedup_p.png", [this](Ref* ref) {

		auto udf = UserDefault::getInstance();
		int ind=udf->getIntegerForKey("LEVEL", 0);
		this->MeiroDetaRenzoku(ind);

	}));

	this->setMenu7(Menu::create(_btn7, NULL));
	_menu7->alignItemsVerticallyWithPadding(25);
	_menu7->setPosition(winSize.width / 2, winSize.height - 40);
	_nomove2->addChild(_menu7, 2, Vec2::ZERO, _menu7->getPosition());

	this->setBtn2(MenuItemImage::create("speedup.png", "speedup_p.png", [this](Ref* ref) {

		this->getMMeder()->MadeFarCource();
		this->GoalPt.set(this->getMMeder()->GoalPt);
		_goal2->setPosition(this->getMMeder()->ChgPositionFromMapToImage(this->_mMeder->GoalPt));

		this->StartPt.set(this->getMMeder()->StartPt);
		_player->setPosition(this->getMMeder()->ChgPositionFromMapToImage(this->_mMeder->StartPt));
		_player->mapImgPt_.set(_player->getPosition());

	}));

	this->setMenu2(Menu::create(_btn2, NULL));
	_menu2->alignItemsVerticallyWithPadding(25);
	_menu2->setPosition(140, this->winSize.height - 40);
	_nomove2->addChild(_menu2, 2, Vec2::ZERO, _menu2->getPosition());

}
void MainScene::MeiroDetaRenzoku(int indx) {
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
		this->getMMeder()->WriteDeta3(udf->getIntegerForKey("INDEX", 0));

	}

}
void MainScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {

		auto scene = SelectScene::createScene();
		auto transition = TransitionCrossFade::create(0.5, scene);
		Director::getInstance()->replaceScene(transition);
	}
}
void MainScene::onEnterTransitionDidFinish() {

	if (UserDefault::getInstance()->getBoolForKey("bgmkey", true)) {
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("bgm.mp3", true);
	}
	auto udf = UserDefault::getInstance();
	nowLvl = UserDefault::getInstance()->getIntegerForKey("LEVEL", 1);
	this->setMMeder(MeiroMeder::create());
	this->getMMeder()->scale_ = this->scale_;
//	this->getMMeder()->w = this->w;
//	this->getMMeder()->t = this->t;
	this->getMMeder()->SetLevel(nowLvl);
//	this->getMMeder()->getMsgLabel()->setPosition(this->ctPt);
//	this->_nomove2->addChild(this->getMMeder()->getMsgLabel(), 3, Vec2::ZERO,
//			this->getMMeder()->getMsgLabel()->getPosition());
//	this->MapSet(_lvl);

	if (this->getMMeder()->GetMeiroStatus(nowLvl) == 0) {
		this->getMMeder()->SetMeiroStatus(nowLvl, 1);
	}
	this->getMMeder()->MeiroMadeAll();
	this->getMMeder()->GetMeiroSize();
	this->_meiscene->setPosition(this->ctPt - this->getMMeder()->MeiroCenter);

//
//②デバック迷路作成時
	this->setDebugBtn();
//	this->getMMeder()->ResetMap();

//	this->fstFlg = true;
//	this->setState(GameState::MADE);
//	this->scheduleUpdate();
//
//	return;
	//ここで止める。

//	while (this->getMMeder()->MeiroMadeStep()) {
////		this->DrawMeiro3_neo();
//		this->getMsgLabel()->setString(
//				"迷路作成中!\r\n" + StringUtils::toString((int) this->getMMeder()->madeRate));
//	}

	auto fade_ = FadeOut::create(0.3f);
	_msgLabel->runAction(fade_);
//	_msgLabel->setVisible(false);
	this->getMMeder()->MadeFarCource();

//	保存するとき
//	this->getMMeder()->WriteDeta3(_lvl);
//	加古混むとき
//	this->getMMeder()->ReadDeta3(_lvl);
	this->getMMeder()->GetMeiroSize();
	this->_meiscene->setPosition(this->ctPt - this->getMMeder()->MeiroCenter);

	this->GoalPt.set(this->getMMeder()->GoalPt);
	this->StartPt.set(this->getMMeder()->StartPt);
//ゴールを新たにセット
	this->setGoal2(Item::create());
//	_goal2->setState(Item::ItemState::T11);
//	_goal2->setAnchorPoint(Vec2(0.15,0.15));
//	_goal2->setScale(0.9f);
	this->GoalPt.set(this->getMMeder()->GoalPt);
	_goal2->setPosition(this->getMMeder()->ChgPositionFromMapToImage(this->_mMeder->GoalPt));
	this->_meiscene->addChild(_goal2, 1);
//プレイヤーをセット
	this->setPlayer(Ball::create());
	_player->w = this->w;
	_player->d = this->d;
	_player->scale_ = this->scale_;
	_player->setVisible(true);
	_player->setScale(scale_);
	_player->setPosition(this->getMMeder()->ChgPositionFromMapToImage(this->_mMeder->StartPt));
	_player->updateFlg = false;
	_player->setMMeder(this->getMMeder());
	_player->setLevel(nowLvl);
	this->_meiscene->addChild(_player, 6);
	this->_meiscene->setOpacity(0);
	this->MapInitShow(true);
	this->DrawMeiro3_neo();
	this->_ad->AdShow(false, false, false, false, false, false);

//①本番用
//this->getMMeder()->MeiroMadeFromFile(index);		//PLISTファイルから迷路データを生成
//this->DrawMeiro4();
//①
//this->DrawMeiroDumy(1);

	this->meiroDrawFlg = true;

	auto delay_ = DelayTime::create(0.5f);
	auto func_ = CallFuncN::create([this](Node* nd) {
		this->scheduleUpdate();
	});

	auto seq_ = Sequence::create(delay_, func_, NULL);
	this->runAction(seq_);

}

