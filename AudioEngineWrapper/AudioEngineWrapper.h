#pragma once

using namespace System;

#include "../AudioEngine/AudioEngine.h"
#include "AudioDevices.h"


namespace AudioEngineWrapper
{
	public enum class AudioStreategyType
	{
		Duplex = 0,
		Loopback,
		FilePlayback,
		SinWave,
		FilteredDuplexStrategy,
		LoopbackFilteredStrategy
	};

	public ref class AudioEngineService
	{
	public:
		AudioEngineService(size_t sampleRate, size_t maxBufferSize);

		void Start(const DeviceData^ playback, const DeviceData^ capture,String^ audioFilePath, AudioStreategyType type);
		void Stop();

		void ClearData();

		~AudioEngineService();
		!AudioEngineService();

		array<double>^ GetBuffer();

	internal:
		const std::vector<float>& GetLastBuffer();

	private:
		AudioEngine::FancyAudioEngine* engine;
	};
}
