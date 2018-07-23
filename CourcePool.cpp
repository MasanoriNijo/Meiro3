#include "Cource.h"
#include "CourcePool.h"

USING_NS_CC;

CourcePool::CourcePool(): _bachNode(NULL){

}
CourcePool::~CourcePool() {
	CC_SAFE_RELEASE_NULL(_bachNode);
}

CourcePool* CourcePool::create(int size) {
	auto pool = new CourcePool();
	if (pool && pool->init(size)) {
		pool->autorelease();
		return pool;
	} else {
		CC_SAFE_DELETE(pool);
		return nullptr;
	}
}

bool CourcePool::init(int size) {

	//this->setBachNode( CCSpriteBatchNode::create("cources_mini.png"));



	for (int i = 0; i < size; i++) {

		//auto cource_ = Cource::createWithTexture(_bachNode->getTexture());
		auto cource_=Cource::create();
		// �g���I��������̃R�[���o�b�N��ݒ肷��
		/*
		 EnemyA_->onUpDateListener = [this](EnemyA* sender) {

		 sender->getPhysicsBody()->applyImpulse(Vec2(1,1));
		 };
		 */

		cource_->onFinishListener = [this](Cource* sender) {
			// �v�[���ɖ߂�
				this->push(sender);
				sender->release();
			};

		// �\�����I�������e����폜�����悤�ɂ���I

		//em->setAutoRemoveOnFinish(true);
		// ��~��ԂŊi�[����
		//em->stopSystem();
		push(dynamic_cast<Cource*>(cource_));
	}
	return true;
}

void CourcePool::push(Cource* bl) {
	_pool.pushBack(bl);
}

int CourcePool::getSize(){

	return _pool.size();

}


Cource* CourcePool::pop() {
	if (_pool.empty()) {
		//CCLOG("�v�[������ł�!");
		return nullptr;
	}
	auto em = _pool.back();
	em->retain();
	_pool.popBack();
	//em->resetSystem();
	return em;
}
