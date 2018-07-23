

#ifndef __neomeiro__ParticleSystemPool__
#define __neomeiro__ParticleSystemPool__

#include "cocos2d.h"
#include "NParticleSystemQuad.h"

class ParticleSystemPool : public cocos2d::Ref {

public:
	static ParticleSystemPool* create(std::string filename, size_t size);
	bool init(std::string filename, size_t size);
	void push(NParticleSystemQuad* particle);
	NParticleSystemQuad* pop();

protected:
	/* �v�[���̎��� */
	cocos2d::Vector<NParticleSystemQuad*> _pool;
};



#endif /* defined(__androidtest__ParticleSystemPool__) */
