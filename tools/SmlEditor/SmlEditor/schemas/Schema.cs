// -------------------------------------------------------------------------------------------------------------------
// Generated code, do not edit
// Command Line:  DomGen "Sml.xsd" "Schema.cs" "Sml" "SmlEditor"
// -------------------------------------------------------------------------------------------------------------------

using System;
using System.Collections.Generic;

using Sce.Atf.Dom;

namespace SmlEditor
{
    public static class Schema
    {
        public const string NS = "Sml";

        public static void Initialize(XmlSchemaTypeCollection typeCollection)
        {
            Initialize((ns,name)=>typeCollection.GetNodeType(ns,name),
                (ns,name)=>typeCollection.GetRootElement(ns,name));
        }

        public static void Initialize(IDictionary<string, XmlSchemaTypeCollection> typeCollections)
        {
            Initialize((ns,name)=>typeCollections[ns].GetNodeType(name),
                (ns,name)=>typeCollections[ns].GetRootElement(name));
        }

        private static void Initialize(Func<string, string, DomNodeType> getNodeType, Func<string, string, ChildInfo> getRootElement)
        {
            textureSequenceType.Type = getNodeType("Sml", "textureSequenceType");
            textureSequenceType.textureChild = textureSequenceType.Type.GetChildInfo("texture");

            textureType.Type = getNodeType("Sml", "textureType");
            textureType.nameAttribute = textureType.Type.GetAttributeInfo("name");
            textureType.pathAttribute = textureType.Type.GetAttributeInfo("path");

            textureSeuenceRootElement = getRootElement(NS, "textureSeuence");
        }

        public static class textureSequenceType
        {
            public static DomNodeType Type;
            public static ChildInfo textureChild;
        }

        public static class textureType
        {
            public static DomNodeType Type;
            public static AttributeInfo nameAttribute;
            public static AttributeInfo pathAttribute;
        }

        public static ChildInfo textureSeuenceRootElement;
    }
}
