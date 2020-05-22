#include "mask.h"
#include "ui_mask.h"
#include <QStringList>
#include <iostream>

Mask::Mask(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Mask)
{
    ui->setupUi(this);
    init();
    initAlphaBeta();
    connect( tableWidget, SIGNAL(cellActivated(int,int)), this, SLOT(setCenter(int,int)));
    connect( boxAlpha,  SIGNAL(currentIndexChanged(QString)), this, SLOT(on_boxAlpha_Changed(QString )));
    connect( boxBeta,  SIGNAL(currentIndexChanged(QString )), this, SLOT(on_boxBeta_Changed(QString )));

}

Mask::~Mask()
{
    delete ui;
}

void Mask::init()
{
    lastCenterRow = 0;
    lastCenterColumn = 0;
    tableWidget = ui->tableWidget;

    tableWidget->setRowCount(2);
    tableWidget->setColumnCount(2);

    for ( int row = 0; row < tableWidget->rowCount(); ++row )
        for( int column = 0; column < tableWidget->columnCount(); ++column )  {

            QTableWidgetItem *newItem = new QTableWidgetItem();
            tableWidget->setItem(row, column, newItem);

        }
}
void Mask::initAlphaBeta()
{
    boxAlpha = ui->comboBox_alpha;
    boxBeta = ui->comboBox_beta;

    boxAlpha->addItem("sum");
    boxAlpha->addItem("min");
    boxAlpha->addItem("max");
    boxAlpha->addItem("median");

    boxBeta->addItem("product");
    boxBeta->addItem("sum");
    boxBeta->addItem("diff");

    alphaLabel = "sum";
    betaLabel = "product";

}
void Mask::on_spinBox_columns_valueChanged(int arg1)
{
    int diff = arg1 - tableWidget->columnCount();

    if ( diff == 0 )
        return;
    else if ( diff > 0 ) {

        for( int i = 0; i < diff; ++i )
            tableWidget->insertColumn( tableWidget->columnCount() );

        insertElements( tableWidget->rowCount(), arg1 - diff );

    } else
        for( int i = tableWidget->columnCount(); i > arg1; --i )
            tableWidget->removeColumn( tableWidget->columnCount()-1 );

    if ( diff < 0 ) {
        lastCenterRow = 0;
        lastCenterColumn = 0;
    }
    setCenter(lastCenterRow, lastCenterColumn);
}

void Mask::on_spinBox_rows_valueChanged(int arg1)
{
    int diff = arg1 - tableWidget->rowCount();

    if ( diff == 0 )
        return;
    else if ( diff > 0) {

        for( int i = 0; i < diff; ++i )
            tableWidget->insertRow( tableWidget->rowCount() );

        insertElements( arg1 - diff , tableWidget->columnCount() );

    } else
        for( int i = tableWidget->rowCount(); i > arg1; --i )
            tableWidget->removeRow( tableWidget->rowCount()-1 );

    if ( diff < 0 ) {

        lastCenterRow = 0;
        lastCenterColumn = 0;
    }
    setCenter(lastCenterRow, lastCenterColumn);
}

void Mask::insertElements( int startRow, int startColumn )
{
    for ( int row = startRow; row < tableWidget->rowCount(); ++row )
        for( int column = startColumn; column < tableWidget->columnCount(); ++column )  {

            QTableWidgetItem *newItem = new QTableWidgetItem();
            tableWidget->setItem(row, column, newItem);

        }

    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}
void Mask::setCenter(int row, int column)
{
    lastCenterRow = row;
    lastCenterColumn = column;
    QStringList horizontalHeader, verticalHeader;

    for ( int i = 0; i < tableWidget->rowCount(); ++i )
        verticalHeader.append( QString::number(i - row) );

    for ( int i = 0; i < tableWidget->columnCount(); ++i )
        horizontalHeader.append( QString::number(i - column) );

    tableWidget->setHorizontalHeaderLabels( horizontalHeader );
    tableWidget->setVerticalHeaderLabels( verticalHeader );
}
void Mask::on_boxAlpha_Changed(QString s)
{
    alphaLabel = s;
    std::cout<<alphaLabel.toStdString()<<std::endl;
}

void Mask::on_boxBeta_Changed(QString s)
{
    betaLabel = s;
    std::cout<<betaLabel.toStdString()<<std::endl;
}
