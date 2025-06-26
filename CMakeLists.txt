cmake_minimum_required(VERSION 3.15)
project(HoneycombFrame LANGUAGES CXX)

# Require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable warnings
if (MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Wconversion)
endif()

# Option to enable VTK
option(USE_VTK "Enable VTK visualization" ON)

include_directories(${PROJECT_SOURCE_DIR}/include)

# Find VTK only if requested
if (USE_VTK)
    find_package(VTK CONFIG REQUIRED
        COMPONENTS 
            CommonCore 
            FiltersSources 
            RenderingCore 
            InteractionStyle 
            RenderingOpenGL2
    )
endif()

# Sources
set(SOURCES
    src/main.cpp
    
    src/ExporterOBJ.cpp
    src/VisualizerVTK.cpp
    src/HexGridMatrix.cpp
)

add_executable(HoneycombFrame ${SOURCES})

# Link VTK if enabled
if (USE_VTK)
    target_link_libraries(HoneycombFrame PRIVATE
        VTK::CommonCore
        VTK::FiltersSources
        VTK::RenderingCore
        VTK::InteractionStyle
        VTK::RenderingOpenGL2
    )
    target_compile_definitions(HoneycombFrame PRIVATE USE_VTK)
    vtk_module_autoinit(
        TARGETS HoneycombFrame
        MODULES
            VTK::CommonCore
            VTK::FiltersSources
            VTK::RenderingCore
            VTK::RenderingOpenGL2
            VTK::InteractionStyle
    )
endif()

# Optionally add tests
# enable_testing()
# add_executable(HexGridTest tests/HexGridTest.cpp src/HexGrid.cpp)
# target_link_libraries(HexGridTest PRIVATE GTest::gtest_main)
# add_test(NAME HexGridTest COMMAND HexGridTest)
