#ifndef __neomeiro__MainScene_Debug__
#define __neomeiro__MainScene_Debug__
//#define RAND_FLOAT(LO,HI) LO + static_cast<float>(rand())/(static_cast<float>RAND_MAX(HI-LO))))


#include "platform/android/jni/JniHelper.h"

// 呼び出すメソッドが書かれているパッケージ名とjavaクラス名
#define  CLASS_NAME "org/cocos2dx/cpp/AppActivity"
#define TWEET "tweet"
#define OPENRNK "openRankPark"
#define SENDSCR "sendRankParkScore"
#define WRITEDETA "writeDeta"
#define READDETA "readDeta"


#include "cocos2d.h"
#include "ParticleSystemPool.h"
#include "Ball.h"
#include "Cource.h"

#include "CourcePool.h"
#include "Item.h"
#include "ItemPool.h"
#include "MeiroMeder.h"
#include <vector>       // ヘッダファイルインクルード
using namespace std;

USING_NS_CC;

class MainScene_Debug: public cocos2d::Layer {
protected:
MainScene_Debug();
virtual ~MainScene_Debug();
bool init()
override;
const int ballCatg = 1 << 0;
const int itemCatg = 1 << 1;
const int courceCatg = 1 << 2;
const int startCatg = 1 << 3;
const int goalCatg = 1 << 4;

//void didAccelerate(CCAcceleration* pAccl) override;
void onAcceleration(Acceleration* acc, Event* unused_event);

bool updateFlg;

bool meiroDrawFlg=false;

bool mapFlg = false;
bool goalFlg = false;
bool btnFlg = false;
bool gravFlg = true; //加速度センサーを有効にする

bool retryFlg;//一度タイムアップになったらtrueになる。

cocos2d::Vec2 _point1;
cocos2d::Vec2 _point2;

int pcnt; //アタックの繰り返し回数
int _sec;
float _time;

//float Kdo;

private:

//Size winSize;
Vec2 madeRndPos();
Vec2 madeRndPosOuter();

//	void CourceTestSet(); //test
bool inWinSize(cocos2d::Vec2 x);

enum class GameState {

	//ゲームスタート前、迷路作成中。
	READY,
	//プレイ中
	PLAY,
	//ストップ中
	STOP,
	//ゲームオーバー
	GAMECLEAR,

	//ゲームオーバー
	GAMEOVER

};

enum class AttackState {

	A, B, C, D, E, F, G, H, I, J, K, L, M, N

};

//int _madeNo;
//	int _barNo;
void onReady();
void onPlay();
void onGameOver();
void onStageClear();
//	void onScoreUp(int x);
void setAction(AttackState x);
//	void MadeCource();
//	bool MadeCourceByStep();
//	bool MadeTrack(Cource* C1);
void ShowMsg(cocos2d::Vec2 pt, std::string msg);
//	int _stepCnt;

public:
Size winSize;

float scale_=0.5f;//コースのスケールとあわせる。
int w=30;
int d=5;//迷路画像の余白

// 通知イベント受け取りメソッド
void observerEventActionClose(Ref* pSender);
bool ansFlg=false;


//迷路データの連続作成。
void MeiroDetaRenzoku(int indx);


//迷路データの読み書き
//void WriteDeta(int index,String deta);
void WriteDeta(int index);
String ReadDeta(int index);
void ReSetCource(Vec2 pt);//ptに対して,コースをリセットする。
Cource* GetOuterCource(Vec2 pt);//mapptに対して一番離れているコースを返す。
Cource* FindCource(Vec2 pt);//指定のmapptに存在しているコースを返す。。


//アイテム
void DrawMeiro(); //現在の状態で迷路画像を配列する
void DrawMeiroDumy(int x); //現在の状態で迷路画像をx個配列する
void DrawMeiro(int x); //現在の状態で迷路画像をx個配列する
void DrawMeiro2(); //現在の状態で迷路画像を配列する
void DrawMeiro3(); //現在の状態で迷路画像を描写する
void DrawMeiro4(); //現在の状態で迷路画像を描写する
void DrawAns(); //アンサーを描く。
void DrawAns(int L); //Lだけアンサーを描く。
void SpeedUp(); //x秒スピードアップ。
void MapShow(float tm); //指定の時間で全マップ画像を表示。
void MapShow(float tm, float scale); //現在の地点で、指定のスケール、時間で縮小する。
void MapShow(bool x); //trueでマップ化。
void MapInitShow(bool); //スタート時の初期の画面
void Bomb(Vec2 pt); //ptのポジションの壁を破壊。
void TimePlus(int x); //残り時間をプラスする。
void MapSet(int Lvl); //レベルに応じてマップをセットする。
void SetItemRnd(int x); //アイテムをｘ個ランダムにセット
void SetGoal();
void StageLvlShow();

int dctCnt; //現在保持しているアイテムの数。
int mapCnt;
int spdCnt;
int bomCnt;
int bestLvl; //ベストレベル
int nowLvl; //現在のレベル
float restTime; //残り時間
void MemoryClear();
static cocos2d::Scene* createScene();
void update(float dt);
CREATE_FUNC(MainScene_Debug);
CC_SYNTHESIZE_RETAIN(MeiroMeder*, _mMeder, MMeder);
CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*, _backGround, BackGround);
CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*,_backGround1,BackGround1);
CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*,_backGround2,BackGround2);
CC_SYNTHESIZE_RETAIN(cocos2d::Label*,_scoreLabel,ScoreLabel);
CC_SYNTHESIZE_RETAIN(cocos2d::Label*,_bestLabel,BestLabel);
CC_SYNTHESIZE_RETAIN(cocos2d::Label*,_lifeLabel,LifeLabel);
CC_SYNTHESIZE_RETAIN(cocos2d::Label*,_msgLabel,MsgLabel);
CC_SYNTHESIZE_RETAIN(cocos2d::Label*,_dctCnt,DctCnt);
CC_SYNTHESIZE_RETAIN(cocos2d::Label*,_mapCnt,MapCnt);
CC_SYNTHESIZE_RETAIN(cocos2d::Label*,_spdCnt,SpdCnt);
CC_SYNTHESIZE_RETAIN(cocos2d::Label*,_bomCnt,BomCnt);
CC_SYNTHESIZE_RETAIN(cocos2d::Label*,_lvlLavel,LvlLavel);
CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*,_goalMap,GoalMap);


CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*,_startMap,StartMap);


CC_SYNTHESIZE_RETAIN(Ball*,_player,Player);
CC_SYNTHESIZE_RETAIN(CourcePool*,_courcePool,CourcePool);
CC_SYNTHESIZE_RETAIN(ItemPool*, _itemPool, ItemPool);
CC_SYNTHESIZE(cocos2d::PhysicsWorld*,_world,World);
CC_SYNTHESIZE(int,_playScore,Score);
CC_SYNTHESIZE(int,_bestScore,BestScore);
CC_SYNTHESIZE(int,_level,Level);
CC_SYNTHESIZE(GameState,_state,State);
CC_SYNTHESIZE(AttackState,_attackState,AttackState);
CC_SYNTHESIZE(bool,_attackFlg,AttackFlg);
CC_SYNTHESIZE(cocos2d::Vector<Cource*>,_cources,Cources);
CC_SYNTHESIZE(cocos2d::Vector<Item*>,_items,Items);
CC_SYNTHESIZE(cocos2d::Vector<Sprite*>,_dots,Dots);

//CC_SYNTHESIZE(cocos2d::Vec2, _point1,Point1);
//CC_SYNTHESIZE(cocos2d::Vec2, _point2,Point2);
void onEnterTransitionDidFinish() override;
std::function<void(MainScene_Debug*)> onUpDateListener;
std::function<void(MainScene_Debug*)> onsecUpDateListener;
void secupdate();
CC_SYNTHESIZE_RETAIN(cocos2d::SpriteBatchNode* ,_meiroImg,MeiroImg);
CC_SYNTHESIZE_RETAIN(cocos2d::SpriteBatchNode* ,_meiroImg2,MeiroImg2);
CC_SYNTHESIZE_RETAIN(cocos2d::SpriteBatchNode* ,_ansBase,AnsBase);
CC_SYNTHESIZE_RETAIN(cocos2d::DrawNode*,_mapImg,MapImg);
CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*,_dot0,Dot0);
CC_SYNTHESIZE_RETAIN(MenuItemImage*, _btn1,Btn1);
CC_SYNTHESIZE_RETAIN(MenuItemImage*, _btn2,Btn2);
CC_SYNTHESIZE_RETAIN(MenuItemImage*, _btn3,Btn3);
CC_SYNTHESIZE_RETAIN(MenuItemImage*, _btn4,Btn4);
CC_SYNTHESIZE_RETAIN(MenuItemImage*, _btn5,Btn5);
CC_SYNTHESIZE_RETAIN(MenuItemImage*, _btn6,Btn6);
CC_SYNTHESIZE_RETAIN(MenuItemImage*, _btn7,Btn7);
CC_SYNTHESIZE_RETAIN(Menu*, _menu1,Menu1);
CC_SYNTHESIZE_RETAIN(Menu*, _menu2,Menu2);
CC_SYNTHESIZE_RETAIN(Menu*, _menu3,Menu3);
CC_SYNTHESIZE_RETAIN(Menu*, _menu4,Menu4);
CC_SYNTHESIZE_RETAIN(Menu*, _menu5,Menu5);
CC_SYNTHESIZE_RETAIN(Menu*, _menu6,Menu6);
CC_SYNTHESIZE_RETAIN(Menu*, _menu7,Menu7);
CC_SYNTHESIZE_RETAIN(cocos2d::ParallaxNode *, _nomove1,noMove1);
CC_SYNTHESIZE_RETAIN(cocos2d::ParallaxNode *, _nomove2,noMove2);
CC_SYNTHESIZE_RETAIN(cocos2d::Layer *, _meiscene,meiScene);


//redystart
CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*,_ready,Ready);
CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*,_start,Start);
CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*,_levelShow,LevelShow);
//スタート時のレベル表示
//gameover
CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*,_timeUp,TimeUp);
CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*,_goal,Goal);
CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*,_youBest,YouBest);
CC_SYNTHESIZE_RETAIN(Menu*, _tryAgainM,TryAgainM);
CC_SYNTHESIZE_RETAIN(Menu*, _menuM,MenuM);
CC_SYNTHESIZE_RETAIN(MenuItemImage*, _tryAgainI,TryAgainI);
//nextStageも兼ねる。
CC_SYNTHESIZE_RETAIN(MenuItemImage*, _menuI,MenuI);


CC_SYNTHESIZE_RETAIN(EventListenerTouchOneByOne*, _touchlistener,TouchListenner)
;CC_SYNTHESIZE_RETAIN( EventListenerPhysicsContact*, _contactlistener,ContactListenner)
;

};

#endif // __HELLOWORLD_SCENE_H__
