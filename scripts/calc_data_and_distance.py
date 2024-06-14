import os
import subprocess

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

import logging


def remove_prefix(s, prefix):
    return s[len(prefix):] if s.startswith(prefix) else s


def remove_suffix(s, suffix):
    return s[:-len(suffix)] if s.endswith(suffix) else s


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
    logging.info("Running %s", s)
    subprocess.run(s, shell=True, check=True)
    return filename


def generate_data(solver: str, to: float, step: float = None, atol=None, rtol=None, every: float = None, filename: str = None):
    solver = solver.upper()
    if step is not None and every < step:
        every = step
    if solver == "DOPRI54":
        if filename is None:
            filename = f"data/{solver}_{to}_a{atol}_r{rtol}_{every}.csv"
    else:
        if filename is None:
            filename = f"data/{solver}_{to}_{step}_{every}.csv"
    if not os.path.exists(filename):
        logging.info("Data does not exist in %s", filename)
        filename = create_data(solver=solver, to=to, step=step,
                               atol=atol, rtol=rtol, every=every, filename=filename)
    else:
        logging.info("Data already exists in %s", filename)
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
    l1 = remove_suffix(lable1, '.csv')
    l1 = remove_prefix(l1, 'data/').replace('/', '_')
    l2 = remove_suffix(lable2, '.csv')
    l2 = remove_prefix(l2, 'data/').replace('/', '_')

    filename = f"data/distance_{l1}_{l2}.csv"
    dis.to_csv(filename)
    logging.info("Saved distance to %s", filename)
    save_plot_distance(lable1, lable2, filename)
    return filename


def save_plot_distance(lable1, lable2, data_filepath):
    l1 = remove_suffix(lable1, '.csv')
    l1 = remove_prefix(l1, 'data/').replace('/', '_')
    l2 = remove_suffix(lable2, '.csv')
    l2 = remove_prefix(l2, 'data/').replace('/', '_')
    # Извлекаем имена методов из имени файла данных

    data_filepath = f"data/distance_{l1}_{l2}.csv"

    # Формируем название выходного файла
    output_filename = f"plots/{l1}_{l2}.gp"

    t1 = l1.replace("_", r"\\_")
    t2 = l2.replace("_", r"\\_")
    # Генерируем код для gnuplot
    gnuplot_code = f"""set datafile separator ","
set title "Distance between {t1} and {t2}"
set xlabel "time"
set ylabel "Distance"
set grid
plot '{data_filepath}' using 1:2 with linespoints

pause -1
"""

    if not os.path.exists("plots"):
        os.makedirs("plots")
    
    # Сохраняем код в файл
    with open(output_filename, 'w') as f:
        f.write(gnuplot_code)

    logging.info("GNUplot script saved to %s", output_filename)


def main():
    logging.basicConfig(level=logging.INFO)

    dir_path = os.path.dirname(os.path.realpath(__file__))

    os.chdir(dir_path + "/..")

    logging.info("Project dict: %s", os.getcwd())

    end_point = 20

    rk4_filename, rk4_data = generate_data(
        "RK4", to=end_point, step=0.0005, every=0.01)
    logging.info("Calculated with RK4 and save data to %s", rk4_filename)

    step = 0.01
    dopri8_filename, dopri8_data = generate_data(
        "dopri8", to=end_point, step=step, every=0.01)
    logging.info("Calculated with dopri8 and save data to %s", dopri8_filename)

    dopri8_next_filename, dopri8_next_data = generate_data(
        "dopri8", to=end_point, step=step/10, every=0.01)
    logging.info("Calculated with dopri8_next and save data to %s",
                 dopri8_next_filename)
    
    dopri8_2_next_filename, dopri8_2_next_data = generate_data(
        "dopri8", to=end_point, step=step/100, every=0.01)
    logging.info("Calculated with dopri8_2_next and save data to %s",
                 dopri8_2_next_filename)

    ab_filename, ab_data = generate_data(
        "ADAMS_BASHFORTH", to=end_point, step=0.01, every=0.01)
    logging.info(
        "Calculated with ADAMS_BASHFORTH and save data to %s", ab_filename)

    am_filename, am_data = generate_data(
        "ADAMS_MOULTON", to=end_point, step=0.01, every=0.01)
    logging.info(
        "Calculated with ADAMS_MOULTON and save data to %s", am_filename)

    dopri54_filename, dopri54_data = generate_data(
        "DOPRI54", to=end_point, atol=1e-3, rtol=1e-11, every=0.01)
    logging.info("Calculated with DOPRI54 and save data to %s",
                 dopri54_filename)

    save_distance(dopri8_data, dopri54_data, dopri8_filename, dopri54_filename)

    save_distance(dopri54_data, ab_data, dopri54_filename, ab_filename)

    save_distance(dopri54_data, am_data, dopri54_filename, am_filename)

    save_distance(dopri8_data, ab_data, dopri8_filename, ab_filename)

    save_distance(dopri8_data, dopri8_next_data,
                  dopri8_filename, dopri8_next_filename)
    
    save_distance(dopri8_next_data, dopri8_2_next_data,
                  dopri8_next_filename, dopri8_2_next_filename)

    save_distance(dopri8_data, am_data, dopri8_filename, am_filename)

    save_distance(ab_data, am_data, ab_filename, am_filename)



if __name__ == "__main__":
    main()
