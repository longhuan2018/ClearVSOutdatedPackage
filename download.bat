cd /d "%~dp0"
vs_community.exe --layout "%~dp0\vs2019layout" --add Microsoft.VisualStudio.Workload.NativeDesktop --add Microsoft.VisualStudio.Component.VC.ATLMFC --add Microsoft.VisualStudio.Component.VC.CLI.Support --add Microsoft.VisualStudio.Component.VC.Modules.x86.x64 --add Microsoft.VisualStudio.Workload.VisualStudioExtension --add Component.GitHub.VisualStudio --add Microsoft.VisualStudio.Component.VC.v141.x86.x64 --add Microsoft.VisualStudio.Component.VC.v141.ATL --add Microsoft.VisualStudio.Component.VC.v141.MFC --add Microsoft.VisualStudio.Component.WinXP --add Microsoft.VisualStudio.Component.VC.v141.CLI.Support --add Microsoft.VisualStudio.Component.Windows10SDK --includeRecommended --lang zh-CN --lang en-US
ClearVSOutdatedPackage "%~dp0\vs2019layout"
vs_community.exe --layout "%~dp0\vs2019layout" --add Microsoft.VisualStudio.Workload.NativeDesktop --add Microsoft.VisualStudio.Component.VC.ATLMFC --add Microsoft.VisualStudio.Component.VC.CLI.Support --add Microsoft.VisualStudio.Component.VC.Modules.x86.x64 --add Microsoft.VisualStudio.Workload.VisualStudioExtension --add Component.GitHub.VisualStudio --add Microsoft.VisualStudio.Component.VC.v141.x86.x64 --add Microsoft.VisualStudio.Component.VC.v141.ATL --add Microsoft.VisualStudio.Component.VC.v141.MFC --add Microsoft.VisualStudio.Component.WinXP --add Microsoft.VisualStudio.Component.VC.v141.CLI.Support --add Microsoft.VisualStudio.Component.Windows10SDK --includeRecommended --lang zh-CN --lang en-US