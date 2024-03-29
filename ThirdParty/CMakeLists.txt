set(third_party_folder "ThirdParty")

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

if (NOT TARGET glfw)
    option(GLFW_BUILD_EXAMPLES "" OFF)
    option(GLFW_BUILD_TESTS "" OFF)
    option(GLFW_BUILD_DOCS "" OFF)
    option(GLFW_INSTALL "" OFF)
    add_subdirectory(glfw)
    set_target_properties(glfw PROPERTIES FOLDER ${third_party_folder}/glfw)
    set_target_properties(update_mappings PROPERTIES FOLDER ${third_party_folder}/glfw)
endif ()

if (NOT TARGET glad)
    add_subdirectory(glad)
endif ()

if (NOT TARGET fmt)
    add_subdirectory(fmt)
endif ()

if (NOT TARGET nlohmann_json)
    set(JSON_BuildTests OFF CACHE INTERNAL "")
    add_subdirectory(json)
endif ()

if (NOT TARGET stb)
    include(stb.cmake)
endif ()

if (NOT TARGET bustache)
    include(bustache.cmake)
endif ()

if (NOT TARGET Catch2)
    add_subdirectory(Catch2)
endif ()

if (NOT TARGET lua)
    include(lua.cmake)
endif ()
