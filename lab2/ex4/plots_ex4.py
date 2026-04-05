import subprocess
import matplotlib.pyplot as plt

PAIRS = [
    (1, 100000), (2, 50000), (4, 25000), (5, 20000), (10, 10000),
    (20, 5000), (40, 2500), (50, 2000), (100, 1000), (200, 500),
    (250, 400), (316, 316), (400, 250), (500, 200), (1000, 100),
    (2000, 50), (2500, 40), (5000, 20), (10000, 10), (20000, 5),
    (25000, 4), (50000, 2), (100000, 1)
]

saddleback_results = []
binary_results = []
x_labels = []

for m, n in PAIRS:
    result = subprocess.run(['./matrix', str(m), str(n)], capture_output=True, text=True)
    
    comps = result.stdout.strip().split()
    saddleback_results.append(int(comps[0]))
    binary_results.append(int(comps[1]))
    x_labels.append(f"{m}x{n}")
    
    print(f"Macierz {m}x{n} -> Saddleback: {comps[0]:>6}, Binary: {comps[1]:>6}")


plt.figure(figsize=(14, 7))
plt.plot(range(len(PAIRS)), saddleback_results, 'r.-', label='Saddleback (Złożoność: O(m + n))')
plt.plot(range(len(PAIRS)), binary_results, 'b.-', label='Multi Binary Search (Złożoność: O(min(m,n) * log(max(m,n))))')

plt.xticks(range(len(PAIRS)), x_labels, rotation=45, ha='right')
plt.title('Zadanie 4: Porównanie algorytmów dla macierzy o stałym rozmiarze (m * n = 100 000)')
plt.xlabel('Wymiary macierzy (Wiersze x Kolumny)')
plt.ylabel('Liczba porównań w najgorszym przypadku')
plt.legend()
plt.grid(True)
plt.tight_layout()

plt.savefig('zad4_wykres.png')