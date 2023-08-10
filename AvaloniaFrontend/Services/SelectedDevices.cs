using AudioEngineWrapper;
using CommunityToolkit.Mvvm.ComponentModel;

namespace AvaloniaFrontend.Services;

public partial class SelectedDevices : ObservableObject
{

    public SelectedDevices()
    {
        using AudioDevices audioDevices = new();
        PlaybackDevices = audioDevices.GetPlaybackDevices();
        CaptureDevices = audioDevices.GetCaptureDevices();

        SelectedPlayback = PlaybackDevices.First(x => x.IsDefault);
        SelectedCapture = CaptureDevices.First(x => x.IsDefault);
    }
    public DeviceData[] CaptureDevices { get; }
    public DeviceData[] PlaybackDevices { get; }

    [ObservableProperty] private DeviceData _selectedPlayback;
    [ObservableProperty] private DeviceData _selectedCapture;
}
