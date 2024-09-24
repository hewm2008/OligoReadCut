#!/bin/sh
#$ -S /bin/sh
#Version1.0	P_bc_rd@genomics.org.cn	2018-02-8
echo Start Time : 
date
echo g++	-O3	-g	src/OligoReadCut.cpp  	-L ./lib	-lz	-o	bin/OligoReadCut -static	
/share/appspace_data/shared_groups/BGI/01.Softwares/03.Soft_ALL/gcc-6.4.0/bin/g++	-O3	-g	src/OligoReadCut.cpp	   -L	/zfssz5/BC_PUB/Software/01.Usr/lib/  -I ./include/ -L ./lib	-lz	-o	bin/OligoReadCut	 -static 
echo End Time : 
date
