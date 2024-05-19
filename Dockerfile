# Сборка ---------------------------------------

# В качестве базового образа для сборки используем gcc:latest
FROM gcc:latest as build

# Установим рабочую директорию для сборки GoogleTest
#WORKDIR /gtest_build

# Скачаем все необходимые пакеты и выполним сборку GoogleTest
# Такая длинная команда обусловлена тем, что
# Docker на каждый RUN порождает отдельный слой,
# Влекущий за собой, в данном случае, ненужный оверхед
#RUN apt-get update && \
#    apt-get install -y \
#      libboost-dev libboost-program-options-dev \
#      libgtest-dev \
#      cmake \
#    && \
#    cmake -DCMAKE_BUILD_TYPE=Release /usr/src/gtest && \
#    cmake --build . && \
#    mv lib*.a /usr/lib


RUN apt-get update && \
    apt-get install -y \
      libboost-dev libboost-program-options-dev \
      cmake 

# Скопируем директорию /src в контейнер
ADD ./src /app/src
ADD ./CMakeLists.txt /app/CMakeLists.txt

# Установим рабочую директорию для сборки проекта
WORKDIR /app/build

# Выполним сборку нашего проекта, а также его тестирование
RUN cmake .. && \
    cmake --build .

# Запуск ---------------------------------------

# В качестве базового образа используем ubuntu:latest
FROM ubuntu:latest

# Добавим пользователя, потому как в Docker по умолчанию используется root
# Запускать незнакомое приложение под root'ом неприлично :)
RUN groupadd -r sample && useradd -r -g sample sample
USER sample

# Установим рабочую директорию нашего приложения
WORKDIR /app

# Скопируем приложение со сборочного контейнера в рабочую директорию
COPY --from=build /app/build/main .

# Установим точку входа
ENTRYPOINT ["./main"]