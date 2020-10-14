#include "domain/client/client.hpp"

#include <string>
#include <any>
#include <vector>

namespace  // anonymous (private) working area
{
  auto & persistentdata = technicalservices::persistence::persistencehandler::instance();

  
  #define stubclient(functionname)  std::any functionname( domain::client::clientsection & /*session*/, const std::vector<std::string> & /*args*/ ) \
                              { return {}; }  // stubbed for now
  stub( bugpeople    )
  stub( collectfines )
  stub( help         )
  stub( openarchives )
  stub( payfines     )
  stub( resetaccount )
  stub( returnbook   )
  stub( shutdown     )



  std::any checkoutbook( domain::session::sessionbase & session, const std::vector<std::string> & args )
  {
     to-do  verify there is such a book and the mark the book as being checked out by user
    std::string results = "title \"" + args[0] + "\" checkout by \"" + session._credentials.username + '"';
    session._logger << "checkoutbook:  " + results;
    return results;
  }
  std::any showallclients(domain::session::sessionbase& session, const std::vector<std::string>& args)
  {
      std::string results = "done";
      return results;
  }
  std::any addnewclient(domain::session::sessionbase& session, const std::vector<std::string>& args)
  {
       to-do  verify there is such a book and the mark the book as being checked out by user
      std::string results = args[0];
      std::string username = session._credentials.username;
      technicalservices::persistence::client newclient = persistentdata.generateclientid(username);

      session._logger << "client id already generated: " + args[0] + "by" + username;
      
      return results;
  }

  
}    // anonymous (private) working area










namespace domain::client
{
    clientsection::clientsection( const std::string & description, const client & client ) : _clientid( clie ), _name( description )
  {
    _logger << "session \"" + _name + "\" being used and has been successfully initialized";
  }


 

  sessionbase::~sessionbase() noexcept
  {
    _logger << "session \"" + _name + "\" shutdown successfully";
  }




  std::vector<std::string> sessionbase::getcommands()
  {
    std::vector<std::string> availablecommands;
    availablecommands.reserve( _commanddispatch.size() );

    for( const auto & [command, function] : _commanddispatch ) availablecommands.emplace_back( command );

    return availablecommands;
  }




  std::any sessionbase::executecommand( const std::string & command, const std::vector<std::string> & args )
  {
    std::string parameters;
    for( const auto & arg : args )  parameters += '"' + arg + "\"  ";
    _logger << "responding to \"" + command + "\" request with parameters: " + parameters;

    auto it = _commanddispatch.find( command );
    if( it == _commanddispatch.end() )
    {
      std::string message = __func__;
      message += " attempt to execute \"" + command + "\" failed, no such command";

      _logger << message;
      throw badcommand( message );
    }

    auto results = it->second( *this, args);

    if( results.has_value() )
    {
       the type of result depends on function called.  let's assume strings for now ...
      _logger << "responding with: \"" + std::any_cast<const std::string &>( results ) + '"';
    }

    return results;
  }



   2) now map the above system events to roles authorized to make such a request.  many roles can request the same event, and many
      events can be requested by a single role.
  itadministratorsession::itadministratorsession( const usercredentials & credentials ) : sessionbase( "it admin", credentials )
  {
    _logger << "login successful for \"" + credentials.username + "\" as role \"it admin\".";

    _commanddispatch = { {"add new account",   addnewaccount },
                         {"back-up database",   backupdb }//,
                         {"shutdown system", shutdown    } 
    };
  }




  assistantsession::assistantsession( const usercredentials & credentials ) : sessionbase( "assistant", credentials )
  {
    _logger << "login successful for \"" + credentials.username + "\" as role \"assistant\".";

    _commanddispatch = {
                         { "show all clients", showallclients },
                        {"add new client", addnewclient},
                         {"modify client",          modifyclient        },
                         {"ask it for help",     askhelp    },
                         {"schedule event",   scheduleevent  },
                         { "attach client document", attachclientdocument },
                         { "invite client", inviteclient }//,
    };
  }




  salespersonsession::salespersonsession( const usercredentials & credentials ) : sessionbase( "salesperson", credentials )
  {
    _logger << "login successful for \"" + credentials.username + "\" as role \"salesperson\".";

    _commanddispatch = { {"make sale", makesale}//,
                         {"collect fines", collectfines},
                         {"help",          help        },
                         {"open archives", openarchives} 
    };
  }




  salesmanagersession::salesmanagersession( const usercredentials & credentials ) : sessionbase( "sales manager", credentials )
  {
    _logger << "login successful for \"" + credentials.username + "\" as role \"sales manager\".";

    _commanddispatch = { {"manage subscription", managesubscription}//,
                         {"help",       help} 
    };
  }
}    // namespace domain::session
