#ifndef OKTABLESTARITEM_H
#define OKTABLESTARITEM_H

#include <QTableWidgetItem>

class okTableStarItem : public QTableWidgetItem
{
public:
    okTableStarItem();
	void setChecked(bool checked);
	void toggle();
	bool isChecked() const;
	bool operator< (const QTableWidgetItem& other) const;

private:
	bool checkState;
};

#endif // OKTABLESTARITEM_H
