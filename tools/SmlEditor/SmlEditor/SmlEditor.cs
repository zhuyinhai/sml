using System;
using System.Collections.Generic;
using System.ComponentModel.Composition;
using System.IO;
using System.Linq;
using System.Windows.Forms;

using Sce.Atf;
using Sce.Atf.Adaptation;
using Sce.Atf.Applications;
using Sce.Atf.Controls.PropertyEditing;
using Sce.Atf.Controls.Timelines;
using Sce.Atf.Dom;

namespace SmlEditor
{
        /// <summary>
    /// Editor class that creates and saves timeline documents. 
    /// There is just one instance of this class in this application.
    /// It creates a D2dTimelineRenderer and D2dTimelineControl to render and display timelines.
    /// It registers this control with the hosting service so that the control appears in the Windows docking framework.
    /// This document client handles file operations, such as saving and closing a document, and
    /// handles application data persistence.</summary>
    [Export(typeof(IInitializable))]
    [PartCreationPolicy(CreationPolicy.Shared)]
    public class SmlEditor : IInitializable
    {
        [ImportingConstructor]
        public SmlEditor(
            IControlHostService controlHostService,
            ICommandService commandService,
            IContextRegistry contextRegistry,
            IDocumentRegistry documentRegistry,
            IDocumentService documentService,
            ISettingsService settingsService)
        {
        }

        #region IInitializable

        /// <summary>
        /// Finishes initializing component by setting up scripting service, subscribing to document
        /// events, and creating PropertyDescriptors for settings</summary>
        void IInitializable.Initialize()
        {
        }

        #endregion
    }
}
