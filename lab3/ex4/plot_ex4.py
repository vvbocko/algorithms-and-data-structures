import subprocess
import matplotlib.pyplot as plt
import random
import math

M_REPEATS = 50
N_VALUES = list(range(10000, 300001, 10000)) 

def f1(x):
    return math.pow(math.log2(x + 1), 3)


def f2(x):
    return math.sqrt(x) + math.log2(x + 1)


for func_num in [1, 2]:
    results_classic = []
    results_altered = []

    for n in N_VALUES:
        sum_classic = 0
        sum_altered = 0
        
        for _ in range(M_REPEATS):
            target_idx = random.randint(0, n - 1)
            
            if func_num == 1:
                q = random.uniform(f1(target_idx), f1(target_idx) + 10.0)
            else:
                q = random.uniform(f2(target_idx), f2(target_idx) + 50.0)
            
            str_n = str(n)
            str_q = f"{q:.10f}"
            str_fnum = str(func_num)
            
            gen_proc = subprocess.Popen(['./gen4', str_n, str_q, str_fnum], stdout=subprocess.PIPE, text=True)
            
            solve_proc = subprocess.Popen(['./ex4'], stdin=gen_proc.stdout, stdout=subprocess.PIPE, text=True)
            
            gen_proc.stdout.close()
            out, _ = solve_proc.communicate()
            
            lines = out.strip().split('\n')
            sum_classic += int(lines[-2])
            sum_altered += int(lines[-1])
            
        avg_classic = sum_classic / M_REPEATS
        avg_altered = sum_altered / M_REPEATS
        
        results_classic.append(avg_classic)
        results_altered.append(avg_altered)
        
        print(f"Rozmiar n={n:6d} | Classic BS: {avg_classic:5.1f} por. | Altered BS: {avg_altered:5.1f} por.")
        
    plt.figure(figsize=(10, 6))
    
    plt.plot(N_VALUES, results_classic, 'b.-', label='Binary Search')
    plt.plot(N_VALUES, results_altered, 'r.-', label='Altered Binary Search')
    
    wzor = "f(x) = (log2(x+1))^3" if func_num == 1 else "f(x) = sqrt(x) + log2(x+1)"
    plt.title(f'Porównanie kosztów algorytmów wyszukiwania\n{wzor}')
    plt.xlabel('Rozmiar tablicy (N)')
    plt.ylabel('Średnia liczba porównań kluczy')
    plt.legend()
    plt.grid(True)
    
    filename = f'plot_task4_func{func_num}.png'
    plt.savefig(filename)
    plt.close()