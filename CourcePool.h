
#ifndef __neomeiro__CourcePool__
#define __neomeiro__CourcePool__

#include "cocos2d.h"
#include "Cource.h"

class CourcePool: public cocos2d::Ref {

	CourcePool();
	virtual ~CourcePool();

public:
	static CourcePool* create(int size);
	bool init(int size);
	void push(Cource* bl);
	int getSize();
	Cource* pop();

CC_SYNTHESIZE_RETAIN(cocos2d::CCSpriteBatchNode*, _bachNode,BachNode);

protected:
	/* ÉvÅ[ÉãÇÃé¿ëÃ */
	cocos2d::Vector<Cource*> _pool;
};

#endif /* defined(__androidtest__EnemyPool__) */
