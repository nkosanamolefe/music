#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qspinbox.h"
#include <QMainWindow>
#include <QStandardItemModel>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QTableView>
#include <QHeaderView>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void addItems();
    void updateRow(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QList<int> &roles);
    void deleteRow();

private:
    QStandardItemModel *model;
    QTableView *tableView;

    QLabel* titleLabel;
    QLabel* composerLabel;
    QLabel* albumTitleLabel;
    QLabel* replacementCostLabel;
    QLabel* ratingLabel;

    QLineEdit* composerLineEdit;
    QLineEdit* albumTitleLineEdit;
    QDoubleSpinBox* replacementCostLineEdit;
    QSpinBox* ratingLineEdit;

    QPushButton* addRecordButton;
    QPushButton* deleteRecordButton;

    QTextEdit* dataTextEdit;
};
#endif // MAINWINDOW_H
