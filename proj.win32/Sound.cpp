#include "Sound.h"
#include "Global.h"

Sound::Sound(){}
Sound::~Sound(){}

bool Sound::init()
{
	//预加载音乐及音效文件
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("background1.wav");
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("background0.wav");
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("background2.wav");

	//SimpleAudioEngine::sharedEngine()->preloadEffect("hit_button.WAV");
	return true;
}

//播放音乐
void Sound::play_bgmusic(int scene_number)
{
	if (global->getMusicPause())
	{
		return;
	}
	switch (scene_number)
	{
	case 0:
		/*if (b_change_state == true)
		{*/
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background0.wav", true);
		/*} else{}*/
		break;
	case 1:
		/*if (b_change_state == true)
		{*/
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background1.wav", true);
		/*} else{}*/
		break;
	case 2:
		/*if (b_change_state == true)
		{*/
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background3.wav", true);
		/*} else{}*/
		break;
	default:
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background0.wav", true);
	}

}

//播放音效
//void Sound::play_effect()
//{
//	if (global->getSoundPause())
//	{
//		return;
//	}
//
//	SimpleAudioEngine::sharedEngine()->playEffect("hit_button.WAV");
//}

//暂停音乐
void Sound::pause_bgmusic()
{
	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

//暂停播放音效
//void Sound::pause_all_effects()
//{
//	SimpleAudioEngine::sharedEngine()->pauseAllEffects();
//}

//恢复播放音乐
void Sound::resume_bgmusic()
{
	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

//恢复播放所有音效
//void Sound::resume_all_effects()
//{
//	SimpleAudioEngine::sharedEngine()->resumeAllEffects();
//}

//停止播放音乐
void Sound::stop_bgmusic()
{
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}

////停止播放所有音效
//void Sound::stop_all_effects()
//{
//	SimpleAudioEngine::sharedEngine()->stopAllEffects();
//}

//释放SimpleAudioEngin所占用资源
void Sound::release_sound()
{
	void end();
}

//设置音量大小
void Sound::set_bg_volume(float s)
{
	float setBackgroundMusicVolume(s);
}

//获得音量大小
float Sound::get_bg_volume()
{
	return SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume();
}