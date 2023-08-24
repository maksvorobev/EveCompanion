#include "MainPageModelData.h"
#include <QDebug>


void MainPageModelData::print() const
{
    qDebug() << QString::fromStdString(image_url) << QString::fromStdString(name) <<  QString::fromStdString(wallet_balance);
}
