#include "GameEngine/AudioSystem.h"

using namespace GameEngine::Systems;
using namespace GameEngine::Components;

void AudioSystem::Execute(entt::registry& scene_registry)
{
	auto ui_audio_view = scene_registry.view<AudioComponent>();

	for (auto ui_audio_entity : ui_audio_view)
	{
		AudioComponent& audio = ui_audio_view.get<AudioComponent>(ui_audio_entity);

		if (audio.shouldPlayAudio == true && audio.isPlaying == false)
		{
			audio.isPlaying = true;
			audio.m_sound->play();
		}
		else if(audio.shouldPlayAudio == false && audio.isPlaying == true)
		{
			audio.isPlaying = false;
			audio.m_sound->stop();
		}
	}
}
