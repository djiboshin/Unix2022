from calendar import c
import subprocess
from sys import stderr
import time

test_numbers = [-2.1, -1, 0, 1, 5, 13.54]
test_n_threads = range(1, 20, 1)
N = 100000000
with open('process.txt', 'w') as file:
    file.write(f'type\tthreads\ttotal time, s\ttime per step, us\tn\tx\n')
    for n_threads in test_n_threads:
        for x in test_numbers:
            processes = []

            start = time.time()
            for _ in range(n_threads):
                processes.append(subprocess.Popen(
                    [r"./build/sequence", str(x), str(N/n_threads)],  stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL))

            for i in range(n_threads):
                processes[i].wait()

            elapsed = time.time() - start
            tps = float(elapsed/N * 1e6)

            file.write(f'processes\t{n_threads}\t{elapsed}\t{tps}\t{N}\t{x}\n')
            print(f'{n_threads}\t{elapsed}\t{tps}\t{x}')
