#pragma once

#include <any>
#include <string>
#include <vector>
#include <memory>      // unique_ptr
#include <stdexcept>    // domain_error, runtime_error
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"


namespace Domain::Event
{
    using TechnicalServices::Persistence::Event;
    using TechnicalServices::Persistence::UserCredentials;
    using TechnicalServices::Persistence::UserEvents;

    // Event Package within the Domain Layer Abstract class
    class EventHandler
    {
    public:
        struct   EventException : std::runtime_error { using runtime_error::runtime_error; };
        struct   NoSuchEvent : EventException { using EventException::EventException; };
        struct   NoSuchProperty : EventException { using EventException::EventException; };

        // object return event with creator 
        static std::unique_ptr<EventHandler> UseEventManagement(const UserCredentials& User);


        // Operations menu
        virtual std::vector<std::string>   getCommandsEvent() = 0;    // retrieves the list of actions (commands)
        virtual std::any                   executeCommandEvent(const std::string& command, const std::vector<std::string>& args) =0;    // executes one of the actions retrieved

        // Operations of Event management
        virtual std::vector<UserCredentials>    UsersDB(const std::vector<UserCredentials>& UsersDB) = 0;
        virtual std::vector<Event>              EventsDB(const std::vector<Event>& EventsDB) = 0;
        virtual std::vector<UserEvents>         UserEventsDB(const std::vector<UserEvents>& UserEvents) = 0;
        virtual void                            viewEvents(const std::vector<Event>& EventsDB, const std::vector<UserCredentials> UsersDB) = 0;
        virtual void                            viewUserEvents(const std::vector<UserEvents>& UserEventsDB, const std::vector<UserCredentials>& UsersDB) = 0;
        virtual std::vector<std::string>        availableTimes(const std::vector<UserEvents> UserEventsDB, const std::string UserIDs) = 0;
        virtual std::vector<std::string>        availableLocations(const std::vector<Event> EventsDB, std::vector<std::string> OfficeValues, const std::string Time) = 0;
        virtual Event                           searchEventId(const int EventId) = 0;
        virtual std::vector<Event>              addEvent(const Event& Event) = 0;
        virtual std::vector<Event>              updateEvent(const Event& Event) = 0;

        


        virtual ~EventHandler() noexcept = 0;


    protected:
        // Copy assignment operators, protected to prevent mix derived-type assignments
        EventHandler&
            operator=(const EventHandler& rhs) = default;                // copy assignment
        EventHandler& operator=(EventHandler&& rhs) = default;    // move assignment


    };    // class EventHandler






} // namespace Domain::Event
