file(GLOB HEADERS "*.hpp")
add_library( eospark_api_plugin
            eospark_api_plugin.cpp
             ${HEADERS} )

target_link_libraries( eospark_api_plugin chain_plugin http_plugin appbase )
target_include_directories( eospark_api_plugin PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}" )
