#!/bin/sh
echo Start Time : 
date
../bin/OligoReadCut	-InFq1	Oligo.R1.fq.gz	-InFq2	Oligo.R2.fq.gz	-OutFq1	NewOligo.R1.fq	-OutFq2	NewOligo.R2.fq	
echo End Time : 
date
