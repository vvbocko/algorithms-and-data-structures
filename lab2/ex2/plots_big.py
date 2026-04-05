import subprocess
import matplotlib.pyplot as plt

K_REPEATS = 100
THRESHOLD = "8"
N_VALUES = list(range(1000, 50001, 1000))

results = {
    "Quick":     {"c": [], "s": [], "c_n": [], "s_n": []},
    "Hybrid":    {"c": [], "s": [], "c_n": [], "s_n": []}
}

print(f"k={K_REPEATS}")

for n in N_VALUES:
    str_n = str(n)
    
    sum_c = {"Quick": 0, "Hybrid": 0}
    sum_s = {"Quick": 0, "Hybrid": 0}
    
    for _ in range(K_REPEATS):
        data = subprocess.check_output(['../ex1/generators/rand.exe', str_n], text=True)
        
        qui = subprocess.run(['../ex1/quick.exe'], input=data, capture_output=True, text=True)
        lines = qui.stdout.strip().split('\n')
        sum_c["Quick"] += int(lines[-2])
        sum_s["Quick"] += int(lines[-1])
        
        hyb = subprocess.run(['../ex1/hybrid.exe', THRESHOLD], input=data, capture_output=True, text=True)
        lines = hyb.stdout.strip().split('\n')
        sum_c["Hybrid"] += int(lines[-2])
        sum_s["Hybrid"] += int(lines[-1])


    print(f"n={n}")
    for algo in results.keys():
        avg_c = sum_c[algo] / K_REPEATS
        avg_s = sum_s[algo] / K_REPEATS
        
        results[algo]["c"].append(avg_c)
        results[algo]["s"].append(avg_s)
        results[algo]["c_n"].append(avg_c / n)
        results[algo]["s_n"].append(avg_s / n)


fig, axs = plt.subplots(2, 2, figsize=(10, 8))
fig.suptitle(f'Porównanie algorytmów sortowania (n ∈ [1000, 2000, ..., 50000], k={K_REPEATS})', fontsize=16)

# Średnia liczba porównań (c)
axs[0, 0].plot(N_VALUES, results["Quick"]["c"], 'b.-', label='Quick')
axs[0, 0].plot(N_VALUES, results["Hybrid"]["c"], 'g.-', label='Hybrid')
axs[0, 0].set_title('Średnia liczba porównań (c)')
axs[0, 0].set_xlabel('n')
axs[0, 0].set_ylabel('Liczba porównań')
axs[0, 0].legend()
axs[0, 0].grid(True)

# Średnia liczba przestawień (s)
axs[0, 1].plot(N_VALUES, results["Quick"]["s"], 'b.-', label='Quick')
axs[0, 1].plot(N_VALUES, results["Hybrid"]["s"], 'g.-', label='Hybrid')
axs[0, 1].set_title('Średnia liczba przestawień (s)')
axs[0, 1].set_xlabel('n')
axs[0, 1].set_ylabel('Liczba przestawień')
axs[0, 1].legend()
axs[0, 1].grid(True)

# c / n
axs[1, 0].plot(N_VALUES, results["Quick"]["c_n"], 'b.-', label='Quick')
axs[1, 0].plot(N_VALUES, results["Hybrid"]["c_n"], 'g.-', label='Hybrid')
axs[1, 0].set_title('Iloraz c / n')
axs[1, 0].set_xlabel('n')
axs[1, 0].set_ylabel('c / n')
axs[1, 0].legend()
axs[1, 0].grid(True)

# s / n
axs[1, 1].plot(N_VALUES, results["Quick"]["s_n"], 'b.-', label='Quick')
axs[1, 1].plot(N_VALUES, results["Hybrid"]["s_n"], 'g.-', label='Hybrid')
axs[1, 1].set_title('Iloraz s / n')
axs[1, 1].set_xlabel('n')
axs[1, 1].set_ylabel('s / n')
axs[1, 1].legend()
axs[1, 1].grid(True)


plt.tight_layout()
plt.savefig(f'plots_big_k{K_REPEATS}.png')