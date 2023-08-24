#include "../include/DataStorage.h"

#include <QString>


DataStorage::DataStorage(): storage_(QSettings("EveCompanion", "maksvorobev"))
{

}

void DataStorage::setValue(std::string key, std::string value)
{
    storage_.setValue(std::move(QString::fromStdString(key)), QVariant(QString::fromStdString(std::move(value))));
    return;
}

std::vector<std::string> DataStorage::allKeys() const
{
    std::vector<std::string> v;
    auto key_list = storage_.allKeys();
    for (const auto& x: key_list){
        v.push_back(std::move(x.toStdString()));
    }
    return std::move(v);
}

void DataStorage::clear()
{
    storage_.clear();
}

std::string DataStorage::operator[](const std::string &key) const
{
    return storage_.value(QString::fromStdString(key)).toString().toStdString();
}
