# OligoReadCut
<b>OligoReadCut: A new simple and efficient software to cut off Oligo read</b>

###  1) Install
------------
The <b>new version</b> will be updated and maintained in <b>[hewm2008/OligoReadCut](https://github.com/hewm2008/OligoReadCut)</b>, please click below Link to download the latest version
</br><p align="center"><b>[hewm2008/OligoReadCut](https://github.com/hewm2008/OligoReadCut)</b></p>
<b> [Download](https://github.com/hewm2008/OligoReadCut/archive/v1.30.tar.gz) </b>

For <b>linux/Unix </b> static
</br>you can use the statically compiled programs <i>directly</i>
<pre>
         chmod 755 ./bin/OligoReadCut
        ./bin/OligoReadCut </pre>

  </br> Just [make]  or [sh  make.sh ]  to compile this software.the final software can be found in the Dir <b>[bin/OligoReadCut]</b>
  </br> For <b>linux /Unix </b> and <b>macOS</b>
  <pre>
        tar -zxvf  OligoReadCutXXX.tar.gz             # if Link do not work ,Try <b>re-install</b> [zlib]library
        cd OligoReadCutXXX;                           # [zlib] and copy them to the library Dir
        make ; make clean                        # OligoReadCut-xx/src/include/zlib
        ./bin/OligoReadCut  </pre>
  
**Note:** If fail to link,try to <b>re-install</b> the libraries [**_zlib_**](https://zlib.net/)

###  2) Example of OligoReadCut
------------
* 1) Parameter description:
```php

	./bin/OligoReadCut

	Usage:OligoReadCut  -InFq <Oligo.R2.fq>  -OutFq <out.fq> [options]

		-InFq       <str>   File name of InFq Input
		-OutFq      <str>   Prefix of OUT File name

		-Adapter1   <str>   Input adapters1 seq [TCTGCG]
		-Adapter2   <str>   Input adapters2 seq [CCTTCC]

		-help               Show this help[hewm2008 v1.30]



```

* 2) To Stat Fq file see the Dir [example]

```
# 2.1)  Oligo Read2  fq file
	./bin/OligoReadCut -InFq1 Oligo.R1.fq -InFq2 Oligo.R2.fq  -OutFq1 NewOligo.R1.fq -OutFq2 NewOligo.R2.fq
 
```


###  3) Results
------------
	Read1 length 30bp   ---> Read1 20bp  (index1+index2)
	Read2 length 100bp  ---> Read2 30bp  (UMI+index1+index2)

###  4) Discussing
------------
- [:email:](https://github.com/hewm2008/OligoReadCut) hewm2008@gmail.com / hewm2008@qq.com
- join the<b><i> QQ Group : 125293663</b></i>


######################swimming in the sky and flying in the sea ########################### ##
