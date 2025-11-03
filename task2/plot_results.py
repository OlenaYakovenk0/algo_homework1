import pandas as pd
import matplotlib.pyplot as plt


df = pd.read_csv("results.csv")


df['variant']  = df['variant'].astype(str)
df['size']     = df['size'].astype(int)
df['mem_MB']   = df['mem_MB'].astype(float)
df['total_ops']= df['total_ops'].astype(int)


df = df.sort_values(by=['variant', 'size'])


def plot_metric(y, ylabel, title, filename, logx=True):
    plt.figure(figsize=(8,5))
    for v in df['variant'].unique():
        sub = df[df['variant'] == v]
        plt.plot(sub['size'], sub[y], marker='o', label=v)
    if logx:
        plt.xscale('log')
    plt.xlabel("Number of students (N)")
    plt.ylabel(ylabel)
    plt.title(title)
    plt.legend(title="Variant")
    plt.grid(True, which='both', linestyle='--', alpha=0.6)
    plt.tight_layout()
    plt.savefig(filename, dpi=300)
    plt.close()


plot_metric('mem_MB', "Memory usage (MB)",
            "Memory usage vs database size", "memory_vs_size.png")

plot_metric('total_ops', "Total operations (in 10 s)",
            "Total operations vs database size", "total_ops_vs_size.png")
