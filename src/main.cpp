#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        // Run the original init() first
        if (!MenuLayer::init()) return false;

        auto winSize = CCDirector::sharedDirector()->getWinSize();

        // 1. Create the button sprite
        // Using a standard sprite frame name from the game's sheets
        auto sprite = CCSprite::createWithSpriteFrameName("GJ_playBtn_001.png");
        sprite->setScale(0.5f);

        // 2. Create the button
        // menu_selector is fine, but Geode also supports modern lambda callbacks!
        auto btn = CCMenuItemSpriteExtra::create(
            sprite, 
            this, 
            menu_selector(MenuLayer::onMoreGames) // Reusing an existing function
        );

        // 3. Create the menu container
        // It's better to add the button to the existing 'main-menu' 
        // or create a new CCMenu to handle layout/touch priority.
        auto menu = CCMenu::create();
        menu->setPosition({ winSize.width / 2, (winSize.height / 2) + 80.f });
        menu->setID("my-custom-menu"_spr); // Good practice for compatibility with other mods

        menu->addChild(btn);
        this->addChild(menu);

        return true;
    }
};
