# Links
- [NS2 Basics](https://www.tutorialsweb.com/ns2/NS2-5.htm)
- [TCL Basics](https://www.tcl.tk/about/language.html)
- [ns-simple.tcl](http://nile.wpi.edu/NS/simple_ns.html)
- [Monitoring Network Traffic](https://www.nsnam.com/2013/03/awk-scripts-for-ns2-to-process-data.html)

### Other info
Tcl (Tool Command Language) is a very powerful but easy to learn dynamic programming language, suitable for a very wide range of uses, including web and desktop applications, networking, administration, testing and many more. Open source and business-friendly, Tcl is a mature yet evolving language that is truly cross platform, easily deployed and highly extensible.

Tk is a graphical user interface toolkit that takes developing desktop applications to a higher level than conventional approaches. Tk is the standard GUI not only for Tcl, but for many other dynamic languages, and can produce rich, native applications that run unchanged across Windows, Mac OS X, Linux and more. 

IN TCL:
- [] means subquery/return. Statement within [] will execute first and then will be replaced instead of []
- {} & "" define lists
    - when using "", tcl variable values are substituted
        
            set b 2
            set t { 1 $b 3 }
            puts stdout $t
        
        output
        
            1 $b 3
    - when using {}, tcl variable values are not substituted    
            
            set b 2
            set t " 1 $b 3 "
            puts stdout $t
        output
            
            1 2 3