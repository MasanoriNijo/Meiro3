#include "AppDelegate.h"
//#include "HelloWorldScene.h"
#include "TitleScene.h"
#include "FstScene.h"
#include "TestScene.h"
#include "IMobileCocos2dxModule.h"
#include "SimpleAudioEngine.h"

//トップのアイコン、SHOWID="AD_ICON_TOP"
#define IMOBILE_ICON_PID 	"34243"
#define IMOBILE_ICON_MID 	"306001"
#define IMOBILE_ICON_SID 	"1021496"

//下のアイコン、SHOWID="AD_ICON_DOWN"
#define IMOBILE_ICON_PID2 	"34243"
#define IMOBILE_ICON_MID2 	"306001"
#define IMOBILE_ICON_SID2 	"1040050"

//真ん中のアイコン、SHOWID="AD_ICON_MID"
#define IMOBILE_ICON_PID3 	"34243"
#define IMOBILE_ICON_MID3 	"306001"
#define IMOBILE_ICON_SID3 	"1384470"

//フルスクリーンのインステSHOWID="FULL_INST"
#define IMOBILE_FULLSCREENAD_PID 	"34243"
#define IMOBILE_FULLSCREENAD_MID 	"306001"
#define IMOBILE_FULLSCREENAD_SID 	"1384469"

//テキストポプアップ、SHOWID="AD_TEXT"
#define IMOBILE_TEXTPOPUP_PID 	"34243"
#define IMOBILE_TEXTPOPUP_MID 	"306001"
#define IMOBILE_TEXTPOPUP_SID 	"1021470"

//上部バナー、"AD_BANNER"
#define IMOBILE_BANNER_PID 	"34243"
#define IMOBILE_BANNER_MID 	"306001"
#define IMOBILE_BANNER_SID 	"1039829"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() {
}

bool AppDelegate::applicationDidFinishLaunching() {
	// initialize director
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
		glview = GLView::create("My Game");
		director->setOpenGLView(glview);
	}
	glview->setDesignResolutionSize(720, 1280, ResolutionPolicy::SHOW_ALL);

	FileUtils::getInstance()->addSearchPath("images");
	FileUtils::getInstance()->addSearchPath("gcharactors");
	FileUtils::getInstance()->addSearchPath("sounds");
	FileUtils::getInstance()->addSearchPath("fonts");
	FileUtils::getInstance()->addSearchPath("merodeta");

	// turn on display FPS
	//director->setDisplayStats(true);

	// set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0 / 60);

	//ちらつき防止:falseにする。
	CCDirector::sharedDirector()->setDepthTest(false);

	//スプライトキャッシュを生成。
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("cources.plist");

	// create a scene. it's an autorelease object
	//auto scene = HelloWorld::createScene();
	//auto scene = TestScene::createScene();
	auto scene = FstScene::createScene();
	//auto scene = TitleScene::createScene();
	// run
	director->runWithScene(scene);

	/*
	//imobile広告表示
	//広告の取得、表示処理

	// トップアイコンの設定
	IMobileCocos2dxModule::registerSpotInline(IMOBILE_ICON_PID,
	IMOBILE_ICON_MID, IMOBILE_ICON_SID);
	// アイコン表示パラメータを作成します
	IMobileCocos2dxModuleIconParams iconParams;
	iconParams.iconTitleEnable = false;
	int adViewId_top = IMobileCocos2dxModule::show(IMOBILE_ICON_SID,
			IMobileCocos2dxModule::ICON, IMobileCocos2dxModule::CENTER,
			IMobileCocos2dxModule::TOP, iconParams);
	UserDefault::getInstance()->setIntegerForKey("AD_ICON_TOP", adViewId_top);
	IMobileCocos2dxModule::setVisibility(adViewId_top, false);

	// ダウンアイコンの設定
	IMobileCocos2dxModule::registerSpotInline(IMOBILE_ICON_PID2,
	IMOBILE_ICON_MID2, IMOBILE_ICON_SID2);
	int adViewId_down = IMobileCocos2dxModule::show(IMOBILE_ICON_SID2,
			IMobileCocos2dxModule::ICON, IMobileCocos2dxModule::CENTER,
			IMobileCocos2dxModule::BOTTOM, iconParams);
	UserDefault::getInstance()->setIntegerForKey("AD_ICON_DOWN", adViewId_down);
	IMobileCocos2dxModule::setVisibility(adViewId_down, false);


    // 中間アイコンの設定
    IMobileCocos2dxModule::registerSpotInline(IMOBILE_ICON_PID3, IMOBILE_ICON_MID3, IMOBILE_ICON_SID3);
    int adViewId_mid = IMobileCocos2dxModule::show(IMOBILE_ICON_SID, IMobileCocos2dxModule::ICON,
					        IMobileCocos2dxModule::CENTER, IMobileCocos2dxModule::MIDDLE, iconParams);
	UserDefault::getInstance()->setIntegerForKey("AD_ICON_MID", adViewId_mid);
	IMobileCocos2dxModule::setVisibility(adViewId_mid, false);


	// フルスクリーンインステ
	IMobileCocos2dxModule::registerSpotFullScreen(IMOBILE_FULLSCREENAD_PID,
			IMOBILE_FULLSCREENAD_MID, IMOBILE_FULLSCREENAD_SID);

	// テキストポップアップ
	IMobileCocos2dxModule::registerSpotFullScreen(IMOBILE_TEXTPOPUP_PID,
	IMOBILE_TEXTPOPUP_MID, IMOBILE_TEXTPOPUP_SID);


    // 上部バナー、"AD_BANNER"
    IMobileCocos2dxModule::registerSpotInline(IMOBILE_BANNER_PID, IMOBILE_BANNER_MID, IMOBILE_BANNER_SID);
    int adViewId_banar =IMobileCocos2dxModule::show(IMOBILE_BANNER_SID, IMobileCocos2dxModule::BANNER,
					        IMobileCocos2dxModule::CENTER, IMobileCocos2dxModule::TOP);
	UserDefault::getInstance()->setIntegerForKey("AD_BANNER", adViewId_banar);
	IMobileCocos2dxModule::setVisibility(adViewId_banar, false);
*/
	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();

	// if you use SimpleAudioEngine, it must be pause
	// SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();

	// if you use SimpleAudioEngine, it must resume here
	// SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
