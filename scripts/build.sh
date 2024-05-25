BASEDIR=$(dirname $0)

mkdir -p "$BASEDIR/../build"

cd "$BASEDIR/../build"

cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
echo "Copying main to root directory"
cp ./main ..
echo "Build complete"
