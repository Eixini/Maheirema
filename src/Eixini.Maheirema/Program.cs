using System;

using Avalonia;

namespace Eixini.Maheirema;

public class Program {
    /// <summary>
    /// Avalonia configuration, don't remove; also used by visual designer
    /// </summary>
    /// <returns>
    /// Configured platform-specific services
    /// </returns>
    public static AppBuilder BuildAvaloniaApp() {
        return AppBuilder.Configure<App>()
            .UsePlatformDetect()
            .LogToTrace();
    }

    /// <summary>
    /// Initialization code. Don't use any Avalonia, third-party APIs or any
    /// SynchronizationContext-reliant code before AppMain is called: things aren't initialized
    /// yet and stuff might break
    /// </summary>
    /// <param name="args">
    /// Application arguments
    /// </param>
    [STAThread]
    public static void Main(string[] args) {
        BuildAvaloniaApp().StartWithClassicDesktopLifetime(args);
    }
}
