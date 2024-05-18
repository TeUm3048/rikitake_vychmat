BASEDIR=$(dirname $0)

cd "$BASEDIR/../build"

cmake ..
cmake build .
cp main ..