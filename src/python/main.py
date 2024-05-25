import os
import subprocess

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt


def create_data(solver: str, to: float, step: float = None, atol=None, rtol=None, every: float = None, filename: str = None):
    if not os.path.exists("data"):
        os.makedirs("data")
    every_param = f"--every {every}" if every is not None else ""
    # if every / step - every // step:
    #     raise ValueError("every should be a multiple of step", every, step, every/step)
    solver = solver.upper()
    if solver == "DOPRI54":
        if filename is None:
            filename = f"data/{solver}_{to}_a{atol}_r{rtol}_{every}.csv"
        s = f"./main --solver {solver} --end {to} --atol {atol} --rtol {rtol} {every_param} > {filename}"
    else:
        if filename is None:
            filename = f"data/{solver}_{to}_{step}_{every}.csv"
        s = f"./main --solver {solver} --end {to} --step {step} {every_param} > {filename}"
    subprocess.run(s, shell=True, check=True)
    return filename


def generate_data(solver: str, to: float, step: float = None, atol=None, rtol=None, every: float = None, filename: str = None):
    solver = solver.upper()

    if solver == "DOPRI54":
        if filename is None:
            filename = f"data/{solver}_{to}_a{atol}_r{rtol}_{every}.csv"
    else:
        if filename is None:
            filename = f"data/{solver}_{to}_{step}_{every}.csv"
    if not os.path.exists(filename):
        filename = create_data(solver=solver, to=to, step=step,
                               atol=atol, rtol=rtol, every=every, filename=filename)
    return filename, pd.read_csv(filename).set_index("time")


def find_distance(solver_data1, solver_data2) -> pd.DataFrame:
    # Assuming solver_data1 and solver_data2 are pandas DataFrames
    dist = np.sqrt(((solver_data1 - solver_data2) ** 2).sum(axis=1))
    dist.dropna(inplace=True)
    dist = pd.DataFrame(dist, columns=["distance"])
    dist = dist.iloc[:-1]
    # Save to a file
    return dist


def save_distance(data1, data2, lable1, lable2):
    dis = find_distance(data1, data2)

    # if not os.path.exists("data"):
    #     os.makedirs("data")
    l1 = lable1.removesuffix('.csv').removeprefix('data/').replace('/', '_')
    l2 = lable2.removesuffix('.csv').removeprefix('data/').replace('/', '_')

    filename = f"data/distance_{l1}_{l2}.csv"
    dis.to_csv(filename)


def main():
    dir_path = os.path.dirname(os.path.realpath(__file__))

    os.chdir(dir_path + "/../..")

    end_point = 20

    rk4_filename, rk4_data = generate_data(
        "RK4", to=end_point, step=0.0005, every=0.01)
    dopri8_filename, dopri8_data = generate_data(
        "dopri8", to=end_point, step=0.01, every=0.01)
    ab_filename, ab_data = generate_data(
        "ADAMS_BASHFORTH", to=end_point, step=0.01, every=0.01)
    am_filename, am_data = generate_data(
        "ADAMS_MOULTON", to=end_point, step=0.0005, every=0.01)
    dopri54_filename, dopri54_data = generate_data(
        "DOPRI54", to=end_point, atol=1e-8, rtol=1e-8, every=0.01)

    save_distance(rk4_data, dopri8_data, rk4_filename, dopri8_filename)
    save_distance(rk4_data, ab_data, rk4_filename, ab_filename)
    save_distance(rk4_data, am_data, rk4_filename, am_filename)
    save_distance(rk4_data, dopri54_data, rk4_filename, dopri54_filename)
    save_distance(dopri54_data, am_data, dopri54_filename, am_filename)



if __name__ == "__main__":
    main()