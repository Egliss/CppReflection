using System;
using System.ComponentModel.Design;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using CppReflection.Reflector;
using Egliss.CppReflection;
using EnvDTE;
using EnvDTE80;
using Microsoft.VisualStudio.Shell;
using Microsoft.VisualStudio.Shell.Interop;
using Task = System.Threading.Tasks.Task;

namespace CppReflection
{
    /// <summary>
    /// Command handler
    /// </summary>
    internal sealed class CppReflectionWindowCommand
    {
        public const int CommandId = 0x0100;
        public static readonly Guid CommandSet = new Guid("20e86c39-0bd8-46e6-8151-1d18aa9dff79");
        private static readonly string OutputPaneName = "CppReflection";
        private readonly AsyncPackage package;
        public static CppReflectionWindowCommand Instance { get; private set; }
        public DTE2 DteObject { get; private set; }
        private OutputWindowPane _outputPane;
        public OutputWindowPane OutputPane
        {
            get
            {
                if (this.DteObject == null)
                    return null;

                var panes = this.DteObject.ToolWindows.OutputWindow.OutputWindowPanes;
                this._outputPane = this._outputPane ?? panes.Add(OutputPaneName);
                return _outputPane;
            }
        }
        private Microsoft.VisualStudio.Shell.IAsyncServiceProvider ServiceProvider => this.package;

        private CppReflectionWindowCommand(AsyncPackage package, OleMenuCommandService commandService)
        {
            this.package = package ?? throw new ArgumentNullException(nameof(package));
            commandService = commandService ?? throw new ArgumentNullException(nameof(commandService));

            // メニュー要素を構築して登録
            var menuCommandID = new CommandID(CommandSet, CommandId);
            var menuItem = new MenuCommand(this.Execute, menuCommandID);
            commandService.AddCommand(menuItem);
        }

        public static async Task InitializeAsync(AsyncPackage package)
        {
            await ThreadHelper.JoinableTaskFactory.SwitchToMainThreadAsync(package.DisposalToken);

            // VisualStudioが持つサービスを引っ張る
            var commandService = (await package.GetServiceAsync(typeof(IMenuCommandService))) as OleMenuCommandService;

            Instance = new CppReflectionWindowCommand(package, commandService);
        }

        private void Execute(object sender, EventArgs e)
        {
            ThreadHelper.JoinableTaskFactory.Run(async delegate
            {
                await ThreadHelper.JoinableTaskFactory.SwitchToMainThreadAsync();

                // TODO 遅延で取らないとnullになる
                if ((this.DteObject = (await package.GetServiceAsync(typeof(DTE))) as DTE2) == null)
                    return;

                // ソリューションの情報を引っ張る
                SolutionNode node = SolutionNode.Create(this.DteObject);
                var project = node.FindProjectByName("ComponentSystem");
                if (project == null)
                {
                    Instance.OutputPane.OutputString("ProjectName'ComponentSystem' not found");
                    return;
                }

                // プロジェクトをお好みの形で加工する
                var baseComponentName = "Egliss::ComponentSystem::Component";
                var vcClasses = project.RootNode
                    .FindAllOf<ClassNode>();
                var baseComponent = vcClasses.Where(m => m.FullName == "global::" + baseComponentName).FirstOrDefault();
                if (baseComponent == null)
                {
                    Instance.OutputPane.OutputString($"the class({baseComponentName}) not found");
                    return;
                }
                var components = vcClasses
                    .Where(m => m.VCClass.IsDerivedFrom[baseComponentName])
                    .ToList();
                if (components.Count == 0)
                {
                    Instance.OutputPane.OutputString($"{baseComponentName}'s child class not found");
                    return;
                }

                var tree = TypeDeriverTree.MakeTree(components, baseComponent);
                var description = TypeDescription.CreateDescription(tree);
                var directory = Path.GetDirectoryName(project.Project.FileName);
                ClassExporter.OutputCppFile(description, $"{directory}\\Source\\Reflection\\DynamicType.cpp");
                ClassExporter.OutputInlineFile(description, $"{directory}\\Source\\Reflection\\StaticType.inl");
            });
        }
    }
}
