import subprocess
import matplotlib.pyplot as plt

# Ustawienia eksperymentu
M_REPEATS = 50
N_VALUES = list(range(1000, 50001, 1000)) 

K_SCENARIOS = {
    "k=1 (min)": lambda n: 1,
    "k=n_2 (mediana)": lambda n: n // 2,
    "k=n (max)": lambda n: n
}

FILENAME_MAP = {
    "k=1 (min)": "min",
    "k=n_2 (mediana)": "median",
    "k=n (max)": "max"
}

results = {
    "RandomSelect": {scenario: {"c": [], "s": [], "c_n": [], "s_n": []} for scenario in K_SCENARIOS},
    "Select":       {scenario: {"c": [], "s": [], "c_n": [], "s_n": []} for scenario in K_SCENARIOS}
}


for n in N_VALUES:
    str_n = str(n)
    

    sum_c = {"RandomSelect": {scen: 0 for scen in K_SCENARIOS}, "Select": {scen: 0 for scen in K_SCENARIOS}}
    sum_s = {"RandomSelect": {scen: 0 for scen in K_SCENARIOS}, "Select": {scen: 0 for scen in K_SCENARIOS}}
    
    for scenario_name, k_func in K_SCENARIOS.items():
        str_k = str(k_func(n))
        
        for _ in range(M_REPEATS):
            data = subprocess.check_output(['../ex1/generators/gen_rand', str_n, str_k], text=True)
            
            rsel = subprocess.run(['../ex1/RandSelect'], input=data, capture_output=True, text=True)
            lines = rsel.stdout.strip().split('\n')
            sum_c["RandomSelect"][scenario_name] += int(lines[-2])
            sum_s["RandomSelect"][scenario_name] += int(lines[-1])
            
            sel = subprocess.run(['../ex1/Select'], input=data, capture_output=True, text=True)
            lines = sel.stdout.strip().split('\n')
            sum_c["Select"][scenario_name] += int(lines[-2])
            sum_s["Select"][scenario_name] += int(lines[-1])
            
    
    for algo in results.keys():
        for scenario_name in K_SCENARIOS.keys():
            avg_c = sum_c[algo][scenario_name] / M_REPEATS
            avg_s = sum_s[algo][scenario_name] / M_REPEATS
            
            results[algo][scenario_name]["c"].append(avg_c)
            results[algo][scenario_name]["s"].append(avg_s)
            results[algo][scenario_name]["c_n"].append(avg_c / n)
            results[algo][scenario_name]["s_n"].append(avg_s / n)



for scenario_name in K_SCENARIOS.keys():
    fig, axs = plt.subplots(2, 2, figsize=(12, 10))
    
    tytul_k = scenario_name.replace('_', '/')
    fig.suptitle(f'Porównanie algorytmów dla {tytul_k}\n(n ∈ [1000...50000], m={M_REPEATS})', fontsize=16)

    # Średnia liczba porównań (c)
    axs[0, 0].plot(N_VALUES, results["RandomSelect"][scenario_name]["c"], 'b.-', label='RandomSelect')
    axs[0, 0].plot(N_VALUES, results["Select"][scenario_name]["c"], 'r.-', label='Select')
    axs[0, 0].set_title('Średnia liczba porównań (c)')
    axs[0, 0].set_xlabel('n')
    axs[0, 0].set_ylabel('Liczba porównań')
    axs[0, 0].legend()
    axs[0, 0].grid(True)

    # Średnia liczba przestawień (s)
    axs[0, 1].plot(N_VALUES, results["RandomSelect"][scenario_name]["s"], 'b.-', label='RandomSelect')
    axs[0, 1].plot(N_VALUES, results["Select"][scenario_name]["s"], 'r.-', label='Select')
    axs[0, 1].set_title('Średnia liczba przestawień (s)')
    axs[0, 1].set_xlabel('n')
    axs[0, 1].set_ylabel('Liczba przestawień')
    axs[0, 1].legend()
    axs[0, 1].grid(True)

    # c / n
    axs[1, 0].plot(N_VALUES, results["RandomSelect"][scenario_name]["c_n"], 'b.-', label='RandomSelect')
    axs[1, 0].plot(N_VALUES, results["Select"][scenario_name]["c_n"], 'r.-', label='Select')
    axs[1, 0].set_title('Iloraz c / n')
    axs[1, 0].set_xlabel('n')
    axs[1, 0].set_ylabel('c / n')
    axs[1, 0].legend()
    axs[1, 0].grid(True)

    # s / n
    axs[1, 1].plot(N_VALUES, results["RandomSelect"][scenario_name]["s_n"], 'b.-', label='RandomSelect')
    axs[1, 1].plot(N_VALUES, results["Select"][scenario_name]["s_n"], 'r.-', label='Select')
    axs[1, 1].set_title('Iloraz s / n')
    axs[1, 1].set_xlabel('n')
    axs[1, 1].set_ylabel('s / n')
    axs[1, 1].legend()
    axs[1, 1].grid(True)

    plt.tight_layout()
    
    safe_name = FILENAME_MAP[scenario_name]
    filename = f'plot_selection_{safe_name}.png'
    plt.savefig(filename)
    plt.close()