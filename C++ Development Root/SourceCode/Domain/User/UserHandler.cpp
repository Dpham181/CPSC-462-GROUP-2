// this one if u want to check condition like sesstion handler cpp

#include "Domain/Session/SessionHandler.hpp"

#include <algorithm>    // std::any_of()
#include <memory>       // unique_ptr, make_unique<>()
#include <stdexcept>    // logic_error
#include <string>

#include "Domain/User/User.hpp"

#include "TechnicalServices/Persistence/PersistenceHandler.hpp"




namespace Domain::User
{
    UserHandler::~UserHandler() noexcept = default;



    // returns a specialized object specific to the specified role
    std::unique_ptr<UserHandler> UserHandler::UseUserManagement(const UserCredentials& user)
    {
        auto& persistentData = TechnicalServices::Persistence::PersistenceHandler::instance();
        UserCredentials credentialsFromDB = persistentData.findCredentialsByName(user.userName);
        if (credentialsFromDB.status == 1) 
        {
            if (credentialsFromDB.roles[0] == "IT Admin") return std::make_unique<Domain::User::ITAdminUserManagement>(user);
            if (credentialsFromDB.roles[0] == "Security Officer") return std::make_unique<Domain::User::SecurityOfficerUserManagement>(user);
        }
        
        return nullptr;
    }


} // namespace Domain::Session
