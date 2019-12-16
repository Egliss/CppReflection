using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CppReflection.Reflector
{
    //write to cpp 
    public class TypeDescription
    {
        public int Id { get; set; }
        public int ParentId { get; set; }
        public string Name { get; set; }
        public string FullName { get; set; }
        public bool IsNotAbstract { get; set; }
        public List<int> ParentChain { get; set; } 

        public string File { get; set; }
        public int Indent { get; set; } = 0;

        public static List<TypeDescription> CreateDescription(TypeTreeNode node)
        {
            var descritopns = new List<TypeDescription>();
            CreateDescription(ref descritopns, node, -1);
            return descritopns;
        }

        private static void CreateDescription(ref List<TypeDescription> descriptors, TypeTreeNode node, int parentId, int indent = 0)
        {
            TypeDescription desc = new TypeDescription();
            desc.Name = node.Node.Name;
            desc.FullName = node.Node.FullName.Replace("global::", "");
            desc.ParentId = parentId;
            desc.Id = descriptors.Count;
            desc.Indent = indent;
            desc.File = node.Node.VCClass.File;
            desc.IsNotAbstract = !node.Node.VCClass.IsAbstract;
            descriptors.Add(desc);

            foreach (var item in node.Childs)
            {
                CreateDescription(ref descriptors, item, desc.Id, indent + 1);
            }

            MakeParentChain(ref descriptors, desc);
        }

        private static void MakeParentChain(ref List<TypeDescription> descriptions, TypeDescription node)
        {
            node.ParentChain = new List<int>();
            var activeNode = node;

            while (true)
            {
                node.ParentChain.Add(activeNode.Id);
                if (activeNode.ParentId == -1)
                    break;

                activeNode = descriptions[activeNode.ParentId];
            }
        }
    }
}
