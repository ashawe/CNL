import java.io.BufferedInputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.net.*;
import java.util.Scanner;

/**
 * Server
 */
public class Server {

    static boolean end = false;

    public static void main(String[] args)
    {
        ServerSocket ss= null;
        Socket s= null;
        Scanner sc = new Scanner(System.in); 
        DataOutputStream dos = null;
        try{
            ss = new ServerSocket(1217);
            s = ss.accept();
            GetMesssage getMessage = new GetMesssage(new DataInputStream(new BufferedInputStream(s.getInputStream())));
            dos = new DataOutputStream(s.getOutputStream());
            String ip = "";
            getMessage.start();
            while(!ip.equals("sv_end_chat") && !end)
            {
                System.out.print("You:");
                ip = sc.nextLine();
                dos.writeUTF(ip);
            }
            end = true;
        }
        catch(Exception e)
        {
            System.out.println("Connection closed");
        }
        finally
        {
            try{
                sc.close();
                dos.close();
                s.close();
                ss.close();
            }
            catch(Exception e)
            {
                System.out.println("Conn closed");
            }
        }
    }
}

class GetMesssage extends Thread{
    DataInputStream ds;
    
    public GetMesssage(DataInputStream ds)
    {
        this.ds = ds;
    }

    public void run()
    {
        try{
            //System.out.print("Listening");
            String ip = "";
            while(!Server.end && !ip.equals("sv_end_chat"))
            {
                ip = ds.readUTF();
                System.out.println("Client: " + ip);       
            }
            System.out.println("Client closed connection");
            ds.close();
            Server.end = true;
            System.exit(1);
        }
        catch(Exception e)
        {
            // e.printStackTrace();
        }
    }
}