

#include "ParticleSystemPool.h"

ParticleSystemPool* ParticleSystemPool::create(std::string filename, size_t size) {
	auto pool = new ParticleSystemPool();
	if (pool && pool->init(filename, size)) {
		pool->autorelease();
		return pool;
	} else {
		CC_SAFE_DELETE(pool);
		return nullptr;
	}
}

bool ParticleSystemPool::init(std::string filename, size_t size) {
	for (int i = 0; i < size; i++) {
		auto particle = NParticleSystemQuad::create(filename);
		// �g���I��������̃R�[���o�b�N��ݒ肷��
		particle->onFinishListener = [this](NParticleSystemQuad* sender) {
			// �v�[���ɖ߂�
			this->push(sender);
			sender->release();
		};
		// �\�����I�������e����폜�����悤�ɂ���I
		particle->setAutoRemoveOnFinish(true);
		// ��~��ԂŊi�[����
		particle->stopSystem();
		push(particle);
	}
	return true;
}

void ParticleSystemPool::push(NParticleSystemQuad* particle) {
	_pool.pushBack(particle);
}

NParticleSystemQuad* ParticleSystemPool::pop() {
	if (_pool.empty()) {
		//CCLOG("�v�[������ł�!");
		return nullptr;
	}
	auto particle = _pool.back();
	particle->retain();
	_pool.popBack();
	particle->resetSystem();
	return particle;
}
