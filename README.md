# file_converter_project
program converts a file format into another

It supports the following formats:

 .csv (comma separated values) file: stores tabular data in plain text. Each line of the
file represents a table row containing one or more cells separated by commas.

 .tl5 file: stores tabular data in plain text. Each line of the file represents a table row
containing one or more cells separated by ’|’ character. Each cell is 5-characters long
and contains a left-aligned string. If the string stored in a cell has n < 5 characters,
the rest of it will be filled with spaces; i.e. there will be 5 −n extra space characters in
the field after the string. However, if a string with more than 5 characters is supposed
to be placed in a cell, only its first 5 characters is stored in the cell.
