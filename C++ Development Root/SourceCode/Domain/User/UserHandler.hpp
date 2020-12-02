#pragma once

#include <any>
#include <string>
#include <vector>
#include <memory>      // unique_ptr
#include <stdexcept>    // domain_error, runtime_error
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"


namespace Domain::User
{
    using TechnicalServices::Persistence::UserCredentials;

    // User Package within the Domain Layer Abstract class
    class UserHandler
    {
    public:
        struct   UserException : std::runtime_error { using runtime_error::runtime_error; };
        struct   NoSuchUser : UserException { using UserException::UserException; };
        struct   NoSuchProperty : UserException { using UserException::UserException; };

        // object return user with creator 
        static std::unique_ptr<UserHandler> UseUserManagement(const UserCredentials& user);


        // Operations menu
        virtual std::vector<std::string>   getCommandsUser() = 0;    // retrieves the list of actions (commands)
        virtual std::any                   executeCommandUser(const std::string& command, const std::vector<std::string>& args) =0;    // executes one of the actions retrieved

        // Operations of User management
        virtual std::vector<UserCredentials>     UsersDB(const std::vector<UserCredentials>& UsersDB) = 0;
        virtual void                             viewUsers(const std::string UserName) = 0;
        virtual UserCredentials                  searchUserId(const int UserId) = 0;
        virtual std::vector<UserCredentials>     addUser(const int UserID, const std::string UserName, const std::string Role) = 0;
        virtual std::vector<UserCredentials>     updateUser(const UserCredentials& User) = 0;
        virtual std::vector<UserCredentials>     banUser(const int UserID) = 0;
        


        virtual ~UserHandler() noexcept = 0;


    protected:
        // Copy assignment operators, protected to prevent mix derived-type assignments
        UserHandler&
            operator=(const UserHandler& rhs) = default;                // copy assignment
        UserHandler& operator=(UserHandler&& rhs) = default;    // move assignment


    };    // class UserHandler

} // namespace Domain::User
