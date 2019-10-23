BEGIN {

        recieved = 0;
        dropped = 0;
  }

   

  /^r.*/ {

          recieved ++ ;

  }

  

 /^d.*/ {

         dropped ++ ;

 }

  

 END {

    if( dropped!= 0)
        printf "total recieved: %d, total dropped: %d, ratio:%.4f",recieved,dropped,(recieved/dropped); 
    else
        printf "hi"
 }

  