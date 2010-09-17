#include "savedialog.h"
#include "ui_savedialog.h"

savedialog::savedialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::savedialog)
{
    ui->setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	QRegExp rx("[a-zA-Z0-9 ._-]+");
	QValidator *validator = new QRegExpValidator(rx, this);
	ui->lineEdit->setValidator(validator);

	checkIfCanBeSaved("");

	connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(checkIfCanBeSaved(QString)));

	connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(checkIfCanBeSaved()));
	connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

savedialog::~savedialog()
{
    delete ui;
}

QString savedialog::fileName()
{
	return QApplication::applicationDirPath() + "/playlists/" + ui->lineEdit->text() + ".m3u";
}

void savedialog::checkIfCanBeSaved()
{
	if(QFile::exists(fileName()))
	{
		int answer = QMessageBox::question(this,
							  "Playlist already exists",
							  "Playlist with such name already exists. Replace?",
							  QMessageBox::Yes, QMessageBox::No
							  );
		if(answer == QMessageBox::Yes) accept();
	}
	else accept();
}

void savedialog::checkIfCanBeSaved(QString text)
{
	int pos = 10;
	bool valid = (ui->lineEdit->validator()->validate(text, pos) == QValidator::Acceptable);
	ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(valid && (text.count() != 0));
}
