#pragma once
#include "LoopbackStrategy.h"
#include "DigitalFilters.h"
namespace AudioEngine
{
	class LoopbackFilteredStrategy : public LoopbackStrategy
	{
		virtual void OnCallback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount) override;
	};
}

