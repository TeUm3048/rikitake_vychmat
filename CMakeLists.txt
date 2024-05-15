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
        src/cpp/main.cpp
        src/cpp/System.hh
        src/cpp/IStepper.hh
        src/cpp/IOneStepper.hh
        src/cpp/ExplicitMethods/UniversalRungeKuttaStepper/UniversalRungeKuttaStepper.hh
        src/cpp/ExplicitMethods/UniversalRungeKuttaStepper/ButcherTable.hh
        src/cpp/RikitakeModel/dx_dt.hh
        src/cpp/RikitakeModel/Parameters.hh
        src/cpp/RikitakeModel/State.hh
        src/cpp/RikitakeModel/dx_dt.cpp
        src/cpp/RikitakeModel/State.cpp
        src/cpp/ExplicitMethods/RK4.cpp
        src/cpp/ExplicitMethods/RK4.hh
        src/cpp/ExplicitMethods/DOPRI8.cpp
        src/cpp/ExplicitMethods/DOPRI8.hh
        src/cpp/AdamsBashforth/AdamsBashforth.hh
        src/cpp/AdamsBashforth/AdamsBashforth.hh
        src/cpp/AdamsMoulton/AdamsMoulton.hh
        src/cpp/AdamsMoulton/last_backward_difference.hh
        src/cpp/solve_model.cpp
)

target_link_libraries(main ${Boost_LIBRARIES})


