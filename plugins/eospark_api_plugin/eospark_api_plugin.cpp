/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#include <eospark_api_plugin.hpp>
#include <eosio/chain/exceptions.hpp>

#include <fc/io/json.hpp>
#include <iostream>

// register eospark_api_plugin for application::find_plugin
//static appbase::abstract_plugin& _eospark_api_plugin = appbase::app().register_plugin<eospark::eospark_api_plugin>();

namespace eospark {
using namespace eosio;

// implement class
class eospark_api_plugin_impl {
public:
   eospark_api_plugin_impl(controller& db)
      : db(db) {}

   controller& db;
};

// function implementtation
eospark_api_plugin::eospark_api_plugin(){}
eospark_api_plugin::~eospark_api_plugin(){}

// get the configuration of the command line and configuration files
void eospark_api_plugin::set_program_options(options_description&, options_description&) {}

// plugin initialize
void eospark_api_plugin::plugin_initialize(const variables_map&) {}

// register api 
#define EOSPARK_CALL(api_handle, call_name, http_response_code)\
{std::string("/v1/chain/" #call_name),\
   [&api_handle](string, string body, url_response_callback cb) mutable { \
      try { \
         if (body.empty()) body = "{}"; \
             auto result = api_handle.call_name(fc::json::from_string(body).as<eospark::eospark_api_plugin::call_name ## _params>()); \
             cb(http_response_code, fc::json::to_string(result)); \
      } catch (...) { \
         http_plugin::handle_exception("eospark_api_plugin", #call_name, body, cb); \
      } \
   } \
}

// plugin startup
void eospark_api_plugin::plugin_startup() {
   ilog( "starting eospark_api_plugin" );
   my.reset(new eospark_api_plugin_impl(app().get_plugin<chain_plugin>().chain()));
   auto& handle_objest = *this;

   auto& _http_plugin = app().get_plugin<http_plugin>();

   _http_plugin.add_api({
      EOSPARK_CALL(handle_objest, get_vote_component, 200)
   });
}

// plugin shutdown
void eospark_api_plugin::plugin_shutdown() {}

// api
eospark_api_plugin::get_vote_component_results eospark_api_plugin::get_vote_component(const eospark_api_plugin::get_vote_component_params& params )const {
   get_vote_component_results result;
   result.account_name = params.account_name;
   return result;
}

} // namespace eospark
