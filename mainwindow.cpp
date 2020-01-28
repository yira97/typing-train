#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <qfile.h>
#include <qfiledialog.h>
#include <qtextstream.h>
#include <qmessagebox.h>
#include <qstring.h>
#include <QKeyEvent>
#include <QtDebug>
#include <string>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFocusPolicy(Qt::StrongFocus);

    wrong_fmt.setForeground(QBrush(Qt::red));
    wrong_fmt.setFontWeight(QFont::DemiBold);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
}

void MainWindow::reset_clean_keymap_tab()
{
    current_file.clear();
    current_file_text.clear();
    ui->real_text_browser->clear();
    ui->your_input_edit->clear();
    this->update_filename_label();
}

void MainWindow::update_filename_label()
{
    ui->select_file_name_label->setText(this->current_file);
}

void MainWindow::on_select_file_btn_pressed()
{
    QString filename = QFileDialog::getOpenFileName(this, "open text");
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "warning", "can't open file: " + file.errorString());
        return;
    }
    this->reset_clean_keymap_tab();
    this->current_file = std::move(filename);
    ui->select_file_name_label->setText(this->current_file);
    QTextStream in(&file);
    current_file_text = in.readAll();
    ui->real_text_browser->setText(current_file_text);
    file.close();
}

void MainWindow::on_keymap_start_btn_pressed()
{
    ui->your_input_edit->clear();
}

void MainWindow::on_your_input_edit_textChanged()
{
    QString input{ui->your_input_edit->toPlainText()};
    if (input.length() == 0)
        return;

    ui->your_input_edit->blockSignals(true);
    QTextCursor cursor = ui->your_input_edit->textCursor();
    int old_pos = cursor.position();

    for (int i = 0; i < input.length() && i < current_file_text.length(); i++)
    {
        cursor.setPosition(i);
        cursor.deleteChar();
        input[i] == current_file_text[i] ? cursor.setCharFormat(right_fmt) : cursor.setCharFormat(wrong_fmt);
        cursor.insertText(QString(input[i]));
    }

    cursor.setPosition(old_pos);
    ui->your_input_edit->setTextCursor(cursor);
    ui->your_input_edit->blockSignals(false);
}
