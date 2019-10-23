set ns [new Simulator]

$ns color 1 Blue
$ns color 2 Red

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
set n3 [$ns node]
set n4 [$ns node]

$ns duplex-link $n0 $n3 2Mb 10ms DropTail
$ns duplex-link $n1 $n3 2Mb 10ms DropTail

$ns duplex-link $n3 $n2 1Mb 10ms DropTail
$ns duplex-link $n3 $n4 1Mb 10ms DropTail

$ns queue-limit $n3 $n2 10
$ns queue-limit $n3 $n4 10

$ns duplex-link-op $n0 $n3 orient right-down
$ns duplex-link-op $n1 $n3 orient right-up

$ns duplex-link-op $n3 $n2 orient right-up
$ns duplex-link-op $n3 $n4 orient right-down

$ns duplex-link-op $n3 $n2 queuePos 0.5
$ns duplex-link-op $n3 $n4 queuePos 0.5

set tcp [new Agent/TCP]
$tcp set class_ 2
$ns attach-agent $n0 $tcp
set sink [new Agent/TCPSink]
$ns attach-agent $n2 $sink
$ns connect $tcp $sink
$tcp set fid_ 1

set tcp1 [new Agent/TCP]
$tcp1 set class_ 2
$ns attach-agent $n1 $tcp1
set sink1 [new Agent/TCPSink]
$ns attach-agent $n4 $sink1
$ns connect $tcp1 $sink1
$tcp1 set fid_ 2

set ftp [new Application/FTP]
$ftp attach-agent $tcp
$ftp set type_ FTP

set ftp1 [new Application/FTP]
$ftp1 attach-agent $tcp1
$ftp1 set type_ FTP


$ns at 0.1 "$ftp start" 
$ns at 2 "$ftp stop" 
$ns at 0.2 "$ftp1 start" 
$ns at 2 "$ftp1 stop" 
$ns at 2.1 "finish"

$ns run