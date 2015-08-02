#ifndef COMPOSITION_DIALOG_H
#define COMPOSITION_DIALOG_H

#include <QDialog>
namespace Ui {class CompositionDialog;};

class ItemComposition;

// -----------------------------------
//  CompositionDialog
// -----------------------------------
class CompositionDialog : public QDialog
{
	Q_OBJECT

public:
	explicit CompositionDialog(QWidget *parent = nullptr);
	virtual ~CompositionDialog(void);

	QString getName(void) const;

	void setComposition(ItemComposition* composition);

private slots:
	void onClickedOK(void);
	void onClickedCancel(void);

private:
	Ui::CompositionDialog *ui_;
	ItemComposition* composition_;
};

#endif // COMPOSITION_DIALOG_H
