#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;

class $modify(MyPauseLayer, PauseLayer) {
    void customSetup() {
        PauseLayer::customSetup();
        this->addLevelInfoButton();
    }
    
    void addLevelInfoButton() {
        auto buttonSprite = CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png");
        
        auto levelInfoButton = CCMenuItemSpriteExtra::create(
            buttonSprite,
            this,
            menu_selector(MyPauseLayer::onLevelInfoButton)
        );
        
        auto menu = this->getChildByID("left-button-menu");
        if (menu) {
            menu->addChild(levelInfoButton);
            menu->updateLayout();
        }
    }
    
    void onLevelInfoButton(CCObject* sender) {
        auto playLayer = PlayLayer::get();
        if (!playLayer || !playLayer->m_level) return;
        
        auto infoLayer = LevelInfoLayer::create(playLayer->m_level, false);
        if (infoLayer) {
            auto scene = CCDirector::sharedDirector()->getRunningScene();
            scene->addChild(infoLayer, 10000);
            infoLayer->onInfo(nullptr);
        }
    }
};
