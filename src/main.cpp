
#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/modify/EditorUI.hpp>

using namespace geode::prelude;

// ==========================================
// 1. ANIMACIÓN ÉPICA AL INSTALAR / INICIAR EL MOD
// ==========================================
class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        // Usamos una variable estática para asegurarnos de que la animación solo ocurra una vez por sesión
        static bool hasAnimatedThisSession = false;

        if (!hasAnimatedThisSession) {
            hasAnimatedThisSession = true;

            // Contenedor semi-transparente para oscurecer el fondo durante la intro
            auto winSize = CCDirector::sharedDirector()->getWinSize();
            auto bgOverlay = CCLayerColor::create(ccc4(0, 0, 0, 0));
            bgOverlay->setZOrder(105);
            this->addChild(bgOverlay);

            // Texto principal dorado
            auto titleText = CCLabelBMFont::create("¡MOD DE CURACIÓN ACTIVADO!", "goldFont.fnt");
            titleText->setPosition({winSize.width / 2, winSize.height / 2 + 30});
            titleText->setScale(0.0f); 
            bgOverlay->addChild(titleText);

            // Subtítulo descriptivo informativo
            auto subtitleText = CCLabelBMFont::create("Detección de Rated Layouts en línea", "chatFont.fnt");
            subtitleText->setPosition({winSize.width / 2, winSize.height / 2 - 20});
            subtitleText->setScale(0.0f);
            bgOverlay->addChild(subtitleText);

            // ---- ORQUESTACIÓN DE LA ANIMACIÓN ÉPICA ----
            bgOverlay->runAction(CCFadeTo::create(0.4f, 180));
            
            titleText->runAction(CCSequence::create(
                CCEaseElasticOut::create(CCScaleTo::create(0.8f, 1.3f), 0.5f),
                CCDelayTime::create(1.5f),
                CCEaseExponentialIn::create(CCScaleTo::create(0.4f, 0.0f)),
                nullptr
            ));

            subtitleText->runAction(CCSequence::create(
                CCDelayTime::create(0.2f),
                CCEaseElasticOut::create(CCScaleTo::create(0.8f, 1.0f), 0.5f),
                CCDelayTime::create(1.3f),
                CCEaseExponentialIn::create(CCScaleTo::create(0.4f, 0.0f)),
                CCCallFuncN::create(this, callfuncN_selector(MyMenuLayer::cleanupEpicAnimation)),
                nullptr
            ));
        }

        return true;
    }

    void cleanupEpicAnimation(CCNode* sender) {
        if (sender && sender->getParent()) {
            sender->getParent()->removeFromParentAndCleanup(true);
        }
    }
};

// ==========================================
// 2. DETECCIÓN DE MODS Y AJUSTE INTELIGENTE DE INTERFAZ
// ==========================================
class $modify(MyCustomRateLayer, LevelInfoLayer) {
    bool init(GJGameLevel* level, bool p1) {
        if (!LevelInfoLayer::init(level, p1)) return false;

        auto menu = this->getChildByID("left-side-menu");
        if (!menu) return true;

        // Intentar cargar el sprite personalizado desde disco
        auto buttonSprite = CCSprite::create("custom_rate_icon.png");
        if (!buttonSprite) {
            // Alternativa nativa si no pones ninguna imagen personalizada en los assets
            buttonSprite = CCSprite::createWithSpriteFrameName("GJ_starsIcon_001.png");
            buttonSprite->setColor({ 255, 140, 0 }); // Tinte naranja distintivo
        }

        auto myButton = CCMenuItemSpriteExtra::create(
            buttonSprite,
            this,
            menu_selector(MyCustomRateLayer::onMyCustomRateBtn)
        );
        myButton->setID("my-custom-rate-button");

        // Analiza de forma segura si la ID del mod "Rated Layouts" está cargada en el Loader actual
        bool hasRatedLayouts = Loader::get()->isModLoaded("alphalaneous.rated_layouts");

        if (hasRatedLayouts) {
            // Desplazar hacia abajo para evitar superposición exacta
            myButton->setPosition({ 0, -45 });
            log::info("[TeamMod] Colisión prevenida: Rated Layouts detectado.");
        } else {
            myButton->setPosition({ 0, 0 });
        }

        menu->addChild(myButton);
        menu->updateLayout();

        return true;
    }

    void onMyCustomRateBtn(CCObject* sender) {
        FLAlertLayer::create(
            "Estatus de Nivel", 
            "Este diseño cumple con las directrices base del equipo. Listo para revisión interna.", 
            "Cerrar"
        )->show();
    }
};

// ==========================================
// 3. GUÍA COMPLETA DE CURACIÓN INTERACTIVA EN EL EDITOR
// ==========================================
class $modify(MyEditorGuideline, EditorUI) {
    bool init(LevelEditorLayer* editor) {
        if (!EditorUI::init(editor)) return false;

        auto menu = this->getChildByID("undo-menu");
        if (!menu) return true;

        auto infoSprite = CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png");
        infoSprite->setScale(0.85f);
        infoSprite->setColor({ 122, 162, 247 }); // Tonalidad azul cyan tecnológico

        auto guideButton = CCMenuItemSpriteExtra::create(
            infoSprite,
            this,
            menu_selector(MyEditorGuideline::onOpenRateGuide)
        );
        guideButton->setID("team-rate-guide-btn");

        menu->addChild(guideButton);
        menu->updateLayout();

        return true;
    }

    void onOpenRateGuide(CCObject* sender) {
        std::string mensaje = 
            "<cg>GUÍA OFICIAL DE CURACIÓN (TEAM MOD)</c>\n\n"
            "<cy>1. Estructura y Layout:</c>\n"
            "Las estructuras deben ser legibles. Evitar transiciones ciegas y spam de orbes injustificado.\n\n"
            "<cy>2. Sincronización (Sync):</c>\n"
            "Los clics principales deben reaccionar directamente con los golpes fuertes de la música.\n\n"
            "<cy>3. Regulación de Dificultad:</c>\n"
            "Mantener un balance real. Si una sección es Insane, todo el layout debe mantenerse en ese rango.\n\n"
            "<co>Recuerda: Tu decisión representa los estándares de nuestro equipo.</c>";

        auto alert = FLAlertLayer::create("Panel de Criterios", mensaje, "Entendido");
        alert->show();
    }
};
