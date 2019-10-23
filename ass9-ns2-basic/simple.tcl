set ns [new Simulator]

$ns color 1 Blue

set nf [open out.nam w]
$ns namtrace-all $nf

set nt [open out.tr w]
$ns trace-all $nt

proc finish {} {

    global ns nf nt
    $ns flush-trace

    close $nf
    close $nt

    exec nam out.nam &
    exit 0
}

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]

$ns duplex-link $n0 $n1 2Mb 10ms DropTail
$ns duplex-link $n1 $n2 1Mb 10ms DropTail

$ns queue-limit $n1 $n2 10

$ns duplex-link-op $n0 $n1 orient right
$ns duplex-link-op $n1 $n2 orient right

$ns duplex-link-op $n1 $n2 queuePos 0.5

set tcp [new Agent/TCP]
$tcp set class_ 2
$ns attach-agent $n0 $tcp
set sink [new Agent/TCPSink]
$ns attach-agent $n2 $sink
$ns connect $tcp $sink
$tcp set fid_ 1

set ftp [new Application/FTP]
$ftp attach-agent $tcp
$ftp set type_ FTP

$ns at 0.1 "$ftp start" 
$ns at 2 "$ftp stop" 
$ns at 2.1 "finish"

$ns run