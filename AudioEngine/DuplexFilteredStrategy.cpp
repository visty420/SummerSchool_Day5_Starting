#include "DuplexFilteredStrategy.h"

void AudioEngine::DuplexFilteredStrategy::OnCallback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
	const int kcut = 100;

	LowPassFilter filter(1. / pDevice->sampleRate, 2 * std::numbers::pi * kcut);

	for (int i = 0; i < frameCount; i++)
	{
		((float*)pInput)[i] = filter.update(((float*)pInput)[i]);
	}
	DuplexStrategy::OnCallback(pDevice, pOutput, pInput, frameCount);

}
