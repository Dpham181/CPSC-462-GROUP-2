
// this one if u want to check condition like sesstion handler cpp

#include <algorithm>    // std::any_of()
#include <memory>       // unique_ptr, make_unique<>()
#include <stdexcept>    // logic_error
#include <string>

#include "Domain/Sale/Sale.hpp"

#include "TechnicalServices/Persistence/PersistenceHandler.hpp"




namespace Domain::Sale
{
    SaleHandler::~SaleHandler() noexcept = default;

    std::unique_ptr<SaleHandler> SaleHandler::UseSaleManagement(const UserCredentials& user)
    {
        auto& persistentData = TechnicalServices::Persistence::PersistenceHandler::instance();
        UserCredentials credentialsFromDB = persistentData.findCredentialsByName(user.userName);
        if (credentialsFromDB.status == 1) return std::make_unique<Domain::Sale::SaleManagement>(user);

        return nullptr;
    }

  
} // namespace Domain::Sale
