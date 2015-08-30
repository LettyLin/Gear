#include "Sound.h"
#include "Global.h"

Sound::Sound(){}
Sound::~Sound(){}

bool Sound::init()
{
	//Ԥ�������ּ���Ч�ļ�
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("background1.wav");
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("background0.wav");
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("background2.wav");

	//SimpleAudioEngine::sharedEngine()->preloadEffect("hit_button.WAV");
	return true;
}

//��������
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

//������Ч
//void Sound::play_effect()
//{
//	if (global->getSoundPause())
//	{
//		return;
//	}
//
//	SimpleAudioEngine::sharedEngine()->playEffect("hit_button.WAV");
//}

//��ͣ����
void Sound::pause_bgmusic()
{
	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

//��ͣ������Ч
//void Sound::pause_all_effects()
//{
//	SimpleAudioEngine::sharedEngine()->pauseAllEffects();
//}

//�ָ���������
void Sound::resume_bgmusic()
{
	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

//�ָ�����������Ч
//void Sound::resume_all_effects()
//{
//	SimpleAudioEngine::sharedEngine()->resumeAllEffects();
//}

//ֹͣ��������
void Sound::stop_bgmusic()
{
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}

////ֹͣ����������Ч
//void Sound::stop_all_effects()
//{
//	SimpleAudioEngine::sharedEngine()->stopAllEffects();
//}

//�ͷ�SimpleAudioEngin��ռ����Դ
void Sound::release_sound()
{
	void end();
}

//����������С
void Sound::set_bg_volume(float s)
{
	float setBackgroundMusicVolume(s);
}

//���������С
float Sound::get_bg_volume()
{
	return SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume();
}