using System;
using System.Collections.Generic;
using System.ComponentModel.Composition;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using Sce.Atf;
using Sce.Atf.Adaptation;
using Sce.Atf.Applications;
using Sce.Atf.Controls.PropertyEditing;

namespace SmlEditor
{
    [Export(typeof(IInitializable))]
    [PartCreationPolicy(CreationPolicy.Shared)]
    public class TextureListEditor : IInitializable, IControlHostClient
    {
        [ImportingConstructor]
        public TextureListEditor(
            IControlHostService controlHostService,
            ICommandService commandService,
            IContextRegistry contextRegistry
            )
        {
            m_controlHostService = controlHostService;
            m_commandService = commandService;
            m_contextRegistry = contextRegistry;
        }

        

        #region IInitializable Members

        void IInitializable.Initialize()
        {
            m_listView = new ListView();
            m_listView.SmallImageList = ResourceUtil.GetImageList16();
            m_listView.AllowDrop = true;
            m_listView.MultiSelect = false;
            m_listView.AllowColumnReorder = true;
            m_listView.LabelEdit = true;
            m_listView.Dock = DockStyle.Fill;

            m_controlInfo = new ControlInfo(
                "Textures".Localize(),
                "Textures for sml".Localize(),
                StandardControlGroup.Left);

            m_controlHostService.RegisterControl(m_listView, m_controlInfo, this);
        }

        #endregion


        #region IControlHostClient Members

        void IControlHostClient.Activate(Control control)
        {}

        void IControlHostClient.Deactivate(Control control)
        {}

        bool IControlHostClient.Close(Control control)
        {
            return true;
        }

        #endregion

        private void listView_MouseUp(object sender, MouseEventArgs e)
        { }

        private void listView_DragOver(object sender, DragEventArgs e)
        { }
        
        private void listView_DragDrop(object sender, DragEventArgs e)
        { }




        private IControlHostService m_controlHostService;
        private ICommandService m_commandService;
        private IContextRegistry m_contextRegistry;
        private ListView m_listView;
        private ListViewAdapter m_listViewAdapter;
        private ControlInfo m_controlInfo;
    }
}
