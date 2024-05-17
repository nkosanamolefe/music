#include "mainwindow.h"
#include <QStringList>
#include <QList>
#include <QColor>
#include <QMessageBox>
#include "rating.h"
#include <QTableView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    // Create model and set headers
    model = new QStandardItemModel(this);
    QStringList headerRow;
    headerRow << "Composer" << "Album title" << "Replacement cost" << "Rating";
    model->setHorizontalHeaderLabels(headerRow);

    // Create table view and set model
    tableView = new QTableView(this);
    tableView->setModel(model);
    tableView->setSortingEnabled(true);
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->setItemDelegateForColumn(3, new Rating(this));

    // Create labels and line edits for input fields
    composerLabel = new QLabel("Composer:", this);
    albumTitleLabel = new QLabel("Album title:", this);
    replacementCostLabel = new QLabel("Replacement cost:", this);
    ratingLabel = new QLabel("Rating:", this);

    composerLineEdit = new QLineEdit(this);
    albumTitleLineEdit = new QLineEdit(this);
    replacementCostLineEdit = new QDoubleSpinBox(this);
    replacementCostLineEdit->setDecimals(2);
    replacementCostLineEdit->setRange(0.0, 999.99);
    ratingLineEdit = new QSpinBox(this);
    ratingLineEdit->setRange(0, 100);

    // Create buttons
    addRecordButton = new QPushButton("Add", this);
    deleteRecordButton = new QPushButton("Delete", this);

    // Connect signals and slots
    connect(addRecordButton, &QPushButton::clicked, this, &MainWindow::addItems);
    connect(deleteRecordButton, &QPushButton::clicked, this, &MainWindow::deleteRow);
    connect(model, &QAbstractTableModel::dataChanged, this, &MainWindow::updateRow);

    // Layout for headings and input fields
    QGridLayout* headingLayout = new QGridLayout;
    headingLayout->addWidget(composerLabel,0,0);
    headingLayout->addWidget(composerLineEdit,1,0);
    headingLayout->addWidget(albumTitleLabel,0,1);
    headingLayout->addWidget(albumTitleLineEdit,1,1);
    headingLayout->addWidget(replacementCostLabel,0,2);
    headingLayout->addWidget(replacementCostLineEdit,1,2);
    headingLayout->addWidget(ratingLabel,0,3);
    headingLayout->addWidget(ratingLineEdit,1,3);
    headingLayout->addWidget(addRecordButton,1,4);
    headingLayout->addWidget(tableView,2,0,2,5);
    headingLayout->addWidget(deleteRecordButton,4,4);

    // Create main layout for the window
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(headingLayout);

    // Create central widget and set main layout
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}

void MainWindow::addItems()
{
    // Get values from input fields
    QString composer = composerLineEdit->text();
    QString album = albumTitleLineEdit->text();
    float price = replacementCostLineEdit->value();
    int rating = ratingLineEdit->value();

    // Input validation
    if (composer.isEmpty() || album.isEmpty() || price < 0 || rating < 0 || rating > 100) {
        QMessageBox::warning(this, "Invalid Input", "Please enter valid data for all fields.");
        return;
    }

    // Reset input fields
    composerLineEdit->clear();
    albumTitleLineEdit->clear();
    replacementCostLineEdit->setValue(00.0);
    ratingLineEdit->setValue(0);
    composerLineEdit->setFocus();

    // Add data to the model
    QList<QStandardItem*> row;
    row << new QStandardItem(composer) << new QStandardItem(album)
        << new QStandardItem(QString::number(price, 'f', 2)) << new QStandardItem(QString::number(rating));
    model->appendRow(row);

    // Highlight the newly added row
    tableView->selectRow(model->rowCount() - 1);
}

void MainWindow::updateRow(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QList<int> &roles)
{
    // Get the row number
    int row = topLeft.row();

    // Check if any of the changed roles are Qt::DisplayRole
    if (roles.contains(Qt::DisplayRole)) {
        // Get the price value from the model
        float price = model->item(row, 2)->data(Qt::DisplayRole).toFloat();
        QColor color = (price >= 200) ? Qt::red : Qt::white;

        // Update the background color of all items in the row
        for (int col = 0; col < 4; col++) {
            model->item(row, col)->setBackground(color);
        }
    }
}

void MainWindow::deleteRow()
{
    QModelIndex index = tableView->currentIndex();
    if (!index.isValid()) {
        return;
    }

    if (QMessageBox::Yes == QMessageBox::warning(this, "Delete row", "Are you sure?", QMessageBox::Yes | QMessageBox::No)) {
        model->removeRow(index.row());
    }
}

MainWindow::~MainWindow()
{
}
