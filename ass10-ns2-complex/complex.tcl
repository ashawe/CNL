set ns [new Simulator]

$ns color 1 Blue
$ns color 2 Red
$ns color 3 Green
$ns color 4 Black

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
$ns duplex-link $n1 $n3 1Mb 10ms DropTail
$ns duplex-link $n2 $n3 1Mb 10ms DropTail

$ns duplex-link $n3 $n4 4Mb 5ms DropTail

$ns queue-limit $n3 $n4 10

$ns duplex-link-op $n0 $n3 orient right-down
$ns duplex-link-op $n1 $n3 orient right
$ns duplex-link-op $n2 $n3 orient right-up

$ns duplex-link-op $n3 $n4 orient right

# $ns duplex-link-op $n0 $n3 queuePos 0.5
$ns duplex-link-op $n3 $n4 color Red
$ns duplex-link-op $n3 $n4 queuePos 0.5


# TCP NODE 1
set tcp [new Agent/TCP]
$tcp set class_ 2
$ns attach-agent $n0 $tcp
$tcp set fid_ 1

set ftp [new Application/FTP]
$ftp attach-agent $tcp

# TCP NODE 2
set tcp1 [new Agent/TCP]
$tcp1 set class_ 2
$ns attach-agent $n1 $tcp1
$tcp1 set fid_ 2

set ftp1 [new Application/FTP]
$ftp1 attach-agent $tcp1

# TCP NODE 3
set tcp2 [new Agent/TCP]
$tcp2 set class_ 2
$ns attach-agent $n2 $tcp2
$tcp2 set fid_ 3

set ftp2 [new Application/FTP]
$ftp2 attach-agent $tcp2

# TCP SINK
set sink [new Agent/TCPSink]
$ns attach-agent $n4 $sink

set sink1 [new Agent/TCPSink]
$ns attach-agent $n4 $sink1

set sink2 [new Agent/TCPSink]
$ns attach-agent $n4 $sink2

$ns connect $tcp $sink
$ns connect $tcp1 $sink1
$ns connect $tcp2 $sink2


set udp [new Agent/UDP]
$ns attach-agent $n0 $udp
set null [new Agent/Null]
$ns attach-agent $n4 $null
$ns connect $udp $null
$udp set fid_ 4

set cbr [new Application/Traffic/CBR]
$cbr attach-agent $udp
$cbr set type_ CBR
$cbr set packet_size_ 500
$cbr set rate_ 1mb
$cbr set random_ false

$ns at 0.1 "$ftp start"
$ns at 0.15 "$ftp1 start"
$ns at 0.2 "$ftp2 start"
$ns at 0.2 "$cbr start"

$ns at 2.0 "$ftp stop"
$ns at 2.0 "$ftp1 stop"
$ns at 2.0 "$ftp2 stop"
$ns at 2.0 "$cbr stop"

$ns at 5.0 "finish"

$ns run