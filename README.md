hexdump
=======

simple hexdump utility. Also does base64 encoding and decoding

--On incorrect command, the program outputs the correct usage
--Base64 decoding code handles cases such as newlines in input & illegal characters before parsing the file. 
For this reason I had to read the input to a temporary file as stdin would not work for multiple passes over the input.
--Base64 algorithm taken from http://en.wikibooks.org/wiki/Algorithm_Implementation/Miscellaneous/Base64 but modified for ease of understanding
