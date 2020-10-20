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
        std::vector<User>               UsersDB(const std::vector<User>& UsersDB) override;
        std::vector<UserCredentials>    UsersPDB(const std::vector<UserCredentials>& UsersPDB) override;
        void                            viewUsers(const std::vector<User>& UsersDB) override;
        void                            viewUserProfiles(const std::vector<UserCredentials>& UsersPDB) override;
        UserCredentials                 searchUserId(const int UserId) override;
        //std::pair<std::vector<User>, std::vector<UserCredentials>>               addUser(const User& User) override;
        std::vector<User>               addUser(const User& User) override;
        UserCredentials                 updateUserProfile(const std::string userName, std::string passPhrase, std::string role, const int status) override;

        ~UserDomain() noexcept override = 0;

    protected:
    public:
        using DispatchTable = std::map<std::string, std::any(*)(Domain::User::UserDomain &, const std::vector<std::string> &)>;

        friend class Policy;

        // Instance Attributes
        std::unique_ptr<TechnicalServices::Logging::LoggerHandler> _loggerPtr = TechnicalServices::Logging::LoggerHandler::create();
        TechnicalServices::Logging::LoggerHandler& _logger = *_loggerPtr;
        std::vector<User>                               _UpdatedUserDB;
        std::vector<UserCredentials>                    _UpdatedUserProfileDB;
        std::string     const                           _name = "Undefined";
        User                                            _User;
        UserCredentials                                 _Userfile;
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
