#include "../include/MainPageModel.h"
#include <QQmlEngine>
MainPageModel::MainPageModel()
{
    //MainPageModelData dt = {"eff", "wefwfe", "wefwf"};
    //m_data.push_back(dt);
}

void MainPageModel::registerMe(const std::string &modeleName)
{
    qmlRegisterType<MainPageModel>(modeleName.c_str(), 1, 0, "MainPageModel");
    return;
}

int MainPageModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return static_cast<int>(m_data.size());
}

QVariant MainPageModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() or index.row() > rowCount(index)){
        return {};
    }
    const auto& character = m_data.at(index.row());

    switch (role){
    case MainPageRoles::name: {
        return QVariant::fromValue(QString::fromStdString(character.name));
    }
    case MainPageRoles::image_url: {
        return QVariant::fromValue(QString::fromStdString(character.image_url));
    }
    case MainPageRoles::wallet_balance: {
        return QVariant::fromValue(QString::fromStdString(character.wallet_balance));
    }

    default: {
        return true;
    }
    }
}
QHash<int, QByteArray> MainPageModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[MainPageRoles::image_url] = "image_url";
    roles[MainPageRoles::name] = "name";
    roles[MainPageRoles::wallet_balance] = "wallet_balance";
    return roles;
}

void MainPageModel::get_model_data()
{
    qDebug() << "model output";
    for (auto& x : m_data){
        qDebug() << QString::fromStdString(x.image_url) << QString::fromStdString(x.name) <<  QString::fromStdString(x.wallet_balance);
    }
}


void MainPageModel::addData(MainPageModelData x)
{
    /*
     * Update FULL range of m_data !!!
     */
    //m_data.swap(x);

    int row = m_data.size();
    beginInsertRows( QModelIndex(), row, row );

    m_data.push_back(x);

    endInsertRows();




    qDebug() << "MainPageModel::addData func : save next data below:";
    get_model_data();
    qDebug() << "m_data.size() = "  << m_data.size();
    //qDebug() << "ptr = " << this;
    int i =0;
    //qDebug() << QString::fromStdString(m_data[i].name) << QString::fromStdString(m_data[i].image_url) << QString::fromStdString(m_data[i].wallet_balance);
    //qDebug() << "emit signal dataChanged from c++ to qml ListView";
    //emit dataChanged(createIndex(0, 0), createIndex(m_data.size(), 0));
    emit test_sig(m_data.size());
    return;
}

