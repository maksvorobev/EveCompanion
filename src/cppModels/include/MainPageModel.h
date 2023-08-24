#pragma once
#include <QAbstractListModel>
#include <vector>
#include "MainPageModelData.h"



class User_data_handler;
class MainPageModel: public QAbstractListModel
{
    Q_OBJECT
public:
    MainPageModel() = default;
    static void registerMe(const std::string& modeleName);
    void addData(MainPageModelData x);
    void get_model_data() const;
    void fill_data();


    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;


private:
    std::vector<MainPageModelData> m_data;

    enum MainPageRoles{
        image_url = Qt::UserRole + 1,
        name,
        wallet_balance
    };

};

