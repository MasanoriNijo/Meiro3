#ifndef __neomeiro__ImovileAd__
#define __neomeiro__ImovileAd__
#include "cocos2d.h"
USING_NS_CC;

//トップのアイコン、SHOWID="AD_ICON_TOP"アイコンバナー(57x57, 他)
#define IMOBILE_ICON_PID "34243"
#define IMOBILE_ICON_MID "447293"
#define IMOBILE_ICON_SID "1480149"

//下のアイコン、SHOWID="AD_ICON_DOWN"アイコンバナー(57x57, 他)
#define IMOBILE_ICON_PID2 "34243"
#define IMOBILE_ICON_MID2 "447293"
#define IMOBILE_ICON_SID2 "1480150"

//フルスクリーンのインステSHOWID="FULL_INST" フルスクリーン/インステ(800x1200)
#define IMOBILE_FULLSCREENAD_PID "34243"
#define IMOBILE_FULLSCREENAD_MID "447293"
#define IMOBILE_FULLSCREENAD_SID "1480152"

//テキストポプアップ、SHOWID="AD_TEXT"
#define IMOBILE_TEXTPOPUP_PID "34243"
#define IMOBILE_TEXTPOPUP_MID "447293"
#define IMOBILE_TEXTPOPUP_SID "1480153"

//上部バナー、"AD_BANNER" スマートフォンバナー(320x50 / 640x100)
#define IMOBILE_BANNER_PID "34243"
#define IMOBILE_BANNER_MID "447293"
#define IMOBILE_BANNER_SID "1480154"

//下部バナー、"AD_BANNER2" スマートフォンバナー(320x50 / 640x100)

#define IMOBILE_BANNER_PID3 	"34243"
#define IMOBILE_BANNER_MID3 "447293"
#define IMOBILE_BANNER_SID3 	"1480780"

//ミディアムレクタングルSHOWID="MID_RECT" ミディアムレクタングル(300x250 / 600x500)
#define IMOBILE_BANNER_PID2 	"34243"
#define IMOBILE_BANNER_MID2 "447293"
#define IMOBILE_BANNER_SID2 	"1480155"

class ImovileAd: public cocos2d::Ref {
protected:

	ImovileAd();
	virtual ~ImovileAd();
	bool init();

private:

public:

	bool adShowFlg = false; //一回でも広告が表示（広告が機能）しているかどうか？
	bool adClickFlg = false; //一回でも広告をクリックしたかどうか？
	bool adCloseFlg = false;

	void FstSet(); //ゲーム開始時に一回のみ実行する。
	bool txtFlg = false;
	bool instFlg = false;

	void SetObserver();

	void AdShowAction(Ref* psender);
	void AdClickAction(Ref* psender);
	void AdCloseAction(Ref* psender);

	CREATE_FUNC(ImovileAd)
	;
	void AdAllOff(); //全てのＡＤをオフにする。
	void AdShow(bool top_, bool down_, bool mid_, bool txt_, bool inst_, bool top2_);
	void AdShow(float dt);
	void AdShow_Frec(bool top_, bool down_, bool mid_, bool txt_, bool inst_, bool top2_); //時々表示
};

#endif // __HELLOWORLD_SCENE_H__
