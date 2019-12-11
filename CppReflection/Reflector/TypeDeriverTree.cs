using Egliss.CppReflection;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CppReflection.Reflector
{
    public static class TypeDeriverTree
    {
        public static TypeDeriverTreeNode MakeTree(IEnumerable<ClassNode> nodes, ClassNode parent)
        {
            TypeDeriverTreeNode parentNode = new TypeDeriverTreeNode();
            parentNode.Own = parent;
            foreach (var item in nodes)
            {
                if (item.ParentClasses.Any(m => m == parent.Name))
                    parentNode.Childs.Add(MakeTree(nodes, item));
            }
            return parentNode;
        }
    }
    public class TypeDeriverTreeNode
    {
        public ClassNode Own { get; set; }
        public List<TypeDeriverTreeNode> Childs { get; } = new List<TypeDeriverTreeNode>();
    }
}
