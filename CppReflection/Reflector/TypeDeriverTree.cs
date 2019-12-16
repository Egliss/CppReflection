using Egliss.CppReflection;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public static class TypeDeriverTree
{
    public static TypeTreeNode MakeTree(IEnumerable<ClassNode> nodes, ClassNode parent)
    {
        TypeTreeNode parentNode = new TypeTreeNode();
        parentNode.Node = parent;
        foreach (var item in nodes)
        {
            if (item.ParentClasses.Any(m => m == parent.Name))
                parentNode.Childs.Add(MakeTree(nodes, item));
        }
        return parentNode;
    }
}
public class TypeTreeNode
{
    public ClassNode Node { get; set; }
    public List<TypeTreeNode> Childs { get; } = new List<TypeTreeNode>();
}
