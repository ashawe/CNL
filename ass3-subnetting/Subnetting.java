import java.util.*;
import java.lang.Math;

public class Subnetting
{
    // 8+8+8+x
    // powerNumber = 2^x
    int powerNumber;

    private int getPowerNumber()
    {
        return powerNumber;
    }

    private void setPowerNumberFromNoOfSubnets( int nSubnets )
    {
        while( 256%nSubnets != 0 )
        {
            nSubnets++;
        }
        // powerNumber = (int)Math.pow(2,nSubnets);
        powerNumber = 256/nSubnets;
    }

    private void setPowerNumberFromCIDR( int cidr )
    {
        // finding 8 + 8 + ? + ?
        int mod = cidr%8;
        powerNumber = (int)Math.pow(2,8-mod);
    }

    private int getNumberOfSubnets()
    {
        return (256/powerNumber);
    }


    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);
        String ip,subnetMask = "255.255.";
        int choice,cidr,nSubnets;
        boolean isSupernetting = false;
        Subnetting subnetting = new Subnetting(); // created object because main() is static. Either do this or create another class especially for main()
        
        System.out.println("Enter Ip Address");
        ip = sc.next();
        String[] test = ip.split("\\.",5);
        for ( String str : test )
        {
            int x = Integer.valueOf(str);
            if( x < 0 || x > 255 )
            {
                System.out.println("Invalid IP");
                System.exit(1);
            }
        }

        System.out.println("1. Enter CIDR ( ex. 26 )");
        System.out.println("2. Enter number of subnets ( ex. 4 )");
        choice = sc.nextInt();

        if( choice!=1 && choice !=2)
        {
            System.out.println("Invalid Input");
            sc.close();
            System.exit(1);
        }
        
        
        if( choice == 1 )
        {
            cidr = sc.nextInt();
            if( cidr < 16 || cidr > 31)
            {
                System.out.println("CIDR Does not fit into subnetting or supernetting");
                System.exit(1);
            }
            // finding if supernetting or subnetting
            if( Integer.valueOf(cidr / 8) < 3 )
                isSupernetting = true;

            subnetting.setPowerNumberFromCIDR(cidr);
        }
        else if ( choice == 2 )
        {
            nSubnets = sc.nextInt();
            subnetting.setPowerNumberFromNoOfSubnets(nSubnets);
        }


        int host = 256 - subnetting.getPowerNumber();
        
        if( isSupernetting )
            subnetMask += host + ".0";
        else
            subnetMask += "255." + host;
        System.out.println(subnetMask);

        if(!isSupernetting)
            System.out.println("Number of subnets formed: " + subnetting.getNumberOfSubnets());
        else
            System.out.println("Number of supernets formed: " + subnetting.getNumberOfSubnets());

        // removing last element from 
        ArrayList<String> test2 = new ArrayList<>(Arrays.asList(test));
        int lastIpBits;
        if( isSupernetting )
        {    
            test2.remove(2);
            test2.remove(2);
            lastIpBits = Integer.valueOf(test[2]);
        }
        else
        {
            test2.remove(3);
            lastIpBits = Integer.valueOf(test[3]);
        }
        
        // converting array back to string
        // half ip will be first 3 ip bits e.g. 192.168.13. ( for printing range )
        String halfIp = "";
        for( String str : test2 )
        {
            halfIp = halfIp + str + ".";
        }

        // finding range
        int pow = subnetting.getPowerNumber();
        int maxLimit = pow;
        int minLimit = 0;
        while( 256 >= maxLimit )
        {
            if( !isSupernetting )
                System.out.print( halfIp + minLimit + " to " + halfIp + (maxLimit-1) );
            else
                System.out.print( halfIp + minLimit + ".0" + " to " + halfIp + (maxLimit-1) + ".0");

            if( minLimit < lastIpBits && maxLimit > lastIpBits )
                System.out.print(" <- ip belongs to this range\n");
            else
                System.out.println();
            minLimit = maxLimit;
            maxLimit += pow;
        }

        sc.close();
    }
}