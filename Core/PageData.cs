namespace Core;

public class PageData
{
    public Type? Type { get; init; }
    public string? Name { get; init; }
    public Type? ViewModelType { get; init; }
    public string? Icon { get; init; }
    public bool ShowSidePanel { get; init; } = true;
}
