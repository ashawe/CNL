BEGIN {

fromNode=1; toNode=3;

lineCount = 0;totalBits = 0;
droppedBits = 0;

}

/^r/ {

    totalBits += 8*$6;

if ( lineCount==0 ) {

timeBegin = $2; lineCount++;

} else {

timeEnd = $2;

};

};

/^d/{
     droppedBits += 8*$6;
}

END{

duration = timeEnd-timeBegin;

printf("Number of records is %d\n", NR);

print "Output: ";

#print "Transmission: N" fromNode "->N" toNode; 

print "  - Total transmitted bits = " totalBits " bits";

print "  - Total droppedBits bits = " droppedBits " bits";

print "  - duration = " duration " s"; 

print "  - Thoughput = "  totalBits/duration/1e3 " kbps.";

};