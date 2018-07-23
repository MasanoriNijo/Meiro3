#include "Item.h"
#include "ItemPool.h"

USING_NS_CC;

ItemPool::ItemPool() {

}
ItemPool::~ItemPool() {

}

ItemPool* ItemPool::create(int size) {
	auto pool = new ItemPool();
	if (pool && pool->init(size)) {
		pool->autorelease();
		return pool;
	} else {
		CC_SAFE_DELETE(pool);
		//pool=NULL;
		return nullptr;
	}
}

bool ItemPool::init(int size) {
	for (int i = 0; i < size; i++) {
		auto ig = Item::create();
		// �g���I��������̃R�[���o�b�N��ݒ肷��
		/*
		 EnemyA_->onUpDateListener = [this](EnemyA* sender) {

		 sender->getPhysicsBody()->applyImpulse(Vec2(1,1));
		 };
		 */

		ig->onFinishListener = [this](Item* sender) {
			// �v�[���ɖ߂�

				if(sender->getParent()!=NULL) {
					sender->removeFromParent();
				}
				sender->stopAllActions();
				this->push(sender);
				sender->release();
			};

		// �\�����I�������e����폜�����悤�ɂ���I

		//em->setAutoRemoveOnFinish(true);
		// ��~��ԂŊi�[����
		//em->stopSystem();
		push(ig);
	}
	return true;
}

void ItemPool::push(Item* ig) {
	_pool.pushBack(ig);
}

int ItemPool::getSize() {

	return _pool.size();

}

Item* ItemPool::pop() {
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
