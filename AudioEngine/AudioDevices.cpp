#include "AudioDevices.h"

AudioEngine::AudioDevices::AudioDevices()
{
    if(ma_context_init(nullptr, 0, nullptr, &m_context) != MA_SUCCESS)
    {
        throw std::exception("Failed to initialize context ! ");
    }
    ma_device_info* pPlaybackDeviceInfos;
    ma_uint32 playbackDeviceCount;
    ma_device_info* pCaptureDeviceInfos;
    ma_uint32 captureDeviceCount;
    ma_result result = ma_context_get_devices(&m_context, &pPlaybackDeviceInfos, &playbackDeviceCount, &pCaptureDeviceInfos, &captureDeviceCount);

    if (result != MA_SUCCESS) {
        throw std::exception("Devices not initialized! ");
    }

    printf("Playback Devices\n");
    for (ma_uint32 iDevice = 0; iDevice < playbackDeviceCount; ++iDevice) {
        m_playbackDeviceInfos.push_back(pPlaybackDeviceInfos[iDevice]);
    }

    printf("\n");

    printf("Capture Devices\n");
    for (ma_uint32 iDevice = 0; iDevice < captureDeviceCount; ++iDevice) {
        m_captureDeviceInfos.push_back(pCaptureDeviceInfos[iDevice]);
    }

}

std::vector<ma_device_info> AudioEngine::AudioDevices::GetPlaybackDevices() const
{
    return m_playbackDeviceInfos;
}

std::vector<ma_device_info> AudioEngine::AudioDevices::GetCaptureDevices() const
{
    return m_captureDeviceInfos;
}

AudioEngine::AudioDevices::~AudioDevices()
{
    ma_context_uninit(&m_context);
}
