#pragma once
#include <QAbstractListModel>
#include <vector>
#include "MainPageModelData.h"
#include <QScopedPointer>

class MainPageModel: public QAbstractListModel
{
    Q_OBJECT
public:
    MainPageModel();
    static void registerMe(const std::string& modeleName);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    void addData(MainPageModelData x);
    void get_model_data();


    std::vector<MainPageModelData> m_data;
signals:
    void test_sig(int x);

private:
    enum MainPageRoles{
        image_url = Qt::UserRole + 1,
        name,
        wallet_balance
    };

};

