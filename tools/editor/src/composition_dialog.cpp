
#include "composition_dialog.h"
#include "ui_composition_dialog.h"

// -----------------------------------
//  CompositionDialog
// -----------------------------------
CompositionDialog::CompositionDialog(QWidget *parent)
	: QDialog(parent)
	, composition_(nullptr)
{
	ui_ = new Ui::CompositionDialog();
	ui_->setupUi(this);

	connect( ui_->okButton, SIGNAL(clicked()),this, SLOT(onClickedOK()));
	connect( ui_->cancelButton, SIGNAL(clicked()), this, SLOT(onClickedCancel()));
}

CompositionDialog::~CompositionDialog()
{
	::SafeDelete(ui_);
}

QString CompositionDialog::getName(void) const
{
	return ui_->nameEdit->text();
}

void CompositionDialog::setComposition(ItemComposition* composition)
{
	composition_ = composition;
}

void CompositionDialog::onClickedOK(void)
{
	accept();
	if( composition_ )
	{
	}
}

void CompositionDialog::onClickedCancel(void)
{
	reject();
}