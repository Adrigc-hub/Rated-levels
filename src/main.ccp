#include <Geode/Geode.hpp>
#include <Geode/modify/LevelBrowserLayer.hpp>

using namespace geode::prelude;

class $modify(MyCustomBrowser, LevelBrowserLayer) {
    bool init(GJSearchObject* search) {
        if (!LevelBrowserLayer::init(search)) return false;

        auto winSize = CCDirector::get()->getWinSize();
        auto menu = CCMenu::create();
        menu->setID("custom-layout-menu");
        this->addChild(menu);

        // --- BOTÓN DE METRO (EL MÁS ALTO) ---
        auto metroSprite = CCSprite::createWithSpriteFrameName("GJ_completesIcon_001.png"); 
        metroSprite->setColor({ 0, 255, 255 }); // Color Cian
        metroSprite->setScale(0.7f);

        auto metroBtn = CCMenuItemSpriteExtra::create(
            metroSprite, this, menu_selector(MyCustomBrowser::onMetro)
        );
        // El 80 lo hace estar más arriba
        metroBtn->setPosition({ -160, 80 }); 
        menu->addChild(metroBtn);

        // --- BOTÓN DE LAYOUTS ---
        auto layoutSprite = CCSprite::createWithSpriteFrameName("GJ_plainBtn_001.png");
        layoutSprite->setColor({ 255, 150, 0 }); // Color Naranja
        layoutSprite->setScale(0.6f);

        auto layoutBtn = CCMenuItemSpriteExtra::create(
            layoutSprite, this, menu_selector(MyCustomBrowser::onCustomLayouts)
        );
        // El 40 lo hace estar debajo del Metro
        layoutBtn->setPosition({ -160, 40 }); 
        menu->addChild(layoutBtn);

        return true;
    }

    void onMetro(CCObject* sender) {
        auto searchObj = GJSearchObject::create(SearchType::Featured); 
        auto scene = LevelBrowserLayer::scene(searchObj);
        CCDirector::get()->replaceScene(CCTransitionFade::create(0.5f, scene));
    }

    void onCustomLayouts(CCObject* sender) {
        auto searchObj = GJSearchObject::create(SearchType::Search, "Layout");
        auto scene = LevelBrowserLayer::scene(searchObj);
        CCDirector::get()->replaceScene(CCTransitionFade::create(0.5f, scene));
    }
};
