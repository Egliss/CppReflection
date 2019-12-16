using EnvDTE;
using EnvDTE80;
using Microsoft.VisualStudio.Shell;
using Microsoft.VisualStudio.VCCodeModel;
using Newtonsoft.Json;
using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;

namespace Egliss.CppReflection
{
    /// <summary>
    /// スコープの要素として振舞うインターフェース
    /// </summary>
    public interface IScopeElement
    {
        string Name { get; set; }
        string FullName { get; }
        IScope ParentScope { get; set; }
    }
    /// <summary>
    /// 型として振舞うインターフェース
    /// </summary>
    public interface ITypeElement : IScopeElement
    {
    }
    /// <summary>
    /// <see cref="IScopeElement"/>を内包できるインターフェース
    /// </summary>
    public interface IScope : IScopeElement, IEnumerable<IScopeElement>
    {
        void AddElement(IScopeElement element);
        void RemoveElement(IScopeElement element);
        IScope FindScope(string Name);
        bool ExistScope(string Name);
    }
    /// <summary>
    /// <see cref="VCCodeElement"/>を持つインターフェース
    /// </summary>
    public interface IVCElement
    {
        VCCodeElement VCElement { get; set; }
    }

    /// <summary>
    /// <see cref="IScope"/>の実装<para/>
    /// スコープ化可能なオブジェクトはこのクラスから派生する
    /// </summary>
    public class Scope : IScope
    {
        public string Name { get; set; }
        public string FullName
        {
            get
            {
                if (ParentScope == null)
                    return Name;
                else
                    return ParentScope.FullName + "::" + Name;
            }
        }
        public IScope ParentScope { get; set; }
        public void AddElement(IScopeElement element)
        {
            this.elements.Add(element);
            element.ParentScope = this;
        }
        public void RemoveElement(IScopeElement element)
        {
            this.elements.Remove(element);
            element.ParentScope = null;
        }
        public bool ExistScope(string scopeName)
        {
            foreach (var item in this.elements.OfType<IScope>())
            {
                if (item.Name == scopeName)
                    return true;
            }
            return false;
        }
        public IScope FindScope(string scopeName)
        {
            foreach (var item in this.elements.OfType<IScope>())
            {
                if (item.Name == scopeName)
                    return item;
            }
            return null;
        }

        /// <summary>
        /// スコープ内に指定のスコープが存在するかをチェックします
        /// スコープ名はScope1::Scope2::Scope3 にように::を使うと階層として認識されます
        /// </summary>
        /// <param name="scopeFullName">スコープ名</param>
        /// <returns></returns>
        public bool ExistScopeByFullName(string scopeFullName)
        {
            if (scopeFullName.Length == 0)
                return false;

            var scopes = scopeFullName.Split(new string[] { "::" }, StringSplitOptions.None);

            foreach (var item in this.elements.OfType<IScope>())
            {
                if (item.Name == scopes.First())
                {
                    if (scopes.Length == 1)
                        return true;
                    else
                        return ExistScopeByFullName(scopeFullName.Remove(0, scopes.First().Length + 1));
                }
            }
            return false;
        }

        public IScope FindScopeByFullName(string scopeFullName)
        {
            if (scopeFullName.Length == 0)
                return null;

            var scopes = scopeFullName.Split(new string[] { "::" }, StringSplitOptions.None);

            foreach (var item in this.elements.OfType<IScope>())
            {
                if (item.Name == scopes.First())
                {
                    if (scopes.Count() == 1)
                        return item;
                    else
                    {
                        var nextScope = string.Join("::", scopes.Skip(1).ToArray());
                        return ((Scope)item).FindScopeByFullName(nextScope);
                    }
                }
            }
            return null;
        }

        public IScopeElement FindElement<T>(string Name) where T : IScopeElement
        {
            foreach (var item in this.elements.OfType<T>())
            {
                if (item.Name == Name)
                    return item;
            }
            return null;
        }
        protected List<IScopeElement> elements = new List<IScopeElement>();

        public IEnumerable<T> FindAllOf<T>()
        {
            foreach (var item in this.OfType<T>())
            {
                yield return item;
            }

            foreach (var item in this.OfType<Scope>())
            {
                var ar = item.FindAllOf<T>();
                foreach (var item2 in ar)
                {
                    yield return item2;
                }
            }
        }

        public IEnumerator<IScopeElement> GetEnumerator()
        {
            foreach (var item in this.elements)
                yield return item;
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return this.GetEnumerator();
        }
    }

    public class SolutionNode
    {
        public string Name { get; set; }
        public Solution Solution { get; private set; }
        public IEnumerable<ProjectNode> Projects => this.Solution.Projects.OfType<Project>().Select(m => ProjectNode.Create(m));
        public static SolutionNode Create(DTE2 dte2)
        {
            return new SolutionNode()
            {
                Solution = dte2.Solution,
                Name = dte2.Solution.FullName,
            };
        }
        public ProjectNode FindProjectByName(string name)
        {
            var project = this.Solution.Projects.OfType<Project>()
                .Where(m => m.Name == name)
                .FirstOrDefault();

            if (project == null)
                return null;
            return ProjectNode.Create(project);
        }
    }
    /// <summary>
    /// プロジェクトそのものを表すノード<para/>
    /// RootNodeは"global::"というnamespaceを仮想的に作成し、そこに要素を展開している
    /// </summary>
    public class ProjectNode
    {
        public string Name { get; set; }
        public NamespaceNode RootNode { get; private set; }
        public Project Project { get; private set; }
        public VCCodeElement VCElement { get; set; }
        public IEnumerable<T> FindAllOf<T>()
        {
            foreach (var item in this.RootNode.OfType<T>())
                yield return item;

            foreach (var item in this.RootNode.OfType<Scope>())
            {
                var ar = item.FindAllOf<T>();
                foreach (var item2 in ar)
                    yield return item2;
            }
        }

        public static ProjectNode Create(Project project)
        {
            ThreadHelper.ThrowIfNotOnUIThread();

            //make project 
            ProjectNode node = new ProjectNode();
            node.Name = project.Name;
            node.Project = project;
            //make root namespace
            node.RootNode = new NamespaceNode();
            node.RootNode.Name = "global";
            string path = Path.GetDirectoryName(project.FileName);

            foreach (ProjectItem item in project.ProjectItems)
            {
                string fileName = item.FileNames[1];
                var fileDirectory = Path.GetDirectoryName(fileName);
                var fileExtension = Path.GetExtension(fileName);

                // header only 
                if (fileExtension != ".h" && fileExtension != ".hpp" && fileExtension != ".inl")
                    continue;
                if (fileDirectory.IndexOf(path) == -1)
                    continue;
                if (item.FileCodeModel == null)
                    continue;

                foreach (VCCodeElement element in item.FileCodeModel.CodeElements)
                {
                    AssigneElement(path, element, node.RootNode);
                }
            }
            return node;
        }
        public static void AssigneElement(string baseDirectory, VCCodeElement element, IScope parent)
        {
            if (element == null)
                return;
            var name = element.FullName;

            IScope scope = parent;
            switch (element.Kind)
            {
                case vsCMElement.vsCMElementClass:
                {
                    var item = element as VCCodeClass;
                    scope = parent.FindScope(item.Name);

                    if (scope != null)
                        break;

                    var classNode = new ClassNode();
                    classNode.Name = item.Name;
                    classNode.VCElement = element;
                    foreach (VCCodeElement baseClass in item.Bases)
                    {
                        classNode.ParentClasses.Add(baseClass.Name);
                    }
                    scope = classNode;
                    parent.AddElement(scope);
                    break;
                }
                case vsCMElement.vsCMElementNamespace:
                {
                    var item = element as VCCodeNamespace;
                    scope = parent.FindScope(item.Name);

                    if (scope != null)
                        break;

                    scope = new NamespaceNode();
                    ((NamespaceNode)scope).VCElement = element;
                    scope.Name = item.Name;
                    parent.AddElement(scope);
                    break;
                }
                case vsCMElement.vsCMElementEnum:
                case vsCMElement.vsCMElementFunction:
                case vsCMElement.vsCMElementParameter:
                case vsCMElement.vsCMElementVariable:
                    return;

                default:
                    break;
            }

            var ex = element.Children.OfType<VCCodeClass>()
                .Select(m => m.FullName)
                .ToList();
            foreach (VCCodeElement item in element.Children)
            {
                AssigneElement(baseDirectory, item, scope);
            }
        }
    }
    public class NamespaceNode : Scope, IVCElement
    {
        public IEnumerable<ClassNode> Classes => this.elements.OfType<ClassNode>();
        public IEnumerable<ValueNode> Values => this.elements.OfType<ValueNode>();
        public IEnumerable<NamespaceNode> Namespaces => this.elements.OfType<NamespaceNode>();

        [JsonIgnore]
        public VCCodeElement VCElement { get; set; }
        [JsonIgnore]
        public VCCodeNamespace VCNamespace => VCElement as VCCodeNamespace;
    }
    public class ClassNode : Scope, ITypeElement, IVCElement
    {
        public List<string> ParentClasses { get; private set; } = new List<string>();
        public IEnumerable<ClassNode> InnerClasses => this.elements.OfType<ClassNode>();
        public IEnumerable<ValueNode> Values => this.elements.OfType<ValueNode>();
        [JsonIgnore]
        public VCCodeElement VCElement { get; set; }
        [JsonIgnore]
        public VCCodeClass VCClass => VCElement as VCCodeClass;
    }
    public class ValueNode : IScopeElement, IVCElement
    {
        public string Name { get; set; }
        public string FullName
        {
            get
            {
                if (ParentScope == null)
                    return Name;
                else
                    return ParentScope.FullName + "." + Name;
            }
        }
        public IScope ParentScope { get; set; }
        [JsonIgnore]
        public VCCodeElement VCElement { get; set; }
        [JsonIgnore]
        public VCCodeVariable VCValue => VCElement as VCCodeVariable;
    }
    public class DeclaredTypeNode : ITypeElement, IVCElement
    {
        public string Name { get; set; }
        public string FullName
        {
            get
            {
                if (ParentScope == null)
                    return Name;
                else
                    return ParentScope.FullName + "." + Name;
            }
        }
        public string UndeclName { get; set; }
        [JsonIgnore]
        public IScope ParentScope { get; set; }
        [JsonIgnore]
        public VCCodeElement VCElement { get; set; }
    }
}