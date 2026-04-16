#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        // 1. Obtener el tamaño de la ventana para posicionamiento relativo
        auto winSize = CCDirector::sharedDirector()->getWinSize();

        // 2. Crear el sprite de tu botón (puedes usar uno existente del juego)
        auto sprite = CCSprite::createWithSpriteFrameName("GJ_playBtn_001.png"); // Cambia por tu icono
        sprite->setScale(0.5f);

        // 3. Crear el botón con una función (callback)
        auto btn = CCMenuItemSpriteExtra::create(
            sprite, this, menu_selector(MenuLayer::onMoreGames) // Cambia onMoreGames por tu función
        );

        // 4. Crear un menú para contener el botón
        auto menu = CCMenu::create();
        
        // POSICIONAMIENTO: Aquí es donde lo subes
        // winSize.width / 2 es el centro horizontal
        // winSize.height / 2 + 50 lo sube 50 unidades arriba del centro
        menu->setPosition({ winSize.width / 2, (winSize.height / 2) + 80.f });
        
        menu->addChild(btn);
        this->addChild(menu);

        return true;
    }
};