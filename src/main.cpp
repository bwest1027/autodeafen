#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include <Geode/ui/GeodeUI.hpp>
#include <Geode/Loader.hpp>
#include <Windows.h>
using namespace geode::prelude;

//Autodeafen
bool isActive = false;
class $modify(PlayLayer) {
	TodoReturn updateProgressbar(){
		int result = PlayLayer::getCurrentPercentInt();
		auto adEnabled = Mod::get()->getSettingValue<bool>("adEnabled");
		auto adPercent = Mod::get()->getSettingValue<int64_t>("adPercent");
		
		if (adEnabled) {
			if (result == adPercent && !isActive) {
			//log the result
			log::info("Autodeafen is active");
			
			// Simulate pressing the Page Up key
    		INPUT input;
    		input.type = INPUT_KEYBOARD;
 	   		input.ki.wScan = MapVirtualKey(VK_PRIOR, MAPVK_VK_TO_VSC); // Page Up key
    		input.ki.time = 0;
    		input.ki.dwFlags = KEYEVENTF_SCANCODE;
    		input.ki.wVk = VK_PRIOR;
    		input.ki.dwExtraInfo = GetMessageExtraInfo();

    		SendInput(1, &input, sizeof(INPUT));

    		// Simulate releasing the Page Up key
   	 		input.ki.dwFlags |= KEYEVENTF_KEYUP;
   			SendInput(1, &input, sizeof(INPUT));

			//set isActive to true
			isActive = true;
		}
		}
		
		//add return statement
		return;
	};

	TodoReturn levelComplete() {
		PlayLayer::levelComplete();
		//log that the level has been completed
		log::info("Level has been completed");
		if (isActive) {
			//log that the level has been completed with autodeafen active
			log::info("Level has been completed while autodeafen is active");
			// Simulate pressing the Page Up key
			INPUT input;
			input.type = INPUT_KEYBOARD;
 	   		input.ki.wScan = MapVirtualKey(VK_PRIOR, MAPVK_VK_TO_VSC); // Page Up key
			input.ki.time = 0;
			input.ki.dwFlags = KEYEVENTF_SCANCODE;
			input.ki.wVk = VK_PRIOR;
			input.ki.dwExtraInfo = GetMessageExtraInfo();

			SendInput(1, &input, sizeof(INPUT));

			// Simulate releasing the Page Up key
   	 		input.ki.dwFlags |= KEYEVENTF_KEYUP;
   			SendInput(1, &input, sizeof(INPUT));

			//set isActive to false
			isActive = false;
		}

		return;
	};

};

class $modify(PlayerObject) {
	TodoReturn playerDestroyed(bool p0) {
		PlayerObject::playerDestroyed(p0);
		//log that the player has been destroyed
		log::info("Player has been destroyed");
		if (isActive) {
			//log that the player has been destroyed with autodeafen active
			log::info("Player has been destroyed while autodeafen is active");
			// Simulate pressing the Page Up key
    		INPUT input;
    		input.type = INPUT_KEYBOARD;
 	   		input.ki.wScan = MapVirtualKey(VK_PRIOR, MAPVK_VK_TO_VSC); // Page Up key
    		input.ki.time = 0;
    		input.ki.dwFlags = KEYEVENTF_SCANCODE;
    		input.ki.wVk = VK_PRIOR;
    		input.ki.dwExtraInfo = GetMessageExtraInfo();

    		SendInput(1, &input, sizeof(INPUT));

    		// Simulate releasing the Page Up key
   	 		input.ki.dwFlags |= KEYEVENTF_KEYUP;
   			SendInput(1, &input, sizeof(INPUT));

			//set isActive to false
			isActive = false;
		}
		return;
	}
};


class $modify(ModifiedPauseLayer, PauseLayer) {
	void customSetup() {
		PauseLayer::customSetup();
			auto sprite = CCSprite::createWithSpriteFrameName("GJ_plainBtn_001.png");
			sprite->setScale(0.6f);

			auto icon = CCSprite::createWithSpriteFrameName("GJ_statsBtn_001.png");
			icon->setScale(0.95f);
			icon->setPosition(sprite->getContentSize()/2);
			sprite->addChild(icon);
			
			auto button = CCMenuItemSpriteExtra::create(
				sprite, 
				this, 
				menu_selector(ModifiedPauseLayer::openDISettings)
			);

			auto menu = this->getChildByID("right-button-menu");
			menu->addChild(button);
			menu->updateLayout();
		
	}	

	void openDISettings(CCObject*) {
		geode::openSettingsPopup(Mod::get());
	}
};