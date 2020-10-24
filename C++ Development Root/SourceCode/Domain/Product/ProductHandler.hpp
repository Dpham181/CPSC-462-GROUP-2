#pragma once

#include <any>
#include <memory>      // unique_ptr
#include <stdexcept>   // runtime_error
#include <string>
#include <vector>   // domain_error, runtime_error
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"

namespace Domain::Product
{
    using TechnicalServices::Persistence::Product;
    using TechnicalServices::Persistence::UserCredentials;

  // Product Package within the Domain Layer Abstract class
  class ProductHandler
  {
    public:
     
     static std::unique_ptr<ProductHandler> UseProductManagement( const UserCredentials& User);

      //  Operations menu
     virtual std::vector<std::string> getCommandsProduct() =0;    // retrieves the list of actions (commands)
     virtual std::any                executeCommandProduct(const std::string& command, const std::vector<std::string>& args) =0;    // executes one of the actions retrieved



   // Operations of management inventory
     // default operations
     virtual std::vector<Product>   view() =0;
     virtual void   viewCompany() = 0;
     virtual  Product   add(const int ProductId, const std::string ProductName, const int Price, const int CompanyId)=0;
     virtual  std::vector<Product>   save(const Product & Product) = 0;

     virtual  std::vector<Product>   del(const int ProductId)=0;
     virtual  std::vector<Product>   modify(const int CurrentProduct, const std::string ProductName, const int Price)=0;


      virtual ~ProductHandler() noexcept = 0;


      protected :
        // Copy assignment operators, protected to prevent mix derived-type assignments
          ProductHandler&
        operator=( const ProductHandler& rhs ) = default;                // copy assignment
          ProductHandler& operator=(ProductHandler&& rhs ) = default;    // move assignment
 
  };    // class ProductHandler


} // namespace Domain::Product
