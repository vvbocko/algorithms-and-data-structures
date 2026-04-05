import subprocess

n = "10000"
k = 10
best_threshold = 0
min_operations = float('inf')

print(f"najlepszy próg dla Hybrydowego (n={n}, k={k})")
print("-" * 100)

for t in range(2, 51):
    sum_comparisons = 0
    sum_swaps = 0
    
    for _ in range(k):
        data = subprocess.check_output(['../ex1/generators/rand.exe', str(n)], text=True)
        hyb = subprocess.run(['../ex1/hybrid.exe', str(t)], input=data, capture_output=True, text=True)
        
        lines = hyb.stdout.strip().split('\n')
        sum_comparisons += int(lines[-2])
        sum_swaps += int(lines[-1])
        
    avg_comparisons = sum_comparisons // k
    avg_swaps = sum_swaps // k
    total_operations = avg_comparisons + avg_swaps
    
    print(f"Próg: {t:2d}      | Śr. Porównania: {avg_comparisons:8d}      | Śr. Przestawienia: {avg_swaps:8d}      | Suma: {total_operations:8d}")
    
    if total_operations < min_operations:
        min_operations = total_operations
        best_threshold = t

print("-" * 100)
print(f"Najmniejszą sumę operacji ma próg: {best_threshold}")