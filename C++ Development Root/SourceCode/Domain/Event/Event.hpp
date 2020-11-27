#pragma once

#include <any>
#include <memory>
#include <string>
#include <vector>

#include "Domain/Event/EventHandler.hpp"
#include "TechnicalServices/Logging/LoggerHandler.hpp"

namespace Domain::Event
{

    class EventDomain : public EventHandler
    {
    public:

        EventDomain(const std::string& description, const UserCredentials& user);

        //  Operations menu
        std::vector<std::string>        getCommandsEvent() override;    // retrieves the list of actions (commands)
        std::any                        executeCommandEvent(const std::string& command, const std::vector<std::string>& args) override;    // executes one of the actions retrieved

        // Operations
        std::vector<UserCredentials>    UsersDB(const std::vector<UserCredentials>& UsersDB) override;
        std::vector<Event>              EventsDB(const std::vector<Event>& EventsDB) override;
        std::vector<UserEvents>         UserEventsDB(const std::vector<UserEvents>& UserEvents) override;
        void                            viewEvents( ) override;
        void                            viewUserEvents( ) override;
        std::vector<std::string>        availableTimes(const std::string UserIDs) override;
        std::vector<std::string>        availableLocations(std::vector<std::string> OfficeValues, const std::string Time) override;
        Event                           searchEventId(const int EventId) override;
        std::vector<Event>              addEvent(const Event& Event) override;
        std::vector<Event>              updateEvent(const Event& Event) override;
        void                            sendNotifications(const std::string meetingName, const std::string userIDs, const std::string meetingTime, const std::string meetingLocation) override;


        ~EventDomain() noexcept override = 0;

    protected:
    public:
        using DispatchTable = std::map<std::string, std::any(*)(Domain::Event::EventDomain &, const std::vector<std::string> &)>;

        friend class Policy;

        // Instance Attributes
        std::unique_ptr<TechnicalServices::Logging::LoggerHandler> _loggerPtr = TechnicalServices::Logging::LoggerHandler::create();
        TechnicalServices::Logging::LoggerHandler& _logger = *_loggerPtr;

        std::vector<UserCredentials>                    _UpdatedUserDB;
        std::vector<Event>                              _UpdatedEventDB;
        std::vector<UserEvents>                         _UpdatedUserEventsDB;
        std::string     const                           _name = "Undefined";
        Event                                           _Event;
        DispatchTable                                   _commandDispatch;
        UserCredentials const                           _Creator;

    private:

    };// class Event


    /*****************************************************************************
    ** Inline implementations
    ******************************************************************************/
    inline EventDomain::~EventDomain() noexcept
    {
        _logger << "Session \"" + _name + "\" shutdown successfully";

    }
    struct EventManagement : EventDomain { EventManagement(const UserCredentials& User); };



}  // namespace Domain::Event
