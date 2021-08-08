#include "GameEngine/AudioSystem.h"

using namespace GameEngine::Systems;
using namespace GameEngine::Components;

void AudioSystem::Execute(entt::registry& scene_registry)
{
	auto ui_audio_view = scene_registry.view<AudioComponent>();

	for (auto ui_audio_entity : ui_audio_view)
	{
		AudioComponent& audio = ui_audio_view.get<AudioComponent>(ui_audio_entity);

		if (audio.shouldPlayAudio && audio.m_sound->getStatus() != sf::SoundSource::Status::Playing)
		{
			audio.m_sound->play();
		}
		else
		{
			audio.m_sound->stop();
		}
		audio.shouldPlayAudio = false;
	}
}
