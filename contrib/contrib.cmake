if (WIN32)
  # SFML
  set(SFML_DIR ${CMAKE_SOURCE_DIR}/contrib/win/SFML-2.5.1/lib/cmake/SFML)
  find_package(SFML COMPONENTS graphics window system)

  if (NOT SFML_FOUND)
    message(FATAL "SFML Not found!")
  endif()

else()
  message(FATAL "Contribs only exist for Win32, aborting!")
endif()

# Shared on all platforms
set(glm_DIR ${CMAKE_SOURCE_DIR}/contrib/glm-0.9.9.8/glm/cmake/glm)
find_package(glm)

if (NOT glm_FOUND)
  message(FATAL "glm not found!")
endif()