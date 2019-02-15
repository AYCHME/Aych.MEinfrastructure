/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once
#include <eosio/chain_plugin/chain_plugin.hpp>
#include <eosio/http_plugin/http_plugin.hpp>

#include <appbase/application.hpp>
#include <eosio/chain/controller.hpp>

namespace eospark
{
using eosio::chain::controller;
using std::unique_ptr;
using namespace appbase;
using namespace eosio;

class eospark_api_plugin_impl;

class eospark_api_plugin : public plugin<eospark_api_plugin>
{
public:
  APPBASE_PLUGIN_REQUIRES((chain_plugin)(http_plugin))

  eospark_api_plugin();
  virtual ~eospark_api_plugin();

  virtual void set_program_options(options_description &, options_description &) override;

  void plugin_initialize(const variables_map &);
  void plugin_startup();
  void plugin_shutdown();

private:
  unique_ptr<class eospark_api_plugin_impl> my;

public:
  // get_vote_component api
  struct get_vote_component_params
  {
    std::string account_name;
  };

  struct get_vote_component_results
  {
    std::string account_name;
  };

  get_vote_component_results get_vote_component(const get_vote_component_params &params) const;
};

} // namespace eospark

// api parameter
FC_REFLECT(eospark::eospark_api_plugin::get_vote_component_params, (account_name))
FC_REFLECT(eospark::eospark_api_plugin::get_vote_component_results, (account_name))
