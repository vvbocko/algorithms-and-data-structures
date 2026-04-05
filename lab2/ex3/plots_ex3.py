import subprocess
import matplotlib.pyplot as plt

K_REPEATS = 10 
N_VALUES = list(range(1000, 50001, 2000))

results = {
    "Classic": {"c": [], "s": [], "c_n": [], "s_n": []},
    "Natural": {"c": [], "s": [], "c_n": [], "s_n": []}
}

# ./gen_asc ./gen_desc ./gen_rand
GENERATOR = './gen_asc' 

for n in N_VALUES:
    str_n = str(n)
    
    sum_c = {"Classic": 0, "Natural": 0}
    sum_s = {"Classic": 0, "Natural": 0}
    
    for _ in range(K_REPEATS):

        data = subprocess.check_output([GENERATOR, str_n], text=True)
        
        classic = subprocess.run(['./classic'], input=data, capture_output=True, text=True)
        lines = classic.stdout.strip().split('\n')
        sum_c["Classic"] += int(lines[-2])
        sum_s["Classic"] += int(lines[-1])
        
        natural = subprocess.run(['./natural'], input=data, capture_output=True, text=True)
        lines = natural.stdout.strip().split('\n')
        sum_c["Natural"] += int(lines[-2])
        sum_s["Natural"] += int(lines[-1])
    
        print(f"n={n:5d}")

    for algo in results.keys():
        avg_c = sum_c[algo] / K_REPEATS
        avg_s = sum_s[algo] / K_REPEATS
        
        results[algo]["c"].append(avg_c)
        results[algo]["s"].append(avg_s)
        results[algo]["c_n"].append(avg_c / n)
        results[algo]["s_n"].append(avg_s / n)


fig, axs = plt.subplots(2, 2, figsize=(12, 10))
fig.suptitle(f'Zadanie 3: Classic Merge vs Natural Merge (Gen: {GENERATOR})', fontsize=16)


axs[0, 0].plot(N_VALUES, results["Classic"]["c"], 'b.-', label='Classic Merge')
axs[0, 0].plot(N_VALUES, results["Natural"]["c"], 'g.-', label='Natural Merge')
axs[0, 0].set_title('Liczba porównań (c)')
axs[0, 0].set_xlabel('n')
axs[0, 0].set_ylabel('Porównania')
axs[0, 0].legend()
axs[0, 0].grid(True)

axs[0, 1].plot(N_VALUES, results["Classic"]["s"], 'b.-', label='Classic Merge')
axs[0, 1].plot(N_VALUES, results["Natural"]["s"], 'g.-', label='Natural Merge')
axs[0, 1].set_title('Liczba przestawień/kopiowań (s)')
axs[0, 1].set_xlabel('n')
axs[0, 1].set_ylabel('Kopiowania')
axs[0, 1].legend()
axs[0, 1].grid(True)

axs[1, 0].plot(N_VALUES, results["Classic"]["c_n"], 'b.-', label='Classic Merge')
axs[1, 0].plot(N_VALUES, results["Natural"]["c_n"], 'g.-', label='Natural Merge')
axs[1, 0].set_title('Iloraz c / n')
axs[1, 0].set_xlabel('n')
axs[1, 0].set_ylabel('c / n')
axs[1, 0].legend()
axs[1, 0].grid(True)

axs[1, 1].plot(N_VALUES, results["Classic"]["s_n"], 'b.-', label='Classic Merge')
axs[1, 1].plot(N_VALUES, results["Natural"]["s_n"], 'g.-', label='Natural Merge')
axs[1, 1].set_title('Iloraz s / n')
axs[1, 1].set_xlabel('n')
axs[1, 1].set_ylabel('s / n')
axs[1, 1].legend()
axs[1, 1].grid(True)

plt.tight_layout()
plt.savefig(f'zad3_wykres_{GENERATOR[2:]}.png')