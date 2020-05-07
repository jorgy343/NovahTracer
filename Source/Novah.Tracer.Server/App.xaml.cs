using System.Windows;
using Novah.Tracer.Server.View;
using Novah.Tracer.Server.ViewModel;

namespace Novah.Tracer.Server
{
    public partial class App : Application
    {
        protected override void OnStartup(StartupEventArgs e)
        {
            base.OnStartup(e);

            ShellView shell = new ShellView();
            shell.DataContext = new ShellViewModel();

            Current.MainWindow = shell;
            Current.MainWindow.Show();
        }
    }
}