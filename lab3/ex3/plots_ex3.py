import subprocess
import matplotlib.pyplot as plt

M_REPEATS = 30
N_VALUES = list(range(1000, 50001, 1000))
GROUP_SIZES = [3, 5, 7, 9, 19, 21]

results = {g: {"c": [], "s": [], "t": []} for g in GROUP_SIZES}

print(f"Badanie wplywu rozmiaru grupy na Select (powtórzenia={M_REPEATS})...")

for n in N_VALUES:
    str_n = str(n)
    str_k = str(n // 2)
    
    sum_c = {g: 0 for g in GROUP_SIZES}
    sum_s = {g: 0 for g in GROUP_SIZES}
    sum_t = {g: 0 for g in GROUP_SIZES}
    
    for _ in range(M_REPEATS):
        data = subprocess.check_output(['../ex1/generators/gen_rand', str_n, str_k], text=True)
        
        for g in GROUP_SIZES:
            sel = subprocess.run(['./select_ex3', str(g)], input=data, capture_output=True, text=True)
            lines = sel.stdout.strip().split('\n')
            sum_c[g] += int(lines[-3])
            sum_s[g] += int(lines[-2])
            sum_t[g] += int(lines[-1])
            
    print(f"Przetestowano n={n:5d}")
    
    for g in GROUP_SIZES:
        results[g]["c"].append(sum_c[g] / M_REPEATS)
        results[g]["s"].append(sum_s[g] / M_REPEATS)
        results[g]["t"].append(sum_t[g] / M_REPEATS)


fig, axs = plt.subplots(1, 3, figsize=(18, 5))
fig.suptitle(f'Wpływ rozmiaru grupy na algorytm SELECT (Mediana, m={M_REPEATS})', fontsize=16)


for g in GROUP_SIZES:
    axs[0].plot(N_VALUES, results[g]["c"], '.-', label=f'Grupa {g}')
axs[0].set_title('Średnia liczba porównań')
axs[0].set_xlabel('n')
axs[0].set_ylabel('Porównania')
axs[0].legend()
axs[0].grid(True)


for g in GROUP_SIZES:
    axs[1].plot(N_VALUES, results[g]["s"], '.-', label=f'Grupa {g}')
axs[1].set_title('Średnia liczba przestawień')
axs[1].set_xlabel('n')
axs[1].set_ylabel('Przestawienia')
axs[1].legend()
axs[1].grid(True)


for g in GROUP_SIZES:
    axs[2].plot(N_VALUES, results[g]["t"], '.-', label=f'Grupa {g}')
axs[2].set_title('Średni czas działania (µs)')
axs[2].set_xlabel('n')
axs[2].set_ylabel('Czas [mikrosekundy]')
axs[2].legend()
axs[2].grid(True)

plt.tight_layout()
plt.savefig('plot_group_sizes.png')
print("Zapisano wykres do pliku 'plot_group_sizes.png'.")