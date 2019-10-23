# Youtube Videos
- [Basics of CPT](https://www.youtube.com/watch?v=QmL0AXymS5U)
- [RIP in CPT](https://www.youtube.com/watch?v=krM9GprN6qA)
- [OSPF in CPT](https://www.youtube.com/watch?v=B7-7RcZCIbM)
- [BGP in CPT part 1](https://www.youtube.com/watch?v=zbQsx-zcug4)
- [BGP in CPT part 2](https://www.youtube.com/watch?v=wdihCne_rP4)
- [BGP in CPT part 3](https://www.youtube.com/watch?v=oC8aGteHOPY)
- [BGP in CPT part 4](https://www.youtube.com/watch?v=Kg71q3hANQ8)

(optional)
- [Complex Network in CPT](https://www.youtube.com/watch?v=q-UUbPk6fYo)


# Commands for OSPF ( interior gateway protocol )

    router ospf 1
    network 192.168.1.0 0.0.0.255 area 0

# Commands for BGP ( exterior gateway protocol )

- machine 1

        router bgp 100
        network 70.0.0.0 mask 255.0.0.0
        network 20.0.0.0 mask 255.0.0.0
        neighbor 8.8.8.2 remote-as 200

- machine 2
    
        router bgp 200 // enters bgp configuration
        network 60.0.0.0 mask 255.0.0.0 //broadcast networks
        network 10.0.0.0 mask 255.0.0.0 
        neighbor 8.8.8.1 remote-as 100 // declare neighbor


### NOTE
    Declaring neighbors on both sides is imp

# Other basic commands
- shows which protocols are running

        sh ip protocols

- shows routers ip table
    
        sh ip route
    
- shows info about bgp & bgp routing table

        sh ip bgp

- shows bgp neighbor info
    
        sh ip bgp neighbors

- others

        conf t  // enters configuration mode

        sh ip run

        end // ends configuration mode

        exit
