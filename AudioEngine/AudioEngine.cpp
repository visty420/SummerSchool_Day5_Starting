#include "pch.h"

#include <exception>
#include "AudioEngine.h"
#include "DuplexStrategy.h"
#include "LoopbackStrategy.h"
#include "FilePlaybackStrategy.h"
#include "SinWaveStrategy.h"
#include "DuplexFilteredStrategy.h"
#include "LoopbackFilteredStrategy.h"

namespace AudioEngine
{
	FancyAudioEngine* _instance = nullptr;

	void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
	{
		_instance->callback(pDevice, pOutput, pInput, frameCount);
	}

	FancyAudioEngine::FancyAudioEngine(size_t sampleRate, size_t maxBufferSize) 
		: m_device(nullptr), m_maxBufferSize(maxBufferSize), m_strategy(nullptr), m_sampleRate(sampleRate), m_mutex()
	{
		_instance = this;
	}

	void FancyAudioEngine::Start(const ma_device_id* playback, const ma_device_id* capture,const std::string& audioFilePath, AudioStreategyType type )
	{
		switch (type)
		{
		case AudioEngine::AudioStreategyType::Duplex:
			m_strategy.reset(new DuplexStrategy());
			break;
		case AudioEngine::AudioStreategyType::Loopback:
			m_strategy.reset(new LoopbackStrategy());
			break;
		case AudioEngine::AudioStreategyType::FilePlayback:
			m_strategy.reset(new FilePlaybackStrategy());
			break;
		case AudioEngine::AudioStreategyType::SinWave:
			m_strategy.reset(new SinWaveStrategy());
			break;
		case AudioEngine::AudioStreategyType::DuplexFilteredStrategy:
			m_strategy.reset(new DuplexFilteredStrategy);
		case AudioEngine::AudioStreategyType::LoopbackFilteredStrategy:
			m_strategy.reset(new LoopbackFilteredStrategy());
		default:
			break;
		}

		AudioParameters params = { playback, capture, ma_format_f32, m_sampleRate, 1, data_callback , audioFilePath};

		m_buffers.clear();

		if (m_strategy->Init(params) == false)
		{
			throw std::exception("strategy not started!");
		}
	}

	void FancyAudioEngine::Stop()
	{
		m_strategy->Uninit();
	}

	void FancyAudioEngine::ClearBuffer()
	{
		m_mutex.Lock();

		if (m_buffers.size() > 0)
		{
			m_buffers.erase(m_buffers.begin());
		}

		m_mutex.Unlock();
	}

	const std::vector<float>& FancyAudioEngine::GetBufferData() noexcept
	{
		m_mutex.Lock();

		if (m_buffers.size() == 0)
		{
			m_buffers.emplace_back();
		}

		auto& result = m_buffers.front();

		if (result.size() < m_maxBufferSize)
		{
			result.resize(m_maxBufferSize);
		}

		m_mutex.Unlock();

		return result;
	}

	void FancyAudioEngine::callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
	{
		m_strategy->OnCallback(pDevice, pOutput, pInput, frameCount);

		auto size = ma_get_bytes_per_frame(pDevice->capture.format, pDevice->capture.channels);

		if (m_buffers.size() == 0)
		{
			m_buffers.emplace_back();
			m_buffers.back().reserve(m_maxBufferSize);
		}

		float* input = (float*)m_strategy->ChooseData(pInput, pOutput);

		for (size_t i = 0; i < frameCount; i++)
		{
			m_mutex.Lock();
			if (m_buffers.back().size() >= m_maxBufferSize)
			{
				m_buffers.emplace_back();
				m_buffers.back().reserve(m_maxBufferSize);
			}
			auto& currentBuffer = m_buffers.back();
			currentBuffer.push_back(input[i]);
			m_mutex.Unlock();
		}
	}
}