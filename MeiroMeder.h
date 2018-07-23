#ifndef __neomeiro__MeiroMeder__
#define __neomeiro__MeiroMeder__

#include "cocos2d.h"
#include "Kabe.h"
#include "KabePool.h"

//#include "saveSQL.h"
//#include "Cource.h"
//#include "Item.h"
#include <vector>       // ヘッダファイルインクルード
using namespace std;
USING_NS_CC;

// 呼び出すメソッドが書かれているパッケージ名とjavaクラス名
#define  CLASS_NAME "org/cocos2dx/cpp/AppActivity"
#define TWEET "tweet"
#define OPENRNK "openRankPark"
#define SENDSCR "sendRankParkScore"
#define WRITEDETA "writeDeta"
#define READDETA "readDeta"

class MeiroMeder: public cocos2d::Ref {

	MeiroMeder();
	virtual ~MeiroMeder();

public:

	float scale_ = 0.5f; //コースのスケールとあわせる。
	int w = 20;
	int t = 4;

	static MeiroMeder* create(int x_, int y_, int t_); //迷路の大きさｘ、ｙ、迷路作成ルートの数ｔ
	bool init(int x_, int y_, int t_);
	static MeiroMeder* create();

	Size winSize;
	Vec2 ctPt; //センターポジション

	Vec2 courceSize; //コースのサイズを指定。奇数同士
	Vec2 MeiroSize; //迷路の実際のサイズ
	Vec2 MeiroCenter; //迷路の実際のセンター位置（オフセットポジションを含む）

	Rect MoveRect; //可動範囲をセット
	//	迷路の実際のサイズを表示
	Vec2 GetMeiroSize();
	Vec2 GetMovePoint(Vec2 pt);
	Vec2 MovePoint;
	Vec2 OffSetPt;
	Vec2 OffSetPt0 = Vec2(20, 230);	//初期値
	int min_x;
	int min_y;
	int max_x;
	int max_y;

	std::vector<int> mMap; //0:なし、1：外壁、2：壁、3：壁メーダー、4：start、5：goal 1：成長壁,2：メーダー壁,3：終了壁

CC_SYNTHESIZE_RETAIN(KabePool*, _Maders,Maders)
	;

	std::vector<cocos2d::Vec2> mMaders; //壁メーダーの位置を保持
	std::vector<int> mMaderDirects; //壁メーダーの進行方向を保持
	std::vector<int> mMaderKabes; //壁メーダーの接している壁の方向を保持。接していない時は0
	std::vector<cocos2d::Vec2> mAns; //アンサールートを保持
	int maderCnt; //めーだーの数

	void SetLevel(int lvl_); //レベル別にパラメーターをセットする。0のときは、ユーザーセットをしたもの。任意設定
	int Level; //現在のレベル

	;CC_SYNTHESIZE_RETAIN(cocos2d::Label*,_msgLabel,MsgLabel)
	;

	int GetLevelStatus(int lvl_); //-1:ロック、0:ロック解除状態、1以上はクリヤ数とアンロック状態を示す。
	void SetLevelStatus(int lvl_, int atai_);
	void AddLevelStatus(int lvl_, int d_);

	void ReadDeta3(int index);	//UserDefaulより読み込み
	void WriteDeta3(int index);	//UserDefaulへ書き込み

	void SetMapStatus(Vec2 pt, int sts); //指定のポイントのマップのステータスを設定する
	int GetMapStatus(Vec2 pt); //指定のポイントのマップのステータスを取得

	//迷路データの読み書き
	//void WriteDeta(int index,String deta);
	void WriteDeta(int index);

	void WriteDeta_neo(int index);	//コースタイプ0-15でデータを保持する。
	void WriteDetaSQLite(int index);	//SQLiteへ保存
	String ReadDeta(int index);
	String ReadDeta2(int index);	//あせっとふぁいるより読み出し

	std::string DetaOut();
	Vec2 StartPt;	//スタートポイント
	Vec2 GoalPt;	//ゴールポイント
	int cntMax;	//コースの長さを保持。一時的
	int cntMaxA;	//コースの長さを保持。

	int thokuPrm = 40;	//初期直進性
	int edaPrm = 1000;	//初期枝分かれ性
	int zizokPrm = 10000;	//初期連続性
	int kabePrm = 100;	//壁への回り込み性
	int syokiRen = 350;	//初期パラメータの連続性
	int syokiRen_ = 0;	//初期パラメータの連続性変数
	bool fstFlg = true;

	int madeStep = 0;	//0:初期、1：次

	int thokuPrm2 = 10;	//直進性
	int edaPrm2 = 10;	//枝分かれ性
	int zizokPrm2 = 10;	//連続性
	int kabePrm2 = 10;	//壁への回り込み性
	bool kurl = false;	//くるくる性
	bool kurlCng = false;	//くるくる性

	int GetMadeRate();	//現在の進捗率パーセントを算出
	int madeRate = 0;
	int madeRateAll = 0;	//レート計算時の母数、initMap時に同時に算出する
	bool _madeFin=false;//迷路が完成した場合true


	Vec2 GetWakuPosition(long index); //インデックスより、迷路の外枠ポジションを帰す。
	Vec2 MaderSet(int pos, int stindex);
	Vec2 MaderSet(int pos); //フリーのメーダーのセット可能位置を探す。0:全部、1：壁のみ、2：枝のみ
	Vec2 GetDirection(int index); //インデックスよりめーだの進行方向をVec2に変換する。
	bool MoveChk(Vec2 pt, int direct); //指定の方向に移動可能かどうかチェック。
	int ChgDirect(Vec2 pt, int dct); //現在の方向dctから時計回りに、動ける方向を探す。
	bool MaderMove(int index, int chokPrm); //指定のインデックスのメーダーが移動する。直進パラメーターを指定。いけない場合方向を変える。
	bool MaderMove(int index, int chokPrm, int kabePrm); //指定のインデックスのメーダーが移動する。直進パラメーターを指定。いけない場合方向を変える。
	bool ChkKabe(int index); //壁かどうかチェックする

	Vec2 GetMapPosition(int index); //インデックスよりマップのポジションを取得。
	int GetMapIndex(Vec2 pt); //指定のポジションのコースインデックスを返す。

	Vec2 GetJunctionPoint(Vec2 nowPt, Vec2 dctPt);
	//現在のポイントから指定の方向へ次のジャンクションポイント（一本道以外のポイント）を探す

	bool MeiroMadeStep(); //迷路の作成ステップ。thokuPrm:直進性。edaPrm:枝に生成性。zizokPrm:継続性
	void MeiroMadePercent(int parcent_); //迷路を指定のパーセントまで作る。
	void MeiroMadeAll(); //迷路を完成まで作る。
	bool MeiroMadeFromSQLite(int index); //SQLiteファイルより読み込み
	void MeiroMadeFromFile(int index); //完成版plistファイルより読み込み
	bool MeiroMadeFromFile_debug(int index); //debug strageファイルより読み込み
	bool MeiroMadeFromFile_debug_neo(int index); //コースタイプ0-15空変換する。
	void ResetMap(); //マップの情報をリセットする。
	void InitMap(Vec2 cSize, int maderCnt, int tyokuPrm_, int edaPrm_, int zizokPrm_, int kabePrmint_,
			int syokiCnt, int tyokuPrm, int edaPrm, int zizokPrm, int kabePrm); //コースを初期化。
	void InitMap(Vec2 cSize, int maderCnt, int tyokuPrm, int edaPrm, int zizokPrm, int kabePrm); //コースを初期化。
	void InitMap(Vec2 cSize, int maderCnt, int tyokuPrm, int edaPrm, int zizokPrm); //コースを初期化。
	void InitMap(Vec2 cSize, int maderCnt); //コースを初期化。
	void InitMap_Prm(Vec2 cSize); //コースを初期化。
	bool MadeAns(Vec2 pt1, Vec2 pt2); //pt1→pt2アンサールートを作成する。
	void AnsPtSet(Vec2 pt); //新たなポイントを追加する。戻っている場合は削除する。

	Vec2 MadeFarPoint(Vec2 pt_); //現在いるポイントから一番遠いポイントを探す。
	void MadeFarCource();

	int GetMeiroStatus(int index);
	void SetMeiroStatus(int index, int status);

	int GetCourceNo(Vec2 pt); //指定のポイントの上下左右の状態より、コースNoを取得

	void MemoryClear();

	Vec2 ChgPositionFromMapToImage(Vec2 mapPt_); //マップのポイントを実際のspriteのポジションに変換
	Vec2 ChgPositionFromImageToMap2(Vec2 mapPt_); //マップのポイントを実際のspriteのポジションに変換.奇数のみ
	Vec2 ChgPositionFromImageToMap(Vec2 imgPt_); //spriteのポイントを実際のマップのポジションに変換

//	CC_SYNTHESIZE_RETAIN(SaveSQL*, _sqlite,SQLite);

protected:
	/* プールの実体 */
	//cocos2d::Vector<Item*> _pool;
};

#endif /* defined(__androidtest__EnemyPool__) */
