#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qstring.h>
#include <QTextCharFormat>
// #include <vector>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void on_select_file_btn_pressed();

    void on_keymap_start_btn_pressed();

    void on_your_input_edit_textChanged();

private:
    Ui::MainWindow *ui;
    QString current_file{};
    QString current_file_text{};
    void reset_clean_keymap_tab();
    void update_filename_label();
    QTextCharFormat wrong_fmt;
    QTextCharFormat right_fmt;
};
#endif // MAINWINDOW_H
