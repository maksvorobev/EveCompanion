#pragma once
#include <QSettings>
#include <vector>

class DataStorage
{
public:
    DataStorage();
    void setValue(std::string key, std::string value);
    std::vector<std::string> allKeys() const;
    void clear();
    std::string operator[](const std::string& key) const;
private:
    QSettings storage_;
};

