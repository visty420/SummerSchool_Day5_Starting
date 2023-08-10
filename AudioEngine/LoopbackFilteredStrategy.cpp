#include "LoopbackFilteredStrategy.h"

void AudioEngine::LoopbackFilteredStrategy::OnCallback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
	const int kcut = 100;
	LowPassFilter filter(1. / pDevice->sampleRate, 2 * std::numbers::pi * kcut);
	for (int index = 0; index < frameCount; index++)
	{
		((float*)pInput)[index] = filter.update(((float*)pInput)[index]);
	}
	LoopbackStrategy::OnCallback(pDevice, pOutput, pInput, frameCount);
}
