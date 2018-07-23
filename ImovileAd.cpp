#include "ImovileAd.h"
#include "IMobileCocos2dxModule.h"

ImovileAd::ImovileAd() {
}

ImovileAd::~ImovileAd() {

	IMobileCocos2dxModule::removeObserver(this, IMobileCocos2dxModule::DID_CLICK, IMOBILE_TEXTPOPUP_SID);
	IMobileCocos2dxModule::removeObserver(this, IMobileCocos2dxModule::DID_CLICK, IMOBILE_FULLSCREENAD_MID);
	IMobileCocos2dxModule::removeObserver(this, IMobileCocos2dxModule::DID_SHOW, IMOBILE_TEXTPOPUP_SID);
	IMobileCocos2dxModule::removeObserver(this, IMobileCocos2dxModule::DID_SHOW, IMOBILE_FULLSCREENAD_MID);
	IMobileCocos2dxModule::removeObserver(this, IMobileCocos2dxModule::DID_CLOSE, IMOBILE_TEXTPOPUP_SID);
	IMobileCocos2dxModule::removeObserver(this, IMobileCocos2dxModule::DID_CLOSE, IMOBILE_FULLSCREENAD_MID);
}

bool ImovileAd::init() {

//特に何もしない。

	return true;

}

void ImovileAd::FstSet() {
	//ゲーム開始時に一回のみ実行する。
	//imobile広告表示
	//広告の取得、表示処理

	// トップアイコンの設定
	IMobileCocos2dxModule::registerSpotInline(IMOBILE_ICON_PID,
	IMOBILE_ICON_MID, IMOBILE_ICON_SID);
	// アイコン表示パラメータを作成します
	IMobileCocos2dxModuleIconParams iconParams;
	iconParams.iconTitleEnable = false;
	int adViewId_top = IMobileCocos2dxModule::show(IMOBILE_ICON_SID, IMobileCocos2dxModule::ICON,
			IMobileCocos2dxModule::CENTER, IMobileCocos2dxModule::TOP, iconParams);
	UserDefault::getInstance()->setIntegerForKey("AD_ICON_TOP", adViewId_top);
	IMobileCocos2dxModule::setVisibility(adViewId_top, false);

	// ダウンアイコンの設定
	IMobileCocos2dxModule::registerSpotInline(IMOBILE_ICON_PID2,
	IMOBILE_ICON_MID2, IMOBILE_ICON_SID2);
	int adViewId_down = IMobileCocos2dxModule::show(IMOBILE_ICON_SID2, IMobileCocos2dxModule::ICON,
			IMobileCocos2dxModule::CENTER, IMobileCocos2dxModule::BOTTOM, iconParams);
	UserDefault::getInstance()->setIntegerForKey("AD_ICON_DOWN", adViewId_down);
	IMobileCocos2dxModule::setVisibility(adViewId_down, false);

	// フルスクリーンインステ
	IMobileCocos2dxModule::registerSpotFullScreen(IMOBILE_FULLSCREENAD_PID,
	IMOBILE_FULLSCREENAD_MID, IMOBILE_FULLSCREENAD_SID);

	instFlg = true;
	// テキストポップアップ
	IMobileCocos2dxModule::registerSpotFullScreen(IMOBILE_TEXTPOPUP_PID,
	IMOBILE_TEXTPOPUP_MID, IMOBILE_TEXTPOPUP_SID);
	txtFlg = true;

	// 上部バナー、"AD_BANNER"
	IMobileCocos2dxModule::registerSpotInline(IMOBILE_BANNER_PID, IMOBILE_BANNER_MID, IMOBILE_BANNER_SID);
	int adViewId_banar = IMobileCocos2dxModule::show(IMOBILE_BANNER_SID, IMobileCocos2dxModule::BANNER,
			IMobileCocos2dxModule::CENTER, IMobileCocos2dxModule::TOP);
	UserDefault::getInstance()->setIntegerForKey("AD_BANNER", adViewId_banar);
	IMobileCocos2dxModule::setVisibility(adViewId_banar, false);

	// 下部バナー、"AD_BANNER"
	IMobileCocos2dxModule::registerSpotInline(IMOBILE_BANNER_PID3, IMOBILE_BANNER_MID3, IMOBILE_BANNER_SID3);
	int adViewId_banar2 = IMobileCocos2dxModule::show(IMOBILE_BANNER_SID3, IMobileCocos2dxModule::BANNER,
			IMobileCocos2dxModule::CENTER, IMobileCocos2dxModule::BOTTOM);
	UserDefault::getInstance()->setIntegerForKey("AD_BANNER2", adViewId_banar2);
	IMobileCocos2dxModule::setVisibility(adViewId_banar2, false);

	//ミデイアムレクタングル
	// スポット情報を設定します
	IMobileCocos2dxModule::registerSpotInline(IMOBILE_BANNER_PID2, IMOBILE_BANNER_MID2, IMOBILE_BANNER_SID2);

	// 広告の表示位置を指定して表示します(画面中央下)
	int midiam_rect = IMobileCocos2dxModule::show(IMOBILE_BANNER_SID, IMobileCocos2dxModule::MEDIUM_RECTANGLE,
			IMobileCocos2dxModule::CENTER, IMobileCocos2dxModule::BOTTOM);
	UserDefault::getInstance()->setIntegerForKey("MID_RECT", midiam_rect);
	IMobileCocos2dxModule::setVisibility(midiam_rect, false);

}

void ImovileAd::AdShow(bool top_, bool down_, bool mid_, bool txt_, bool inst_, bool top2_) {
//広告の表示操作する。
//広告を表示する
	IMobileCocos2dxModule::setVisibility(UserDefault::getInstance()->getIntegerForKey("AD_ICON_TOP"), top_);
//	IMobileCocos2dxModule::setVisibility(UserDefault::getInstance()->getIntegerForKey("AD_ICON_DOWN"), down_);
	IMobileCocos2dxModule::setVisibility(UserDefault::getInstance()->getIntegerForKey("AD_BANNER2"), down_);
	IMobileCocos2dxModule::setVisibility(UserDefault::getInstance()->getIntegerForKey("MID_RECT"), mid_);

	IMobileCocos2dxModule::setVisibility(UserDefault::getInstance()->getIntegerForKey("AD_BANNER"), top2_);

	if (txt_) {
		IMobileCocos2dxModule::show(IMOBILE_TEXTPOPUP_SID);
	}
	if (inst_) {
		IMobileCocos2dxModule::show(IMOBILE_FULLSCREENAD_SID);
	}

}

void ImovileAd::AdShow_Frec(bool top_, bool down_, bool mid_, bool txt_, bool inst_, bool top2_) {
//広告の表示操作する。
//広告を表示する
	IMobileCocos2dxModule::setVisibility(UserDefault::getInstance()->getIntegerForKey("AD_ICON_TOP"), top_);
	//	IMobileCocos2dxModule::setVisibility(UserDefault::getInstance()->getIntegerForKey("AD_ICON_DOWN"), down_);
	IMobileCocos2dxModule::setVisibility(UserDefault::getInstance()->getIntegerForKey("AD_BANNER2"), down_);
	IMobileCocos2dxModule::setVisibility(UserDefault::getInstance()->getIntegerForKey("MID_RECT"), mid_);
	IMobileCocos2dxModule::setVisibility(UserDefault::getInstance()->getIntegerForKey("AD_BANNER"), top2_);

	int rndx = arc4random() % static_cast<int>(4);

	if (rndx == 0) {

		if (txt_) {
			IMobileCocos2dxModule::show(IMOBILE_TEXTPOPUP_SID);
		}
		if (inst_) {
			IMobileCocos2dxModule::show(IMOBILE_FULLSCREENAD_SID);
		}
	}
}
void ImovileAd::AdAllOff() {
	//全てのＡＤをオフにする。
	this->AdShow(false, false, false, false, false, false);

}

void ImovileAd::AdShow(float dt) {

}

void ImovileAd::SetObserver() {
	const char *str0 = "ImovileAd::SetObserver()";
	log("%s", str0);
	// 広告が表示された際に呼び出される処理の登録
	IMobileCocos2dxModule::addObserver(this, IMobileCocos2dxModule::DID_SHOW,
	IMOBILE_TEXTPOPUP_SID, callfuncO_selector(ImovileAd::AdShowAction));

	// 広告がクリックされた際に呼び出される処理の登録
	IMobileCocos2dxModule::addObserver(this, IMobileCocos2dxModule::DID_CLICK,
	IMOBILE_TEXTPOPUP_SID, callfuncO_selector(ImovileAd::AdClickAction));

	// 広告が閉じられた際に呼び出される処理の登録
	IMobileCocos2dxModule::addObserver(this, IMobileCocos2dxModule::DID_CLOSE,
	IMOBILE_TEXTPOPUP_SID, callfuncO_selector(ImovileAd::AdCloseAction));

	// 広告が表示された際に呼び出される処理の登録
	IMobileCocos2dxModule::addObserver(this, IMobileCocos2dxModule::DID_SHOW,
	IMOBILE_FULLSCREENAD_SID, callfuncO_selector(ImovileAd::AdShowAction));

	// 広告がクリックされた際に呼び出される処理の登録
	IMobileCocos2dxModule::addObserver(this, IMobileCocos2dxModule::DID_CLICK,
	IMOBILE_FULLSCREENAD_SID, callfuncO_selector(ImovileAd::AdClickAction));

	// 広告が閉じられた際に呼び出される処理の登録
	IMobileCocos2dxModule::addObserver(this, IMobileCocos2dxModule::DID_CLOSE,
	IMOBILE_FULLSCREENAD_SID, callfuncO_selector(ImovileAd::AdCloseAction));

}

void ImovileAd::AdShowAction(Ref* psender) {
	const char *str0 = "ImovileAd::AdShowAction";
	log("%s", str0);
	this->adShowFlg = true;
}
void ImovileAd::AdClickAction(Ref* psender) {
	const char *str0 = "ImovileAd::AdClickAction";
	log("%s", str0);
	this->adClickFlg = true;
}
void ImovileAd::AdCloseAction(Ref* psender) {
	const char *str0 = "ImovileAd::AdCloseAction";
	log("%s", str0);
	this->adCloseFlg = true;
}
