#pragma once
#include <vector>
#include "ImportExport.h"
#include "miniaudio.h"

namespace AudioEngine
{
	class AUDIOENGINE_API AudioDevices
	{
	public:
		AudioDevices();
		const std::vector<ma_device_info>& GetPlaybackDevices() const;
		const std::vector<ma_device_info>& GetCaptureDevices() const;
		~AudioDevices();

	private:
		ma_context m_context;
		std::vector<ma_device_info> m_playbackDeviceInfos;
		std::vector<ma_device_info> m_captureDeviceInfos;
	};

}
