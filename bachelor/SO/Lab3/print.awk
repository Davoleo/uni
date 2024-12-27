BEGIN {
    getline; 
    print "Start of file:", FILENAME 
}

{ 
    print $1, $3, $NF 
}

END { 
    print "End of file" 
}