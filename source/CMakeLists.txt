# root_generate_dictionary(ostap_dict ${CMAKE_CURRENT_SOURCE_DIR}/dict/Dict.h ${CMAKE_CURRENT_SOURCE_DIR}/dict/selections.xml)

find_package(ROOT 6 CONFIG REQUIRED )

if(ROOT_FIND_VERSION VERSION_LESS "6.16.0")
    include(CMakeROOT_6_14.cmake)
else()
    include(CMakeROOT_6.16.cmake)
endif()
