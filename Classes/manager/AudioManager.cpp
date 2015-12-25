/*
 * AudioManager.cpp
 *
 *  Created on: 2014. 6. 1.
 *      Author: pc
 */

#include "AudioManager.h"
#include "../ResourcesID.h"

AudioManager::AudioManager() {
	// TODO Auto-generated constructor stub
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.4);
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.4f);
}

AudioManager::~AudioManager() {
	// TODO Auto-generated destructor stub
}

AudioManager* AudioManager::Audiomanager;

void AudioManager::playEffectAudio(int id){
	switch(id){
	case SOUND_CLICK:
		SimpleAudioEngine::sharedEngine()->playEffect("common/sounds/buttonclick.ogg");
		break;
	case SOUND_JUMP:
			SimpleAudioEngine::sharedEngine()->playEffect("runnergameScene/sounds/jump.ogg");
			break;
	case SOUND_RESULT:
		SimpleAudioEngine::sharedEngine()->playEffect("common/sounds/result.ogg");
		break;
	case SOUND_SHOT:
			SimpleAudioEngine::sharedEngine()->playEffect("shootinggameScene/sounds/shot.ogg");
			break;
	default:

		break;
	}

}
void AudioManager::playSound(int id){
	switch(id){
	case SOUND_MENUAUDIO:
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("menuScene/sounds/menuback.mp3",true);
		break;
	case SOUND_RUNBACK:
			SimpleAudioEngine::sharedEngine()->playBackgroundMusic("runnergameScene/sounds/runback.mp3",true);
			break;
	case SOUND_GYMBACK:
			SimpleAudioEngine::sharedEngine()->playBackgroundMusic("gymnasticgameScene/sounds/gymback.mp3",true);
			break;
	case SOUND_SHOTBACK:
			SimpleAudioEngine::sharedEngine()->playBackgroundMusic("shootinggameScene/sounds/shotback.mp3",true);
			break;
	case SOUND_READYAUDIO:
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("readyScene/sounds/readyBackground.mp3",true);
		break;
	case SOUND_HALL:
			SimpleAudioEngine::sharedEngine()->playBackgroundMusic("wintable/sounds/halloffame.mp3",true);
			break;
	default:
		break;
	}
}
void AudioManager::pauseSound(){
	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}
void AudioManager::stopSound(){
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}
void AudioManager::resumeSound(){
	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
void AudioManager::preloadSound(int id){

}
void AudioManager::clearSound(int id){

}
bool AudioManager::isPlaySound(){
return SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying();
}
void AudioManager::setSFXvolume(float value)
{
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(value/10.0);
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(value/10.0);
}

