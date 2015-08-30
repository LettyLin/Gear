#ifndef SOUND_H_
#define SOUND_H_
#include <SimpleAudioEngine.h>
#include <cocos2d.h>
using namespace cocos2d;
using namespace CocosDenshion;

class Sound
{
public:
	Sound();
	~Sound();
	virtual bool init();

	static void play_bgmusic(int scene_number);
	static void play_effect();

	static void pause_bgmusic();
	static void pause_all_effects();

	static void resume_bgmusic();
	static void resume_all_effects();


	static void stop_bgmusic();
	static void stop_all_effects();

	static void release_sound();

	static void set_bg_volume(float s);
	static float get_bg_volume();

	/*static bool b_change_state;*/

};

#endif