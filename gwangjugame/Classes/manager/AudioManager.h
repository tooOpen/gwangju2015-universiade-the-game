/*
 * AudioManager.h
 *
 *  Created on: 2014. 2. 7.
 *      Author: sjw
 */

#ifndef AudioManager_H_
#define AudioManager_H_

#include "SimpleAudioEngine.h"
#include "../ResourcesID.h" //after coordination rmove
using namespace CocosDenshion;



class AudioManager {
public:
	static AudioManager* getAudioManager()
		{
				if(!Audiomanager)
				{
					Audiomanager = new AudioManager();
				}
				return Audiomanager;
		}

	virtual ~AudioManager();
	void playEffectAudio(int id);
			void playSound(int id);
			void pauseSound();
			void stopSound();
			void resumeSound();
			bool isPlaySound();
			void setSFXvolume(float value);
			void preloadSound(int id);
			void clearSound(int id);

private:
	static AudioManager* Audiomanager;
	AudioManager();
};


#endif /* AudioManager_H_ */
