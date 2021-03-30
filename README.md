   
    # file_converter_project
    COP-4338 Systems Programming
    Programming Assignment 5
    FIU Spring 2021
    Professor Kianoosh G. Boroojeni
    By: Laura Figueroa PID-4918449
    
    program converts a file format into another
    
    It supports the following formats: .csv .tc9 .tl5 .tr9
    
    from/to csv tl5 tr9 tc9
        csv  Y   Y   Y   Y
        tl5  Y   Y   Y   Y
        tr9  Y   Y   Y   Y
        tc9  Y   Y   Y   Y
    
    Summary:
    Available commands:
        1- 'Quit' -> ends the program
        2- 'convert source.xxx destination.yyy'
            a.transforms the content of a file of type .xxx into a file of type .yyy
                i  -> in the main class, the input is read and the input and output files are sent to the appropriate method:
                ii -> depending on the .yyy file, either the toTR9(), toTL5(),toTC9(), or toCSV() will be called
