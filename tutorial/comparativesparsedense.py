from numpy import eye, empty, insert
from scipy.sparse import eye_array
import matplotlib.pyplot as plt
from time import perf_counter


def get_free_memory():
    with open("/proc/meminfo", "r") as f:
        lines = f.readlines()
    for line in lines:
        if "MemFree" in line:
            parts = line.split()
            return int(parts[1]) * 1024
    return 0


repeats = 5
max_N = 3000
# max_N = int((get_free_memory() // (2 * 3.1)) ** 0.5)

# memory_dense = empty(shape=(max_N, 1))
# memory_sparse = empty(shape=(max_N, 1))
time_dense = empty(shape=max_N)
time_sparse = empty(shape=max_N)

for N in range(1, max_N, 2 * 1024):
    """Measure allocation time sparse vs dense
    """
    dense_times = empty(shape=repeats)
    sparse_times = empty(shape=repeats)
    for _ in range(repeats):
        start = perf_counter()
        dense_mat = eye(N=N) - eye(N=N, k=1)
        end = perf_counter()
        insert(dense_times, _, end - start, axis=0)
        # insert(memory_dense, dense_mat.nbytes)
        del dense_mat

        start = perf_counter()
        sparse_mat = eye_array(m=N) - eye_array(m=N, k=1)
        end = perf_counter()
        insert(sparse_times, _, end - start, axis=0)
        # append(
        #     memory_sparse,
        #     sparse_mat.data.nbytes
        #     + sparse_mat.indices.nbytes
        #     + sparse_mat.indptr.nbytes,
        # )
        del sparse_mat

    insert(time_dense, N, dense_times.mean(), axis=0)
    insert(time_sparse, N, sparse_times.mean(), axis=0)

    # print(f"Dense (NumPy) assembly time (s): {round(etime, 3)}")
    # print(f"Dense (NumPy) memory (MiB): {round(memory_dense / 1024 / 1024, 3)}")
    # print(f"Dense (NumPy) memory (GiB): {round(memory_dense / 1024 / 1024 / 1024, 3)}")
    # print(f"Sparse (SciPy) assembly time (s): {round(etime, 3)}")
    # print(f"Sparse (SciPy) memory (MiB): {round(memory_sparse / 1024 / 1024, 3)}")
    # print(
    #     f"Sparse (SciPy) memory (GiB): {round(memory_sparse / 1024 / 1024 / 1024, 3)}"
    # )

print(time_dense, time_sparse)
