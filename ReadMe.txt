EPR v1.0.3
How to use EPR software:
1)Copy the source txt files to Src directory. They should have .bin extension for binary files and .txt for text files.
2)Open the file potentials.txt and put potentials if it's needed to be included in the matrix header.
The amount of potentials lines should be the same as txt files count in Src folder. Otherwise it will
be ignored
3)Open Settings.txt and set the reqired settings:
	1)Binary file. If the files are binary, it should be set to 1. Can take values 0 (false) or 1 (true).
	2)Save output files. This attribute allows to purify initial files. Can take values 0 (false) or 1 (true).
	3)Create total matrix 1. Creates one matrix with general x colomn and different y. Can be employd of
	the files with the same x values. Can take values 0 (false) or 1 (true).
	4)First order integration matrix and Second order integration matrix allow to integrate results 1 and 2 
	times respectively. Can take values 0 (false) or 1 (true).
	5)Left integtation edge and Right integtation edge serve for setting the integration edges. Can take
	0 (integrate all range) or any float.
Today it is compiled for Windows 10, can be build for any other OS.