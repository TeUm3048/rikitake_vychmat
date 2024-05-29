BASEDIR=$(dirname $0)

mkdir -p "$BASEDIR/../data"

cd "$BASEDIR/.."

./main --solver RK4 --end 20 --step 0.0005 --every 0.01 >data/RK4_20_0.0005_0.01.csv
./main --solver DOPRI8 --end 20 --step 0.01 --every 0.01 >data/DOPRI8_20_0.01_0.01.csv
./main --solver ADAMS_BASHFORTH --end 20 --step 0.01 --every 0.01 >data/ADAMS_BASHFORTH_20_0.01_0.01.csv
./main --solver ADAMS_MOULTON --end 20 --step 0.0005 --every 0.01 >data/ADAMS_MOULTON_20_0.0005_0.01.csv
./main --solver DOPRI54 --end 20 --atol 1e-08 --rtol 1e-08 --every 0.01 >data/DOPRI54_20_a1e-08_r1e-08_0.01.csv
