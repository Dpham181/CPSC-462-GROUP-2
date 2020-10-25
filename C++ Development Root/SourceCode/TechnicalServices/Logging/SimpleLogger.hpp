#pragma warning(disable:4996)
#pragma once

#include <iostream>
#include <chrono>
#include <iomanip>

#include "TechnicalServices/Logging/LoggerHandler.hpp"


namespace TechnicalServices::Logging
{
  class SimpleLogger : public TechnicalServices::Logging::LoggerHandler
  {
    public:
      //Constructors
      SimpleLogger( std::ostream & loggingStream = std::clog);

      // Operations
      SimpleLogger & operator<< ( const std::string & message ) override;

      // Destructor
      ~SimpleLogger() noexcept override;


    protected:
      std::ostream & _loggingStream;
  }; // class SimpleLogger






  /*****************************************************************************
  ** Inline implementations
  ******************************************************************************/
  inline SimpleLogger::SimpleLogger( std::ostream & loggingStream )
    : _loggingStream( loggingStream )
  {
    // Let's set the buffering behavior of the stream so the order and context of inserted information is preserved. Force the
    // buffer to be flushed after each insertion. One normally doesn't want to do this, but log files are very often viewed in real
    // time as the program executes (e.g. tailing a file).  Waiting for the buffer to fill before seeing the contents may give false
    // information in such cases.
    _loggingStream << std::unitbuf;

    // call operator<< so the time stamp and newline get inserted too
    *this << "Simple Logger being used and has been successfully initialized";
  }


  inline SimpleLogger::~SimpleLogger() noexcept
  {
    *this << "Simple Logger shutdown successfully";
  }



  inline SimpleLogger & SimpleLogger::operator<< ( const std::string & message )
  {
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    _loggingStream << std::put_time( std::localtime( &now ), "%Y-%m-%d %X" ) << " | ";
    _loggingStream << message << '\n';

    return *this;
  }

} // namespace TechnicalServices::Logging
