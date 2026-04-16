class $modify(MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        // 1. Obtener tamaño de ventana
        auto winSize = CCDirector::sharedDirector()->getWinSize();

        // 2. Crear el sprite del botón
        auto sprite = CCSprite::createWithSpriteFrameName("GJ_playBtn_001.png");
        sprite->setScale(0.5f);

        // 3. Crear el botón con una función 
        auto btn = CCMenuItemSpriteExtra::create(
            sprite, 
            this, 
            menu_selector(MenuLayer::onMoreGames)
        );

        // 4. Crear menú y posicionar
        auto menu = CCMenu::create();
        menu->setPosition({ winSize.width / 2, (winSize.height / 2) + 80.f });

        menu->addChild(btn);
        this->addChild(menu);

        return true;
} 
;}