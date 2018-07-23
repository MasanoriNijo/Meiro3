#ifndef __neomeiro__KabePool__
#define __neomeiro__KabePool__

#include "cocos2d.h"
#include "Kabe.h"

class KabePool: public cocos2d::Ref {

	KabePool();
	virtual ~KabePool();

public:
	static KabePool* create(int size);
	bool init(int size);
	void push(Kabe* ig);
	int getSize();
	Kabe* pop();CC_SYNTHESIZE(cocos2d::Vector<Kabe*>,_member,Member)
	;
	void AllReset();//パラメータをそのままに初期状態にする。
	void AllPop();//全てだす。
	void AllPop(int tyokuPrm_, int edaPrm_, int zizokPrm_, int kabePrmint_,
			int syokiCnt, int tyokuPrm, int edaPrm, int zizokPrm, int kabePrm);//全てのパラメータをセットしてだす。

protected:
	/* �v�[���̎��� */
	cocos2d::Vector<Kabe*> _pool;
};

#endif /* defined(__androidtest__EnemyPool__) */
