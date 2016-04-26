#!/bin/bash

#SBATCH --account UCB7111101
# The job name will be displayed in the output of squeue
#SBATCH --job-name CacheSim-all

# Set a time limit for the job (HH:MM:SS)
#SBATCH --time 24:00:00

# Start a single task (de facto on a single node)
#SBATCH --ntasks 1

module load slurm
zcat /lustre/janus_scratch/$USER/traces-long/astar.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/default.conf /lustre/janus_scratch/$USER/astar-default.txt
zcat /lustre/janus_scratch/$USER/traces-long/astar.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/L1-2way.conf /lustre/janus_scratch/$USER/astar-L1-2way.txt
zcat /lustre/janus_scratch/$USER/traces-long/astar.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/L1-8way.conf /lustre/janus_scratch/$USER/astar-L1-8way.txt
zcat /lustre/janus_scratch/$USER/traces-long/astar.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/all-2way.conf /lustre/janus_scratch/$USER/astar-all-2way.txt
zcat /lustre/janus_scratch/$USER/traces-long/astar.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/all-4way.conf /lustre/janus_scratch/$USER/astar-all-4way.txt
zcat /lustre/janus_scratch/$USER/traces-long/astar.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/L1-small.conf /lustre/janus_scratch/$USER/astar-L1-small.txt
zcat /lustre/janus_scratch/$USER/traces-long/astar.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/L1-small4way.conf /lustre/janus_scratch/$USER/astar-L1-small4way.txt
zcat /lustre/janus_scratch/$USER/traces-long/astar.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/all-small.conf /lustre/janus_scratch/$USER/astar-all-small.txt
zcat /lustre/janus_scratch/$USER/traces-long/astar.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/all-FA.conf /lustre/janus_scratch/$USER/astar-all-FA.txt

zcat /lustre/janus_scratch/$USER/traces-long/bzip2.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/default.conf /lustre/janus_scratch/$USER/bzip2-default.txt
zcat /lustre/janus_scratch/$USER/traces-long/bzip2.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/L1-2way.conf /lustre/janus_scratch/$USER/bzip2-L1-2way.txt
zcat /lustre/janus_scratch/$USER/traces-long/bzip2.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/L1-8way.conf /lustre/janus_scratch/$USER/bzip2-L1-8way.txt
zcat /lustre/janus_scratch/$USER/traces-long/bzip2.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/all-2way.conf /lustre/janus_scratch/$USER/bzip2-all-2way.txt
zcat /lustre/janus_scratch/$USER/traces-long/bzip2.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/all-4way.conf /lustre/janus_scratch/$USER/bzip2-all-4way.txt
zcat /lustre/janus_scratch/$USER/traces-long/bzip2.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/L1-small.conf /lustre/janus_scratch/$USER/bzip2-L1-small.txt
zcat /lustre/janus_scratch/$USER/traces-long/bzip2.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/L1-small4way.conf /lustre/janus_scratch/$USER/bzip2-L1-small4way.txt
zcat /lustre/janus_scratch/$USER/traces-long/bzip2.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/all-small.conf /lustre/janus_scratch/$USER/bzip2-all-small.txt
zcat /lustre/janus_scratch/$USER/traces-long/bzip2.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/all-FA.conf /lustre/janus_scratch/$USER/bzip2-all-FA.txt

zcat /lustre/janus_scratch/$USER/traces-long/gobmk.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/default.conf /lustre/janus_scratch/$USER/gobmk-default.txt
zcat /lustre/janus_scratch/$USER/traces-long/gobmk.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/L1-2way.conf /lustre/janus_scratch/$USER/gobmk-L1-2way.txt
zcat /lustre/janus_scratch/$USER/traces-long/gobmk.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/L1-8way.conf /lustre/janus_scratch/$USER/gobmk-L1-8way.txt
zcat /lustre/janus_scratch/$USER/traces-long/gobmk.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/all-2way.conf /lustre/janus_scratch/$USER/gobmk-all-2way.txt
zcat /lustre/janus_scratch/$USER/traces-long/gobmk.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/all-4way.conf /lustre/janus_scratch/$USER/gobmk-all-4way.txt
zcat /lustre/janus_scratch/$USER/traces-long/gobmk.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/L1-small.conf /lustre/janus_scratch/$USER/gobmk-L1-small.txt
zcat /lustre/janus_scratch/$USER/traces-long/gobmk.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/L1-small4way.conf /lustre/janus_scratch/$USER/gobmk-L1-small4way.txt
zcat /lustre/janus_scratch/$USER/traces-long/gobmk.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/all-small.conf /lustre/janus_scratch/$USER/gobmk-all-small.txt
zcat /lustre/janus_scratch/$USER/traces-long/gobmk.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/all-FA.conf /lustre/janus_scratch/$USER/gobmk-all-FA.txt

zcat /lustre/janus_scratch/$USER/traces-long/libquantum.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/default.conf /lustre/janus_scratch/$USER/libquantum-default.txt
zcat /lustre/janus_scratch/$USER/traces-long/libquantum.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/L1-2way.conf /lustre/janus_scratch/$USER/libquantum-L1-2way.txt
zcat /lustre/janus_scratch/$USER/traces-long/libquantum.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/L1-8way.conf /lustre/janus_scratch/$USER/libquantum-L1-8way.txt
zcat /lustre/janus_scratch/$USER/traces-long/libquantum.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/all-2way.conf /lustre/janus_scratch/$USER/libquantum-all-2way.txt
zcat /lustre/janus_scratch/$USER/traces-long/libquantum.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/all-4way.conf /lustre/janus_scratch/$USER/libquantum-all-4way.txt
zcat /lustre/janus_scratch/$USER/traces-long/libquantum.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/L1-small.conf /lustre/janus_scratch/$USER/libquantum-L1-small.txt
zcat /lustre/janus_scratch/$USER/traces-long/libquantum.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/L1-small4way.conf /lustre/janus_scratch/$USER/libquantum-L1-small4way.txt
zcat /lustre/janus_scratch/$USER/traces-long/libquantum.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/all-small.conf /lustre/janus_scratch/$USER/libquantum-all-small.txt
zcat /lustre/janus_scratch/$USER/traces-long/libquantum.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/all-FA.conf /lustre/janus_scratch/$USER/libquantum-all-FA.txt

zcat /lustre/janus_scratch/$USER/traces-long/omnetpp.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/default.conf /lustre/janus_scratch/$USER/omnetpp-default.txt
zcat /lustre/janus_scratch/$USER/traces-long/omnetpp.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/L1-2way.conf /lustre/janus_scratch/$USER/omnetpp-L1-2way.txt
zcat /lustre/janus_scratch/$USER/traces-long/omnetpp.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/L1-8way.conf /lustre/janus_scratch/$USER/omnetpp-L1-8way.txt
zcat /lustre/janus_scratch/$USER/traces-long/omnetpp.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/all-2way.conf /lustre/janus_scratch/$USER/omnetpp-all-2way.txt
zcat /lustre/janus_scratch/$USER/traces-long/omnetpp.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/all-4way.conf /lustre/janus_scratch/$USER/omnetpp-all-4way.txt
zcat /lustre/janus_scratch/$USER/traces-long/omnetpp.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/L1-small.conf /lustre/janus_scratch/$USER/omnetpp-L1-small.txt
zcat /lustre/janus_scratch/$USER/traces-long/omnetpp.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/L1-small4way.conf /lustre/janus_scratch/$USER/omnetpp-L1-small4way.txt
zcat /lustre/janus_scratch/$USER/traces-long/omnetpp.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/all-small.conf /lustre/janus_scratch/$USER/omnetpp-all-small.txt
zcat /lustre/janus_scratch/$USER/traces-long/omnetpp.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/all-FA.conf /lustre/janus_scratch/$USER/omnetpp-all-FA.txt

zcat /lustre/janus_scratch/$USER/traces-long/sjeng.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/default.conf /lustre/janus_scratch/$USER/sjeng-default.txt
zcat /lustre/janus_scratch/$USER/traces-long/sjeng.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/L1-2way.conf /lustre/janus_scratch/$USER/sjeng-L1-2way.txt
zcat /lustre/janus_scratch/$USER/traces-long/sjeng.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/L1-8way.conf /lustre/janus_scratch/$USER/sjeng-L1-8way.txt
zcat /lustre/janus_scratch/$USER/traces-long/sjeng.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/all-2way.conf /lustre/janus_scratch/$USER/sjeng-all-2way.txt
zcat /lustre/janus_scratch/$USER/traces-long/sjeng.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/all-4way.conf /lustre/janus_scratch/$USER/sjeng-all-4way.txt
zcat /lustre/janus_scratch/$USER/traces-long/sjeng.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/L1-small.conf /lustre/janus_scratch/$USER/sjeng-L1-small.txt
zcat /lustre/janus_scratch/$USER/traces-long/sjeng.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/L1-small4way.conf /lustre/janus_scratch/$USER/sjeng-L1-small4way.txt
zcat /lustre/janus_scratch/$USER/traces-long/sjeng.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/all-small.conf /lustre/janus_scratch/$USER/sjeng-all-small.txt
zcat /lustre/janus_scratch/$USER/traces-long/sjeng.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/all-FA.conf /lustre/janus_scratch/$USER/sjeng-all-FA.txt

zcat /lustre/janus_scratch/$USER/traces-long/sjeng.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/default16.conf /lustre/janus_scratch/$USER/sjeng-default16.txt
zcat /lustre/janus_scratch/$USER/traces-long/sjeng.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/default32.conf /lustre/janus_scratch/$USER/sjeng-default32.txt
zcat /lustre/janus_scratch/$USER/traces-long/sjeng.gz | /projects/$USER/CacheSim/CacheSim/CacheSim /rc_scratch/$USER/default64.conf /lustre/janus_scratch/$USER/sjeng-default64.txt
