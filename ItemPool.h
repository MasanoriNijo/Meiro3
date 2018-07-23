

#ifndef __neomeiro__ItemPool__
#define __neomeiro__ItemPool__

#include "cocos2d.h"
#include "Item.h"

class ItemPool : public cocos2d::Ref {

	ItemPool();
	virtual ~ItemPool();


public:
	static ItemPool* create( int size);
	bool init( int size);
	void push(Item* ig);
	int getSize();
	Item* pop();

protected:
	/* ƒv[ƒ‹‚ÌÀ‘Ì */
	cocos2d::Vector<Item*> _pool;
};



#endif /* defined(__androidtest__EnemyPool__) */
