#!/usr/bin/env python3
import io
import subprocess
import random
import re
import sys
import argparse
import time
from threading import Timer

# /usr/lib64/openmpi/bin/mpirun
# /opt/pgi/linux86-64/2015/mpi/mpich/bin/mpirun
# -iface eth0
#base_cmd = """
#mpirun
#-mca btl_tcp_if_include ens6f0
#-hostfile /home/esaliba/GradMPI/LABMNGR_T/hosts
#-npernode 4
#""".split()
base_cmd = """
mpiexec 
-hostfile LABMNGR_T/hosts 
--mca plm_rsh_no_tree_spawn 1 
--mca btl_tcp_if_include ens6f0 
--prefix /usr/lib64/openmpi 
--map-by ppr:4:node
NPB3.3.1/NPB3.3-MPI/bin/bt.B.64
""".split()
timeout = 1800 # 30 minutes

time_re = re.compile(r"Time in seconds.*?([0-9.]+)")
# time_re = re.compile(r"Total wall time: ([0-9]+):([0-9]+):([0-9]+)")
mode_re = re.compile(r"SDC Detection Method (\w+)")

parser = argparse.ArgumentParser()
parser.add_argument('--iterations', '-i', type=int, default=1, help='number of iterations')
parser.add_argument('--replication', '-r', type=int, action='append', help='replication level')
parser.add_argument('exe', type=str, nargs='+', help='MPI application')
args = parser.parse_args()

repls = args.replication if args.replication else [1]

for i in range(args.iterations):
    for r in repls:
        for e in args.exe:
            nprocs = int(e.split('.')[-1])
            cmd = base_cmd + [
                "-np", str(nprocs * r),
                e,
                "-mrmpi-np", str(nprocs)
                ]
            print(" ".join(cmd))

            #print(e, nprocs, r, end=" ")
            sys.stdout.flush()

            start_time = time.monotonic()
            proc = subprocess.Popen(base_cmd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)

            def kill_proc():
                proc.kill()
                print("killed", end=" ")
            timer = Timer(timeout, kill_proc)

            try:
                timer.start()
                time_found = False
                for line in io.TextIOWrapper(proc.stdout, encoding="utf-8"):
                    match = mode_re.search(line)
                    if match:
                        print(match.group(1))
                        sys.stdout.flush()
                    match = time_re.search(line)
                    if match and not time_found:
                        print(match.group(1))
                        sys.stdout.flush()
                        time_found = True
                        # print(line, end='')
            finally:
                timer.cancel()

            print('{0:.2f}'.format(time.monotonic() - start_time), "hello")
