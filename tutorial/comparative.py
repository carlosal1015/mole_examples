import time
import numpy as np
import scipy.sparse as sp
import matplotlib.pyplot as plt

# Define matrix sizes to test (adjust based on system memory)
N_values = [100, 500, 1000, 2000, 5000, 10000]

# Lists to store results
memory_dense = []
memory_sparse = []
time_dense = []
time_sparse = []

# Number of repeats for timing measurements
repeats = 5

for N in N_values:
    print(f"Processing N={N}...")

    # Dense matrix measurements
    dense_times = []
    for _ in range(repeats):
        start = time.perf_counter()
        dense_mat = np.eye(N) - np.eye(N, k=1)
        end = time.perf_counter()
        dense_times.append(end - start)
        del dense_mat  # Free memory
    avg_dense_time = np.mean(dense_times)
    time_dense.append(avg_dense_time)

    # Memory for dense
    dense_mat = np.eye(N) - np.eye(N, k=1)
    memory_dense.append(dense_mat.nbytes)
    del dense_mat

    # Sparse matrix measurements
    sparse_times = []
    for _ in range(repeats):
        start = time.perf_counter()
        sparse_mat = sp.eye(N) - sp.eye(N, k=1)
        end = time.perf_counter()
        sparse_times.append(end - start)
        del sparse_mat
    avg_sparse_time = np.mean(sparse_times)
    time_sparse.append(avg_sparse_time)

    # Memory for sparse
    sparse_mat = sp.eye(N) - sp.eye(N, k=1)
    sparse_mat_csr = sparse_mat.tocsr()
    mem = (sparse_mat_csr.data.nbytes +
           sparse_mat_csr.indices.nbytes +
           sparse_mat_csr.indptr.nbytes)
    memory_sparse.append(mem)
    del sparse_mat, sparse_mat_csr

# Convert memory to MiB
memory_dense_mib = [x / (1024 ** 2) for x in memory_dense]
memory_sparse_mib = [x / (1024 ** 2) for x in memory_sparse]

# Plot Memory Usage
plt.figure(figsize=(10, 6))
plt.plot(N_values, memory_dense_mib, 'o-', label='Dense (NumPy)')
plt.plot(N_values, memory_sparse_mib, 's-', label='Sparse (SciPy)')
plt.xscale('log')
plt.yscale('log')
plt.xlabel('Matrix Order (N)')
plt.ylabel('Memory Usage (MiB)')
plt.legend()
plt.grid(True, which='both', linestyle='--')
plt.title('Memory Usage vs. Matrix Order')
plt.savefig('memory_usage.png')
plt.close()

# Plot Assembly Time
plt.figure(figsize=(10, 6))
plt.plot(N_values, time_dense, 'o-', label='Dense (NumPy)')
plt.plot(N_values, time_sparse, 's-', label='Sparse (SciPy)')
plt.xscale('log')
plt.yscale('log')
plt.xlabel('Matrix Order (N)')
plt.ylabel('Assembly Time (seconds)')
plt.legend()
plt.grid(True, which='both', linestyle='--')
plt.title('Assembly Time vs. Matrix Order')
plt.savefig('assembly_time.png')
plt.close()
