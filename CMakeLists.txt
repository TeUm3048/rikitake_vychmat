# Указываем минимально необходимую версию CMake
cmake_minimum_required(VERSION 3.10)
project(main)


# Устанавливаем стандарт C++
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CXX_STANDARD_REQUIRED True)


# Ищем необходимые библиотеки (для графики)
# find_package(SDL2 REQUIRED)
# find_package(X11 REQUIRED)
# find_package(OpenGL REQUIRED)
# find_package(GLU REQUIRED)


# используем Boost.Program_options
# дабы не переусложнять, в качестве статической библиотеки
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS program_options REQUIRED)
include_directories(${BOOST_INCLUDE_DIRS})

# Связываем исполняемый файл с найденными библиотеками
add_executable(main
        src/main.cpp
        src/System.hh
        src/IStepper.hh
        src/IOneStepper.hh
        src/ExplicitMethods/UniversalRungeKuttaStepper/UniversalRungeKuttaStepper.hh
        src/ExplicitMethods/UniversalRungeKuttaStepper/ButcherTable.hh
        src/RikitakeModel/dx_dt.hh
        src/RikitakeModel/Parameters.hh
        src/RikitakeModel/State.hh
        src/RikitakeModel/dx_dt.cpp
        src/RikitakeModel/State.cpp
        src/ExplicitMethods/RK4.cpp
        src/ExplicitMethods/RK4.hh
        src/ExplicitMethods/DOPRI8.cpp
        src/ExplicitMethods/DOPRI8.hh
        src/AdamsBashforth/AdamsBashforth.hh
        src/AdamsBashforth/AdamsBashforth.hh
        src/AdamsMoulton/AdamsMoulton.hh
        src/AdamsMoulton/last_backward_difference.hh
)

target_link_libraries(main ${Boost_LIBRARIES})


