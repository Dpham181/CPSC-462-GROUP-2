#pragma once
#include <chrono>
#include <any>
#include <memory>      // unique_ptr
#include <stdexcept>   // runtime_error
#include <string>
#include <vector>   // domain_error, runtime_error
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"

namespace Domain::Sale
{
    using TechnicalServices::Persistence::Product;
    using TechnicalServices::Persistence::UserCredentials;
    using TechnicalServices::Persistence::Commission;
    using TechnicalServices::Persistence::Sale;

  // Client Package within the Domain Layer Abstract class
  class SaleHandler
  {
    public:
     
     static std::unique_ptr<SaleHandler> UseSaleManagement( const UserCredentials& User);

      //  Operations menu
     virtual std::vector<std::string> getCommandsSale() =0;    // retrieves the list of actions (commands)
     virtual std::any                executeCommandSale(const std::string& command, const std::vector<std::string>& args) =0;    // executes one of the actions retrieved



   // Operations of management inventory
     // default operations
       virtual Sale             MakeSale( const int UserId, const int ClientId, const std::vector<Product> purchasedProduct) =0;
       virtual Commission       GenerateCommission(const int CommissionId) =0;

      virtual ~SaleHandler() noexcept = 0;


      protected :
        // Copy assignment operators, protected to prevent mix derived-type assignments
          SaleHandler&
        operator=( const SaleHandler& rhs ) = default;                // copy assignment
          SaleHandler& operator=(SaleHandler&& rhs ) = default;    // move assignment
 
  };    // class SaleHandler


} // namespace Domain::Sale
