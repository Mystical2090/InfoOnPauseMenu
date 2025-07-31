#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>

using namespace geode::prelude;

class $modify(MyPlayLayer, PlayLayer) {
    CCMenuItemSpriteExtra* m_levelInfoButton = nullptr;
    
    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects)) {
            return false;
        }
        
        this->addLevelInfoButton();
        return true;
    }
    
    void addLevelInfoButton() {
        auto buttonSprite = CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png");
        buttonSprite->setScale(0.8f);

        m_levelInfoButton = CCMenuItemSpriteExtra::create(
            buttonSprite,
            this,
            menu_selector(MyPlayLayer::onLevelInfoButton)
        );

        auto winSize = CCDirector::sharedDirector()->getWinSize();
        m_levelInfoButton->setPosition({50.0f, winSize.height - 50.0f});

        auto menu = CCMenu::create();
        menu->addChild(m_levelInfoButton);
        menu->setPosition({0, 0});

        this->addChild(menu,9999);
    }
    
    void onLevelInfoButton(CCObject* sender) {
        auto level = this->m_level;
        if (!level) return;

        auto infoLayer = LevelInfoLayer::create(level, false);
        if (infoLayer) {
            auto scene = CCDirector::sharedDirector()->getRunningScene();
            scene->addChild(infoLayer, 1000);
        }
    }

    void onQuit() {
        PlayLayer::onQuit();
    }
};

class $modify(MyLevelInfoLayer, LevelInfoLayer) {
    bool init(GJGameLevel* level, bool challenge) {
        if (!LevelInfoLayer::init(level, challenge)) {
            return false;
        }

        return true;
    }
};
