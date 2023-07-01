using AvaloniaFrontend.Models;

namespace AvaloniaFrontend.ViewModels;

public sealed class PlotViewModel : IPlotVM
{
    public string Title { get; init; } = string.Empty;

    public event Action<object, PlotData>? OnPlotChanged;

    public void UpdatePlot(PlotData data)
    {
        OnPlotChanged?.Invoke(this, data);
    }
}
