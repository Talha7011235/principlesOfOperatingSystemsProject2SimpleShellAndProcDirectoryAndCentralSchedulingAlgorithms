# makefile for fork() program
#
# make forkSampleCProgramExtraCreditPartOne - for HussainTalha_forkSampleCProgramExtraCreditPartOne.c File
# make 3forks - for HussainTalha_3forks.c File
# make forkExperiment - for HussainTalha_forkExperiment.c File

CC=gcc
CFLAGS=-Wall

clean:
	rm -rf *.o
	rm -rf forkSampleCProgramExtraCreditPartOne
	rm -rf 3forks
	rm -rf forkExperiment

forkSampleCProgramExtraCreditPartOne: HussainTalha_forkSampleCProgramExtraCreditPartOne.c
	$(CC) $(CFLAGS) -o forkSampleCProgramExtraCreditPartOne HussainTalha_forkSampleCProgramExtraCreditPartOne.c

3forks: HussainTalha_3forks.c
	$(CC) $(CFLAGS) -o 3forks HussainTalha_3forks.c

forkExperiment:
	$(CC) $(CFLAGS) -o forkExperiment HussainTalha_forkExperiment.c
