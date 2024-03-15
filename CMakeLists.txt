cmake_minimum_required(VERSION 3.10)
# Указываем минимально необходимую версию CMake
project(main)


# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# Ищем необходимые библиотеки (для графики)
# find_package(SDL2 REQUIRED)
# find_package(X11 REQUIRED)
# find_package(OpenGL REQUIRED)
# find_package(GLU REQUIRED)




# Связываем исполняемый файл с найденными библиотеками
add_executable(main
        src/main.cpp
        src/calc_model.h
        src/calc_model.cpp
        src/State.h
        src/State.cpp
        src/Parameters.h
        src/explicit_methods/ForwardEuler.h
        src/explicit_methods/Midpoint.h
        src/explicit_methods/DOPRI8.h
)

# target_link_libraries(main SDL2 X11 OpenGL GLU)
target_link_libraries(main)

