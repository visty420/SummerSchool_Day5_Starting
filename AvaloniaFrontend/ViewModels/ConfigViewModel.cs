using Avalonia.Controls;
using AvaloniaFrontend.Services;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;

namespace AvaloniaFrontend.ViewModels;

public partial class ConfigViewModel : ObservableObject
{
    public SelectedDevices SelectedDevices { get; }

    private readonly Window _window;

    public ConfigViewModel(SelectedDevices selectedDevices, Window window)
    {
        SelectedDevices = selectedDevices;
        _window = window;
    }

    [RelayCommand]
    private async Task ShowFilePicker()
    {
        var saveFileDialog = new SaveFileDialog
        {
            Title = "Save File",
            DefaultExtension = "wav",
            Filters = new List<FileDialogFilter>
        {
            new FileDialogFilter { Name = "Wav Files", Extensions = new List<string> { "wav" } },
            new FileDialogFilter { Name = "All Files", Extensions = new List<string> { "*" } }
        }
        };

        var result = await saveFileDialog.ShowAsync(_window);

        if (result != null)
        {
            SelectedDevices.FilePath = result;
        }

    }
}
