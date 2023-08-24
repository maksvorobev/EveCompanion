#include "../include/MainPageModel.h"
#include <QQmlEngine>



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

void MainPageModel::get_model_data() const
{
    qDebug() << "func get_model_data(): print all model data";
    for (auto& x : m_data){
        x.print();
    }
}

void MainPageModel::fill_data()
{
    /*
     * Fill m_data in MainPageModel
    */

}


void MainPageModel::addData(MainPageModelData x)
{
    /*
     * Update FULL range of m_data !!!
     */
    qDebug() << "func MainPageModel::addData(MainPageModelData x)";
    int row = m_data.size();

    beginInsertRows( QModelIndex(), row, row );
    m_data.push_back(x);
    endInsertRows();


    return;
}

