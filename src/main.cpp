class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        // ... tu código anterior ...

        auto myButton = CCMenuItemSpriteExtra::create(
            buttonSprite, 
            this, 
            menu_selector(MyMenuLayer::onMyCustomButton) // Cambiado aquí
        );

        // ... resto del código ...
        return true;
    }

    // Tu nueva función
    void onMyCustomButton(CCObject* sender) {
        FLAlertLayer::create(
            "¡Hola!", 
            "Este es un botón personalizado creado con <cr>Geode</c>.", 
            "OK"
        )->show();
    }
};
