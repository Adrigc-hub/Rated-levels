#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        auto winSize = CCDirector::get()->getWinSize();

        // 1. Crear el sprite del botón (puedes cambiar "GJ_playBtn_001.png" por otro)
        auto sprite = CCSprite::createWithSpriteFrameName("GJ_playBtn_001.png");
        sprite->setScale(0.6f);

        // 2. Crear el botón con una función (lambda) que se ejecuta al tocarlo
        auto btn = CCMenuItemSpriteExtra::create(
            sprite,
            this,
            menu_selector(MyMenuLayer::onMyCustomButtonClick)
        );

        // 3. Buscar el menú principal de Geode para que sea compatible con otros mods
        auto menu = this->getChildByID("main-menu");
        
        if (menu) {
            menu->addChild(btn);
            btn->setID("rated-layouts-btn"_spr); // ID único
            menu->updateLayout(); // Reorganiza los botones automáticamente
        }

        return true;
    }

    // Función que se ejecuta al tocar el botón
    void onMyCustomButtonClick(CCObject* sender) {
        FLAlertLayer::create(
            "Rated Layouts",    // Título
            "¡El botón funciona!", // Mensaje
            "OK"                // Botón de cerrar
        )->show();
    }
};
