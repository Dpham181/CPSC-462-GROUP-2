#pragma once

#include <any>
#include <memory>
#include <string>
#include <vector>

#include "Domain/User/UserHandler.hpp"
#include "TechnicalServices/Logging/LoggerHandler.hpp"

namespace Domain::User
{

    // Class for IT Admin
    class ITAdminUserDomain : public UserHandler
    {
    public:

        ITAdminUserDomain(const std::string& description, const UserCredentials& User);

        //  Operations menu
        std::vector<std::string>        getCommandsUser() override;    // retrieves the list of actions (commands)
        std::any                        executeCommandUser(const std::string& command, const std::vector<std::string>& args) override;    // executes one of the actions retrieved

        // Operations
        std::vector<UserCredentials>    UsersDB(const std::vector<UserCredentials>& UsersDB) override;
        void                            viewUsers(const UserCredentials& User) override;         //view users for IT Admin
        UserCredentials                 searchUserId(const int UserId) override;
        std::vector<UserCredentials>    addUser(const int UserID, const std::string UserName, const std::string Role) override;
        std::vector<UserCredentials>    updateUser(const UserCredentials& User) override;
        std::vector<UserCredentials>    banUser(const int UserID) override;


        ~ITAdminUserDomain() noexcept override = 0;

    protected:
    public:
        using DispatchTable = std::map<std::string, std::any(*)(Domain::User::ITAdminUserDomain &, const std::vector<std::string> &)>;

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

    };

    // Class for Assistant
    class AssistantUserDomain : public UserHandler
    {
    public:

        AssistantUserDomain(const std::string& description, const UserCredentials& User);

        //  Operations menu
        std::vector<std::string>        getCommandsUser() override;    // retrieves the list of actions (commands)
        std::any                        executeCommandUser(const std::string& command, const std::vector<std::string>& args) override;    // executes one of the actions retrieved

        // Operations
        std::vector<UserCredentials>    UsersDB(const std::vector<UserCredentials>& UsersDB) override;
        void                            viewUsers(const UserCredentials& User) override;         //view users for IT Admin
        UserCredentials                 searchUserId(const int UserId) override;
        std::vector<UserCredentials>    addUser(const int UserID, const std::string UserName, const std::string Role) override;
        std::vector<UserCredentials>    updateUser(const UserCredentials& User) override;
        std::vector<UserCredentials>    banUser(const int UserID) override;


        ~AssistantUserDomain() noexcept override = 0;

    protected:
    public:
        using DispatchTable = std::map<std::string, std::any(*)(Domain::User::AssistantUserDomain&, const std::vector<std::string>&)>;

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

    };

    // Class for Sales Person
    class SalespersonUserDomain : public UserHandler
    {
    public:

        SalespersonUserDomain(const std::string& description, const UserCredentials& User);

        //  Operations menu
        std::vector<std::string>        getCommandsUser() override;    // retrieves the list of actions (commands)
        std::any                        executeCommandUser(const std::string& command, const std::vector<std::string>& args) override;    // executes one of the actions retrieved

        // Operations
        std::vector<UserCredentials>    UsersDB(const std::vector<UserCredentials>& UsersDB) override;
        void                            viewUsers(const UserCredentials& User) override;         //view users for IT Admin
        UserCredentials                 searchUserId(const int UserId) override;
        std::vector<UserCredentials>    addUser(const int UserID, const std::string UserName, const std::string Role) override;
        std::vector<UserCredentials>    updateUser(const UserCredentials& User) override;
        std::vector<UserCredentials>    banUser(const int UserID) override;

        ~SalespersonUserDomain() noexcept override = 0;

    protected:
    public:
        using DispatchTable = std::map<std::string, std::any(*)(Domain::User::SalespersonUserDomain&, const std::vector<std::string>&)>;

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

    };

    // Class for Sales Mananger
    class SalesManagerUserDomain : public UserHandler
    {
    public:

        SalesManagerUserDomain(const std::string& description, const UserCredentials& User);

        //  Operations menu
        std::vector<std::string>        getCommandsUser() override;    // retrieves the list of actions (commands)
        std::any                        executeCommandUser(const std::string& command, const std::vector<std::string>& args) override;    // executes one of the actions retrieved

        // Operations
        std::vector<UserCredentials>    UsersDB(const std::vector<UserCredentials>& UsersDB) override;
        void                            viewUsers(const UserCredentials& User) override;         //view users for IT Admin
        UserCredentials                 searchUserId(const int UserId) override;
        std::vector<UserCredentials>    addUser(const int UserID, const std::string UserName, const std::string Role) override;
        std::vector<UserCredentials>    updateUser(const UserCredentials& User) override;
        std::vector<UserCredentials>    banUser(const int UserID) override;

        ~SalesManagerUserDomain() noexcept override = 0;

    protected:
    public:
        using DispatchTable = std::map<std::string, std::any(*)(Domain::User::SalesManagerUserDomain&, const std::vector<std::string>&)>;

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

    };

    // Class for Security Officer
    class SecurityOfficerUserDomain : public UserHandler
    {
    public:

        SecurityOfficerUserDomain(const std::string& description, const UserCredentials& User);

        //  Operations menu
        std::vector<std::string>        getCommandsUser() override;    // retrieves the list of actions (commands)
        std::any                        executeCommandUser(const std::string& command, const std::vector<std::string>& args) override;    // executes one of the actions retrieved

        // Operations
        std::vector<UserCredentials>    UsersDB(const std::vector<UserCredentials>& UsersDB) override;
        void                            viewUsers(const UserCredentials& User) override;         //view users for Security Officer
        UserCredentials                 searchUserId(const int UserId) override;
        std::vector<UserCredentials>    addUser(const int UserID, const std::string UserName, const std::string Role) override;
        std::vector<UserCredentials>    updateUser(const UserCredentials& User) override;
        std::vector<UserCredentials>    banUser(const int UserID) override;


        ~SecurityOfficerUserDomain() noexcept override = 0;

    protected:
    public:
        using DispatchTable = std::map<std::string, std::any(*)(Domain::User::SecurityOfficerUserDomain&, const std::vector<std::string>&)>;

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

    };

    /*****************************************************************************
    ** Inline implementations
    ******************************************************************************/
    // IT Admin
    inline ITAdminUserDomain::~ITAdminUserDomain() noexcept
    {
        _logger << "Session \"" + _name + "\" shutdown successfully";

    }
    struct ITAdminUserManagement : ITAdminUserDomain { ITAdminUserManagement(const UserCredentials& User); };

    // Assitant
    inline AssistantUserDomain::~AssistantUserDomain() noexcept
    {
        _logger << "Session \"" + _name + "\" shutdown successfully";

    }
    struct AssistantUserManagement : AssistantUserDomain { AssistantUserManagement(const UserCredentials& User); };

    // Sales Person
    inline SalespersonUserDomain::~SalespersonUserDomain() noexcept
    {
        _logger << "Session \"" + _name + "\" shutdown successfully";

    }
    struct SalespersonUserManagement : SalespersonUserDomain { SalespersonUserManagement(const UserCredentials& User); };

    // Sales Manager
    inline SalesManagerUserDomain::~SalesManagerUserDomain() noexcept
    {
        _logger << "Session \"" + _name + "\" shutdown successfully";

    }
    struct SalesManagerUserManagement : SalesManagerUserDomain { SalesManagerUserManagement(const UserCredentials& User); };

    // Security Officer
    inline SecurityOfficerUserDomain::~SecurityOfficerUserDomain() noexcept
    {
        _logger << "Session \"" + _name + "\" shutdown successfully";

    }
    struct SecurityOfficerUserManagement : SecurityOfficerUserDomain { SecurityOfficerUserManagement(const UserCredentials& User); };

}  // namespace Domain::User
