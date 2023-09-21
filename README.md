# PPM Image Converter
 Program written in C that can convert PPM (Portable Pixel Map) images with certain transformations.
 Running the Makefile will create an executable file called "ppmcvt".
 It can perform the following transformations:
 -b: converts the input file to a Portable Bitmap (PBM) image. (Default transformation if no other transformation specified).
 -g: converts the input file to a Portable Gray Map (PGM) image using a specified max grayscale pixel value [1-65535]. 
 -i: isolates the specified RGB channel. Valid channels are "red", "green", or "blue".
 -r: removes the specified RGB channel. Valid channels are "red", "green", or "blue".
 -s: a sepia transformation is applied. 
 -m: vertically mirrors the first half of the input image to the second half.
 -t: reduces the input image to a thumbnail by a given scaling factor [1-8]. 
 -n: tiles thumbnails of the input image by a given scaling factor [1-8]. 
 -o: writes output image to the specified file. Existent output files will be overwritten.

 ONLY ONE TRANSFORMATION CAN BE APPLIED AT THE SAME TIME.

 THe following transformations require an argument to work:
 -g with a value from 1-65535
 -i with either red, blue, or green.
 -r with either red, blue, or green. 
 -t with a value from 1-8.
 -n with a value from 1-8.

 Command to run transformations:

 ppmcvt -b -o output_name input_file
-output_name is the name you want your output file to be and input_file is the image you want your transformation to be applied on. 

Command to run transformation if an argument is needed:

ppmcvt -g arg -o output_name input_file
-arg is a placeholder here for whatever argument is needed for the transformation to run. 
 
 
