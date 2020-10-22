#pragma once

#include <any>
#include <memory>
#include <string>
#include <vector>

#include "Domain/User/UserHandler.hpp"
#include "TechnicalServices/Logging/LoggerHandler.hpp"

namespace Domain::User
{

    class UserDomain : public UserHandler
    {
    public:

        UserDomain(const std::string& description, const UserCredentials& User);

        //  Operations menu
        std::vector<std::string>        getCommandsUser() override;    // retrieves the list of actions (commands)
        std::any                        executeCommandUser(const std::string& command, const std::vector<std::string>& args) override;    // executes one of the actions retrieved

        // Operations
        std::vector<UserCredentials>    UsersDB(const std::vector<UserCredentials>& UsersDB) override;
        void                            viewUsers(const std::vector<UserCredentials>& UsersDB) override;         //view users for IT Admin
        void                            viewUserProfiles(const std::vector<UserCredentials>& UsersDB) override;         //view users for Security Officer
        UserCredentials                 searchUserId(const int UserId) override;
        std::vector<UserCredentials>    addUser(const int UserID, const std::string UserName, const std::string Role) override;
        //std::vector<UserCredentials>    updateUser(const int UserID, const std::string UserName, const std::string PassPhrase, const std::string Role, const int Status, const std::vector<std::string> SpareTime) override;
        std::vector<UserCredentials>    updateUser(const UserCredentials& User) override;


        ~UserDomain() noexcept override = 0;

    protected:
    public:
        using DispatchTable = std::map<std::string, std::any(*)(Domain::User::UserDomain &, const std::vector<std::string> &)>;

        friend class Policy;

        // Instance Attributes
        std::unique_ptr<TechnicalServices::Logging::LoggerHandler> _loggerPtr = TechnicalServices::Logging::LoggerHandler::create();
        TechnicalServices::Logging::LoggerHandler& _logger = *_loggerPtr;

        std::vector<UserCredentials>                    _UpdatedUserDB;
        std::string     const                           _name = "Undefined";
        UserCredentials                                 _User;
        DispatchTable                                   _commandDispatch;
        UserCredentials const                           _Creator;

    private:

    };// class User


    /*****************************************************************************
    ** Inline implementations
    ******************************************************************************/
    inline UserDomain::~UserDomain() noexcept
    {
        _logger << "Session \"" + _name + "\" shutdown successfully";

    }
    struct UserManagement : UserDomain { UserManagement(const UserCredentials& User); };



}  // namespace Domain::User
