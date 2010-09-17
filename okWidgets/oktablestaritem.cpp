#include "oktablestaritem.h"

okTableStarItem::okTableStarItem()
{
	QIcon icon;
	icon.addFile(QString::fromUtf8(":/tango/images/icons/tango/star_checked.png"), QSize(16, 16), QIcon::Normal, QIcon::On);

	setIcon(icon);
	//this->setFlags();
	setChecked(false);
}

bool okTableStarItem::operator<(const QTableWidgetItem& other) const
{
	okTableStarItem* temp = (okTableStarItem*) &other;
	return ((int) isChecked() < (int) temp->isChecked());
}

void okTableStarItem::setChecked(bool checked)
{
	checkState = checked;
	if(checked)
	{
		setFlags(Qt::ItemIsEnabled);
	}
	else
	{
		setFlags(!Qt::ItemIsEnabled);
	}
}

void okTableStarItem::toggle()
{
	setChecked(!isChecked());
}

bool okTableStarItem::isChecked() const
{
	return checkState;
}
