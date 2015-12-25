#ifndef RESOURCESID_H_
#define RESOURCESID_H_
//resource type
#include "Manager/ResourcesNameRole.h"

enum idSounds {
	//common
	SOUND_CLICK = TYPE_SOUND + SCENE_COMMON + STAGE_NONE + 1,
	//ready
	SOUND_MENUAUDIO = TYPE_SOUND + SCENE_MAINMENU + STAGE_NONE + 1,

	//gameplay - gameplay
	SOUND_READYAUDIO = TYPE_SOUND+SCENE_READY + STAGE_NONE + 1,
	SOUND_RUNBACK = TYPE_SOUND+SCENE_GAME + RUN_GAME + 1,
	SOUND_JUMP,
	SOUND_GYMBACK = TYPE_SOUND+SCENE_GAME + GYM_GAME + 1,
	SOUND_SHOTBACK = TYPE_SOUND+SCENE_GAME + SHOT_GAME + 1,
	SOUND_SHOT,
	//gameresult
	SOUND_RESULT = TYPE_SOUND + SCENE_GAMERESULT + STAGE_NONE + 1,
	SOUND_HALL,
};

#endif /* RESOURCESID_H_ */

