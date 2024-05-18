BASEDIR=$(dirname $0)

cd "$BASEDIR/.."

scripts/build.sh

./main "$@"
