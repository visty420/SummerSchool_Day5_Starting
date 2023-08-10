using AvaloniaFrontend.Services;

namespace AvaloniaFrontend.ViewModels;

public class ConfigViewModel
{
    public SelectedDevices SelectedDevices { get; }
    public ConfigViewModel(SelectedDevices selectedDevices)
    {
        SelectedDevices = selectedDevices;
    }
}
