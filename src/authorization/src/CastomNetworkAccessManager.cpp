#include "../include/CastomNetworkAccessManager.h"

CastomNetworkAccessManager* CastomNetworkAccessManager::manager_= nullptr;

CastomNetworkAccessManager *CastomNetworkAccessManager::GetInstance()
{
    if (manager_ == nullptr){
        return new CastomNetworkAccessManager;
    }
    return manager_;
}



CastomNetworkAccessManager::CastomNetworkAccessManager(): QNetworkAccessManager()
{

}
