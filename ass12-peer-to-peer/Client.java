import java.io.BufferedInputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.net.Socket;
import java.util.Scanner;


/**
 * Client
 */
public class Client {

    static boolean end = false;

    public static void main(String[] args)throws Exception
    {
        Scanner sc = new Scanner(System.in);
        Socket s = null;
        DataOutputStream os = null;
        try{
            s = new Socket("127.0.0.1",1217);
            GetMessage gMessage = new GetMessage(new DataInputStream(new BufferedInputStream(s.getInputStream())));
            os = new DataOutputStream(s.getOutputStream());
            gMessage.start();
            
            String ip = "";

            while(!ip.equals("sv_end_chat") && !end)
            {
                System.out.print("You:");
                ip = sc.nextLine();
                os.writeUTF(ip);
            }
            end = true;
        }
        catch(Exception e)
        {
            System.out.println("Connection closed");
        }
        try{
            sc.close();
            os.close();
            s.close();
        }
        catch( Exception e )
        {
            System.out.println("Connection closed");
        }
    }
}

class GetMessage extends Thread{

    DataInputStream ds;
    
    public GetMessage(DataInputStream ds)
    {
        this.ds = ds;
    }

    public void run()
    {
        try{
            //System.out.println("Listening");
            String ip = "";
            while(!Client.end && !ip.equals("sv_end_chat"))
            {
                ip = ds.readUTF();
                System.out.println("Server: " + ip);       
            }
            System.out.println("Server closed connection");
            ds.close();
            Client.end = true;
            System.exit(1);
        }
        catch(Exception e)
        {
            // e.printStackTrace();
        }
        
    }
}