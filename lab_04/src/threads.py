import subprocess

test_numbers = [-2.1, -1, 0, 1, 5, 13.54]
test_n_threads = range(1, 20, 1)

with open('threads.txt', 'w') as file:
    file.write(f'type\tthreads\ttotal time, s\ttime per step, us\tn\tx\n')
    for n_threads in test_n_threads:
        for x in test_numbers:
            res = subprocess.run(
                [r"./build/threads", str(x), str(n_threads)], capture_output=True)
            output = res.stdout.decode().split('\n')
            x, n, _ = output[6].split(';')
            x = float(x.split('=')[-1])
            n = float(n.split('=')[-1])
            elapsed = float(output[7].split('time elapsed (s): ')[-1])
            tps = float(output[8].split('time per step (us): ')[-1])
            file.write(f'threading\t{n_threads}\t{elapsed}\t{tps}\t{n}\t{x}\n')
            print(f'{n_threads}\t{elapsed}\t{tps}\t{x}')
