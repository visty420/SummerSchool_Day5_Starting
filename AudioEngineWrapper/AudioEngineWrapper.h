#pragma once

using namespace System;

#include "../AudioEngine/AudioEngine.h"

namespace AudioEngineWrapper
{
	public enum class AudioStreategyType
	{
		Duplex = 0,
		Loopback,
		FilePlayback,
		SinWave,
	};

	public ref class AudioEngineService
	{
	public:
		AudioEngineService(size_t sampleRate, size_t maxBufferSize);

		void Start(AudioStreategyType type);

		void Stop();

		void ClearData();

		~AudioEngineService();
		!AudioEngineService();

		array<double>^ GetBuffer();

	internal:
		std::vector<float> GetLastBuffer();

	private:
		AudioEngine::FancyAudioEngine* engine;
	};
}
