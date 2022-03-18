import time
import numba as nb
x = 1
@nb.njit(nb.void())
def step():
    x**2 - x**2 + x**4-x**5+x+x
    

if __name__ == '__main__':
    step()
    while True:
        try:
            n = int(input("Int: "))
            print(f"n={n}; solving...")
            begin = time.process_time()
            for _ in range(int(n)):
                step()
            end = time.process_time()
            elapsed = end - begin
            print(f'time per step (us): {elapsed/n * 1e6}')
        except ValueError:
            print("exit")
            break