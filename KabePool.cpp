#include "Kabe.h"
#include "KabePool.h"

USING_NS_CC;

KabePool::KabePool() {

}
KabePool::~KabePool() {

}

KabePool* KabePool::create(int size) {
	auto pool = new KabePool();
	if (pool && pool->init(size)) {
		pool->autorelease();
		return pool;
	} else {
		CC_SAFE_DELETE(pool);
		//pool=NULL;
		return nullptr;
	}
}

bool KabePool::init(int size) {
	for (int i = 0; i < size; i++) {
		auto x = Kabe::create();

		x->onFinishListener = [this](Kabe* sender) {

//				if(sender->getParent()!=NULL) {
//					sender->removeFromParent();
//				}
				_member.swap(sender,_member.back());
				_member.popBack();
				this->push(sender);
				sender->release();
			};

		push(x);
	}
	return true;
}
void KabePool::AllPop() {
	//全てだす。
	while (this->pop());
	for (int i = 0; i < this->_member.size(); i++) {
		_member.at(i)->SetPrm(i+1);
	}
}
void KabePool::AllReset(){
	//パラメータをそのままに初期状態にする。

	while (this->pop());
	for (int i = 0; i < this->_member.size(); i++) {
		_member.at(i)->ResetKabe();
	}


}
void KabePool::AllPop(int tyokuPrm_, int edaPrm_, int zizokPrm_, int kabePrm_, int syokiCnt, int tyokuPrm,
		int edaPrm, int zizokPrm, int kabePrm) {
	//全てのパラメータをセットしてだす。

	this->AllPop();

	for (int i = 0; i < this->_member.size(); i++) {
		_member.at(i)->SetPrm(tyokuPrm_, edaPrm_, zizokPrm_, kabePrm_, syokiCnt, tyokuPrm, edaPrm, zizokPrm,
				kabePrm);
	}

}
void KabePool::push(Kabe* x) {
	_pool.pushBack(x);
}

int KabePool::getSize() {

	return _pool.size();

}

Kabe* KabePool::pop() {
	if (_pool.empty()) {
		return nullptr;
	}
	auto x = _pool.back();
	x->retain();
	_pool.popBack();
	_member.pushBack(x);
	return x;
}
